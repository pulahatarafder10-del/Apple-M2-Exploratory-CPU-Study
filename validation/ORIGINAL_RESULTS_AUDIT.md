# Independent inspection of archived CSV summaries

This report checks the **archived experimental records** and arithmetic. It does not establish that the original experiment's conditions were controlled.

**Input:** [data/results.csv](../data/results.csv), 30 original observations recorded by Pulaha Tarafder on an Apple M2 MacBook.  
**Code:** [src/verify_results.cpp](../src/verify_results.cpp)  
**Automated check:** [GitHub Actions](../actions)

All six combinations of hidden width (32, 128, 512) and type (float32, float64) contain **five timed blocks**, each consisting of **10,000 inferences**.

| Hidden units | Precision | Mean (µs) | Sample SD (µs) | Min (µs) | Max (µs) | Model bytes |
|---:|---|---:|---:|---:|---:|---:|
| 32 | float32 | 3.076287 | 1.491961 | 1.858288 | 5.547550 | 9376 |
| 32 | float64 | 3.387064 | 1.021144 | 2.343571 | 5.009154 | 18752 |
| 128 | float32 | 12.540315 | 0.991742 | 11.082625 | 13.400521 | 37408 |
| 128 | float64 | 12.201112 | 1.049562 | 10.832650 | 13.782117 | 74816 |
| 512 | float32 | 52.851942 | 2.720460 | 50.593913 | 57.195846 | 149536 |
| 512 | float64 | 63.793738 | 0.829977 | 62.713425 | 64.766800 | 299072 |

The 512-neuron numerical comparison was reviewed in the joint manuscript, with Saket Ghosh providing discussion notes. Calculations:

- Float32: five block means average to **52.8519418 µs** (rounded **52.852 µs**).
- Float64: five block means average to **63.7937384 µs** (rounded **63.794 µs**).
- Mean reduction in latency relative to float64: **(63.7937384 − 52.8519418) / 63.7937384 × 100 = 17.152...%**, approximately **17.2%**.
- Stored parameter counts follow **(73H + 8) × sizeof(T)**; at H=512, 149,536 bytes for float32 and 299,072 bytes for float64.

**Important qualification:** Five blocks in one session are not five independent processor sessions. Non-overlapping observed ranges at H=512 do not prove a general causal precision advantage. Type and execution order were confounded. Energy consumption, prediction accuracy and total device RAM were not measured.

Source checks and AI-assisted computation are documented; this report is not independent hardware validation or staff approval.
