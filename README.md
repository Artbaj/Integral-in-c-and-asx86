Polynomial Integration Engine (x86/x87 FPU)

Project Overview 

A low-latency polynomial integration engine designed to benchmark and optimize arithmetic throughput on x86 architectures. The project implements the Riemann Sum approximation algorithm, manually optimized in x86 Assembly (AT&T syntax) utilizing the x87 FPU instruction set.
Used skills:
Systems Programming & Architecture: Deep understanding of the System V ABI, stack memory management, and register allocation strategies.

Performance Engineering: Utilizing manual loop unrolling and register-based accumulation to minimize Memory I/O latency (Load/Store reduction).

Hardware-Aware Optimization: Writing code that respects CPU pipeline mechanics to reduce cycle count (verified via RDTSC profiling).

Hybrid Development: Linking high-level C drivers with low-level Assembly modules.

Low-Level Debugging: Advanced state analysis using GDB to monitor FPU status words and register stacks.

Tech Stack

Languages: C11 (Driver/Logic), x86 Assembly (Compute Kernels).

Tools: GCC , GDB, Valgrind.

Core Concepts: IEEE 754, Algorithm Complexity, Cache Locality.




<details>

  "Original version (Calculated using Riemann summ)":

y = +2.0x^2

step = 0.001

x E <0.000000 , 1.000000> ∫y(x) = 0.66

takes on average: 183604 cycles

takes on average:0.010127 ms




Current (Calculated using Leibniz integral rule; This result will serve as the baseline.):

y = +2.0x^2

dla x E <0.000000 , 1.000000> ∫y(x) = 0.666667

Takes on average 699 cycles

takes on average:0.000015 ms
</details>


