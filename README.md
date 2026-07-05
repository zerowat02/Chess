# Autonomous Chess Robot

ESP32 firmware for a physical chess board that executes moves autonomously via a motorized XY gantry and an electromagnet.

## How it works

Chess pieces sit on a standard board with small permanent magnets on their bases. Beneath the board, an electromagnet mounted on a cartesian XY gantry (driven by two NEMA 17 stepper motors) slides under the surface. When activated, the electromagnet drags the piece above it to any target square. To move a piece from A to B, the robot navigates to A, activates the magnet, and drives to B — all without the piece ever being lifted.

Because the magnet can accidentally drag pieces it passes under, the robot runs **A\* pathfinding** to route around all other pieces on the board. Moves are sent over WiFi as standard UCI chess notation (`e2e4`, `e1g1` for castling, `e7e8q` for promotion) and the robot handles the full move including captures, en passant, castling, and promotion.

## Architecture

```
NetworkManager         receives UCI move over MQTT
    ↓
Robot::movePiece()     validates notation, handles special moves (castling, en passant, promotion)
    ↓
PathPlanner            A* over a 15×23 expanded grid, routing around occupied cells
    ↓
StepConverter          converts grid path → stepper motor step counts
    ↓
MotionController       drives motors via AccelStepper
```

The board is represented as a 15×23 expanded coordinate grid (cell (r,c) maps to expanded (r×2, c×2)). Inter-cell gap nodes at odd indices allow A\* to route the magnet through the narrow gaps between pieces. Columns 0–3 and 19–22 in expanded space are graveyard areas used to park captured pieces.

## Hardware

| Component | Detail |
|---|---|
| Microcontroller | ESP32 (upesy_wroom) |
| Stepper motors | NEMA 17 (×2, XY gantry) |
| Electromagnet | GPIO-controlled, beneath board surface |
| Framework | Arduino via PlatformIO |

## Software dependencies

- [AccelStepper](https://github.com/waspinator/AccelStepper) — stepper motor control
- [PubSubClient](https://github.com/knolleary/pubsubclient) — MQTT client
- [HiveMQ Cloud](https://www.hivemq.com/mqtt-cloud-broker/) — MQTT broker (free tier)

Dependencies are fetched automatically by PlatformIO.

## Build & flash

```bash
# Build
pio run

# Flash to ESP32
pio run --target upload

# Open serial monitor (115200 baud)
pio run --target monitor

# Flash and monitor in one step
pio run --target upload --target monitor
```

## Configuration

### Network & MQTT

Edit `src/NetworkConfig.h` with your broker address and topic names.

Create `src/secrets.h` (this file is gitignored — never commit it):

```cpp
#pragma once
#define WIFI_SSID      "your_wifi_network"
#define WIFI_PASSWORD  "your_wifi_password"
#define MQTT_USERNAME  "your_hivemq_username"
#define MQTT_PASSWORD  "your_hivemq_password"
```

### Hardware calibration

In `src/main.cpp`, adjust the `RobotConfig` constructor to match your hardware:

```cpp
Robot robot(RobotConfig(
    40,   // cellSize: distance between cell centers in mm
    80    // stepsPerMm: stepper steps per millimetre
));
```

## Sending moves

Publish a UCI-encoded move string to the board's MQTT subscribe topic. Examples:

```
e2e4      normal move
e7e8q     pawn promotion to queen
e1g1      white kingside castling
```

The board logs results over serial at 115200 baud.

## Status

Work in progress. Currently functional:

- A\* pathfinding with adjacency penalty for pieces nearby
- Full UCI notation parsing (normal moves, castling, en passant, promotion)
- MQTT/TLS networking (HiveMQ Cloud)
- Motion control via AccelStepper

Not yet implemented:

- Electromagnet control (GPIO on/off to pick up and release pieces)
- Hall sensor matrix for detecting human-initiated moves
- Board state tracking (piece positions updated after each move)
- Server-side move legality validation
- Hardware calibration (cell size and steps/mm are placeholder values)
