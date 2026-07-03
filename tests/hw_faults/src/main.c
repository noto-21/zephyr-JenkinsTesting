#include <zephyr/kernel.h>
#include <zephyr/ztest.h>
#include <zephyr/fatal.h>

/* * 1. OVERRIDE THE DEFAULT KERNEL PANIC HANDLER
 * When the ARM CPU HardFaults, it jumps here instead of locking up.
 */
// void k_sys_fatal_error_handler(unsigned int reason, const struct arch_esf *esf) {
//     printk("Intercepted the expected hardware fault!\n");
//     printk("The CPU successfully protected itself. Passing the test.\n");
    
//     // Tell Twister the test succeeded
//     ztest_test_pass(); 
// }

/*
 * 2. THE TEST CASE
 */
ZTEST(hw_fault_suite, test_hardfault) {
    printk("Injecting a memory fault (Null Pointer Dereference)...\n");

    // Create a function pointer mapped to an invalid memory address
    void (*bad_function)(void) = (void (*)(void))0x00000000;

    // Execute it. The CPU will immediately trap this and jump to k_sys_fatal_error_handler.
    bad_function();

    zassert_unreachable("FAIL: The CPU should have crashed before reaching this line!");
}

ZTEST_SUITE(hw_fault_suite, NULL, NULL, NULL, NULL, NULL);
