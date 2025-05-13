<!--
This file is part of the SV-Benchmarks collection of verification tasks:
https://gitlab.com/sosy-lab/benchmarking/sv-benchmarks

SPDX-FileCopyrightText: 2023 University of Tartu

SPDX-License-Identifier: MIT
-->

# Race Detection Challenges

This suite contains extracted kernels of programs aimed to demonstrate the most important challenges to solve in order to be able to achieve good results on real-world programs.
It mostly consists of variations of thread pools appearing in real-world programs.
Race-free tasks are accompanied by racy task variants, if possible, to capture the intricate correctness conditions of such implementations.
Most tasks use **unbounded number of threads**, which is common in real-world programs.

Although these tasks are inspired **concurrency idioms in real-world programs**, all of their code is written from scratch, without borrowing code from the original programs.
They capture idioms which are not unique to a given project.

These tasks originate from the **Goblint benchmark suite**: https://github.com/goblint/bench/tree/de5f004261fc2199de4f319b2fe5929182b8720b/concrat/race-challenges.
A longer textual overview is in its [`README`](https://github.com/goblint/bench/blob/de5f004261fc2199de4f319b2fe5929182b8720b/concrat/race-challenges/README.md).
