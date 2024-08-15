#include <DHT.h>
#include <Wire.h>
#include <ESPmDNS.h>
#include <Sim800L.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <ThingSpeak.h>
#include <String.h>
#include <WiFi.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_MPU6050.h>
#include <PZEM004T.h>
#include <HardwareSerial.h>

// Define the pin and type of DHT sensor
#define DHT_PIN 4     // GPIO pin where the DHT sensor is connected
#define DHT_TYPE DHT22  // DHT sensor type (DHT11 or DHT22)
#define RX  16
#define TX  17
#define TRIG_PIN 5
#define ECHO_PIN 18
 #define MQ2_PIN 34
 #define BUZZER_PIN 23

// Initialize  sensors
HardwareSerial PzemSerial2(2);     
PZEM004T pzem(&PzemSerial2);
LiquidCrystal_I2C lcd(0x27, 20, 4);

IPAddress ip(192, 168, 1, 1);
DHT dht(DHT_PIN, DHT_TYPE);
Sim800L GSMserial(RX, TX);
Adafruit_MPU6050 mpu;
sensors_event_t a, g, temp;
float temperature, humidity;
int smoke;
char* text1;
char* text2;
char* text3;
char* text4;
char* text5;
char* text6;
char* text7;
float v;
float i;

char* number;
bool error; 
float distance;

void setup() {
Serial.begin(115200);
GSMserial.begin(4800);
Serial.println("Setup started...");  // Debugging line
number="+233502677953"; 
text1="HIGH TRANSFORMER TEMPERATURE!!"; 
text2="SMOKE DETECTED!!";
text3="OIL LEVEL IS TOO HIGH!!"; 
text4="OIL LEVEL IS TOO LOW!!"; 
text5="VIBRATIONS DETECTED!!"; 
text6="LOW VOLTAGE!!";
text7="OVER CURRENT!!";

// Initialize LCD
lcd.init();
lcd.backlight();
dht.begin(); // Initialize DHT sensor
pinMode(BUZZER_PIN, OUTPUT);
   
 Serial.println("LCD and sensors initialized");  // Debugging line
      
}  
    
