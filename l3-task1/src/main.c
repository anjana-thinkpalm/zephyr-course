#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

int main(void)
{
    printk("L3 Task 1 - Kconfig LED Subsystem\n");

    while (1) {
        k_sleep(K_MSEC(CONFIG_LED_BLINK_SLEEP_MS));
    }

    return 0;
}
