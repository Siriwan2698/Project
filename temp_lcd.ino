#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <Servo.h>

Servo myservo;
//LiquidCrystal_I2C lcd(0x27, 2, 1,0,4,5,6,7,3,POSITIVE);
LiquidCrystal_I2C lcd(0x27,20,4); 
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
 
 float tempa=0;
 float tempo=0;
 int led1 = 4 ;
 int led2 = 5 ;
void setup() {
  
   pinMode(led1, OUTPUT);
   pinMode(led2, OUTPUT);
  lcd.begin(16,2);
  lcd.backlight();
  myservo.attach(9);



  
  Serial.println("Adafruit MLX90614 test");  
  Serial.begin(9600);
   mlx.begin();
  lcd.clear(); //Use it to clear the LCD Widget
 // lcd.print(0, 0, "Distance in cm");
}

void loop() {
   lcd.setCursor(0, 0);
  Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempC()); 
  lcd.print("Ambient=");
   lcd.print(mlx.readAmbientTempC());
  lcd.print(" C");
   lcd.setCursor(0,1);
  Serial.print("*C\tObject = "); Serial.print(mlx.readObjectTempC()); Serial.println("*C");
   lcd.print("Object =");
  tempo=mlx.readObjectTempC();
   lcd.print(tempo);
    lcd.print(" C");
  Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempF()); 
  Serial.print("*F\tObject = "); Serial.print(mlx.readObjectTempF()); Serial.println("*F");
  Serial.println();
  delay(500);
 
  int pos = 0;
  int po = 90 ;

  int sensorValue = analogRead(A0);
  Serial.println(sensorValue);
  delay(100); 
  Serial.print("Ambient = "); 
  Serial.print(mlx.readAmbientTempC()); 
  Serial.print("*C\tObject = "); 
  Serial.print(mlx.readObjectTempC()); Serial.println("*C");                  
  //Serial.print("Ping: ");
  //Serial.print(sonar.ping_cm());
  //Serial.println("cm");
  
 if ((mlx.readObjectTempC() >= 33.5) && (mlx.readObjectTempC() <= 37.5)){
    Serial.println("อุณหภูมิ > 34.5   และ   <= 37.5 ")  ; 
    Serial.println("color green ")  ;
   myservo.write(0);
      digitalWrite(led1, HIGH);
      digitalWrite(led2, LOW);
      delay(100);
      myservo.write(pos);

      delay(5000);
      myservo.write(po);
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
     }else if (mlx.readObjectTempC() >= 37.5){
       Serial.println("อุณหภูมิ >  37.5 ")  ; 
       Serial.println("color red ")  ;
         myservo.write(po);
      delay(1000);

      digitalWrite(led1, LOW);
      digitalWrite(led2, HIGH);

      delay(1000);

      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
     }
      else{
    Serial.println("อุณหภูมิอื่นๆ : ")  ; 
    Serial.print(mlx.readObjectTempC());
    Serial.println("color red ")  ; 
    
  }
   // myservo.write(pos);
    delay(1000);
  }
