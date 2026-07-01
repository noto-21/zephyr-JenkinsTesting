#include <zephyr/ztest.h>

ZTEST(hw_fault_suite, test_hardfault) {
    printk("Injecting a memory fault (Null Pointer Dereference)...\n");

    // Create a function pointer mapped to an invalid memory address
    void (*bad_function)(void) = (void (*)(void))0x00000000;

    // Execute the invalid address. 
    // The ARM Cortex-M3 will immediately trap this and throw a hardware HardFault.
    bad_function();

    zassert_unreachable("FAIL: The CPU should have crashed before reaching this line!");
}

ZTEST_SUITE(hw_fault_suite, NULL, NULL, NULL, NULL, NULL);
