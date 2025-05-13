# %%
import os
import glob
import yaml
from subprocess import check_output
import random
import string
import transformers
import pickle
import json
import subprocess
import numpy as np

PROPERTY_SET = "NoDataRace-Main"
PROPERTY_FILE = "../properties/no-data-race.prp"

# %%


# %%
def getRandomStr(length):
    letters = string.ascii_letters
    random_string = "".join(random.choice(letters) for _ in range(length))
    return random_string


def formatter(code):
    tmpfile = getRandomStr(6) + ".c"
    with open(tmpfile, "w") as f:
        f.write(code)
    process = check_output(["clang-format", "--style=microsoft", tmpfile], shell=False)
    os.remove(tmpfile)
    return process.decode()


def strip_comments(source_code):
    process = check_output(
        ["cpp", "-fpreprocessed", "-dD", "-E", "-P", source_code], shell=False
    )
    return formatter(
        "\n".join(
            list(
                filter(
                    lambda item: not item == "",
                    process.decode().split("\n"),
                )
            )
        )
    )


def getDataset(
    ds_path,
    tokenizer_path,
    max_tokens,
    sub_category=None,
):
    TP_count = 0
    TN_count = 0
    races = 0
    raw_data = []
    if sub_category is None:
        sub_category = [
            "goblint-regression",
            "ldv-races",
            "pthread-atomic",
            "pthread-C-DAC",
            "pthread-deagle",
            "pthread-divine",
            "pthread-ext",
            "pthread-lit",
            "pthread-nondet",
            "pthread-race-challenges",
            "pthread-wmm",
            "pthread",
            "weaver",
            "pthread-complex",
            "pthread-driver-races",
        ]

    tokenizer = transformers.AutoTokenizer.from_pretrained(
        tokenizer_path, trust_remote_code=True
    )
    if os.path.exists("{}/c/{}.set".format(ds_path, PROPERTY_SET)):
        with open("{}/c/{}.set".format(ds_path, PROPERTY_SET), mode="r") as f:
            lines = list(
                filter(
                    lambda line: False if line.startswith("#") else True, f.readlines()
                )
            )
            lines = list(map(lambda line: line.strip(), lines))
        for line in lines:
            if sub_category is not None and not os.path.dirname(line) in sub_category:
                continue
            for case in glob.glob("{}/c/{}".format(ds_path, line)):
                c_file_path = os.path.splitext(case)[0] + ".c"
                if not os.path.exists(c_file_path):
                    continue
                with open(case) as f:
                    yml_data = yaml.safe_load(f)
                if "properties" in yml_data:
                    ground_truth = None
                    for p in yml_data["properties"]:
                        if (
                            "property_file" in p
                            and "expected_verdict" in p
                            and p["property_file"] == "../properties/no-data-race.prp"
                        ):
                            ground_truth = not p["expected_verdict"]
                            break
                if ground_truth is not None:
                    code = strip_comments(c_file_path)
                    if "int main(" not in code:
                        # print("WARNING: {} has no main() function!".format(c_file_path))
                        continue
                    result = tokenizer.encode(code)
                    if len(result) > max_tokens:
                        print(f"Too long! {c_file_path}")
                        continue
                    race_label = None
                    race_label_path = os.path.splitext(case)[0] + ".pkl"
                    if os.path.exists(race_label_path):
                        with open(race_label_path, "rb") as race_f:
                            meta_pkl = pickle.load(race_f)
                            race_label = meta_pkl["race_label"]
                            races += len(race_label)
                        raw_data.append(
                            {
                                "label": 1 if ground_truth else 0,
                                "code": code,
                                "filename": c_file_path,
                                "race_label": race_label,
                            }
                        )
                    else:
                        if ground_truth == 1:
                            print(f"WARNING: {race_label_path} does not exist!")
                        raw_data.append(
                            {
                                "label": 1 if ground_truth else 0,
                                "code": code,
                                "filename": c_file_path,
                                "race_label": None,
                            }
                        )

                    if ground_truth:
                        TP_count += 1
                    else:
                        TN_count += 1

        return raw_data, TP_count, TN_count, races


def getSVBenchDataset(sub_category=None, max_tokens=np.inf):
    raw_data, TP_count, TN_count, races = getDataset(
        "sv-benchmarks",
        "deepseek_v3_tokenizer",
        max_tokens=max_tokens,
        sub_category=sub_category,
    )
    print("TP: {} TN: {} races: {}".format(TP_count, TN_count, races))
    return raw_data


# %%


def dataset_transform(item):
    return {
        "label": item["label"],
        "code": item["code"],
        "filename": item["filename"],
        "race_label": item["race_label"] if "race_label" in item else None,
    }


def getSVBench(sub_category=None, max_tokens=np.inf):
    dataset = getSVBenchDataset(sub_category=sub_category, max_tokens=max_tokens)
    transformed = list(map(dataset_transform, dataset))
    return list(filter(lambda x: x["label"] == 1, transformed))


def isLocationCorrect(label, prediction):
    if type(prediction) is str:
        prediction = json.loads(prediction.replace("'", '"'))
    label_lineA = label["lineA"]
    label_lineB = label["lineB"]
    prediction_lineA = int(prediction["lineA"])
    prediction_lineB = int(prediction["lineB"])
    if (
        type(label_lineA) is int
        and type(label_lineB) is int
        and label_lineA == prediction_lineA
        and label_lineB == prediction_lineB
    ):
        return True
    if (
        type(label_lineA) is int
        and type(label_lineB) is int
        and label_lineB == prediction_lineA
        and label_lineA == prediction_lineB
    ):
        return True
    if (
        type(label_lineA) is list
        and type(label_lineB) is list
        and prediction_lineA in label_lineA
        and prediction_lineB in label_lineB
    ):
        return True
    if (
        type(label_lineA) is list
        and type(label_lineB) is list
        and prediction_lineB in label_lineA
        and prediction_lineA in label_lineB
    ):
        return True

    return False


# %%
if __name__ == "__main__":
    ds = getSVBench()

# %%
