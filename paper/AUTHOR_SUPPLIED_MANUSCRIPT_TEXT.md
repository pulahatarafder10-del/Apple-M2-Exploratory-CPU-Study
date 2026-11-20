# Author-supplied manuscript — text archive

**Source:** `Apple_M2_CPP_Inference_Analysis_Formatted(1).pdf` (seven-page formatted manuscript supplied by the authors). The text below preserves the original wording and paragraph order as extracted from the PDF. Charts and original visual layout are not represented by this Markdown transcription. The original PDF remains the authoritative formatting reference.

**Authors:** Pulaha Tarafder (80489) and Saket Ghosh (80564).

**Supporting evidence:** [GitHub repository](https://github.com/pulahatarafder10-del/Apple-M2-Exploratory-CPU-Study)

**Note:** Author approval is not university staff approval. Some references to “inference speed increased” in the supplied PDF should be read as “inference latency increased”, because measured microseconds per inference grew with workload. The research remains a single-session exploratory experiment.

---

## Original PDF — Page 1

Inference Latency and Data Storage of Neural Networks
with C++ on Apple M2
Tarafder, Pulaha (80489) | Ghosh, Saket (80564)
Vistula University, Warsaw, Architecture of Computers (Winter Term 2026/27)
Both authors reviewed and approved (6 th November 2026)



Abstract
A small feedforward neural network was used to investigate how changing the number of units in
the hidden layer and the floating point precision affects inference speed and data storage on a
MacBook with an Apple M2 chip and 16GB unified memory. A C++17 neural network containing
64 inputs, 1 ReLU hidden layer, 8 linear outputs was implemented using 32, 128 and 512 units in
the hidden layer (float32 and float64). For each of these 6 configurations, 500 warmup iterations
were completed. 5 sets of 10,000 forward passes were timed giving 30 data points in total. For
float32 models, mean inference speeds increased from 3.076 to 52.852 µs and for float64 models,
increased from 3.387 to 63.794 µs. At 512 units in the hidden layer, float32 models had 17.2%
less mean inference speeds (non-overlapping data ranges), and half of the data storage of float64
models. However, changes in inference speeds between float32 and float64 models at 32 and 128
units in the hidden layer were small compared to variation within each condition. As float32
models were always run before float64 models, these results may reflect order effects or other
unmeasured effects. Classification accuracy, energy consumption and total memory were not
assessed.
Keywords: AI, Feedforward Neural Network, Apple M2, Floating Point, C++17, Inference Speed



1. Introduction

Balancing computation, data storage and computational precision is important during local
neural network inference. Increasing the number of hidden units in fully connected layers
increases both computation (multiply and add operations) and weight data storage. Float32 and
float64 have different storage sizes and precision; however, the effect on inference speed
depends on implementation and hardware used. The standard for floating point precision and
arithmetic is defined in IEEE 754-2019 [3].

Several studies have analysed how various aspects affect inference efficiency in deep learning
models. Sze et al. provides an overview of efficient deep neural network computations [1], while
Reddi et al. detail MLPerf Inference and highlight representative workloads and consistent
measurement methods to facilitate fair comparisons [2]. While these studies provide useful
context, this student project may not be compliant with MLPerf benchmarks or directly
comparable to standardised model evaluations. This study provides a very small comparative
analysis on a single device. A source code for the models, and raw data has been provided.
Small and inconsistent differences in precision were observed for smaller numbers of hidden
units.


## Original PDF — Page 2

Research Question
How does inference speed and data storage change depending on the number of units in the
hidden layer (H ∈ {32, 128, 512}) and float32/float64 precision, in a single CPU inference
model with 64 inputs and 8 outputs on an Apple M2?
Hypotheses
H1: More units in hidden layer leads to higher inference speed and data storage. H2:
Float64 has double the data storage of float32 for equivalent hidden layer sizes. H3
(Exploratory): Float32 may have lower inference speeds (particularly with higher hidden
layer sizes).


2. Methods

2.1 Equipment and Software
Raw data obtained from a MacBook (Model: Apple M2 with 16GB unified memory). From a
terminal window, it is apparent that the compiler is version 21.0.0 of Apple Clang, compiling for
the arm64-apple-darwin27.0.0 architecture. The C++17 code was compiled with clang++ -O3 -
std=c++17 . Specific specifications of the computer model, version of macOS, CPU state,
temperature, background processes, and core allocation are not recorded (confounding
variables).

2.2 Model and Comparison
The model contains 2 dense layers, with 64 inputs, H hidden units, and 8 linear outputs. The
hidden layer uses ReLU activation. No training or real data is applied. Weights and biases are
randomly generated using a fixed seed and the input vector is kept fixed at 64 values. Due to the
use of pseudo-random number generation, float values are used for both float32 and float64
models (so only comparing arithmetic/ data storage differences rather than prediction
performance between high precision trained models). Within each hidden unit size, float32
inference occurs before float64 inference. Therefore, only H and scalar type are deliberately
changed.

2.3 Inference Speed
Within each condition, 500 warmup iterations occur. Then 5 sets of 10,000 inferences are timed.
The timings are captured using std::chrono::steady_clock , and converted into µs per inference.
A volatile checksum variable was used to discourage skipping large amounts of computation,
although it may introduce overhead. The results from each set of 10,000 inferences are
recorded in a single row in       results.csv . All 30 raw data points have been recorded.
Comparisons are made between float64 and the respective float32 inferences for each hidden
unit size. 5 data sets were recorded in 1 session.

Data storage in bytes = (64H + H + 8H + 8) x sizeof(T) = (73H + 8) x sizeof(T), where T
is float32 (4 bytes) or float64 (8 bytes).

Note that this does not include temporary activation values, or memory overhead from vector
allocations, or total RAM. The mean and sample standard deviation (calculated with n-1 in
denominator) for inference speed within each condition was calculated. This descriptive analysis
does not indicate any statistically significant independent differences.


## Original PDF — Page 3

2.4 Data Validation
The raw data (.csv) was validated independently. It was confirmed that there were 6 groups,
with 5 replicates in each group, 10,000 inferences in each replicate, positive finite inference
speeds, and correct calculation of data storage in bytes. All 30 rows passed. The program
verify_results.cpp was run to validate means and sample standard deviations for each group.
It can be run by both students. This automated validation should not be considered an
independent validation from Saket and Pulaha’s manual validation until they have personally
validated it.

3. Results

Table 1 displays the inference speeds and data storage. Standard deviations shown indicate
variation between 5 sets of 10,000 inferences (sample standard deviation).

Hidden Layer         Scalar       Mean (± 1 SD) Inference             Min-Max Inference     Data Storage
Units             Type              Speed (µs)                       Speed (µs)             (KiB)

32             float32             3.076 (±1.492)                    1.858 – 5.548        9.16

32             float64             3.387 (±1.021)                    2.344 – 5.009       18.31

128            float32            12.540 (±0.992)                   11.083 – 13.401      36.53

128            float64            12.201 (±1.050)                   10.833 – 13.782      73.06

512            float32            52.852 (±2.720)                   50.594 – 57.196      146.03

512            float64            63.794 (±0.830)                   62.713 – 64.767      292.06

Table 1. 5 replicates per configuration. 10,000 inferences per replicate.




Figure 1

Between 32 to 512 hidden units, inference speed increased by 17.18x for float32 (from 3.076 to
52.852 µs) and by 18.83x for float64 (from 3.387 to 63.794 µs). At 512 hidden units, float32 had
a mean inference speed 10.942 µs less, resulting in a 17.2% decrease in inference speed
compared to float64. At 128 hidden units, float64 had a mean inference speed 0.339 µs less than


## Original PDF — Page 4

float32. However, this difference was not significant compared to the variation within each
condition. At 32 hidden units, float32 had a slightly faster mean inference speed (0.311 µs less),
but there was a high variation. It cannot be concluded that float32 is always faster.




Figure 2

Data storage (Bytes):
With 512 hidden units, float32 had data storage of 149536 bytes (146.03 KiB) and float64 had
299072 bytes (292.06 KiB). Within each configuration, data storage is exactly double for float64
models compared to float32 models (as defined by the equation). Therefore, the ratio of data
storage between float64 and float32 models is analytical and is not impacted by timing variation.

4. Discussion

4.1 Interpretation of Results
The most obvious effect on the observed inference speed and data storage was the change in
number of hidden units. In the two dense layers of the network, there are 72H multiply-add
operations. With 32 hidden units, this means 2304 operations. With 128 hidden units, 9216
operations and 36864 with 512 hidden units. The increase in hidden units from 32 to 512 means
a 16x increase in operations. Therefore, inference speeds increased by approximately 17.2x for
float32 and 18.8x for float64. H1 is therefore supported as increasing hidden units increased
inference speed and data storage in the tested configurations.

Within the same hidden unit size, float64 models have double the data storage of float32 models,
as each parameter within float64 models takes up 8 bytes compared to 4 bytes in float32 models
[3]. Therefore, at 512 hidden units, float64 models had 292.06 KiB of data storage, compared to
146.03 KiB for float32 models. Note that this does not include temporary arrays or total process
RAM.

Only at 512 hidden units in this session was H3 supported. The mean inference speeds were
52.852 µs (float32) and 63.794 µs (float64): float32 had 17.2% faster inference speeds (non-
overlapping data ranges). The mean inference speed per multiply-add operation was
approximately 1.43ns for float32 and 1.73ns for float64. This compares to approximately 1.38ns
on average across the other five configurations. This shows that in comparison to the other five


## Original PDF — Page 5

configurations, the larger difference seen in the widest float64 model may be due to a larger
effective cost in this configuration, rather than particularly fast timing in float32.

With 32 and 128 hidden units, mean inference speed differences between float32 and float64
models were 0.311 and 0.339 µs respectively. However, these differences were less than the
sample standard deviations. Therefore, no true advantage in precision was found in either of
these narrower configurations.

4.2 Variation and Other Factors
It may be due to larger data storage in float64 at 512 hidden units (292.06 KiB vs 146.03 KiB in
float32), meaning more data movement within the model. With 128 hidden units, array sizes
were still smaller (73.06 vs 36.53 KiB). As cache allocation and memory movement was not
measured, it cannot be determined if the float64 difference is due to cache size. Data movement
is an important factor to consider in neural network processing [1].

Other factors in compilation may also have caused this difference. As the code was compiled
with -O3 optimisation with clang++, it is unknown what assembly was created. The inner loops
may have not been vectorised according to floating point optimisation rules. Without inspecting
the assembly, we cannot assume that differences in SIMD width is the cause of this difference.

Limitations of this method include float32 being run before float64 in all configurations,
meaning that precision and order of execution are confounded. Only 5 data sets were collected
per condition in 1 session. Only 1 machine and compiler configuration was tested. Thermal
state, background allocation and power were not recorded. Weights in float64 model were
initially generated as floats. Accuracy, energy consumption and total RAM were not measured.
Therefore, these results do not indicate that float32 has a general advantage on any Apple
Silicon devices. They simply provide a useful comparison specific to this workload.

4.3 Further Work
To improve this experiment, precision order should be randomised or alternated. Multiple
independent sessions should be carried out. A fixed warmup period should also be used, and a
larger number of data sets collected. Inspection of assembly and varying vectorisation options
may help determine if factors in compilation contribute to this difference at 512 units. If cache
and power consumption can be directly measured in addition to using a trained task to measure
accuracy, further questions can be investigated without confusion between model data storage
and energy efficiency. Reddi et al. [2] provides a useful comparative method with clear
benchmark conditions and reporting.

5. Conclusion

In this single comparison on an Apple M2, increasing hidden units increased inference speed
and data storage. The float64 model had exactly double the data storage. However, at 512
hidden units, float32 had 17.2% less mean inference speed. In narrower models, no true
advantage in precision was seen. These results provide a useful comparison for this workload,
but no general conclusions can be drawn about advantages in all Apple Silicon devices, AI
accuracy, or energy savings. To understand why the widest model had differences, improved
ordering, measurements, and multiple sessions should be conducted.


## Original PDF — Page 6

6. Declarations and Contributions

Use of Generative AI & AI Assisted Technology: ChatGPT from OpenAI was used to shape
the research question, draft source code, find sources, check numerical calculations, create
graphs, and write/edit this manuscript (including combined discussion section). The inference
speed data comes from the original results.csv on Pulaha Tarafder’s Apple M2. Calculations
were performed with AI assistance. Neither the analysis or text generated by the model can be
considered independent experimentation by either student. However, both authors are
responsible for ensuring sources, calculations, code, and interpretation have been manually
verified.

Contributions: Both authors reviewed and approved. Pulaha Tarafder (80489) provided, ran,
and recorded the Apple M2 C++ benchmark, and reviewed the manuscript. Saket Ghosh
(80564) provided a summary of results at 512 hidden units, and detailed scientific interpretation
and suggestions for improvement. This includes hypothesis, interpretation of operations per
second, other factors, limitations and suggestions for further testing. Both authors have read
and approved this manuscript. The manuscript was drafted, checked, and edited with AI
assistance (as described above).

7. References

[1] V. Sze, Y.-H. Chen, T.-J. Yang, J. S. Emer, Efficient Processing of Deep Neural Networks: A Tutorial and
Survey, in: Proceedings of the IEEE, Vol. 105, No. 12, 2017, pp. 2295-2329. DOI: https://doi.org/
10.1109/JPROC.2017.2761740
[2] V.J. Reddi et al., MLPerf Inference Benchmark, in: 2020 ACM/IEEE 47th Annual International
Symposium on Computer Architecture (ISCA), 2020, pp. 446-459. DOI: https://doi.org/10.1109/
ISCA45697.2020.00045
[3] IEEE, IEEE Standard for Floating-Point Arithmetic - IEEE Std 754-2019, 2019. DOI: https://doi.org/
10.1109/IEEESTD.2019.8766229


Appendix A: Validation

To perform this benchmark again on an Apple Silicon device, place AI_Research_M2_Fresh.cpp in
a directory. Compile with command:               clang++   -O3   -std=c++17   AI_Research_M2_Fresh.cpp         -o
ai_benchmark . Run with command: ./ai_benchmark 10000 5 . However, note that the original data
from results.csv will be overwritten. To check original data, compile verify_results.cpp with
command:      clang++    -O2      -std=c++17   verify_results.cpp    -o   verify_results , then run with
command: ./verify_results results.csv . In the supplementary folder, the input generation
process (no external dataset), dependencies, original and derived .csv files, graphs and
README have been provided. All results will vary between sessions.


## Original PDF — Page 7

Evidence:
The original source code, results.csv containing 30 data points, calculation check program, derived
summary, graphs and instructions to run the code have been provided in the attached evidence file
AI_M2_Research_Evidence.zip. This file has also been added as a PDF attachment for offline
viewing. Different PDF readers may support different attachments. Note that this is an evidence file,
and not a public website. Evidence must be published to a repository or shared directory accessible
to a reviewer. Once published, the VERIFIED URL of the evidence must be added to the PDF before
submitting in Platon (1 attempt). Until evidence has been published with a real URL, no public links
to evidence can be truthfully given.
This manuscript has been approved. It contains measurements from Pulaha and interpretations/
reviews from Saket. Both authors confirm that they have read and approved this version. Assistance
from ChatGPT has been declared.
Instructions for publishing (official website): https://github.com/new.
A public or reviewer accessible project link can be added once the archive has been uploaded.

