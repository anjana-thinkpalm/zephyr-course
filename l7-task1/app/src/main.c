/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * L7 Task 1: the LED sensor is now driven from the shell
 * (see sensor_shell.c), so main() has nothing to loop on.
 */

#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

int main(void)
{
	printk("LED Sensor shell ready. Try: sensorroot info | fetch | read\n");
	return 0;
}