void loop() {
  delay(4000);
   Serial.println("Loop running...");  // Debugging line

  
  // Read temperature in Celsius 
   temperature = dht.readTemperature(); // Read temperature in Celsius
    humidity = dht.readHumidity(); // Read humidity
    // Read MPU6050 sensor
    mpu.getEvent(&a, &g, &temp);
    long duration;
     smoke = analogRead(MQ2_PIN);
     float v = pzem.voltage(ip);
   if (v < 0) v = 0.0;

   float i = pzem.current(ip);
   if (i < 0) i = 0.0;

  
 // Print temperature and humidity values to serial monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C / Humidity");
  Serial.print(temperature);
  Serial.print(" °F, Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");
  delay(2000);


  Serial.print("Accel X: ");
  Serial.print(a.acceleration.x);
  Serial.print(" m/s^2, ");
  Serial.print("Accel Y: ");
  Serial.print(a.acceleration.y);
  Serial.print(" m/s^2, ");
  Serial.print("Accel Z: ");
  Serial.print(a.acceleration.z);
  Serial.println(" m/s^2");

  
  delay(2000);

  displaySet1();
  delay(2000);
   
  



  
digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    duration = pulseIn(ECHO_PIN, HIGH);
    distance = (duration / 2) / 29.1;
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
    delay(2000);

  Serial.print("SMOKE: ");
  Serial.println(smoke);
  delay(2000);

if (GSMserial.available())
    Serial.write(GSMserial.read());
 
 GSMserial.println("AT");
  delay(1000);
 
 GSMserial.println("AT+CPIN?");
  delay(1000);
 
  GSMserial.println("AT+CREG?");
  delay(1000);
 
  GSMserial.println("AT+CGATT?");
  delay(1000);
 
  GSMserial.println("AT+CIPSHUT");
  delay(1000);
 
  GSMserial.println("AT+CIPSTATUS");
  delay(2000);
 
  GSMserial.println("AT+CIPMUX=0");
  delay(2000);
 
  displaySet2();
  delay(2000);
  
  ShowSerialData();
 
  GSMserial.println("AT+CSTT=\"web.gprs.mtnnigeria.net\"");//start task and setting the APN,
  delay(1000);
 
  ShowSerialData();
 
  GSMserial.println("AT+CIICR");//bring up wireless connection
  delay(3000);
 
  ShowSerialData();
 
  GSMserial.println("AT+CIFSR");//get local IP adress
  delay(2000);
 
  ShowSerialData();

 
  GSMserial.println("AT+CIPSPRT=0");
  delay(3000);
 
  ShowSerialData();
  
  GSMserial.println("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",\"80\"");//start up the connection
  delay(6000);
  displaySet3();
 
  ShowSerialData();
 
 GSMserial.println("AT+CIPSEND");//begin send data to remote server
  delay(4000);
  ShowSerialData();
  
  String str="GET https://api.thingspeak.com/update?api_key=5UJKBCFPTE9N4UQF&field1=0" + String(temperature)+"&field2="+String(i) +"&field3="+String(v)+"&field4="+String(smoke)+"&field5="+String(distance) +"&field6="+String(a.acceleration.x)+"&field7="+String(a.acceleration.y)+"&field8="+String(a.acceleration.z);
  Serial.println(str);
  GSMserial.println(str);//begin send data to remote server
  
  delay(4000);
  ShowSerialData();
 
  GSMserial.println((char)26);//sending
  delay(5000);//waitting for reply, important! the time is base on the condition of internet 
  GSMserial.println();
 
  ShowSerialData();
 
  GSMserial.println("AT+CIPSHUT");//close the connection
  delay(100);
  ShowSerialData();

}
void ShowSerialData()
{
  while(GSMserial.available()!=0)
  Serial.write(GSMserial.read());
  delay(5000); 
  
}
void displaySet1() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temperature: ");
    lcd.print(temperature);
    lcd.print("C");
    lcd.setCursor(0, 1);
    lcd.print("SMOKE: ");
    lcd.print(smoke);
    lcd.print("ppm");
    lcd.setCursor(0, 2);
    lcd.print("OL: ");
    lcd.print(distance);
    lcd.print("cm");
     
    }
  
   void displaySet2() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Accel X: ");
    lcd.print(a.acceleration.x);
    lcd.print("m/s^2");
    lcd.setCursor(0, 1);
    lcd.print("Accel Y: ");
    lcd.print(a.acceleration.y);
    lcd.print("m/s^2");
    lcd.setCursor(0, 2);
    lcd.print("Accel Z: ");
    lcd.print(a.acceleration.z);
    lcd.print("m/s^2");
   
    }
    void displaySet3(){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Voltage: ");
    lcd.print(v);
    lcd.print(" V");
    lcd.setCursor(0, 1);
    lcd.print("Current: ");
    lcd.print(i);
    lcd.print(" A");
    }
    

void checkConditions() {
    // Condition to check high temperature
    if (temperature > 75) {
        error=GSMserial.sendSms(number,text1);
        delay(300);
       
    }

    // Condition to check high humidity
    
    if ( smoke > 300) {
   
   error=GSMserial.sendSms(number,text2);
    delay(300); // Delay to prevent multiple messages
  }
    if (distance > 800) {
       
       error=GSMserial.sendSms(number,text3);
        delay(300);
} else if (distance < 300) {

error=GSMserial.sendSms(number,text4);
delay(300);
}
  if ((a.acceleration.x > 10) || (a.acceleration.y > 10) || (a.acceleration.z > 10)) {
        error=GSMserial.sendSms(number,text5);
        delay(3000);
    }
    if (v < 220) {
        error=GSMserial.sendSms(number,text6);
        delay(3000);
    }
if (i > 16) {
        error=GSMserial.sendSms(number,text7);
        delay(3000);
    }

//activate buzzer
if (temperature > 50  || distance > 800 || distance < 300 || a.acceleration.x > 10 || a.acceleration.y > 10 || a.acceleration.z > 10 || smoke > 300 || v < 220 || i > 16) {
digitalWrite(BUZZER_PIN, HIGH);
} else {
digitalWrite(BUZZER_PIN, LOW);
}
}



