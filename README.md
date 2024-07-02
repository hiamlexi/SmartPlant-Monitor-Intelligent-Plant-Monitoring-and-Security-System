# Project Title:
# SmartPlant Monitor: Intelligent Plant Monitoring and Security System


## 1. Project Overview:

The SmartPlant Monitor is an IoT system that helps keep plants healthy and secure. It uses temperature and humidity sensors to monitor conditions and lets users check this data on their phones. Using cloud to send sms and make phone call to user to alert about security threats.

The system has a 24-light LED ring that lights up according to the temperature level collected from the DHT sensor, providing real-time status signals and also have many light animations for decorative lighting. An ultrasonic sensor detects nearby movement, lighting up individual LEDs for better visibility at night.

It also features a buzzer that alerts users to unauthorized access, which can be turned off by scanning an authorized RFID card. This ensures only approved users can stop the alert. Overall, the SmartPlant Monitor combines plant care with security features for easy and effective monitoring

### TLDR: if you just want to see how the system works, go to section 11. Finalizing the design. You can watch different scenarios with user stories and acceptance criteria. 

# SmartPlant Monitor V.2.0

In this updated version:
1. 24-light LED ring now lights up according to the distance from the ultrasonic sensor since the DHT11 is broken.(physically)
2. Add an button using interrupt to control the animation of the decorative lights.
3. Add the button also using interrupt to manually turned off the security function e.g turned off the alarm if needed to.
4. Send sms and phone call to the user if something is tryng to approach the plant within the safte distance (5cm) AND without a authorized card. 

