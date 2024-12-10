#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <HTTPClient.h>


//Blynk Config
#define BLYNK_TEMPLATE_ID "TMPL65XD8BURu"
#define BLYNK_TEMPLATE_NAME "ProyekAkhirIOTServer"
#define BLYNK_AUTH_TOKEN "OiB3vqfrgZiP0djNwhvuJ-_2Ot0Q9fSY"
#include <BlynkSimpleEsp32.h>
WidgetTerminal terminal(V0);

// WiFi
char ssid[] = "E COST LT 3";  // WiFi Name
char pass[] = "Agustus2024";  // WiFi Password


// MQTT
const char* mqtt_server = "w7a84bcb.ala.eu-central-1.emqxsl.com";
const int mqtt_port = 8883;
const char* mqtt_username = "lmelodus";
const char* mqtt_password = "miaobestfriend";
const char* topic_subscribe_ir = "camfootage/frames";  // Topic to subscribe to

// SSL Certificate
const char* ca_cert = R"(
-----BEGIN CERTIFICATE-----
MIIDrzCCApegAwIBAgIQCDvgVpBCRrGhdWrJWZHHSjANBgkqhkiG9w0BAQUFADBh
MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3
d3cuZGlnaWNlcnQuY29tMSAwHgYDVQQDExdEaWdpQ2VydCBHbG9iYWwgUm9vdCBD
QTAeFw0wNjExMTAwMDAwMDBaFw0zMTExMTAwMDAwMDBaMGExCzAJBgNVBAYTAlVT
MRUwEwYDVQQKEwxEaWdpQ2VydCBJbmMxGTAXBgNVBAsTEHd3dy5kaWdpY2VydC5j
b20xIDAeBgNVBAMTF0RpZ2lDZXJ0IEdsb2JhbCBSb290IENBMIIBIjANBgkqhkiG
9w0BAQEFAAOCAQ8AMIIBCgKCAQEA4jvhEXLeqKTTo1eqUKKPC3eQyaKl7hLOllsB
CSDMAZOnTjC3U/dDxGkAV53ijSLdhwZAAIEJzs4bg7/fzTtxRuLWZscFs3YnFo97
nh6Vfe63SKMI2tavegw5BmV/Sl0fvBf4q77uKNd0f3p4mVmFaG5cIzJLv07A6Fpt
43C/dxC//AH2hdmoRBBYMql1GNXRor5H4idq9Joz+EkIYIvUX7Q6hL+hqkpMfT7P
T19sdl6gSzeRntwi5m3OFBqOasv+zbMUZBfHWymeMr/y7vrTC0LUq7dBMtoM1O/4
gdW7jVg/tRvoSSiicNoxBN33shbyTApOB6jtSj1etX+jkMOvJwIDAQABo2MwYTAO
BgNVHQ8BAf8EBAMCAYYwDwYDVR0TAQH/BAUwAwEB/zAdBgNVHQ4EFgQUA95QNVbR
TLtm8KPiGxvDl7I90VUwHwYDVR0jBBgwFoAUA95QNVbRTLtm8KPiGxvDl7I90VUw
DQYJKoZIhvcNAQEFBQADggEBAMucN6pIExIK+t1EnE9SsPTfrgT1eXkIoyQY/Esr
hMAtudXH/vTBH1jLuG2cenTnmCmrEbXjcKChzUyImZOMkXDiqw8cvpOp/2PV5Adg
06O/nVsJ8dWO41P0jmP6P6fbtGbfYmbW0W5BjfIttep3Sp+dWOIrWcBAI+0tKIJF
PnlUkiaY4IBIqDfv8NZ5YBberOgOzW6sRBc4L0na4UU+Krk2U886UAb3LujEV0ls
YSEY1QSteDwsOoBrp+uvFRTp2InBuThs4pFsiv9kuXclVzDAGySj4dzp30d8tbQk
CAUw7C29C79Fv1C5qfPrmAESrciIxpg0X40KPMbp1ZWVbd4=
-----END CERTIFICATE-----
)";

#define LED 2
#define LOCK 16

// MQTT Client Setup
WiFiClientSecure wifiClientSecure;  // Use WiFiClientSecure for SSL
PubSubClient client(wifiClientSecure);


//HTTP Cam
String serverPath = "http://192.168.100.15:5000/server";

void captureFaceImage() {
  HTTPClient http;
  http.begin(serverPath.c_str());  // Start HTTP request to the server

  int httpResponseCode = http.GET();  // Send the GET request
  if (httpResponseCode > 0) {
    // Print the response code and the payload from the server
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    String payload = http.getString();  // Get the response payload
    Serial.println(payload);
  } else {
    // Print error code if request failed
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }

  http.end();  // End the HTTP request
}

int camera_state = 0;  // Default state

BLYNK_WRITE(V1) {
  camera_state = param.asInt();
  if (camera_state == 1) {
    digitalWrite(LED, HIGH);  
    Serial.println("Capturing Face");
    captureFaceImage();
  } else {
    digitalWrite(LED, LOW);  // Turn off LED if camera state is 0
    Serial.println("OFF");
  }
}

void reconnect() {
  Serial.print("Attempting MQTT connection...");
  if (client.connect("ESP32Server", mqtt_username, mqtt_password)) {
    Serial.println("connected");
    // Subscribe to the topic after connecting
    client.subscribe(topic_subscribe_ir);  // Subscribe to the topic
  } else {
    Serial.print("failed, rc=");
    Serial.print(client.state());
    delay(5000);
  }
}

void mqttCallback(char* topic, byte* payload, unsigned int length) {
  String message = String((char*)payload, length);
  // Print the message received
  Serial.print("Message received on topic: ");
  Serial.print(topic);
  Serial.print(" - Message: ");
  Serial.println(message);
  if (message == "Access Granted") {
    digitalWrite(LED, HIGH);
    digitalWrite(LOCK, HIGH);
    Serial.println("LED turned ON");
  } else {
    Serial.println("Intruder Alert. Sending warning to Blynk...");
    terminal.println("Intruder Alert!");
    terminal.flush();  // Ensure the message is sent immediately
  }
}

// Function to set up WiFi connection
void setupWiFi() {
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void newConnectionCallback(uint32_t nodeId) {
  Serial.printf("--> startHere: New Connection, nodeId = %u\n", nodeId);
}

void setup() {
  Serial.begin(115200);

  // Call WiFi setup function
  setupWiFi();

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Pin Declaration
  pinMode(LED, OUTPUT);
  pinMode(LOCK, OUTPUT);

  // MQTT Client Setup
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(mqttCallback);

  // Set the certificate for SSL connection
  wifiClientSecure.setCACert(ca_cert);
}

void loop() {
  Blynk.run();
  if (!client.connected()) {
    reconnect();  // Call reconnect function to ensure MQTT connection
  }
  client.loop();
}
