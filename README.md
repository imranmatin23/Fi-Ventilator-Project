# Fi-Ventilator-Project
This project was in response to the [Code Life Ventilator Challenge](https://www.agorize.com/en/challenges/code-life-challenge?t=nlalEJjOc1pDmRCro-y3JA) by Agorize. The project opened on March 20th, 2020 and closed on March 31st, 2020. The goal was to design a low-cost, simple, easy-to-use and easy-to-build ventilator that can serve the COVID patients, in an emergency timeframe.

Our team, Fi@UCSD Ventilator Team, consisted of a team of 11 members: Evan Kay, Micheal Arellano, Imran Matin, Clemente Guasch, Clara Romero, Kody Harris, Dayan Khandawa, Marcin Kierebinski, Luca Scotzniovsky, Shan Hannadige, and Kalpa Semashinghe. Our team was split into three subteams: Ventilator, Sensors and Flow Components, and Controls. The final cost of our standalone ventilator was $170.67.

## Controls Sub-Team
This repository was designed and implemented by the Controls Sub-Team consisting of Luca Sctozniovsky, Clemente Guasch, and Imran Matin.

Here is a list of the electronical components that were necessary for this project:
- Arduino Microcontroller
- Arduino Breadboard
- Breadboard Jumper Wires (Male to Male)
- Breadboard Jumper Wires (Male to Female)
- Arduino compatible LCD Display
- Potentiometer Knobs
- MAP Pressure Sensors
- Alarm Buzzer
- DC Motors with Encoders
- Motor Controller with H-Bridge
- External power source (Battery Pack)
- Solenoid Valves

## Interesting Notes about what was learned in this project on the Controls Sub-Team:
- Analog values are from 0 to 1023
- Digital valus are from 0 to 255 (or HIGH and LOW)
- Arduino pins are defined as INPUT or OUTPUT in the code
- Functionality of DC Motors with and without Encoders and Motor Controllers
    - DC motors contain two channels and either can be HIGH or LOW
    - Depending on which channel is HIGH and which is LOW will determine if the motor spins clockwise or counter-clockwise
    - If both channels are LOW, then the motor is stopped. If both channels are HIGH, the wires may melt.
    - A motor encoder does not affect the motor at all. Its sole job is to provide information about the angular position of a rotating shaft.
        - In simple terms it is how far the motor has traveled in total in the +/- direction since inital position). That value can be +, 0, or -.
    - A DC Motor with an Encoder that travels only one direction will have this setup:
        - DC Motor VCC and GND are connected to the power supply
        - Encoder VCC and GND are connected to Arduino (5V)
        - Channel A and B are connected to 2 input pins on the Arduino
    - An [H-Bridge](https://lastminuteengineers.com/l293d-dc-motor-arduino-tutorial/) is an electronic circuit that allows for the polarity of the Voltage applied to a load.
        - Put simply it either provides signals in these pairs: HIGH,LOW ; LOW,HIGH ; LOW,LOW to control the direction the motor is turning.
    -  A Motor Controller can be used to control both speed and direction.
        - The speed of a DC motor can be controlled by varying its input voltage and usually done using PWM (Pulse Width Modulation)
        - The direction of a DC motor can be controlled by an H-Bridge changing the polarity of the voltage applied.
    - A DC Motor with an Encoder and Motor Controller will have this setup:
        - A VCC1 that is 5V
        - A VCC2 that is usually 5V-35V (can vary) to power the motors
        - GND
        - Two output pins that are connected to the +/- terminals of the DC Motor
        - Two input pins that are connected to Arduino pins so Arduino can change which is +/-. These control the switches inside the H-bridge.
        - PWM or Enable pin is an input pin connected to an Arduino pin so the Arduino can change the motor speed to a variable speed by controlling the voltage applied to the DC Motor.
        - The Encoder setup is not affected by adding the Motor Controller, so the same setup is used.
    - Tracking distance traveled using [Arduino Encoder Library](https://www.pjrc.com/teensy/td_libs_Encoder.html)
        - Create an `Encoder` object that takes the two Arduino pins that are connecetd to the motor encoder channelA and channelB.
        - This library tracks how much distance is traveled by the motor in total (+ or -). That value can be read or reset.
        - Attach interrupts to the pins that you are using for the motor encoder for best performance. (On Arduino Uno it is pins 2, 3)
    - Arduino is not able to do multi-threading hence, you cannot check if a condition is satisfied for the whole time the loop() function is execting.


## Ventilator Assembly in Progress
<img src="images/Ventilator In Progress.jpg">

## System Block Diagram
<img src="images/System Block Diagram.png">


## Labeled Fi-Ventilator Circuit Diagram
<img src="images/Fi-Ventilator Circuit Diagram.png">

## Wired Fi-Ventilator Circuit Diagram
<img src="images/Wired Fi-Ventilator Circut Diagram.png">
