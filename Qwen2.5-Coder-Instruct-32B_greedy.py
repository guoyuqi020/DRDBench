# %%
from typing import Dict, List
from SVBench import (
    getSVBench,
    isLocationCorrect,
)
from openai import OpenAI
import configparser
import json
import pickle
import os
import tqdm
from concurrent.futures import ThreadPoolExecutor
import random
import string
import multiprocessing
import copy
from numpy import inf
import traceback
from openai import InternalServerError
import sys
import numpy as np

os.environ["HF_ENDPOINT"] = "hf-mirror.com"
import evaluate
import time
import datetime


# %%
class LLMRaceDetector:
    def __init__(
        self, LLM, config_path="LLMconfig.ini", num_workers=4, peek=False
    ) -> None:
        self.prompts = {
            "detection": """
You are an expert at concurrent program design and data race detection. In the following, you will be given a program. You'll need to carefully look over the program to check whether it contains data race bugs. If it contains data race bugs, please locate them in line number pairs.\n\nThe data race bug is a bug that occurs when (1) two or more threads access a shared variable at the same time, and (2) at least one of the accesses is a write. Note that, two operations **cannot** execute at the same time when (1) both are atomical operations, (2) both are protected by the same mutex, (3) they are guarded by a semaphare which ensures the exclusive access of the shared variable, or (4) other mechanism that forbids the two operations to execute at the same time. \n\nThe program can use `__VERIFIER_atomic_begin()` and `__VERIFIER_atomic_end()` to mark the start and the end of an atomic zone. Besides, if the function name has the `__VERIFIER_atomic` prefix, the corresponding function should also be regarded as an atomic zone. All operations inside the atomic zone should be regarded as atomic.\n\nThe program can use `pthread_mutex_lock(&m)` and `pthread_mutex_unlock(&m)` to lock and unlock a mutex `m`. \n\nThe program can use `sem_wait()` and `sem_post()` to control semaphores; they do not lock or unlock mutexes. A semaphore holds an integer value. The `sem_wait()` is used to decrease the semaphore's value (typically by 1) to signal that the program wants to enter a critical section or use a resource. If the semaphore's value is greater than 0, `sem_wait()` decrements it and then proceeds. If the semaphore's value is 0, `sem_wait()` is blocked until the semaphore's value becomes greater than 0. The `sem_post` is used to increment the semaphore's value (typically by 1), indicating that a resource has been released.\n\nThe program can use `pthread_create()` to create a new thread and use `pthread_join()` to join the created thread. All the operations inside the new thread should happen after the `pthread_create()` site and before the `pthread_join()` site. \n\nThe program can use `pthread_cond_wait()` and `pthread_cond_signal()` to wait and signal a condition variable. It can also use `pthread_barrier_wait()` to wait for a barrier.\n\nThe program also uses `assume_abort_if_not()` as `assert()`. It can use `__VERIFIER_nondet_int()` to get a random integer. Besides, the indices of the lines are provided at the beginning of each line, e.g., "1:", to help locate the line numbers.\n\nYou can follow the following steps to detect the data race bugs:\n1. Read the program carefully and understand how the threads are created and joined.\n2. Check the shared variables and their accesses.\n3. Check the synchronization mechanisms (atomic zones, mutexes, semaphores, condition variables, etc.) and their usage.\n4. For each pair of accesses to the same shared variable, check whether they can constitute a data race.\n\nAfter thoroughly checking all potential data race bugs, please output the all the confirmed data races. If no data race is found, please answer an empty list. Please answer in the following JSON format (each race as one dict):\n\n```json\n{\n"races": [{"shared_variable": "the name of the same shared variable", "lineA": the line number of the first access in `int` format, "lineB": the line number of the second access in `int` format}, ...]\n}\n```
            """
        }
        self.LLM = LLM
        self.config = configparser.ConfigParser()
        self.config.read(config_path)
        self.client = OpenAI(
            api_key=self.config.get(self.LLM, "api_key"),
            base_url=self.config.get(self.LLM, "base_url"),
        )

        self.token_usage = [0, 0, 0, 0]  # (cached, missed, completion, query)
        self.num_workers = num_workers
        self.pool = ThreadPoolExecutor(self.num_workers)
        self.cached_msgs = set()
        self.request_count = [0, 0]
        self.peek = peek

    def removeJsonPrefixandSuffix(self, jsonstr):
        if "```json" in jsonstr and "```" in jsonstr[jsonstr.find("```json") + 7 :]:
            return jsonstr[
                jsonstr.find("```json")
                + 7 : jsonstr.find("```json")
                + 7
                + jsonstr[jsonstr.find("```json") + 7 :].find("```")
            ]
        return jsonstr

    def getResponse(
        self,
        system_prompt,
        user_input,
        samples,
        cache,
        debug=False,
        overwrite=False,
    ):
        msg = [
            {
                "role": "system",
                "content": system_prompt,
            },
            {"role": "user", "content": user_input},
        ]
        if str(msg) not in cache or overwrite is True:
            cache[str(msg)] = []
        tries = 0
        max_tries = 3 * (samples - len(cache[str(msg)]))
        while len(cache[str(msg)]) < samples and tries <= max_tries:
            # print("Round 1 ...")
            # print(system_prompt)
            tries += samples - len(cache[str(msg)])
            round1_features = [
                self.pool.submit(
                    self.client.chat.completions.create,
                    **{
                        **{
                            "model": self.LLM,
                            "messages": msg,
                            "stream": False,
                            "seed": len(cache[str(msg)]) + seed,
                            "timeout": 1200,
                            "temperature": 0.01,
                            "top_p": 0.01,
                            "top_k": 1,
                        },
                    },
                )
                for seed in range(samples - len(cache[str(msg)]))
            ]
            self.request_count[0] += samples - len(cache[str(msg)])
            for item in round1_features:
                try:
                    response = item.result()
                except InternalServerError:
                    continue
                except Exception as e:
                    print(e)
                    raise e
                if response.choices is None:
                    continue
                self.request_count[1] += 1
                cache[str(msg)].append(response)
            if len(cache[str(msg)]) < samples:
                time.sleep(5)
        return (msg, cache[str(msg)][:samples])

    def printUsage(self):
        print(
            "Usage: {:.5f} {} wasted. {} prompt, {} completion, {} queries".format(
                (
                    int(self.token_usage[0])
                    * float(self.config.get(self.LLM, "cached"))
                    + int(self.token_usage[1])
                    * float(self.config.get(self.LLM, "missed"))
                    + int(self.token_usage[2])
                    * float(self.config.get(self.LLM, "output"))
                )
                / 1000000
                + int(self.token_usage[3]) * float(self.config.get(self.LLM, "fixed")),
                self.config.get(self.LLM, "currency"),
                self.token_usage[1],
                self.token_usage[2],
                self.token_usage[3],
            )
        )

    def dumpCache(self, history_cache, cache):
        if history_cache is not None and not self.peek:
            if not os.path.exists(os.path.dirname(history_cache)):
                os.makedirs(os.path.dirname(history_cache))
            with open(history_cache, "wb") as f:
                pickle.dump(cache, f)

    def baseline(self, case, samples, history_cache=None):
        if history_cache is not None and os.path.exists(history_cache):
            with open(history_cache, "rb") as f:
                cache = pickle.load(f)
        else:
            cache = {}
        result = []
        token_usage = []
        have_sampled = 0
        need_sample = samples
        last_sampled = 0
        while need_sample > 0 and have_sampled <= 10 * samples:
            have_sampled += need_sample
            _, response = self.getResponse(
                self.prompts["detection"],
                self.addLinePrefix(case["code"]),
                have_sampled,
                cache,
            )
            self.dumpCache(history_cache, cache)
            for item in response[last_sampled:]:
                try:
                    json_response = json.loads(
                        self.removeJsonPrefixandSuffix(item.choices[0].message.content)
                    )
                    vaild_flag = True
                    if not isinstance(json_response["races"], list):
                        vaild_flag = False
                    if vaild_flag:

                        for idx, json_item in enumerate(json_response["races"]):
                            if not isinstance(json_item, dict):
                                vaild_flag = False
                                break
                            json_response["races"][idx]["shared_variable"] = str(
                                json_item["shared_variable"]
                            )
                            json_response["races"][idx]["lineA"] = int(
                                json_item["lineA"]
                            )
                            json_response["races"][idx]["slineB"] = int(
                                json_item["lineB"]
                            )

                    if vaild_flag:
                        result.append(json_response)
                        token_usage.append(
                            [
                                0,
                                int(item.usage.prompt_tokens),
                                int(item.usage.completion_tokens),
                                1,
                            ]
                        )
                        need_sample -= 1
                except:
                    pass
            last_sampled = len(response)
        if have_sampled > 50:
            print(
                "[{}] {} failed after 50 samples".format(
                    datetime.datetime.now(), case["filename"]
                )
            )
        else:
            print(
                "[{}] {} finished successfully. {} requests were sent, {}({}) succeeded.".format(
                    datetime.datetime.now(),
                    case["filename"],
                    self.request_count[0],
                    self.request_count[1],
                    float(self.request_count[1])
                    / max(float(self.request_count[0]), 1.0),
                )
            )
        sys.stdout.flush()
        return result[:samples], token_usage

    def addLinePrefix(self, code):
        result = []
        line_code = code.split("\n")
        for idx, line in enumerate(line_code):
            result.append("{}: {}".format(idx + 1, line))
        return "\n".join(result)


