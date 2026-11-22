/*
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT renesas_led_sensor

#include <errno.h>
#include <stdint.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/util.h>

#include "led_sensor.h"

struct led_sensor_config {
    struct gpio_dt_spec led;
};

/* Runtime/dynamic data owned by this device instance. */
struct led_sensor_data {
    uint32_t blink_interval_ms;
};

int led_sensor_set_blink_interval(const struct device *dev,
                                 uint32_t interval_ms)
{
    struct led_sensor_data *data;

    if (dev == NULL || interval_ms == 0) {
        return -EINVAL;
    }

    if (!device_is_ready(dev)) {
        return -ENODEV;
    }

    data = dev->data;
    data->blink_interval_ms = interval_ms;

    return 0;
}

int led_sensor_get_blink_interval(const struct device *dev,
                                 uint32_t *interval_ms)
{
    const struct led_sensor_data *data;

    if (dev == NULL || interval_ms == NULL) {
        return -EINVAL;
    }

    if (!device_is_ready(dev)) {
        return -ENODEV;
    }

    data = dev->data;
    *interval_ms = data->blink_interval_ms;

    return 0;
}

static int led_sensor_sample_fetch(const struct device *dev,
                                   enum sensor_channel chan)
{
    const struct led_sensor_config *config = dev->config;

    ARG_UNUSED(chan);

    return gpio_pin_set_dt(&config->led, 1);
}

static int led_sensor_channel_get(const struct device *dev,
                                  enum sensor_channel chan,
                                  struct sensor_value *val)
{
    const struct led_sensor_config *config = dev->config;
    int ret;

    if (chan != SENSOR_CHAN_ALL) {
        return -ENOTSUP;
    }

    ret = gpio_pin_set_dt(&config->led, 0);
    if (ret < 0) {
        return ret;
    }

    val->val1 = 0;
    val->val2 = 0;

    return 0;
}

static int led_sensor_init(const struct device *dev)
{
    const struct led_sensor_config *config = dev->config;
    struct led_sensor_data *data = dev->data;

    if (!gpio_is_ready_dt(&config->led)) {
        return -ENODEV;
    }

    data->blink_interval_ms = 2000;

    return gpio_pin_configure_dt(&config->led, GPIO_OUTPUT_INACTIVE);
}

static const struct sensor_driver_api led_sensor_api = {
    .sample_fetch = led_sensor_sample_fetch,
    .channel_get = led_sensor_channel_get,
};

#define LED_SENSOR_DEFINE(inst)                                        \
    static const struct led_sensor_config led_sensor_config_##inst = { \
        .led = GPIO_DT_SPEC_INST_GET(inst, gpios),                     \
    };                                                                 \
    static struct led_sensor_data led_sensor_data_##inst;              \
    SENSOR_DEVICE_DT_INST_DEFINE(inst,                                 \
                                 led_sensor_init,                      \
                                 NULL,                                  \
                                 &led_sensor_data_##inst,               \
                                 &led_sensor_config_##inst,             \
                                 POST_KERNEL,                           \
                                 CONFIG_SENSOR_INIT_PRIORITY,          \
                                 &led_sensor_api);

DT_INST_FOREACH_STATUS_OKAY(LED_SENSOR_DEFINE)
