# TrafficLightLab3 - corrected demo build

This project keeps the original PA/PB pinout and Proteus schematic while using
the verified control flow from the reference project.

## Timer configuration

- TIM2 internal clock: Prescaler = 7999, Counter Period = 9.
- TIM2 update interrupt: 10 ms.
- Software timer 1: 1000 ms for the normal countdown.
- Software timer 3: 250 ms per toggle for 2 Hz traffic-light blinking.
- Software timer 4: 10 ms per digit-pair scan.

## Expected demonstration

- Mode 1: both roads run and their displayed values decrease once per second.
- Button 1: Mode 1 -> Mode 2 -> Mode 3 -> Mode 4 -> Mode 1.
- Mode 2: red LEDs blink; display A shows the red setting; display B shows 02.
- Mode 3: amber LEDs blink; display A shows the amber setting; display B shows 03.
- Mode 4: green LEDs blink; display A shows the green setting; display B shows 04.
- Button 2: increases the selected value from 1 to 99.
- Button 3: saves the selected value.
- Values in Modes 2-4 are settings, so they do not count down.

## Build before Proteus

1. Import/open the project in STM32CubeIDE.
2. Do not regenerate code unless required. If regenerated, keep user code and
   verify that the three buttons remain GPIO input with pull-up.
3. Select Project > Clean, then Project > Build Project.
4. Load `Debug/TrafficLightLab3.hex` into the STM32 component in Proteus.

The old Debug output was removed because it was compiled from the previous
source and must not be used for simulation.
