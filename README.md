# Smart Home Simulation

## About
This project simulates the autonomate and control home system with the goals to gain the ability to control remotely your connected home from your phone and computer. There are two versions:
- The simplified smart home.
- The advanced smart home.

## How does the advanced smart home work?
Here is the high level structure of the advanced version:
![alt text](https://github.com/mnguyen0226/smart-home-project-ECE-2804/blob/main/imgs/advanced_smart_home_structure.PNG)
![alt text](https://github.com/mnguyen0226/smart-home-project-ECE-2804/blob/main/imgs/arduino_circuit_advanced_sm.PNG)

There are 8 household appliances:
- **The Weather Station** has a Temperature Sensor and 16x4 LCD Screen. It takes the input data from the Temperature Sensor and will send data back out to the LCD Screen and the MIT App Interface.
- **The Fire Alarm System** includes the Flame Sensor, an LED, and an Amplifier. It will take heat data input and will output sounds to the Amplifier and the LED.
- **The Intruder Detection System** includes the Motion Sensor, LED, and a buzzer. It take analog data input constantly from the motion sensor and will output alerts to the LED, Buzzer, and MIT App Inventor. When the Motion Sensor catches any motion in the far distance, the buzzer will be buzzed, LED will be lighted, and an alert will be sent to the MIT App Inventor.
- **The Automated Night Light System** consists of a Photoresistor, a Red LED and 3 changing color LEDs for decoration. The Photoresistor will take analog signals as input and will notify the microcontroller to react by turning on the LEDs with certain thresholds. When there is light, the LEDs will not be brightened; when there is no light or dim light, the LEDs will be brightened.
- **The AC Master Unit** includes a Bluetooth, LED, and 16x4 LCD screen. The AC will take command from MIT App Inventor which connects with the microcontroller via Bluetooth. Then the microcontroller will react by providing output to the LED and the LCD notification.
- **The Clap-control LED System** includes an LED and a Big-sound Sensor. The Big-sound Sensor takes in the analog data signals from hand-clapping sounds, then it will communicate with the microcontroller to generate the output of LED light on or off. When the Owner claps his/her hands loud, the LED will be turned on; and when the Owner claps his/her hands loud again, the LED will be turned off.
- **Pool Level-measurement System** contains the Water Level Sensor and the 16x4 LCD Display. The Water Level Sensor will take analog signals from the current pool water level and displace the water level of the pool to the LCD screen. Note that the Water Level Sensor will constantly take data and generate output to the LCD screen.
- **Password Door-lock System** contains two LEDs, a servo, and a 4x4 pin pad. The system will connect interaction between owner and the microcontrollers by taking the password of the pin pad as input and will output correct password indication (green LED is on) or wrong password indication (red LED is on). Depending on the correct or wrong password, the servo will open or close the Smart Home door. Note that the Servo will continuously take digital data from the pin pad.
## How does the simplified smart home work?
Here is the high level structure of the simplified version:
![alt text](https://github.com/mnguyen0226/smart-home-project-ECE-2804/blob/main/imgs/simplified_smart_home_structure.PNG)
![alt text](https://github.com/mnguyen0226/smart-home-project-ECE-2804/blob/main/imgs/arduino_circuit_simplified_sm.PNG)

There are 5 household appliances:
- **The Automated Night Light System** contains a photoresistor and a LED. If there is no light, the LED will turn on.
- **The Fire Alarm System** contains a speaker, an amplifier, and a button. When the owner presses the button then a recorded message
will be processed by the amplifier which then delivers the message to the speaker.
- **The Weather Station + AC Unit System** contains a temperature sensor and an LED which represents the AC Unit. The weather station will take
real-time temperature, and if the temperature in F goes above 67F, then the LED (AC Unit) is on. The
temperature will constantly be updated on the LCD and MIT App. 
- **The Intruder Detection System** contains a motion sensor and a buzzer. If a motion is detected, then the buzzer will make buzzing noise, the LCD asks the user to call 911, and the MIT App will alert the owner of the theft’s moving and stopping time.
- **The Indoor Lights System** contains a Bluetooth and an LED (indoor light). The LED on/off state will be controlled via MIT app,
Bluetooth, and Arduino Uno.
## How does the MIT phone app work?
(1) Here is the **splash screen** of the MIT phone app:

![alt text](https://github.com/mnguyen0226/smart-home-project-ECE-2804/blob/main/imgs/mit_app_splash_screen.PNG)

When the user clicks on the app icon, the “Zoom University” screen pops up. When the user clicks on the screen, the main menu shows up on the screen. 

(2) Here is the **user interface** of the MIT phone app:

![alt text](https://github.com/mnguyen0226/smart-home-project-ECE-2804/blob/main/imgs/mit_app_user_interface.PNG)

Once the app is connected to the chosen bluetooth device, the user will be directed back to the main menu and the label under bluetooth symbol is changed to “Connected”. 
- The real time temperature is then reported by the weather station. As the user gets the feedback from the weather station, the user is given the choice to turn on or turn off the AC Master Unit. 
- The “turn on” option is the green switch to the left of the AC symbol and the “turn off” option is the red switch to the right of the AC symbol. 
- The other feature in the app is the intruder’s alert. When nothing is detected, only the blue bar is presented under the image; When the system detects the intruder, the time intruder being detected will be printed on the blue bar. The time system finds that the intruder left will also be printed on the blue bar to replace the previous information.
## How to run this project:
- Step 1: Have the hardward circuit implements similar to either the advanced or simplified smart home in the reports below.
- Step 2: Have an Android Phone and import the MIT App Inventor in *src/mit_app_inventor* by following this [instruction](http://appinventor.mit.edu/explore/support/sharing-code).
- Step 3: Install [Arduino IDE](https://www.arduino.cc/en/software) on your local machine.
- Step 4: Download either the *.ino* file in *src/* then import it to your Arduino Uno or Arduino Mega.
## Demo and Test:
The Final Presentation and Test Demo can be found in [here](https://drive.google.com/file/d/10hSpWn1uEGW5zuKIa79ynKUaghiU0qmn/view?usp=sharing)

## Reports:
- [Simplified Smart Home Final Paper](https://github.com/mnguyen0226/smart-home-project-ECE-2804/blob/main/reports/Simplified%20Smart%20Home%20Final%20Technical%20Report.pdf). 
- [Advanced Smart Home Final Paper](https://github.com/mnguyen0226/smart-home-project-ECE-2804/blob/main/reports/Advanced%20Smart%20Home%20Final%20Technical%20Report.pdf).
## Honor Code @VT:
You know what VT's Honor Code is, Hokies :). Don't do it. You have been warned.

