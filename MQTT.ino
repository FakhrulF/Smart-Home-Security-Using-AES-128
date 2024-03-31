// #include <WiFi.h>
// #include <PubSubClient.h>
// #include "AESLib.h"
// #include <SPI.h>
// #include <MFRC522.h>
// #include <DHT.h>
// #include <ArduinoJson.h>

// #define SS_PIN 5    // ESP32 pin GIOP5
// #define RST_PIN 27  // ESP32 pin GIOP27

// #define DHTPIN 4
// #define DHTTYPE DHT22

// const int buttonPin = 13;  // the number of the pushbutton pin
// const int buttonPin2 = 12; // limit switch
// const int relay1 = 22;  // the number of the DL pin
// // variables will change:
// int buttonState = 0;  // variable for reading the pushbutton status
// int buttonState2 = 0;

// MFRC522 mfrc522(SS_PIN, RST_PIN);

// DHT dht(DHTPIN, DHTTYPE);


// unsigned long sekarang = 0;
// unsigned long interval = 10000;


// #define BUILTIN_LED 13
// const char* ssid = "wwe";
// const char* password = "Eulis!@#456";
// const char* mqtt_server = "192.168.1.14";

// WiFiClient espClient;
// PubSubClient client(espClient);
// unsigned long lastMsg = 0;
// #define MSG_BUFFER_SIZE (50)
// char msg[MSG_BUFFER_SIZE];
// int value = 0;

// AESLib aesLib;

// char cleartext[256];
// char ciphertext[512];

// // AES Encryption Key
// byte aes_key[] = { 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30 };

// // General initialization vector (you must use your own IV's in production for full security!!!)
// byte aes_iv[N_BLOCK] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

// unsigned long loopcount = 0;
// byte enc_iv[N_BLOCK] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }; // iv_block gets written to, provide own fresh copy...
// byte dec_iv[N_BLOCK] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

// void setup_wifi() {

// delay(10);
// // We start by connecting to a WiFi network
// Serial.println();
// Serial.print("Connecting to ");
// Serial.println(ssid);

// WiFi.mode(WIFI_STA);
// WiFi.begin(ssid, password);

// while (WiFi.status() != WL_CONNECTED) {
// delay(500);
// Serial.print(".");
// }

// randomSeed(micros());

// Serial.println("");
// Serial.println("WiFi connected");
// Serial.println("IP address: ");
// Serial.println(WiFi.localIP());
// }

// void callback(char* topic, byte* payload, unsigned int length) {
// Serial.print("Message arrived [");
// Serial.print(topic);
// Serial.print("] ");
// for (int i = 0; i < length; i++) {
// Serial.print((char)payload[i]);
// }
// Serial.println();

// // Switch on the LED if an 1 was received as first character
// if ((char)payload[0] == '1') {
// digitalWrite(BUILTIN_LED, LOW); // Turn the LED on (Note that LOW is the voltage level
// // but actually the LED is on; this is because
// // it is active low on the ESP-01)
// } else {
// digitalWrite(BUILTIN_LED, HIGH); // Turn the LED off by making the voltage HIGH
// }
// }

// void reconnect() {
// // Loop until we're reconnected
// while (!client.connected()) {
// Serial.print("Attempting MQTT connection...");
// // Create a random client ID
// String clientId = "ESP8266Client-";
// clientId += String(random(0xffff), HEX);
// // Attempt to connect
// if (client.connect(clientId.c_str())) {
// Serial.println("connected");
// // Once connected, publish an announcement...
// client.publish("topic/smarthome/testing/aes", "Hello ini testing AES Encryption");
// // ... and resubscribe
// client.subscribe("topic/smarthome/testing/aes/sub");
// } else {
// Serial.print("failed, rc=");
// Serial.print(client.state());
// Serial.println(" try again in 5 seconds");
// // Wait 5 seconds before retrying
// delay(5000);
// }
// }
// }

