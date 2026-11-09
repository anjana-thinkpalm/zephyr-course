#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

int main(void)
{
    printk("LED Kconfig application started\n");

#if defined(CONFIG_LED_SUBSYSTEM)
    printk("LED Subsystem: Enabled\n");
#endif

#if defined(CONFIG_LED_BLINK_FAST)
    printk("LED Blink Interval: 500 ms\n");
#elif defined(CONFIG_LED_BLINK_MEDIUM)
    printk("LED Blink Interval: 1000 ms\n");
#elif defined(CONFIG_LED_BLINK_SLOW)
    printk("LED Blink Interval: 2000 ms\n");
#endif

#if defined(CONFIG_ADVANCED_LED_SETTINGS)
    printk("Advanced LED Settings: Enabled\n");
    printk("LED Brightness: %d\n", CONFIG_LED_BRIGHTNESS);
    printk("LED Fade Duration: %d ms\n", CONFIG_LED_FADE_DURATION);
#endif

    while (1) {
        k_sleep(K_SECONDS(1));
    }

    return 0;
}