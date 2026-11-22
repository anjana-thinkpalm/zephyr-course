/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * sensorroot shell command exposing the LED sensor's custom extension API.
 *
 *   sensorroot set <ms>  -> led_sensor_set_blink_interval()  (100..10000 ms)
 *   sensorroot get       -> led_sensor_get_blink_interval()
 */

#include <errno.h>
#include <stdlib.h>
#include <ctype.h>
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/shell/shell.h>

#include "led_sensor.h"

#define BLINK_INTERVAL_MIN_MS 100U
#define BLINK_INTERVAL_MAX_MS 10000U

static const struct device *const led_sensor =
	DEVICE_DT_GET(DT_NODELABEL(led_sensor0));

static int cmd_set(const struct shell *sh, size_t argc, char **argv)
{
	char *end;
	unsigned long value;
	int ret;

	/* SHELL_CMD_ARG already enforces this; kept as a safety net. */
	if (argc != 2) {
		shell_error(sh, "Missing argument. Usage: sensorroot set <%u-%u ms>",
			    BLINK_INTERVAL_MIN_MS, BLINK_INTERVAL_MAX_MS);
		return -EINVAL;
	}

	/* strtoul() accepts a leading '-' or whitespace, so require a digit. */
	if (!isdigit((unsigned char)argv[1][0])) {
		shell_error(sh, "Invalid value '%s': expected a number in ms", argv[1]);
		return -EINVAL;
	}

	errno = 0;
	value = strtoul(argv[1], &end, 10);
	if (errno == ERANGE || *end != '\0') {
		shell_error(sh, "Invalid value '%s': expected a number in ms", argv[1]);
		return -EINVAL;
	}

	if (value < BLINK_INTERVAL_MIN_MS || value > BLINK_INTERVAL_MAX_MS) {
		shell_error(sh, "Value %lu out of range (%u-%u ms)", value,
			    BLINK_INTERVAL_MIN_MS, BLINK_INTERVAL_MAX_MS);
		return -ERANGE;
	}

	ret = led_sensor_set_blink_interval(led_sensor, (uint32_t)value);
	if (ret < 0) {
		shell_error(sh, "led_sensor_set_blink_interval failed: %d", ret);
		return ret;
	}

	shell_print(sh, "Blink interval set to %lu ms", value);
	return 0;
}

static int cmd_get(const struct shell *sh, size_t argc, char **argv)
{
	uint32_t interval_ms;
	int ret;

	ARG_UNUSED(argc);
	ARG_UNUSED(argv);

	ret = led_sensor_get_blink_interval(led_sensor, &interval_ms);
	if (ret < 0) {
		shell_error(sh, "led_sensor_get_blink_interval failed: %d", ret);
		return ret;
	}

	shell_print(sh, "Blink interval: %u ms", interval_ms);
	return 0;
}

SHELL_STATIC_SUBCMD_SET_CREATE(sensorroot_cmds,
	/* mandatory = 2 (command + 1 argument), optional = 0 -> exactly one arg */
	SHELL_CMD_ARG(set, NULL, "Set blink interval in ms (100-10000)\n"
			  "Usage: sensorroot set <ms>", cmd_set, 2, 0),
	SHELL_CMD_ARG(get, NULL, "Show current blink interval", cmd_get, 1, 0),
	SHELL_SUBCMD_SET_END
);

SHELL_CMD_REGISTER(sensorroot, &sensorroot_cmds, "LED sensor commands", NULL);
