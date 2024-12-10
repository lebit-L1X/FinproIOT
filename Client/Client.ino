#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// Blynk Config
#define BLYNK_TEMPLATE_ID "TMPL6hrV-kNLf"
#define BLYNK_TEMPLATE_NAME "ProyekAkhirIOTClient"
#define BLYNK_AUTH_TOKEN "mcZESjQPRAC1Pi2mAwtbH-GLQhVRYVvf"
#define BLYNK_PRINT Serial

#include <BlynkSimpleEsp32.h>

// WiFi
char ssid[] = "E COST LT 3";  // WiFi Name
char pass[] = "Agustus2024";  // WiFi Password


// MQTT
const char* mqtt_server = "w7a84bcb.ala.eu-central-1.emqxsl.com";
const int mqtt_port = 8883;
const char* mqtt_username = "lmelodus";
const char* mqtt_password = "miaobestfriend";
const char* topic_publish_ir = "camfootage/frames";


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

// Components
#define LED 2

// MQTT Client Setup
WiFiClientSecure wifiClientSecure;  // Use WiFiClientSecure for SSL
PubSubClient client(wifiClientSecure);

//Struct for Queue
#define QUEUE_SIZE 10
typedef struct JsonResponseStruct {
  float confidence;
  char message[100];
  bool valid;
} JsonResponse;

// RTOS Declarations
TaskHandle_t QueuetoMQTT;
QueueHandle_t responseQueue;

//HTTP Cam
String capturePath = "http://192.168.100.15:5000/client";
String comparePath = "http://192.168.100.15:5000/compare";

void captureFaceImage() {
  HTTPClient http;
  http.begin(capturePath.c_str());  // Start HTTP request to the server

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

int BLYNK_V0 = 0;  // Default state
int BLYNK_V1 = 0;  // Default state
int has_pic = 0;   //Flag to confirm user has photo
bool isFaceValid = false;

BLYNK_WRITE(V0) {
  BLYNK_V0 = param.asInt();
  if (BLYNK_V0 == 1) {
    digitalWrite(LED, HIGH);  // Turn on LED to indicate camera is capturing
    Serial.println("Capturing Face");
    has_pic = 1;
    // Call the function to capture the image via HTTP GET request
    captureFaceImage();
  } else {
    digitalWrite(LED, LOW);  // Turn off LED if camera state is 0
    Serial.println("OFF");
  }
}


BLYNK_WRITE(V1) {
  BLYNK_V1 = param.asInt();
  if (BLYNK_V1 == 1) {
    if (has_pic == 1) {
      Serial.println("Comparing Face...");
      HTTPClient http;
      http.begin(comparePath.c_str());  // Start HTTP request to the server

      int httpResponseCode = http.GET();  // Send the GET request
      if (httpResponseCode > 0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);

        String payload = http.getString();  // Get the response payload
        Serial.println(payload);

        
        if (httpResponseCode == 500){
          return;
        }

        // Parse JSON response
        const size_t capacity = JSON_OBJECT_SIZE(3) + 40;  // Adjust capacity as needed
        DynamicJsonDocument doc(capacity);
        DeserializationError error = deserializeJson(doc, payload);

        if (!error) {
          // Dynamically allocate memory for JsonResponse using pvPortMalloc
          JsonResponse* response = (JsonResponse*)pvPortMalloc(sizeof(JsonResponse));
          if (response == NULL) {
            Serial.println("Memory allocation failed!");
            vPortFree(response);
            return;
          }

          // Populate the struct with parsed data
          response->confidence = doc["confidence"];
          strcpy(response->message, doc["message"]);
          response->valid = doc["valid"];

          //Attempt to enqueue the response
          if (xQueueSend(responseQueue, &response, portMAX_DELAY) == pdPASS) {
            Serial.println("Response enqueued successfully");
          } else {
            Serial.println("Failed to enqueue response, freeing memory");
            vPortFree(response);
          }

        } else {
          Serial.print("JSON Parse Error: ");
          Serial.println(error.c_str());
        }
      } else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      http.end();
    } else {
      Serial.println("No pics have been submitted");
    }
    has_pic = 0;
  }
}

void reconnect() {
  Serial.print("Attempting MQTT connection...");
  if (client.connect("ESP32Client", mqtt_username, mqtt_password)) {
    Serial.println("connected");
  } else {
    Serial.print("failed, rc=");
    Serial.println(client.state());
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

void publishToMQTTTask(void* param) {
  while (true) {
    if (!client.connected()) {
      reconnect();
    }

    JsonResponse* response;

    if (xQueueReceive(responseQueue, &response, portMAX_DELAY) == pdPASS) {
      String message = response->valid ? "Access Granted" : "Intruder Alert";

      if (client.publish(topic_publish_ir, message.c_str())) {
        Serial.println("Message published successfully.");
      } else {
        Serial.println("Failed to publish message.");
      }

      // Free the dynamically allocated memory for the response
      vPortFree(response);
    } else {
      Serial.println("Failed to receive response from queue.");
    }
    vTaskDelay(500 / portTICK_PERIOD_MS);
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

  // MQTT Client Setup
  client.setServer(mqtt_server, mqtt_port);
  // client.setCallback(mqttCallback); // for server

  // Set the certificate for SSL connection
  wifiClientSecure.setCACert(ca_cert);

  responseQueue = xQueueCreate(QUEUE_SIZE, sizeof(JsonResponse*));
  if (responseQueue == NULL) {
    Serial.println("Failed to create queue");
  } else {
    Serial.println("Queue Created");
  }

  //Create Task
  xTaskCreate(publishToMQTTTask, "PublishToMQTT", 10000, NULL, 1, NULL);

}


void loop() {
  Blynk.run();
  client.loop();  // Ensure MQTT client is processing incoming/outgoing messages
}
