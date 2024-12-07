#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>

//Blynk Config
#define BLYNK_TEMPLATE_ID "TMPL6hrV-kNLf"
#define BLYNK_TEMPLATE_NAME "ProyekAkhirIOT"
#define BLYNK_AUTH_TOKEN "mcZESjQPRAC1Pi2mAwtbH-GLQhVRYVvf"
#define BLYNK_PRINT Serial

#include <BlynkSimpleEsp32.h>

//Wifi
char ssid[] = "fanculo"; //Nama WiFi yang digunakan
char pass[] = "00000000"; //Password WiFi yang digunakan

//Components
#define LED 2

int led_state = 0; //Default

BLYNK_WRITE(V0) {
  int led_state = param.asInt();
  if (led_state == 1) {
    digitalWrite(LED, HIGH);
    Serial.println("ON");
  } else {
    digitalWrite(LED, LOW);
    Serial.println("OFF");
  }
}




void setup() {
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  //Pin Declaration
  pinMode(LED, OUTPUT);
}

void loop() {
  Blynk.run();
}
