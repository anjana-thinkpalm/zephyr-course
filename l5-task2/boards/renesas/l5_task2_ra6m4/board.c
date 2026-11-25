/*
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/init.h>
#include <zephyr/sys/printk.h>

/*
 * This function executes before main().
 */
static int l5_task2_ra6m4_board_init(void)
{
    printk("Board Initialized\n");

    return 0;
}

/*
 * Register board initialization before application main().
 */
SYS_INIT(l5_task2_ra6m4_board_init, APPLICATION, 0);
