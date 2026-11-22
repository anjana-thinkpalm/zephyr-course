/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * L7 Task 2: blink the LED through the sensor API. The interval is re-read
 * every cycle so `sensorroot set <ms>` takes effect immediately.
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
	uint32_t interval_ms = 0;
	int ret;

	if (!device_is_ready(led_sensor)) {
		printk("LED sensor device is not ready\n");
		return 0;
	}

	printk("LED sensor ready. Try: sensorroot set <100-10000> | get\n");

	while (1) {
		ret = led_sensor_get_blink_interval(led_sensor, &interval_ms);
		if (ret < 0) {
			printk("Failed to get blink interval: %d\n", ret);
			k_sleep(K_SECONDS(1));
			continue;
		}

		/* sensor_sample_fetch() turns the LED ON. */
		ret = sensor_sample_fetch(led_sensor);
		if (ret < 0) {
			printk("Sensor sample fetch failed: %d\n", ret);
			k_sleep(K_SECONDS(1));
			continue;
		}
		k_sleep(K_MSEC(interval_ms));

		/* sensor_channel_get() turns the LED OFF. */
		ret = sensor_channel_get(led_sensor, SENSOR_CHAN_ALL, &value);
		if (ret < 0) {
			printk("Sensor channel get failed: %d\n", ret);
			k_sleep(K_SECONDS(1));
			continue;
		}
		k_sleep(K_MSEC(interval_ms));
	}

	return 0;
}
