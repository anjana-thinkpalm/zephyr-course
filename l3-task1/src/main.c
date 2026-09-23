#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

int main(void)
{
    printk("L3 Task 1 - Kconfig LED Subsystem\n");

    while (1) {
        k_sleep(K_SECONDS(1));
    }

    return 0;
}