// Includes
#include <String.h>
#include <DHT_Async.h>

// Constants
static const int DHT_PIN = 47;
static const byte LOR_MODE = 0;
static const byte LOR_S1ADDRESS = 1;
static const byte LOR_S2ADDRESS = 2;
static const byte LOR_S3ADDRESS = 3;
static const byte LOR_C1ADDRESS = 4;
static const byte LOR_C2ADDRESS = 5;
static const byte LOR_C3ADDRESS = 6;
static const byte LOR_NETWORKID = 4;
static const unsigned long LOR_IPR = 115200;
static const unsigned long LOR_BAND = 915000000;

// Globals
DHT_Async dht_sensor(DHT_PIN, DHT_TYPE_22);

// Functions
static bool get_tandh(float *temp, float *humid) {
    static unsigned long last_timestamp = millis();
    /* Measure once every four seconds. */
    if (millis() - last_timestamp > 4000ul) {
        if (dht_sensor.measure(temp, humid)) {
            last_timestamp = millis();
            return (true);
        }
    }
    return (false);
}

void send_tandh(float t, float h) {
  String text_data = String(LOR_C1ADDRESS) + "," + String(t) + "," + String(h);
  String send_data = "AT+SEND=" + String(LOR_S1ADDRESS) + "," + String(text_data.length()) + "," + text_data;
  Serial.println(send_data);
}

// Setup
void setup() {
  Serial.begin(LOR_IPR);
  Serial.println("AT+IPR=" + String(LOR_IPR));
  Serial.println("AT+ADDRESS=" + String(LOR_C1ADDRESS));
  Serial.println("AT+NETWORKID=" + String(LOR_NETWORKID));
  Serial.println("AT+BAND=" + String(LOR_BAND));
  Serial.println("AT+MODE=" + String(LOR_MODE));
}

// Main
void loop() {
  float temperature, humidity = 0.0;
  if (get_tandh(&temperature, &humidity)) { send_tandh(temperature, humidity); }
}
