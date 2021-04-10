
#define BLYNK_PRINT Serial
#include <Wire.h>
#include <PubSubClient.h>
#include <NewPing.h>
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>

Servo servo;
WidgetLED led1(V1);
BlynkTimer timer;

//ไลน์
#include <TridentTD_LineNotify.h>
#define SSID  "vivo1920"    
#define PASSWORD  "siriwan1234"
#define LINE_TOKEN  "GIDAytUVoG9kjSV4rz5V4GZMlhRhd2BtjpADal5xhSB"
//

#include <NewPing.h>
#define TRIGGER_PIN  5  
#define ECHO_PIN     4  
#define MAX_DISTANCE 400

#define wifi_ssid "vivo1920"
#define wifi_password "siriwan1234"
#define mqtt_server "34.87.67.58"
#define us2 "sonar/us"

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
//NewPing sonar1(TRIGGER_PI, ECHO_PI, MAX_DISTANCE);

char auth[] = "t_2A2uMn_MFloA5vEgRvTXFqAMe0HOxl";
char ssid[] = "vivo1920";
char pass[] = "siriwan1234";

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);

  Serial.begin(9600);
  Blynk.begin(auth,ssid,pass);
  servo.attach(15);
 timer.setInterval(1000L, sendSensor);

 //ไลน์
 Serial.begin(115200); Serial.println();
  Serial.println(LINE.getVersion());

  WiFi.begin(SSID, PASSWORD);
  Serial.printf("WiFi connecting to %s\n",  SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(400);
 }


//ไลน์
Serial.printf("\nWiFi connected\nIP : ");
  Serial.println(WiFi.localIP());

  // กำหนด Line Token
  LINE.setToken(LINE_TOKEN);
 
}

String macToStr(const uint8_t* mac)
{
  String result;
  for (int i = 0; i < 6; ++i) {
    result += String(mac[i], 16);
    if (i < 5)
      result += ':';
  }
  return result;
}


void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(wifi_ssid);

  WiFi.begin(wifi_ssid, wifi_password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
      Serial.print("Attempting MQTT connection...");
    
      // Generate client name based on MAC address and last 8 bits of microsecond counter
      String clientName;  
      clientName += "esp8266-";
      uint8_t mac[6];
      WiFi.macAddress(mac);
      clientName += macToStr(mac);
      clientName += "-";
      clientName += String(micros() & 0xff, 16);
      Serial.print("Connecting to ");
      Serial.print(mqtt_server);
      Serial.print(" as ");
      Serial.println(clientName);



    // Attempt to connect
    // If you do not want to use a username and password, change next line to
  if (client.connect((char*) clientName.c_str())) {
    //if (client.connect((char*) clientName.c_str()), mqtt_user, mqtt_password)) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void sendSensor()
{
  int cm= sonar.ping_cm();
  Serial.println(cm);
  Blynk.virtualWrite(V16, cm);

}


void loop() {               

  if (!client.connected()) {
        reconnect();
      }
      client.loop();

      // Wait a few seconds between measurements.
      delay(2000);

      float cm = sonar.ping_cm();
       //Read temperature as Celsius (the default)
      float cm1 = sonar.ping_cm();
      // Read temperature as Fahrenheit (isFahrenheit = true)

      if (isnan(cm) || isnan(cm1) ) {
      Serial.println("Ultrasonic");
      return;
      }
      //int cm = sonar.ping_cm();
      Serial.print("Ultrasonic:");
      Serial.println(String(cm).c_str());
      client.publish(us2, String(cm).c_str(), true);

  Serial.print("Ping: ");
  Serial.print(sonar.ping_cm());
  Serial.println("cm");

  Blynk.run();
  timer.run();

   int us1 = sonar.ping_cm();
  if( us1 >= 17 ){
  LINE.notify("น้ำยาฆ่าเชื้อใกล้จะหมดเเล้ว");
  delay(10000);
  }

}
  BLYNK_WRITE(V16)
  {
    //servo.write(param.asInt());
  }
