# Experimental method, limits, and audit notes

## Experimental design

- Device: Apple M2 MacBook, reported 16 GB unified memory.
- Compiler: Apple Clang 21, C++17 with `-O3`.
- Workload: untrained, synthetic feed-forward network, 64 inputs, one ReLU hidden layer of 32, 128, or 512 neurons, eight linear outputs.
- Numerical types: float32 and float64; generated weights originated from float-valued pseudorandom numbers.
- Test schedule: 500 warm-up passes, five consecutive blocks of 10,000 forward passes per configuration, 30 block averages total.
- Recorded measures: time per inference (µs), stored parameter bytes from `(73H + 8) * sizeof(T)`.
- Observations: collected in **one session**; **float32 ran before float64** in each width condition.

## Interpretation

Wider networks increased the number of multiply-adds and the measured latency. The 512-unit float32 condition had 17.2% less mean latency than float64; this does **not** establish a causal reason. The model's parameter byte counts follow arithmetic and are not measured total memory use.

## Critical limits

1. Execution order and numerical type are confounded; float32 always preceded float64.
2. Five timed blocks per configuration were recorded in a single session; blocks are not five independent hardware sessions.
3. A single Mac, compiler and optimization setting were tested.
4. No temperature, core assignment, scheduling, memory traffic, cache activity or electrical power was recorded.
5. The model was untrained and used fixed synthetic weights and input; no classification accuracy, energy use or general neural-network performance was assessed.
6. Float64 received values originating from float pseudorandom generation; differences here do not characterize accuracy of trained high-precision models.
7. The C++ validation program checks stored rows and arithmetic only, not hardware controls.

## Future controlled work (not part of these data)

Alternate or randomize precision order, run independent sessions with a fixed-duration warm-up, inspect generated assembly and SIMD vectorization, measure temperature and energy where feasible, and evaluate a trained model with a meaningful accuracy metric.

## Scientific integrity

The manuscript declares ChatGPT assistance. Student confirmation of the lecturer-specific AI-writing policy remains necessary. No approval by teaching staff is claimed.
