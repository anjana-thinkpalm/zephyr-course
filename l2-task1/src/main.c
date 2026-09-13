/*
 * L2 Task 1 - LED Blink
 *
 * The LED toggles every second.
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

#define SLEEP_TIME_MS 1000

#define LED0_NODE DT_ALIAS(led0)

#if !DT_NODE_HAS_STATUS(LED0_NODE, okay)
#error "Unsupported board: led0 devicetree alias is not defined"
#endif

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

int main(void)
{
    int ret;
    bool led_state = false;

    if (!gpio_is_ready_dt(&led)) {
        return 0;
    }

    ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_INACTIVE);

    if (ret < 0) {
        return 0;
    }

    while (1) {
        led_state = !led_state;

        ret = gpio_pin_set_dt(&led, led_state);

        if (ret < 0) {
            return 0;
        }

        k_msleep(SLEEP_TIME_MS);
    }

    return 0;
}