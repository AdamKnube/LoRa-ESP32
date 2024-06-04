// Includes
#include <Math.h>
#include <String.h>

// Constants
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

// Functions

// Setup
void setup() {
  Serial.begin(LOR_IPR);
  Serial.println("Initializing modem...");
  Serial.println("AT+IPR=" + String(LOR_IPR));
  Serial.println("AT+ADDRESS=" + String(LOR_S1ADDRESS));
  Serial.println("AT+NETWORKID=" + String(LOR_NETWORKID));
  Serial.println("AT+BAND=" + String(LOR_BAND));
  Serial.println("AT+MODE=" + String(LOR_MODE));
}

// Main
void loop() {
  String recv;
  if (Serial.available()) {
    recv = Serial.readString();
  }
  if (recv.length() > 0) {     
    String recv_test = "RCV=" + String(LOR_S1ADDRESS) + ",";
    int header = recv.indexOf(recv_test);
    // First we make sure the message is for our address. 
    // Will include broadcast adress in future.
    // Side note: why does client not send its address and network info?
    // Below you see I include it in the response. Not network as is redundant,
    // but makes sense to know your clients, for now. Later we can have client types.
    if (header > 0) {
#ifdef DEBUG_2      
      // This should need no explaining ;)
      Serial.print(recv);
#endif
      // Next we split on the next comma as per RFC the next field must be length.
      String recv_len = recv.substring(header + recv_test.length());
      int recv_length = recv_len.indexOf(",");
      char true_length[recv_length];
      for (int x = 0; x < recv_length; x++) { true_length[x] = recv_len.charAt(x); }
      // I'm sure theres a better way to do that.
      // Shitty way of changing ASCII into Integer.
      // Anyways now we have the length as a proper Integer.
      // Use that last field as a starting point and read that many more things.
      String recv_head = recv_test + String(true_length) + ",";      
      int header = recv.indexOf(recv_head);
      if (header > 0) {
        String the_data = recv.substring(header + recv_head.length(), header + recv_head.length() + atoi(true_length));
        int csplit = the_data.indexOf(",");
        // Okay we split all the header shit off now.
        // Now is my data format: ID, DATA.
        // So first split on the "," to seperate client from data.
        if (csplit > 0) {
          String cid = the_data.substring(0, csplit);
          String data = the_data.substring(csplit + 1);      
          // Now we do different things depending on the ClientID.
          // For now is hardcoded, but will make modular in future.
          if (atoi(cid.c_str()) == LOR_C1ADDRESS) {
            // Client1 is DHT22 sensor
            int dsplit = data.indexOf(",");
            if (dsplit > 0) {
              String temp = data.substring(0, dsplit);
              String humid = data.substring(dsplit + 1);
              Serial.println(String(cid.c_str()) + " - Temperature: " + temp + "deg C, Humidity: " + humid + "%");
            }
          }
        }
      }
    }
  }
}
