# L7 Task 2 - Shell Command for the Custom Extension API

Exposes the L6 Task 2 extension API (`led_sensor_set_blink_interval()` /
`led_sensor_get_blink_interval()`) through the `sensorroot` shell command.

| Command | Action |
|---|---|
| `sensorroot set <ms>` | sets the blink interval; valid range 100-10000 ms |
| `sensorroot get`      | prints the current blink interval |

`set` is registered with `SHELL_CMD_ARG(..., 2, 0)`, so the shell rejects a call with
a missing or extra argument. The handler additionally uses `shell_error()` for a missing,
non-numeric or out-of-range value. `main()` re-reads the interval every cycle, so a
change is visible on the LED straight away.

## Build

Run from this `l7-task2` directory in an initialized Zephyr workspace:

```cmd
west build -p always -b l5_task2_ra6m4 -s app -- -DBOARD_ROOT=%CD%\\..\\l5-task2
```

## Example

```
uart:~$ sensorroot set
sensorroot: wrong parameter count
uart:~$ sensorroot set abc
Invalid value 'abc': expected a number in ms
uart:~$ sensorroot set 50
Value 50 out of range (100-10000 ms)
uart:~$ sensorroot set 500
Blink interval set to 500 ms
uart:~$ sensorroot get
Blink interval: 500 ms
```
