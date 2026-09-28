# Parking Sensor Visualizer

A C++20 parking-assistance simulator with four virtual distance sensors and a live 2D display built with raylib. Distance values are entered in the console; the graphical window updates the corresponding sensor arcs without waiting for the next console input.

{SCREENSHOT: add a screenshot of the running application here. Save it under assets/ and replace this line with a Markdown image.}

## Features

- Four sensors: Front Left, Front Right, Rear Left, and Rear Right.
- Distance-based states: Safe, Obstacle Detected, Warning, Brake, and Stop.
- Green/red arcs visualize the alert state of each sensor.
- Console input and rendering run concurrently using a C++ thread.
- Per-sensor shared distance slots use mutexes to transfer new measurements to the visualization thread.

## How it works

The console thread requests one distance at a time in this order: Front Left, Front Right, Rear Left, Rear Right, then repeats. Enter a non-negative integer distance in centimeters and press Enter. After each valid input, the corresponding sensor's visualization updates; the other sensors retain their last values. Invalid or negative input is rejected and the same sensor is requested again.

The acquisition thread publishes a value to its sensor's mutex-protected shared slot. The raylib loop copies pending values, updates the `Sensor` objects, and draws the current alert states. Rendering stays on the main thread; the acquisition thread does not call raylib.

```text
Console input -> acquisition thread -> shared distance slots -> Sensor state -> raylib display
```

## Build and run

Requirements: a C++20 compiler, CMake, and Git. CMake fetches raylib 6.0 during configuration, so the initial configuration requires internet access.

```bash
cmake -S . -B build
cmake --build build
```

Run the `parking_sensor` executable with the build directory as its working directory (for example, configure this in CLion). The image is currently loaded from `../assets/parking_view.png`, a path relative to that directory. If your CMake generator puts the executable in a configuration subdirectory, set its working directory explicitly to `build`. Keep the console available for entering distances.

Press Esc or close the graphical window to stop rendering. **Current limitation:** if the acquisition thread is waiting for console input, closing the window alone may not terminate the process; return to the console and press Enter to let the thread exit and be joined.

## Project structure

- `src/Sensor.*`: sensor state and alert classification.
- `src/Visualizer.*`: raylib window, shared-distance consumption, and arc rendering.
- `src/SharedDistance.h`: mutex-protected distance transfer between threads.
- `src/ConsoleInput.*`: code from the earlier console-only version; the current main loop uses its own console input.
- `src/ProjectConfig.h`: shared configuration and alert-level definitions.
- `assets/parking_view.png`: background image.
- `CMakeLists.txt`: C++20 build and raylib dependency.

## Status and roadmap

This is a software simulation; no physical sensors are connected. Keyboard controls were part of an earlier version, but the current version uses console input for distance updates.

- [x] Model four virtual sensors and alert levels.
- [x] Visualize alert states with raylib.
- [x] Accept console updates while the GUI remains responsive.
- [ ] Make shutdown independent of blocking console input.
- [ ] Add automated tests for sensor thresholds and input handling.
- [ ] Explore acquisition from physical distance sensors.

## Disclaimer

This educational simulator is not designed, tested, or certified for use as a vehicle safety system.
