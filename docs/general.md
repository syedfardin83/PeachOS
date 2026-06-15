# The CPU, Assembly, and Binary

### CPU

The central processing unit is the hardware that performs the main processing work and controls other parts of a computer, such as a laptop, desktop, or mobile phone. CPUs are also found in electrical devices such as refrigerators, televisions, and calculators. The CPU has several registers, each serving a specific purpose. It executes instructions that are ultimately represented in machine code, or binary (0s and 1s). Two major processor architectures are x86 (developed by Intel) and ARM. In this document, I will focus on the x86 processor architecture only. 32-bit x86 processors have general-purpose registers such as EAX, EBX, ECX, and EDX. They also have stack-related registers such as ESP and EBP, along with many others.

### Assembly

The CPU executes instructions written in machine language, or raw binary. Since humans usually do not write binary code directly, we write in assembly language, which is specific to a processor architecture, and use assembler software to convert it into binary that the processor can understand.

There are two types of keywords in x86 assembly. One type is CPU instructions, and the other is assembler directives. Assembly language is used not only to write CPU instructions, but also to generate raw binary data using assembler directives such as `db` (define byte) and `dw` (define word).
