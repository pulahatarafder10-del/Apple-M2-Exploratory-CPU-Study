# Apple M2 C++ Neural-Network Inference Study

**Inference Latency and Data Storage of Neural Networks with C++ on Apple M2**

**Vistula University · Architecture of Computers · 2026/27**

**Authors:** Pulaha Tarafder (80489) and Saket Ghosh (80564)

> **Scope:** A documented **exploratory experiment**, not a validated general comparison of processor performance or neural-network prediction accuracy. All 30 timing observations came from **one session**, with float32 always preceding float64.

## Research question

How do hidden-layer width and floating-point precision affect measured CPU inference latency and parameter storage in a small, untrained feed-forward neural network on an Apple M2 MacBook with 16 GB unified memory?

**Experimental design:** C++17 compiled with `clang++ -O3 -std=c++17`; 64 inputs, one ReLU hidden layer (32, 128 or 512 units), eight linear outputs; 500 warm-up passes and five consecutive timed blocks of 10,000 passes for each of six configurations.

## Recorded results

Mean ± sample standard deviation in microseconds per inference (five blocks each).

| Hidden units | Float32 latency (µs) | Float64 latency (µs) | Float32 parameter KiB | Float64 parameter KiB |
|---:|---:|---:|---:|---:|
| 32 | 3.076 ± 1.492 | 3.387 ± 1.021 | 9.16 | 18.31 |
| 128 | 12.540 ± 0.992 | 12.201 ± 1.050 | 36.53 | 73.06 |
| 512 | 52.852 ± 2.720 | 63.794 ± 0.830 | 146.03 | 292.06 |

At **512 hidden neurons**, float32 had **17.2% lower mean latency** than float64 in this session. The observed ranges did not overlap, but order, scheduling, and thermal effects were uncontrolled. No clear precision effect was established for the two smaller configurations.

## Repository contents

- [Original C++ benchmark](src/original_apple_m2_benchmark.cpp)
- [Original 30 measurements (CSV)](data/results.csv)
- [Derived summary table (CSV)](data/analysis_summary.csv)
- [C++ verification program](src/verify_results.cpp)
- [Methods, limitations and verification scope](docs/METHODS_LIMITATIONS.md)
- [Author contributions](docs/AUTHOR_CONTRIBUTIONS.md)
- [GitHub Actions validation](.github/workflows/validate.yml)

**Formatted PDF and chart files:** the online research data and code are published. The authors' latest formatted PDF and two figure PNGs still need to be uploaded to the `paper/` and `figures/` directories via GitHub's **Add file → Upload files** control. Do not claim those files are online until they appear in this repository. The separately distributed PDF includes a clickable repository evidence link and an embedded offline evidence archive.

## Validate the recorded data

```bash
clang++ -O2 -std=c++17 src/verify_results.cpp -o verify_results
./verify_results data/results.csv
```

This checks CSV structure, group sizes, and descriptive summaries; it does **not** establish that the experiment was free of confounders.

## Re-run the benchmark

```bash
clang++ -O3 -std=c++17 src/original_apple_m2_benchmark.cpp -o ai_benchmark
mkdir -p new_trial
cd new_trial
../ai_benchmark 10000 5
```

Run a new trial in a separate directory so the archived `data/results.csv` is not overwritten. New timings can differ.

## Limits and transparency

Only one Apple M2 machine, one compilation setting and one session were tested. Float32 always ran before float64; cache behavior, temperature, energy, prediction accuracy and total RAM use were not measured. The generated weights were based on float values for both precision variants. The results are **descriptive** rather than proof of a general causal precision advantage. ChatGPT assistance is disclosed in the research manuscript. The authors should confirm compliance with the lecturer's AI-writing policy before final submission.

## Academic references

1. Sze et al. (2017), [Efficient Processing of Deep Neural Networks](https://doi.org/10.1109/JPROC.2017.2761740).
2. Reddi et al. (2020), [MLPerf Inference Benchmark](https://doi.org/10.1109/ISCA45697.2020.00045).
3. IEEE (2019), [IEEE 754-2019](https://doi.org/10.1109/IEEESTD.2019.8766229).

**Author approval is not equivalent to approval by course staff.**
