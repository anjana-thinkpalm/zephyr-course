
# L5 Task 1 - Custom Zephyr Board (RA6M4)

This project defines a custom Renesas RA6M4 board named `l5_ra6m4` and a Hello World application.

## Project structure

- `boards/renesas/l5_ra6m4/`: Custom board definition
- `app/`: Hello World application

The project registers its root directory as `BOARD_ROOT` in `app/CMakeLists.txt`.

## Build

Run from the `l5-task1` directory:

```cmd
west build -p always -b l5_ra6m4 -s app
```

## Expected output

```text
*** Booting Zephyr OS ***
Hello World! l5_ra6m4
```
