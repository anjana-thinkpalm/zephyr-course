#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/devicetree.h>

#define APP_LED_NODE DT_ALIAS(app_led)

#if !DT_NODE_HAS_STATUS(APP_LED_NODE, okay)
#error "app-led alias is not defined or LED is not available"
#endif

static const struct gpio_dt_spec heartbeat_led =
    GPIO_DT_SPEC_GET(APP_LED_NODE, gpios);

int main(void)
{
    int ret;

    if (!gpio_is_ready_dt(&heartbeat_led)) {
        return 0;
    }

    ret = gpio_pin_configure_dt(&heartbeat_led, GPIO_OUTPUT_INACTIVE);
    if (ret < 0) {
        return 0;
    }

    while (1) {
        gpio_pin_toggle_dt(&heartbeat_led);

        k_msleep(CONFIG_APP_HEARTBEAT_PERIOD_MS);
    }

    return 0;
}