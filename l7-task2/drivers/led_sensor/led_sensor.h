/*
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef LED_SENSOR_H__
#define LED_SENSOR_H__

#include <stdint.h>
#include <zephyr/device.h>

/*
 * Set the LED sensor's blink interval in milliseconds.
 * This updates the driver's dynamic data.
 */
int led_sensor_set_blink_interval(const struct device *dev,
                                 uint32_t interval_ms);

/* Read the currently configured blink interval. */
int led_sensor_get_blink_interval(const struct device *dev,
                                 uint32_t *interval_ms);

#endif /* LED_SENSOR_H__ */
