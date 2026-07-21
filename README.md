# **Traffic Light Desk Timer [WIP]**
A traffic-light-themed desk clock and timer that tracks study sessions, with a countdown timer for exam practice.

**Modes**\
Mode 0: Displays current time.\
Mode 1: Displays study time in the current session (reads 00:00:00 if no session is in progress).\
Mode 2: Displays total accumulated study time for the day.\
Mode 3: Countdown timer for practice tests.

```mermaid
flowchart LR
    A["standby\n[MODE 0]"] --> |"red (R)"|B["MODE 3\n(default 1.5h)"]
    A --> |"yellow (Y)"| C["CYCLE MODES\n(excl. mode 3)"]
    A --> |"green (G)"| D[MODE 1;\nstarts session]
    B --> |"R:DP: toggle\nextra time"| E["ADJUST TIME"]
    B --> |"Y: -5 min"|E
    B --> |"G: +5 min"|E
    B --> |R:SP| G[START\nCOUNTDOWN]
    B --> |R:LP| F["CANCEL\n(return to standby)"]
```
**LEGEND:**\
SP: short press\
LP: long press\
DP: double press

### **Bill of Materials**
| Item | Qty | Unit Cost (USD) | Total Cost (USD) | Source |
| --- | --- | :---: | :---: | --- |
| Arduino Nano V3 CH340 | 1 | 1.82 | 1.82 |
| 30mm Arcade Button (Red) | 1 | 0.28 | 0.28 |
| 30mm Arcade Button (Yellow) | 1 | 0.28 | 0.28 |
| 30mm Arcade Button (Green) | 1 | 0.28 | 0.28 |
| LCD 1602 Display with I2C (White Text on Black Backlight) | 1 | 2.51 | 2.51 |
