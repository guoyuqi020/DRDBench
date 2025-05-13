## DRDBench

DRDBench is a benchmark designed to evaluate the capabilities of Large Language Models (LLMs) in detecting data races in pthread-based programs.

The benchmark consists of 226 programs and 555 annotated data races. Each data race is documented with precise locations, including the variable name and line numbers.

## Dataset Usage
To use the benchmark, invoke the `SVBench()` method defined in the `SVBench.py` script.

`SVBench()` returns the dataset as a Python list. Each element of the list corresponds to a program, represented as a Python dictionary with the following sections:

```json
{
    "label": 1,
    "code": "the code of the program",
    "filename": "the filename of the program",
    "race_label": "race location annotations"
}
```

The `race_label` section is a list of data races. Each item in the list represents a data race, where:
- `shared_variable` denotes the name of the shared variable involved.
- `lineA` and `lineB` denote the line numbers of the two conflicting accesses.

Here’s an example:

```json
{
    "race_label":[
        {"shared_variable": "v", "lineA": 24, "lineB": 29},
        {"shared_variable": "v", "lineA": 24, "lineB": 30}
    ]
}
```

## Evaluation Usage
To evaluate LLMs on DRDBench, we provide the following templates:
- `Qwen2.5-Coder-Instruct-32B.py`: used for multi-sampling evaluation of an LLM.
- `Qwen2.5-Coder-Instruct-32B_greedy.py`: used for single-sampling (greedy decoding) evaluation of the same model.

To evaluate an LLM, please follow these steps:
1. Modify `LLMconfig_template.ini` and fill in the `api_key` and
`base_url` sections with those obtained from your LLM provider.
2. Rename the file `LLMconfig_template.ini` to `LLMconfig.ini`.
3. Delete any folders named `baseline_qwen2.5-coder-instruct-32B` or `baseline_qwen2.5-coder-instruct-32B_greedy`. These folders store the history of previous evaluation results. Removing them ensures that results are fresh when evaluating a new LLM.
4. Run the scripts. The evaluation results will be displayed in the terminal.

## License
For the programs within SV-Benchmarks, please refer to the licenses included with each code file in the `sv-benchmarks` folder for detailed licensing information.

The race annotations and the evaluation code of DRDBench are licensed under the Apache-2.0 license.



