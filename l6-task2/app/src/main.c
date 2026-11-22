/*
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/sys/printk.h>

#include "led_sensor.h"

int main(void)
{
    const struct device *led_sensor =
        DEVICE_DT_GET(DT_NODELABEL(led_sensor0));
    struct sensor_value value;
    uint32_t blink_interval_ms = 0;
    int ret;

    if (!device_is_ready(led_sensor)) {
        printk("LED sensor device is not ready\\n");
        return 0;
    }

    /*
     * Call the driver's custom extension API.
     * This changes blink_interval_ms in the driver's dynamic data.
     */
    ret = led_sensor_set_blink_interval(led_sensor, 1000);
    if (ret < 0) {
        printk("Failed to set LED blink interval: %d\\n", ret);
        return 0;
    }

    ret = led_sensor_get_blink_interval(led_sensor, &blink_interval_ms);
    if (ret < 0) {
        printk("Failed to get LED blink interval: %d\\n", ret);
        return 0;
    }

    printk("LED Sensor Application Started\\n");
    printk("Blink interval set to %u ms\\n", blink_interval_ms);

    while (1) {
        /* sensor_sample_fetch() turns the LED ON. */
        ret = sensor_sample_fetch(led_sensor);
        if (ret < 0) {
            printk("Sensor sample fetch failed: %d\\n", ret);
            k_sleep(K_SECONDS(1));
            continue;
        }

        printk("LED ON\\n");
        k_sleep(K_MSEC(blink_interval_ms));

        /* sensor_channel_get() turns the LED OFF. */
        ret = sensor_channel_get(led_sensor, SENSOR_CHAN_ALL, &value);
        if (ret < 0) {
            printk("Sensor channel get failed: %d\\n", ret);
            k_sleep(K_SECONDS(1));
            continue;
        }

        printk("LED OFF\\n");
        k_sleep(K_MSEC(blink_interval_ms));
    }

    return 0;
}
