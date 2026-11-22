/*
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/sys/printk.h>

int main(void)
{
    const struct device *led_sensor =
        DEVICE_DT_GET(DT_NODELABEL(led_sensor0));
    struct sensor_value value;

    if (!device_is_ready(led_sensor)) {
        printk("LED sensor device is not ready\\n");
        return 0;
    }

    printk("LED Sensor Application Started\\n");

    while (1) {
        /* sensor_sample_fetch() turns the LED ON. */
        if (sensor_sample_fetch(led_sensor) < 0) {
            printk("Sensor sample fetch failed\\n");
            k_sleep(K_SECONDS(1));
            continue;
        }

        printk("LED ON\\n");
        k_sleep(K_SECONDS(2));

        /* sensor_channel_get() turns the LED OFF. */
        if (sensor_channel_get(led_sensor, SENSOR_CHAN_ALL, &value) < 0) {
            printk("Sensor channel get failed\\n");
            k_sleep(K_SECONDS(1));
            continue;
        }

        printk("LED OFF\\n");
        k_sleep(K_SECONDS(2));
    }

    return 0;
}
