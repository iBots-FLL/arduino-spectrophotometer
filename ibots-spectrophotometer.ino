#include <Wire.h>

#include <NeoPixelBrightnessBus.h>
#include <NeoPixelBus.h>
#include <NeoPixelAnimator.h>

#define SLAVE_ADDRESS 0x04

const uint8_t PixelPin = 9;
const uint16_t PixelCount = 1;
NeoPixelBus<NeoRgbFeature, Neo800KbpsMethod> strip(PixelCount, PixelPin);

int lightLevel = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receiveData);
  Wire.onRequest(handleRequest);

  strip.Begin();
  RgbColor color(255, 0, 0);
  strip.SetPixelColor(0, color);  
  strip.Show();
  delay(1000);

  RgbColor color1(0, 255, 0);
  strip.SetPixelColor(0, color1);  
  strip.Show();
  delay(1000);

  RgbColor color2(0, 0, 255);
  strip.SetPixelColor(0, color2);  
  strip.Show();
  delay(1000);
  
  Serial.println("Ready!");

}

void loop() {
  // put your main code here, to run repeatedly:
  delay(100);
}

void handleRequest() {
  Serial.println("Handling request: ");
  lightLevel = analogRead(1);     // read the input pin
  Wire.write(lightLevel);
  Serial.println(lightLevel);             // debug value
}


void receiveData(int byteCount){
  Serial.print("Rcv Data byte count: ");
  Serial.print(byteCount);
  if (byteCount == 3) {
    while(Wire.available()) {
      int red = Wire.read();
      int green = Wire.read();
      int blue = Wire.read();
      Serial.print(" - data received: ");
      Serial.print(red);
      Serial.print(", ");
      Serial.print(green);
      Serial.print(", ");
      Serial.println(blue);
      RgbColor color(red, green, blue);
      strip.SetPixelColor(0, color);
      strip.Show();
    } 
  } else if (byteCount == 2) {
      int num1 = Wire.read();
      int num2 = Wire.read();
//      Serial.print("Num1: ");
//      Serial.print(num1);
//      Serial.print(" Num2: ");
//      Serial.println(num2);
    } 
//  RgbColor color(0, 0, 0);
//  strip.SetPixelColor(0, color);
//  strip.Show();
}

