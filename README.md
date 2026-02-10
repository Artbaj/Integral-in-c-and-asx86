Polynomial Integration Engine (x86/x87 FPU)
Project Description A low-level implementation of numerical integration algorithms utilizing x86 Assembly and the x87 FPU instruction set. The project aims to minimize CPU cycle consumption by bypassing compiler overhead in critical arithmetic sections. It features a hybrid architecture (C + ASM) designed for high-throughput polynomial evaluation.

Manual FPU Stack Management: Optimized register allocation strategy to mitigate x87 stack overflow risks and reduce memory I/O latency.

Instruction Level Optimization: Replaced standard fst/fld sequences with a direct register duplication strategy (fldl + fldl), ensuring operands remain in st(0)/st(1) for continuous processing.

Performance Profiling: Conducted rigorous benchmarking using CPU cycle counters (RDTSC). Achieved a 12.6% reduction in execution cycles for quadratic polynomial integration compared to the baseline implementation.

Precision Control: Maintained double-extended precision results (verified to 7 decimal places) while optimizing for speed
