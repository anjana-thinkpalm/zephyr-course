/*
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT renesas_led_sensor

#include <errno.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/util.h>

struct led_sensor_config {
    struct gpio_dt_spec led;
};

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

    if (!gpio_is_ready_dt(&config->led)) {
        return -ENODEV;
    }

    return gpio_pin_configure_dt(&config->led, GPIO_OUTPUT_INACTIVE);
}

static const struct sensor_driver_api led_sensor_api = {
    .sample_fetch = led_sensor_sample_fetch,
    .channel_get = led_sensor_channel_get,
};

#define LED_SENSOR_DEFINE(inst)                                      \
    static const struct led_sensor_config led_sensor_config_##inst = { \
        .led = GPIO_DT_SPEC_INST_GET(inst, gpios),                   \
    };                                                               \
                                                                     \
    SENSOR_DEVICE_DT_INST_DEFINE(inst,                               \
                                 led_sensor_init,                    \
                                 NULL,                                \
                                 NULL,                                \
                                 &led_sensor_config_##inst,          \
                                 POST_KERNEL,                         \
                                 CONFIG_SENSOR_INIT_PRIORITY,        \
                                 &led_sensor_api);

DT_INST_FOREACH_STATUS_OKAY(LED_SENSOR_DEFINE)
