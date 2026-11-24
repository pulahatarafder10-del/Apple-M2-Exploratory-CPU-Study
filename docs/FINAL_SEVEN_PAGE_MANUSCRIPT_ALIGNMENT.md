# Alignment with the authors' final seven-page PDF

**Final author-supplied manuscript:** *Inference Latency and Data Storage of Neural Networks with C++ on Apple M2* (seven pages, supplied 20 November 2026).

**Authors:** Pulaha Tarafder (80489) and Saket Ghosh (80564); Vistula University, Architecture of Computers, 2026/27.

This repository is the online supporting evidence for that specific PDF, **not** for the earlier draft titled *Experimental Evaluation of Neural Network Inference Performance and Numerical Precision*. The online `paper/AUTHOR_SUPPLIED_MANUSCRIPT_TEXT.md` transcribes the final seven-page PDF. `paper/AI_Research_Online_Readable_Copy.pdf` is an auto-generated readable derivative with an evidence link, not an exact facsimile of the original author-formatted PDF.

## Matching source and data

- Appendix A original filename: [`src/AI_Research_M2_Fresh.cpp`](../src/AI_Research_M2_Fresh.cpp), equivalent benchmark source at [`src/original_apple_m2_benchmark.cpp`](../src/original_apple_m2_benchmark.cpp).
- Appendix A verifier: [`src/verify_results.cpp`](../src/verify_results.cpp).
- Table 1 original evidence: [`data/results.csv`](../data/results.csv) (30 timing observations).
- Calculated summary: [`data/analysis_summary.csv`](../data/analysis_summary.csv).
- Figure 1 latency: [`figures/latency_by_configuration.svg`](../figures/latency_by_configuration.svg).
- Figure 2 parameter storage: [`figures/parameter_storage.svg`](../figures/parameter_storage.svg).
- Calculation audit: [`validation/ORIGINAL_RESULTS_AUDIT.md`](../validation/ORIGINAL_RESULTS_AUDIT.md).

## Source PDF Table 1

| Hidden H | Precision | Mean µs | Sample SD µs | Range µs | Parameter KiB |
|---:|---|---:|---:|---|---:|
| 32 | float32 | 3.076 | 1.492 | 1.858–5.548 | 9.16 |
| 32 | float64 | 3.387 | 1.021 | 2.344–5.009 | 18.31 |
| 128 | float32 | 12.540 | 0.992 | 11.083–13.401 | 36.53 |
| 128 | float64 | 12.201 | 1.050 | 10.833–13.782 | 73.06 |
| 512 | float32 | 52.852 | 2.720 | 50.594–57.196 | 146.03 |
| 512 | float64 | 63.794 | 0.830 | 62.713–64.767 | 292.06 |

The study used 64 inputs, one ReLU layer with H = 32/128/512, eight linear outputs, 500 warm-ups, five blocks of 10,000 passes per configuration, C++17, Apple M2 (16 GB), one session. Float32 ran before Float64. Generated weights originated from float values. These descriptive findings are **latency**, not prediction accuracy, power, energy, or total RAM.

## Historical wording and status

Page 7 of the author-supplied PDF was written before public GitHub evidence publication and states that no public URL was available. This repository now hosts the source, CSV, verifier and charts; the source manuscript has not been silently modified. A separate downloadable final-PDF-aligned offline package contains the unchanged source and an evidence-link addendum.

The original author-supplied PDF has wording such as “inference speed increased” while microseconds per inference grew with width. That numerical metric is **latency**, so the supporting charts and data use that term.

AI use is disclosed in the manuscript. Approval refers only to the two authors, not university staff; lecturer-specific AI-writing policy and final Platon submission remain separate requirements.