// String encrypt_impl(char* msg, byte iv[]) {
// int msgLen = strlen(msg);
// char encrypted[2 * msgLen] = { 0 };
// aesLib.encrypt64((const byte*)msg, msgLen, encrypted, aes_key, sizeof(aes_key), iv);
// return String(encrypted);
// }

// String decrypt_impl(char* msg, byte iv[]) {
// int msgLen = strlen(msg);
// char decrypted[msgLen] = { 0 }; // half may be enough
// aesLib.decrypt64(msg, msgLen, (byte*)decrypted, aes_key, sizeof(aes_key), iv);
// return String(decrypted);
// }

// // Generate IV (once)
// void aes_init() {
// Serial.println("gen_iv()");
// aesLib.gen_iv(aes_iv);
// }

// void setup() {
// pinMode(BUILTIN_LED, OUTPUT); // Initialize the BUILTIN_LED pin as an output
// Serial.begin(115200);
// setup_wifi();
// client.setServer(mqtt_server, 1883);
// client.setCallback(callback);
// aes_init();
// aesLib.set_paddingmode(paddingMode::CMS);


// char b64in[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

// char b64out[base64_enc_len(sizeof(aes_iv))];
// base64_encode(b64out, b64in, 16);

// char b64enc[base64_enc_len(10)];
// base64_encode(b64enc, (char*)"0123456789", 10);

// char b64dec[base64_dec_len(b64enc, sizeof(b64enc))];
// base64_decode(b64dec, b64enc, sizeof(b64enc));




// dht.begin();
// SPI.begin();         // init SPI bus
//   mfrc522.PCD_Init();  // init MFRC522

//   mfrc522.PCD_DumpVersionToSerial();
//   Serial.println(F("Scan PICC to see UID"));

//   pinMode(buttonPin, INPUT_PULLUP);
//   pinMode(buttonPin2, INPUT_PULLUP);
//   pinMode(relay1, OUTPUT);




// // tutup
// }
// char UID[50];
// char UID1[] = "85: 0E: 00: 37";
// char UID2[] = "85:0E:00:37";
// int indeks = 0;

// void bacarfid() {
//   if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial())
//     return;
//   Serial.print(F("Card UID: "));
//   indeks = 0;
// for (byte i = 0; i < mfrc522.uid.size; i++) {
//     if (i > 0) {
//         UID[indeks++] = ':';
//     }
//     if (mfrc522.uid.uidByte[i] < 0x10) {
//         UID[indeks++] = '0';
//     }
//     indeks += sprintf(UID + indeks, "%X", mfrc522.uid.uidByte[i]);
// }
// UID[indeks] = '\0';

//   Serial.print(UID);
//   Serial.println();
//   mfrc522.PICC_HaltA();
//   delay(10);
  
//   if (strcmp(UID, UID1) == 0 || strcmp(UID, UID2) == 0) {
//     Serial.println(" || akses oke");
//     digitalWrite(relay1, HIGH);
//   StaticJsonDocument<200> doc;
//   doc["key"] = 1;
//   doc["uid"] = UID;
  

//   String jsonString;
//   serializeJsonPretty(doc, jsonString);
//   Serial.println(jsonString); // Print the JSON string for debugging
//   //encryption
// String encrypted = encrypt_impl(UID, enc_iv);
// sprintf(ciphertext, "%s", encrypted.c_str());
// Serial.print("Ciphertext: ");
// Serial.println(encrypted);
// Serial.print("UID: ");
// Serial.println(UID);
//     client.publish("topic/smarthome/testing/aes", encrypted.c_str());

//   } 
// }


// void loop() {
// bacarfid();
// if (!client.connected()) {
// reconnect();
// }
// client.loop();

// unsigned long now = millis();
// if (now - lastMsg > 2000) {
// lastMsg = now;
// ++value;
// printf(msg, MSG_BUFFER_SIZE);


// }
// }