// This is essentially a table of branch instructions pointing to
// the right handlers.
// Handlers are implemented in C.

// No need for bl (branch-link), the CPU saves context and restores
// when returning from the handler (eret).

.global _vectors

.align 11
_vectors:
        // EXCEPTION TYPES::VECTOR TABLE COLUMNS
        b sync_handler      // exceptions, faults, syscalls
        b irq_handler       // normal hardware interrupt
        b fiq_handler       // fast interrupt, high prio
        b serr_handler      // system error

        // ENTRY STATE::VECTOR TABLE ROWS
        // repeating pattern for simplicity
        //TODO: look up documentation on all 16 states
        .rept 3
        b sync_handler
        b irq_handler
        b fiq_handler
        b serr_handler
        .endr

