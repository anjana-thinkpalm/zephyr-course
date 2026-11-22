# L7 Task 1 - Shell Commands for the LED Sensor Driver

Builds on the L6 Task 1 GPIO LED sensor driver and adds a `sensorroot` shell command.

| Command | Action |
|---|---|
| `sensorroot fetch` | calls `sensor_sample_fetch()` (LED on) |
| `sensorroot read`  | calls `sensor_channel_get()` (LED off) and prints the value |
| `sensorroot info`  | prints the device name and ready state |

## Build

Run from this `l7-task1` directory in an initialized Zephyr workspace:

```cmd
west build -p always -b l5_task2_ra6m4 -s app -- -DBOARD_ROOT=%CD%\\..\\l5-task2
```

Open the shell UART (115200 8N1) and try:

```
uart:~$ sensorroot info
uart:~$ sensorroot fetch
uart:~$ sensorroot read
```