# %%
# %%


def worker(worker_item, output_dir, samples):
    detector = LLMRaceDetector("Qwen2.5-Coder-Instruct", num_workers=2)
    casename = os.path.splitext(worker_item["filename"])[0]
    save_path = os.path.join(output_dir, casename)
    tries = 0
    while True:
        try:
            tries += 1
            result, token_usage = detector.baseline(
                worker_item,
                samples,
                history_cache=os.path.join(save_path, "history.pkl"),
            )
            break
        except KeyboardInterrupt as e:
            raise e
        except Exception as e:
            print("Exception: {}".format(worker_item["filename"]))
            traceback.print_exc()
            sys.stdout.flush()
            return (
                {"ERROR": []},
                token_usage,
                worker_item,
            )
    if not os.path.exists(save_path):
        os.makedirs(save_path)
    with open(os.path.join(save_path, "result.pkl"), mode="wb") as f:
        pickle.dump(result, f)

    return result, token_usage, worker_item


def getPredsandLabels(result, case):
    labels = []
    predictions = []
    ground_label_hit = set()
    prediction_label_hit = set()
    if case["race_label"] is not None or len(result["races"]) > 0:
        if case["race_label"] is not None:
            for ground_label in case["race_label"]:
                for prediction_label in result["races"]:
                    try:
                        if isLocationCorrect(ground_label, prediction_label):
                            ground_label_hit.add(str(ground_label))
                            prediction_label_hit.add(str(prediction_label))
                    except:
                        print(
                            "ERROR: {} {} {}".format(
                                ground_label,
                                prediction_label,
                                type(prediction_label),
                            )
                        )
        labels += [1] * len(ground_label_hit)
        predictions += [1] * len(ground_label_hit)
        if case["race_label"] is not None:
            labels += [1] * (len(case["race_label"]) - len(ground_label_hit))
            predictions += [0] * (len(case["race_label"]) - len(ground_label_hit))
        labels += [0] * (len(result["races"]) - len(prediction_label_hit))
        predictions += [1] * (len(result["races"]) - len(prediction_label_hit))
    return predictions, labels


