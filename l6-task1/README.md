# L6 Task 1 - GPIO LED Sensor Driver

This example implements a simple Zephyr sensor driver backed by a GPIO LED.

- `sensor_sample_fetch()` turns the LED on.
- `sensor_channel_get()` turns the LED off.

## Build

From this directory, in an initialized Zephyr workspace:

```cmd
west build -p always -b l5_task2_ra6m4 -s app -- -DBOARD_ROOT=%CD%\\..\\l5-task2
```

The GPIO controller and pin in `app/app.overlay` must match the LED wiring on the target board.
