/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * sensorroot shell command for the GPIO LED sensor driver.
 *
 *   sensorroot fetch  -> sensor_sample_fetch()  (driver turns LED ON)
 *   sensorroot read   -> sensor_channel_get()   (driver turns LED OFF)
 *   sensorroot info   -> device name and ready state
 */

#include <stdlib.h>
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/shell/shell.h>

#define LED_SENSOR_NODE DT_NODELABEL(led_sensor0)

static const struct device *const led_sensor = DEVICE_DT_GET(LED_SENSOR_NODE);

static int cmd_fetch(const struct shell *sh, size_t argc, char **argv)
{
	ARG_UNUSED(argc);
	ARG_UNUSED(argv);

	if (!device_is_ready(led_sensor)) {
		shell_error(sh, "Sensor device not ready");
		return -ENODEV;
	}

	int ret = sensor_sample_fetch(led_sensor);

	if (ret < 0) {
		shell_error(sh, "sensor_sample_fetch failed: %d", ret);
		return ret;
	}

	shell_print(sh, "Sample fetched");
	return 0;
}

static int cmd_read(const struct shell *sh, size_t argc, char **argv)
{
	struct sensor_value val;

	ARG_UNUSED(argc);
	ARG_UNUSED(argv);

	if (!device_is_ready(led_sensor)) {
		shell_error(sh, "Sensor device not ready");
		return -ENODEV;
	}

	/* The L06 driver only implements SENSOR_CHAN_ALL */
	int ret = sensor_channel_get(led_sensor, SENSOR_CHAN_ALL, &val);

	if (ret < 0) {
		shell_error(sh, "sensor_channel_get failed: %d", ret);
		return ret;
	}

	const char *sign = (val.val1 < 0 || val.val2 < 0) ? "-" : "";

	shell_print(sh, "Value: %s%d.%06d", sign, abs(val.val1), abs(val.val2));
	return 0;
}

static int cmd_info(const struct shell *sh, size_t argc, char **argv)
{
	ARG_UNUSED(argc);
	ARG_UNUSED(argv);

	shell_print(sh, "Device: %s", led_sensor->name);
	shell_print(sh, "Ready:  %s", device_is_ready(led_sensor) ? "yes" : "no");
	return 0;
}

SHELL_STATIC_SUBCMD_SET_CREATE(sensorroot_cmds,
	SHELL_CMD(fetch, NULL, "Fetch a sample (LED on)", cmd_fetch),
	SHELL_CMD(read, NULL, "Read channel value (LED off)", cmd_read),
	SHELL_CMD(info, NULL, "Show device name and ready state", cmd_info),
	SHELL_SUBCMD_SET_END
);

SHELL_CMD_REGISTER(sensorroot, &sensorroot_cmds, "LED sensor commands", NULL);
