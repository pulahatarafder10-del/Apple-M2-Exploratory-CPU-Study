# Dependencies and input generation

## Experimental environment
- Original machine: Apple M2 MacBook, 16 GB unified memory.
- Compiler: Apple Clang 21.0.0, C++17, -O3.
- The benchmark and the CSV verifier use the C++ standard library only; no Python, external data, or third-party runtime dependency is required.
- GitHub's optional readable-PDF build uses Python with ReportLab. That is separate from the original experiment.

## Input generation
The model has 64 inputs, one ReLU hidden layer (H = 32, 128, or 512), and eight linear outputs. It is untrained. Its weights and biases are generated using a fixed pseudorandom seed (123456789). Values originate in float format for both scalar types. The input vector uses (i % 11)/11 for 64 elements, converted to the chosen type. There is no external dataset.

## Measurement protocol
For each of six conditions, the program performs 500 warm-up passes followed by five consecutive blocks of 10,000 inference passes each. All original results were recorded in one session. Float32 always ran before float64. The CSV stores the average microseconds per forward pass for each block. Parameter storage is derived as (73H + 8) times the scalar size in bytes; it does not represent total RAM.

## Validate original data
From repository root on macOS:

    clang++ -O2 -std=c++17 src/verify_results.cpp -o verify_results
    ./verify_results data/results.csv

## Run a NEW experiment without modifying archived data
    clang++ -O3 -std=c++17 src/original_apple_m2_benchmark.cpp -o ai_benchmark
    mkdir -p new_trial && cd new_trial && ../ai_benchmark 10000 5

The new_trial directory will receive a new results.csv. Do not overwrite or mix it with data/results.csv in the repository.

## Interpretation limits
The original session did not control or record processor scheduling, thermals, energy, cache behavior, or total RAM. It does not measure prediction accuracy. The generated weights have float-valued origins in both scalar types. Findings are descriptive.