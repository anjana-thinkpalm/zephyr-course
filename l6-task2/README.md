# L6 Task 2 - Custom Driver Extension API

This task extends the L6 Task 1 GPIO LED sensor driver with a custom API.

- `led_sensor_set_blink_interval()` updates `blink_interval_ms` in the driver's dynamic data.
- `led_sensor_get_blink_interval()` reads the updated value.
- `main.c` calls the setter with 1000 ms and uses the returned value for LED timing.
- `sensor_sample_fetch()` turns the LED on.
- `sensor_channel_get()` turns the LED off.

## Build

Run from this `l6-task2` directory in an initialized Zephyr workspace:

```cmd
west build -p always -b l5_task2_ra6m4 -s app -- -DBOARD_ROOT=%CD%\\..\\l5-task2
```

The GPIO controller and pin in `app/app.overlay` must match the LED wiring on the target board.
