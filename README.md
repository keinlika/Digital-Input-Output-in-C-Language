# Home Security System Project

## Project Objectives
- Learn how to program the digital I/O ports using the C programming language.
- Learn how to reference specific pins in the code and identify them on the board.
- Implement a home security system that requires I/O to operate.
- Develop system specifications as a team.
- Practice pair programming.

## Schematic
<img width="508" alt="Screenshot 2025-01-23 at 1 08 41 AM" src="https://github.com/user-attachments/assets/9219a5b0-cccc-453e-81da-7916e6535867" />

*Figure 1: A schematic showing the connections for the final circuit of the project.*

## Specifications

### Inputs
- **Arm Button**: Connected to PC13 (GPIOC Pin 13)
- **Disarm Button**: Connected to PA4 (GPIOA Pin 4); pull-up resistor used
- **Front Sensor**: Connected to PA6 (GPIOA Pin 6); pull-up resistor used
- **Back Sensor**: Connected to PA7 (GPIOA Pin 7); pull-up resistor used
- **Window Sensor**: Connected to PA9 (GPIOA Pin 9); pull-up resistor used

### Outputs
- **Arm Status LED**: Connected to PA5 (GPIOA Pin 5)
- **Front Alarm LED**: Connected to PB0 (GPIOB Pin 0)
- **Back Alarm LED**: Connected to PB4 (GPIOB Pin 4)
- **Window Alarm LED**: Connected to PA10 (GPIOA Pin 10)

## Test Plan and Results

| Test Scenario                  | Expected Result                  | Observed Result                  |
|--------------------------------|----------------------------------|----------------------------------|
| Arm System                     | ArmStatusPin (PA5) LED turns on  | ArmStatusPin (PA5) LED turns on  |
| Disarm System                  | ArmStatusPin (PA5) LED turns off | ArmStatusPin (PA5) LED turns off |
| Front Door Open                | FrontAlarmPin (PB0) LED turns on | FrontAlarmPin (PB0) LED turns on |
| Window opens                   | WindowAlarmPin (PA10) LED turns on | WindowAlarmPin (PA10) LED turns on |
| Front Door Open While Armed    | FrontAlarmPin (PB0) Green LED turns on | FrontAlarmPin (PB0) Green LED turns on |
| Back Door Open While Armed     | BackAlarmPin (PB5) Yellow LED turns on | BackAlarmPin (PB5) Yellow LED turns on |
| Window Open While Armed        | WindowAlarmPin (PA10) Blue LED turns on | WindowAlarmPin (PA10) Blue LED turns on |
| Sensors Closed After Disarming | Open the sensors (front, back, window) alarm LEDs turn off | Open the sensors (front, back, window) alarm LEDs turn off |

*Table 1: Test plan with expected and observed results.*

## Evidence of Correct Operation
[Video Evidence](https://vimeo.com/832799548?share=copy)
