#include <zephyr/ztest.h>
#include <zephyr/device.h>
#include <zephyr/drivers/i2c.h>

ZTEST(hw_fault_suite, test_i2c_dead_sensor) {
    // 1. Grab the hardware I2C controller from QEMU's digital twin
    const struct device *i2c_dev = DEVICE_DT_GET(DT_NODELABEL(i2c0));
    zassert_true(device_is_ready(i2c_dev), "I2C hardware bus failed to boot.");

    uint8_t data = 0;
    
    // 2. Attempt to read from a fake/broken sensor address (0x42)
    printk("Attempting to read from sensor at 0x42...\n");
    int ret = i2c_read(i2c_dev, &data, 1, 0x42);

    // 3. Evaluate the fault. If the hardware is missing, it SHOULD return a negative error.
    zassert_not_equal(ret, 0, "FAIL: Expected a hardware fault, but the read succeeded!");
    
    printk("SUCCESS: Hardware fault caught! I2C bus returned error code: %d\n", ret);
}

ZTEST_SUITE(hw_fault_suite, NULL, NULL, NULL, NULL, NULL);