def getModelData(model, dataset, max_samples=np.inf):
    passK_summary = 0
    union_labels_summary = []
    union_predictions_summary = []
    intersection_labels_summary = []
    intersection_predictions_summary = []
    majority_labels_summary = []
    majority_predictions_summary = []
    l2_labels_summary = []
    l2_predictions_summary = []
    detected_races_maj = set()
    detected_races_int = set()
    detected_races_uni = set()
    for case in dataset:
        casename = os.path.splitext(case["filename"])[0]
        with open(f"baseline_{model}/{casename}/result.pkl", "rb") as f:
            res = pickle.load(f)
        voting_count = dict()
        passK = False
        for res_idx, result in enumerate(res):
            if res_idx >= max_samples:
                break
            single_sample_set = set()
            if len(l2_labels_summary) <= res_idx:
                l2_labels_summary.append([])
                l2_predictions_summary.append([])
            l2_predictions, l2_labels = getPredsandLabels(result, case)
            if l2_predictions == l2_labels:
                passK = True
            l2_labels_summary[res_idx] += l2_labels
            l2_predictions_summary[res_idx] += l2_predictions
            for item in result["races"]:
                str_race = json.dumps(
                    {
                        "lineA": min(int(item["lineA"]), int(item["lineB"])),
                        "lineB": max(int(item["lineA"]), int(item["lineB"])),
                    }
                )
                if str_race not in single_sample_set:
                    single_sample_set.add(str_race)
                else:
                    continue
                if str_race not in voting_count:
                    voting_count[str_race] = 0
                voting_count[str_race] += 1
        if passK is True:
            passK_summary += 1
        race_union = {"races": list(map(lambda x: json.loads(x), voting_count.keys()))}
        predictions, labels = getPredsandLabels(race_union, case)
        union_labels_summary += labels
        union_predictions_summary += predictions

        race_intersection = {
            "races": list(
                map(
                    lambda x: json.loads(x),
                    filter(
                        lambda x: voting_count[x] == min(len(res), max_samples),
                        voting_count.keys(),
                    ),
                )
            )
        }
        predictions, labels = getPredsandLabels(race_intersection, case)
        intersection_labels_summary += labels
        intersection_predictions_summary += predictions
        race_majority = {
            "races": list(
                map(
                    lambda x: json.loads(x),
                    filter(
                        lambda x: voting_count[x]
                        > float(min(len(res), max_samples)) / 2,
                        voting_count.keys(),
                    ),
                )
            )
        }
        predictions, labels = getPredsandLabels(race_majority, case)
        majority_labels_summary += labels
        majority_predictions_summary += predictions
        for race in race_majority["races"]:
            detected_races_maj.add(
                json.dumps([case["filename"], race["lineA"], race["lineB"]])
            )
        for race in race_intersection["races"]:
            detected_races_int.add(
                json.dumps([case["filename"], race["lineA"], race["lineB"]])
            )
        for race in race_union["races"]:
            detected_races_uni.add(
                json.dumps([case["filename"], race["lineA"], race["lineB"]])
            )
    union_eval = metric.compute(
        predictions=union_predictions_summary, references=union_labels_summary
    )
    intersection_eval = metric.compute(
        predictions=intersection_predictions_summary,
        references=intersection_labels_summary,
    )
    majority_eval = metric.compute(
        predictions=majority_predictions_summary, references=majority_labels_summary
    )
    l2_eval = []
    for idx in range(len(l2_predictions_summary)):
        l2_eval.append(
            metric.compute(
                predictions=l2_predictions_summary[idx],
                references=l2_labels_summary[idx],
            )
        )
    l2_summary = dict()
    for key in ["recall", "precision", "f1"]:
        l2_summary[key] = sorted([l2_eval[i][key] for i in range(len(l2_eval))])

    return (
        float(passK_summary) / len(dataset),
        union_eval,
        intersection_eval,
        majority_eval,
        l2_summary,
        detected_races_maj,
        detected_races_int,
        detected_races_uni,
    )


