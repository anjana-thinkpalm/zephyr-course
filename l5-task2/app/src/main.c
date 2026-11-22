
/*
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/init.h>
#include <zephyr/sys/printk.h>

/*
 * This function executes before main().
 */
static int board_init(void)
{
    printk("Board Initialized\n");

    return 0;
}

/*
 * Register board initialization before application main().
 */
SYS_INIT(board_init, APPLICATION, 0);

int main(void)
{
    printk("Hello World! l5_task2_ra6m4\n");

    while (1) {
        k_sleep(K_SECONDS(1));
    }

    return 0;
}
