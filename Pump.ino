#include <NewPing.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define TRIGGER_PIN  14 //D5
#define ECHO_PIN     12 //D6
#define MAX_DISTANCE 400
unsigned long int duration;
double inches , cm ;
//int Pump = D1;
int Pump = D1 ;
int relay2 = D2 ;
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
char auth[] = "j0hiWyxty_U9Pa44iJFdqOwvq-ZAuw9Q";
char ssid[] = "vivo1920";
char pass[] = "siriwan1234";

BlynkTimer timer;
WidgetLED led_onBoard(V0);


void myTimerEvent() {
  bool StatusLED = digitalRead(D0);
  if (StatusLED == LOW) {
    led_onBoard.on();
  } else {
    led_onBoard.off();
  }
}

void setup() {
  pinMode(Pump, OUTPUT);
   pinMode(relay2, OUTPUT);
   Blynk.begin(auth, ssid, pass);
  Serial.begin(9600);
  
}

void loop() {
  
Blynk.run();
  timer.run();

  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);  
  digitalWrite(TRIGGER_PIN, LOW);

  duration = pulseIn(ECHO_PIN ,HIGH);
  inches = duration / 148.00;
  cm = duration / 58.00;
 Serial.print("cm : "); 
 Serial.println(cm );
  Blynk.virtualWrite(V15, cm);
  
  Serial.print(inches);
  //Serial.print...
  //int pos = 90;
 // int po = -270;
  int sensorValue = analogRead(A0);
  Serial.println(sensorValue);
  //delay(100);                   
  Serial.print("Ping: ");
  Serial.print(sonar.ping_cm());
 Blynk.virtualWrite(V15, sonar.ping_cm() );
  Serial.println("cm");
  
  
if (sonar.ping_cm() <= 40){
 
  digitalWrite(Pump, LOW); 
   delay(5);
   digitalWrite(relay2, HIGH);// ส่งให้ไฟติด
    delay(3000);
  }else{
   digitalWrite(Pump, HIGH);
    delay(5);
   digitalWrite(relay2, LOW);
    delay(3000);
  }
}