if __name__ == "__main__":
    SAMPLES = 1
    pool = multiprocessing.Pool(8)
    OUTPUT_DIR = "./baseline_qwen2.5-coder-instruct-32B_greedy"
    dataset = getSVBench()
    dataset = list(filter(lambda x: x["label"] == 1, dataset))
    l1_predictions = [[] for i in range(SAMPLES)]
    l2_predictions_summary = [[] for i in range(SAMPLES)]
    metric = evaluate.combine(["accuracy", "recall", "precision", "f1"])
    metric2 = evaluate.combine(["recall", "precision"])
    l1_labels = [[] for i in range(SAMPLES)]
    l2_labels_summary = [[] for i in range(SAMPLES)]
    futures = [
        pool.apply_async(
            worker,
            (pool_item, OUTPUT_DIR, SAMPLES),
        )
        for pool_item in dataset
    ]
    summary_usage = [[0, 0, 0, 0] for i in range(SAMPLES)]
    for idx, item in enumerate(tqdm.tqdm(futures, "Detecting races")):
        res, usage, case = item.get()
        casename = os.path.splitext(case["filename"])[0]
        save_path = os.path.join(OUTPUT_DIR, casename)
        for res_idx in range(SAMPLES):
            if len(res) < res_idx + 1:
                print(res)
            result = res[res_idx]
            for i in range(4):
                summary_usage[res_idx][i] += usage[res_idx][i]
            if isinstance(result, dict) and "races" in result:
                l1_predictions[res_idx].append(1 if len(result["races"]) > 0 else 0)
            else:
                l1_predictions[res_idx].append(1 - case["label"])
            l1_labels[res_idx].append(case["label"])
            if case["race_label"] is not None or len(result["races"]) > 0:
                ground_label_hit = set()
                prediction_label_hit = set()
                l2_labels = []
                l2_predictions = []
                if case["race_label"] is not None:
                    for ground_label in case["race_label"]:
                        for prediction_label in result["races"]:
                            try:
                                if isLocationCorrect(ground_label, prediction_label):
                                    ground_label_hit.add(str(ground_label))
                                    prediction_label_hit.add(str(prediction_label))
                            except:
                                print(
                                    "ERROR: {} {} {}".format(
                                        ground_label,
                                        prediction_label,
                                        type(prediction_label),
                                    )
                                )
                l2_labels += [1] * len(ground_label_hit)
                l2_predictions += [1] * len(ground_label_hit)
                if case["race_label"] is not None:
                    l2_labels += [1] * (len(case["race_label"]) - len(ground_label_hit))
                    l2_predictions += [0] * (
                        len(case["race_label"]) - len(ground_label_hit)
                    )
                l2_labels += [0] * (len(result["races"]) - len(prediction_label_hit))
                l2_predictions += [1] * (
                    len(result["races"]) - len(prediction_label_hit)
                )
                l2_labels_summary[res_idx] += l2_labels
                l2_predictions_summary[res_idx] += l2_predictions
    pool.terminate()
    for res_idx in range(SAMPLES):
        print("Result of sample {}:".format(res_idx))
        eval = metric.compute(
            predictions=l1_predictions[res_idx], references=l1_labels[res_idx]
        )
        print("L1 statistics: " + str(eval))
        eval2 = metric2.compute(
            predictions=l2_predictions_summary[res_idx],
            references=l2_labels_summary[res_idx],
        )
        print("L2 statistics (all): {}".format(eval2))
        summary_detector = LLMRaceDetector("Qwen2.5-Coder-Instruct")
        summary_detector.token_usage = summary_usage[res_idx]
        summary_detector.printUsage()
    (
        passKRate,
        union_eval,
        intersection_eval,
        majority_eval,
        l2_summary,
        detected_races_maj,
        detected_races_int,
        detected_races_uni,
    ) = getModelData("qwen2.5-coder-instruct-32B_greedy", dataset, SAMPLES)
    print("PassK rate: {}".format(passKRate))
    print("Majority statistics: " + str(majority_eval))
    print("Intersection statistics: " + str(intersection_eval))
    print("Union statistics: " + str(union_eval))

# %%
