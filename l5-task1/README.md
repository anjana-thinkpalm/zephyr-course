# L5 Task 1 - Custom Zephyr Board (RA6M4)

This starter project follows the folder layout of the supplied `l5-task1.zip` example,
but targets the Renesas EK-RA6M4 hardware and uses the custom board name `l5_ra6m4`.

## Contents

- `boards/renesas/l5_ra6m4/`: custom board definition
- `app/`: Hello World application

## Important compatibility note

The board files are a minimal RA6M4-derived starting point based on the upstream
Zephyr EK-RA6M4 board definition. They have **not** been built against your local
Zephyr checkout or verified on your physical board. Compare them with the exact
`boards/renesas/ek_ra6m4/` directory in your Zephyr 4.2.99 workspace before use.
In particular, retain any SoC/board-specific clock, pinctrl, flash, and memory
configuration required by that checkout. Do not use these files for a different
RA6M4 custom PCB without checking its schematic and pin assignments.

## Build

Run from an initialized Zephyr west workspace, with this project directory as the
current directory:

```cmd
west build -p always -b l5_ra6m4 -s app -- -DBOARD_ROOT=%CD%
```

If your Zephyr version reports a board qualifier, use the exact target shown by
`west boards` instead of `l5_ra6m4`.

## Expected application output

```text
*** Booting Zephyr OS ***
Hello World! l5_ra6m4
```

## Git submission

From this project directory:

```cmd
git init
git add README.md boards/renesas/l5_ra6m4 app
git diff --cached --name-only
git commit -m "Add custom L5 RA6M4 board and Hello World sample"
git tag -a l5-task1 -m "L5 Task 1 - Custom board and Hello World"
```

Add your remote and push:

```cmd
git remote add origin <your-repository-url>
git push -u origin HEAD
git push origin l5-task1
```
