# TGB-Control

## Description
This Arduino program enables you to control a 2-temperature thermal gradient bar using an Arduino board, two temperature sensors, and a user interface (UI) with button inputs and an LCD display. The program allows you to set and monitor the temperatures of the bar at both ends, and set the temperatures over the day.

## Information
- Conects to the Campbell CR1000 running the thermal gradient bar
- User-friendly menu system with buttons and LCD display for interaction.
- Set and view the temperature of the left and right plates.
- Supports up to 96 time slots for temperature configurations.
- Implements a PID-like control algorithm to maintain desired temperatures (but can use bang bang control if wanted).

## Components
The program requires the following components:

1. Arduino board (Arduino Uno).
2. Two DS18B20 digital temperature sensors.
5. LCD display (compatible with the LiquidCrystal library).
6. Input shield for navigation buttons.
7. Powered from Campbell CR1000.


## Usage

1. Upon startup, the program will display the main menu on the LCD.
2. Use the input buttons to navigate the menus and set the desired temperatures.
3. You can view the temperature readings of both plates for each time slot.
4. Use the menu to set and save the desired temperatures for different time slots (saved to EEPROM).
5. The program instruct the Campbell CR1000 what to do, the Campbell will keep going with the last setting if no signal reserved.

## Credits

The UI functions and LCD display code in this project are adapted from Neal Snooke (nns@aber.ac.uk).
