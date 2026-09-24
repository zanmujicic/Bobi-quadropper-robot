#include <esp_now.h>
#include <WiFi.h>

// MAC adresa tvog psa
uint8_t broadcastAddress[] = {0x80, 0xF3, 0xDA, 0x62, 0x88, 0xF4};

typedef struct struct_message {
    char command;
} struct_message;

struct_message myData;
esp_now_peer_info_t peerInfo;
bool lastState13 = HIGH;
bool lastState12 = HIGH;
// Pinovi kontrolera
#define JOY_X 34
#define JOY_Y 35
#define BTN_SIT 13      // Komanda 'S'
#define BTN_DANCE 12    // Komanda 'a'
#define BTN_ATTACK 14   // Komanda 'A'
#define BTN_GYRO_OFF 27 // Komanda '0'
#define BTN_GYRO_ON 26  // Komanda '1'
#define BTN_LIGHT_13 33
#define BTN_LIGHT_12 17
#define BTN_NL_25 25
#define BTN_NR_2 15

#define BTN_L13 BTN_LIGHT_13
#define BTN_L12 BTN_LIGHT_12
void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) return;

  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  if (esp_now_add_peer(&peerInfo) != ESP_OK) return;

  pinMode(BTN_SIT, INPUT_PULLUP);
  pinMode(BTN_DANCE, INPUT_PULLUP);
  pinMode(BTN_ATTACK, INPUT_PULLUP);
  pinMode(BTN_GYRO_OFF, INPUT_PULLUP);
  pinMode(BTN_GYRO_ON, INPUT_PULLUP);
  pinMode(BTN_LIGHT_12, INPUT_PULLUP);
  pinMode(BTN_LIGHT_13, INPUT_PULLUP);
  pinMode(BTN_NL_25, INPUT_PULLUP);
  pinMode(4, OUTPUT);
}

void loop() {
  int xVal = analogRead(JOY_X);
  int yVal = analogRead(JOY_Y);
  char cmd = 'S'; 

  // Logika džojstika
  if (yVal < 1000) cmd = 'F';      
  else if (yVal > 3000) cmd = 'B'; 
  else if (xVal < 1000) cmd = 'R'; 
  else if (xVal > 3000) cmd = 'L'; 
   else if (digitalRead(BTN_NL_25) == LOW) cmd = 'X';
  else if (digitalRead(BTN_NR_2) == LOW) cmd = 'Y';
  // Logika dugmadi
  else if (digitalRead(BTN_SIT) == LOW) cmd = 'D';      
  else if (digitalRead(BTN_DANCE) == LOW) cmd = 'a';    
  else if (digitalRead(BTN_ATTACK) == LOW) cmd = 'A';   
  else if (digitalRead(BTN_GYRO_ON) == LOW) {cmd = '1';  digitalWrite(4, HIGH);}  
  else if (digitalRead(BTN_GYRO_OFF) == LOW) {cmd = '0';  digitalWrite(4, LOW); }
  else if (digitalRead(BTN_LIGHT_12) == LOW) cmd = 'T';  
  else if (digitalRead(BTN_LIGHT_13) == LOW) cmd = 'Q'; 
 



  myData.command = cmd;
  esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
  delay(100); 
}