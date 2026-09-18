# Parking Sensor Visualizer

A C++ simulation of a four-sensor parking assistance system.

## Current status

The current version is a console-based simulator. It receives the distance measured by four virtual sensors and classifies each situation according to predefined alert levels.

The four sensors are:

- Front Left
- Front Right
- Rear Left
- Rear Right

## Features

- Four virtual parking sensors.
- Manual distance input through the terminal.
- Input validation.
- Individual alert level for each sensor.
- Detection of:
  - no nearby obstacle;
  - detected obstacle;
  - warning;
  - braking condition;
  - stop condition.
- Graceful program termination with `-1`.

## Alert thresholds

| Distance | Alert level |
|---:|---|
| More than 150 cm | Safe |
| 81–150 cm | Obstacle detected |
| 41–80 cm | Warning |
| 16–40 cm | Brake |
| 0–15 cm | Stop |

## Example

```text
Front Left sensor --> No nearby obstacle
distance: 800

Front Right sensor --> No nearby obstacle
distance: 600

Rear Left sensor --> Warning!
distance: 55

Rear Right sensor --> STOP!!
distance: 12
```

## Technologies

- C++20
- CMake
- CLion
- Git and GitHub

## Roadmap

- [x] Implement four virtual sensors.
- [x] Add distance validation.
- [x] Add individual alert levels.
- [x] Publish the console version on GitHub.
- [ ] Refactor the sensor model using a C++ class.
- [ ] Add a simulation mode for graphical testing.
- [ ] Add a 2D graphical interface.
- [ ] Evaluate integration with real distance sensors.

## Disclaimer

This project is an educational simulation. It is not a certified automotive safety system.
