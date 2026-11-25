/*
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

int main(void)
{
    printk("Hello World! l5_task2_ra6m4\n");

    while (1) {
        k_sleep(K_SECONDS(1));
    }

    return 0;
}
