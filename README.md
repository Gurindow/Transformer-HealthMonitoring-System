OVERVIEW
This code integrates a number of sensors to track transformer health parameters such as temperature, vibration, smoke level, current, and voltage. When thresholds are breached, the system sends SMS to the users and transfers data to ThingSpeak for real-time monitoring using the GSM SIM800L module.
COMPONENTS USED
•	DHT22 to measure temperature 
•	HC-SR04 ultrasonic sensor to measure transformer oil levels 
•	MPU6050 measures vibration on the X, Y, and Z axes.
•	SIM800L GSM module for sending SMS and communication with ThingSpeak 
•	PZEM 004T meter to measure current and voltage levels
•	Liquidcrystal_i2c-LCD –Shows the readings from sensors and 
•	The buzzer gives an alert as sound outputs.

CODE FUNCTIONALITY
Initialization (setup function):
•	Serial communication is set up.
•	Sensors are initialized, and LCD is configured.
•	The GSM communication is started and set up to send SMS.
Main Loop (loop function):
•	Sensor data Reading: The data retrieved comprises temperature, humidity, acceleration, smoke level, voltage, and current.
•	Displaying Data: Current sensor readings are updated on the LCD.
•	Check for Critical Conditions: Sensor readings are evaluated against predefined thresholds.
•	Send Alerts: If any critical condition is met, mobile phone SMS alerts will be sent, and the buzzer will be triggered.
•	Communication with ThingSpeak: This sends sensor data through GSM to ThingSpeak.
Functions:
•	ShowSerialData(): This can be used to print out messages to the serial monitor from the GSM module while testing or configuring the device.
•	displaySet1(), displaySet2(), and displaySet3(): These functions are used to update the LCD with various sets of data, such as temperature, smoke, distance, acceleration, voltage, and current.
•	checkConditions(): It is a function that compares the received data of the sensors with the given thresholds to send an sms alert and simultaneously activate a buzzer.
How to Use:
1.	Connect Components: Most sensors have specific pins for  connection on the ESP32 microcontroller.[Cross-check the wiring of GSM module and sensors from datasheets]
NB: RX to TX
2.	 Upload Code: Program the microcontroller using the Arduino Integrated Development Environment (IDE) to load the code into the microcontroller.
3.	 Monitor Outputs:
•	Serial Monitor Displays  sensors values and logs of the GSM communication on the Arduino IDE.
•	LCD Display: Monitors and displays  the sensor information in real-time for the local targeted point.
•	Buzzer: Hear alerts if critical conditions are detected.
4. SMS Alerts: Make certain that your GSM module is set and connected to a working SIM card and is programmed to send SMS to the phone number provided.
5. ThingSpeak Integration: Replace the API key component with your ThingSpeak credentials for external data logging purposes.
EXAMPLE ALERTS
•	High Temperature: Ends an SMS alert if the temperature gets to 75°C.
•	Smoke Detection: Sends an SMS if the smoke level exceeds 300 parts per million.
•	Oil Level: Alarms for high or low oil quantities such as more than 800 cm or less than 300 cm.
•	 Vibration: If recognized acceleration > 10 m/s², then issues an alert.
•	Voltage: Danger signals for low voltage LESS than 220 V.
•	Current: High current alarms, including that which is over 16A.
FINAL NOTES
• Modifications in the shown thresholds and configurations must be made according to your transformer and your needs for its monitoring.
• Make Ensure the GSM module has appropriate connectivity for sending SMSs and accessing ThingSpeak.
• To ensure that the system works correctly to the greatest extent, ensure all the components' power supply and connections are correct.