![d1cabb33-aec2-4d3d-a4b5-0cf46bc11a54](https://hackmd.io/_uploads/r1NPHY-vA.jpg)



## 11. Finalizing the design
> 
>  ### [Click here ](https://drive.google.com/drive/folders/1pgtQ7hYxhgqS6kMPK1Miy1mM-PNRt0vt?usp=sharing)to see the use case of the project with different scenarios. 


#### Scenario 1:
* User turns on the security function.
* Machine starts monitoring.
* An unauthorized object approaches the plant within 5cm.
* Buzzer turns on, alerting the user.
* Object backs off beyond 5cm.
* Buzzer turns off.
* 24-light LED ring now lights up according to the distance from the ultrasonic sensor.


#### Scenario 2:
* An unauthorized object approaches the plant within 5cm.
* Buzzer turns on, alerting the user.
* User scanned an authorized card.
* Buzzer turns off.

#### Scenario 3:

* User turns on the security function.
* Machine starts monitoring.
* An unauthorized object approaches the plant within 5cm.
* Buzzer turns on, alerting the user.
* An phone call AND sms to user to alert them with message like "Hi,
This is SmartPlant Monitor. Something is tryng to approach your precious plant at 2024-07-02 13:35:30 +0200. The distance is 14.00."

#### Scenario 4 & 7:

* Show case button to switch between light according to real time data and decorative light

#### Scenario 5:

* An unauthorized object approaches the plant within 5cm.
* Buzzer turns on, alerting the user.
* An unauthorized card is scanned, the buzzer continue to alert user. Red leds to indicated that the access is denied (in the video, the red led is broken).
* An authirized card (with black dot in the video) is scanned, the buzzer goes off, the green led blinks to indicate that the access is allowed.

#### Scenario 6:

* Show case button to manually turn on and off for the security function. (Using interrupt).

## 8. Data Transmission and Visualization

The SmartPlant Monitor project get suppoirted from my python program  for data transmission and ubidots for data visualization and user interface. The workflow is as follows:

* The arduino and sensors collect sensor data.
* The python program helps the data transmission from the MCU to a local PC via the COM port and the script then reads, processes, and formats the data for transfer into the cloud. The only requirement is internet connectivity on the PC. This Python script has been developed and tested on the Windows platform.
* The Ubidots dashboard displays real-time sensor readings.


![image](https://hackmd.io/_uploads/ryO6-eC8C.png)

## 2. Estimated time
To assemble the device and upload the code should take you around 4 hours.

 * What purpose does it serve
 
1. Environmental Monitoring: Tracks temperature and humidity to maintain optimal growing conditions for plants.
2.  Security Monitoring: Uses an ultrasonic sensor and RFID access control to protect plants from unauthorized access and potential threats, including animals in rural areas.
3.  Aesthetic Enhancement: Acts as a decorative light with a 24-LED ring that offers various animations for a visually pleasing environment.
4.  Functional Lighting: Provides practical lighting for users as they approach the plants.


## 4. Components



| Component   | Quantity | Price Kr (Link included)| Purpose           |     |
| ----------- | -------- | ----- | ----------------- | --- |
| Arduino Uno | x1       | [345](https://www.electrokit.com/arduino-uno-rev3)   | Micro  controller |     |
RC522 RFID module |x1    |[129](https://fyndiq.se/produkt/rf-kortlasare-modul-mfrc-522-rc522-rfid-rf-ic-kit-bla-9696374ddf6c4dba/?gad_source=1&gclid=CjwKCAjw4f6zBhBVEiwATEHFVkIKZqHz1A-sibyM_9VNPoaPoeSiA7iGU9xvmeCv95ZBNGnjVphavhoCgOMQAvD_BwE)    | RFID access control|
RFID Card Proximity access control 125khz Blank 0.9mm Thin EM4100 Chip |x1| [39](https://www.electrokit.com/rfid-tag-mifare-13.56mhz-kreditkort?gad_source=1&gclid=CjwKCAjw4f6zBhBVEiwATEHFVjuGpDnv1N-CvSe38FRH6g7xgkWslk6_gQdkrU2IKT8XpmjqFngwDBoCvykQAvD_BwE)   |Authorized access control |
Adafruit 24 RGB neopixel LED-ring | x1| [299](https://www.electrokit.com/neopixel-ring-24-rgb-leds-66mm)     | Decorative lighting |
DHT11 Temperature-Humidity Sensor| x1|[ 49](https://www.electrokit.com/digital-temperatur-och-fuktsensor-dht11)    | Environmental monitoring |
Nichia3.2 V White LED 3mm Through Hole, NSPW315DS| x1| [5 ](https://www.electrokit.com/led-uv-5mm-3.2v-80mcd-385nm-30-gr?gad_source=1&gclid=CjwKCAjw4f6zBhBVEiwATEHFVuqtgVnK5ztao_3B_BQIUsKRN1a0PNVMULJJnHsPQ1reTG2TcetUuxoCxB4QAvD_BwE)    |Functional lighting triggered by ultrasonic sensor|
Ledtech3 V Red LED 5mm Through Hole, L4RR5000H1D1| x1| [5 ](https://www.electrokit.com/led-uv-5mm-3.2v-80mcd-385nm-30-gr?gad_source=1&gclid=CjwKCAjw4f6zBhBVEiwATEHFVuqtgVnK5ztao_3B_BQIUsKRN1a0PNVMULJJnHsPQ1reTG2TcetUuxoCxB4QAvD_BwE)   |Indicator LED|
Ledtech2.1 V Green LED 3mm Through Hole, L02R3000G1EP4| x1| [5 ](https://www.electrokit.com/led-uv-5mm-3.2v-80mcd-385nm-30-gr?gad_source=1&gclid=CjwKCAjw4f6zBhBVEiwATEHFVuqtgVnK5ztao_3B_BQIUsKRN1a0PNVMULJJnHsPQ1reTG2TcetUuxoCxB4QAvD_BwE)    |Indicator LED|
RS PRO 1.2kΩ Metal Film Resistor 0.4W ±0.25%| x3| [3 ](https://uk.rs-online.com/web/p/through-hole-resistors/1742612)   | Current limiting |
Breadboard	| x1| [69](https://www.electrokit.com/kopplingsdack-840-anslutningar?gad_source=1&gclid=CjwKCAjw4f6zBhBVEiwATEHFVkxZ0Cz7hsH7itk4073zSdfXkT84j8v-HBv5djCmHj0oGHflaVXXVBoCDqkQAvD_BwE)    |Prototyping the circuit|
Jumper Wire Male to Male	| bunches | 52  |Connections for breadboard circuit
Jumper Wire Male to Female	| bunches | 52  |Connections for breadboard circuit


## 5. Computer setup

Since this project was developed on a Windows 10 computer, the instructions may differ on other operating systems. 

For the IDE, I chose Visual Studio Code and Arduino IDE because of my prior experience with them. They offer excellent extensions for editing and robust support for microcontrollers.

I utilized Arduino and sensors to gather data, then wrote a program to transmit this data to Ubidots for visualization. Users can easily view and browse this data using their computers or phones.

Since the board lack built-in wireless connectivity, necessitating the addition of a WiFi module such as ESP-01 for connectivity. This addition increases hardware costs and complicates the circuit with additional wiring. Therefor, I developed a Python program for serial data transfer to Cloud. The data transmission from the MCU to a local PC via the COM port and the script then reads, processes, and formats the data for transfer into the cloud. The only requirement is internet connectivity on the PC. This Python script has been developed and tested on the Windows platform.

Data transfer to the Ubidots cloud occurs through HTTP requests using the HTTP POST method. Sensor data is sent in JSON format with the header Content-Type: application/json.

Below are two lists of software that need to be installed to set up the development environment and server:

**Development Environment:**

Visual Studio Code
Arduino IDE
Python 3.7 or newer

**Server Setup:**

My program to send out data 
Ubidots

**Library**

1. Arduino IDE 
*     Adafruit NeoPixel
*     DHT sensor library by Adafruit
*     MFRC522
*     Arduino_Portenta_OTA
*     
2. Packages for python
*     pip install pyserial
*     pip install requests


## 6. How to run the program 
   1. Step 1: Assemble the hardware as show in [section 7].
   2. Step 2: Download Visual Studio Code, Arduino IDE, Python 3.7 or newer. Install all the libaries and packages above.
   3.  Step 3: Flash the sketch:
*          Connect to board to your computer with a USB cable
*          Select board and port

![image](https://hackmd.io/_uploads/HJGXWCTL0.png)
* Uppload the sketch 
    * Optional: 
Click the Verify ![symbol_verify2](https://hackmd.io/_uploads/SkUObATLC.png)button Verify button to try compiling the sketch and check for errors.
    * Click the Upload![symbol_upload2](https://hackmd.io/_uploads/Sk7tZR6IC.png)button Upload button to program the board with the sketch.
    * Your sketch will start running on the board. It will run again each time the board is reset.
    4. Step 4:Set up Ubidots as this [tutorial](https://help.ubidots.com/en/articles/2226697-creating-devices-in-ubidots) 
    5. Step 5: Run the Python program on VS code studio

## 7. Putting everything together

You can arrange the components as desired, but make sure to connect everything correctly. If you want to implement tthe Version 2.0, add button according to the picture above.

![image](https://hackmd.io/_uploads/HkZ1A1R8A.png)


## 9. Code


### Configuring for the python program 
For TOKEN, use the API token from your Ubidots account.

Variable_Label must match the variable name used in your Arduino IDE sketch. Ensure the variable type corresponds to the type used in the Arduino IDE.
![image](https://hackmd.io/_uploads/ryU0MgCI0.png)

![image](https://hackmd.io/_uploads/BJSv7x0UC.png)

The POST request is made and errors   is handled gracefully.
![image](https://hackmd.io/_uploads/Hk2AQl0IC.png)
 
 Read the Script.py file for more detailed information.
 
 ### How to give authorized access for RFID card
 
 After having the circuit ready, go to File > Examples > MFRC522 > DumpInfo and upload the code. This code will be available in your Arduino IDE (after installing the RFID library).

Then, open the serial monitor. You should see something like the figure below:![image](https://hackmd.io/_uploads/S1_V8l0I0.png)
This is the information that you can read from the card, including the card UID that is highlighted in yellow. 

Then open the sketch, go to header RFID. Paste the UID of the card here.
![image](https://hackmd.io/_uploads/Byut8lRI0.png)


## 10. Transmitting the data / connectivity
* The data is sent every minute.
* Which wireless protocols did you use? Wi-fi, Cellular 
* Which transport protocols were used? TCP (Transmission Control Protocol)




### Final Reflections
While creating the project, I successfully achieved my goal but identified several areas for improvement:

* Improve cable management
* Monitor and optimize power consumption
* Add an LCD display to show room temperature and humidity
* Keep backup components on hand




