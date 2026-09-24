#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <esp_now.h>
#include <WiFi.h>

#define I2C_SDA_PIN 21
#define I2C_SCL_PIN 22
#define SERVOMIN  170
#define SERVOMAX  490
bool state13 = false; // Prati stanje pina 13 
bool state12 = false; // Prati stanje pina 12
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);
char receivedChar = 'S';
int senz = 0;

typedef struct struct_message {
    char command;
} struct_message;
struct_message incomingData;

void setServoAngle(uint8_t channel, int angle) {
  if (angle < 0) angle = 0;
  if (angle > 180) angle = 180;
  int pulse = map(angle, 0, 180, SERVOMIN, SERVOMAX);
  pwm.setPWM(channel, 0, pulse);
}

void SSS() {
  setServoAngle(0, 90); setServoAngle(1, 90); setServoAngle(2, 90); setServoAngle(3, 80);
  delay(50);
  setServoAngle(4, 110); setServoAngle(6, 150); setServoAngle(7, 30); setServoAngle(5, 60);
  delay(50);
  setServoAngle(8, 70); setServoAngle(9, 140); setServoAngle(10, 40); setServoAngle(11, 150);
}

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingDataRaw, int len) {
  memcpy(&incomingData, incomingDataRaw, sizeof(incomingData));
  receivedChar = incomingData.command;
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA); // Obavezno za ESP-NOW [cite: 1, 111]
  
  pinMode(2, OUTPUT); 
  pinMode(25, OUTPUT); 
  pinMode(27, INPUT); // Senzor pin [cite: 9, 107]
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  digitalWrite(12, HIGH);
  delay(1000);
  digitalWrite(12, LOW);

  
  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW Init Failed");
    return;
  }
  
  // Registracija callback-a
  esp_now_register_recv_cb(esp_now_recv_cb_t(OnDataRecv));

  Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN); // I2C za PWM driver [cite: 1, 10]
  pwm.begin();
  pwm.setPWMFreq(50); // Servo frekvencija [cite: 10]
  SSS(); // Postavi u početnu pozu [cite: 2, 11]
}

void loop() {
  digitalWrite(2, !digitalRead(27));
  if (digitalRead(27) == LOW && senz == 1) {
    digitalWrite(12, HIGH); tone(25, 1000); delay(100); noTone(25); delay(100);
  }

  switch (receivedChar) {
    case 'F': 

 setServoAngle(0, 90); setServoAngle(1, 90); setServoAngle(2, 90); setServoAngle(3, 80);
  delay(100);
  setServoAngle(4, 140); setServoAngle(6, 180); setServoAngle(7, 20); setServoAngle(5, 40);
  delay(100);
  setServoAngle(8, 70); setServoAngle(9, 140); setServoAngle(10, 40); setServoAngle(11, 150);

    
  // ===== FAZA 1: zadnja lijeva =====
  setServoAngle(1, 105); 
  setServoAngle(2, 80);  
  delay(80);

  setServoAngle(10, 125); 
  delay(80);

  setServoAngle(6, 150);  
  delay(100);

  setServoAngle(10, 45);  
  delay(100);

  // ===== FAZA 2: prednja desna =====
  setServoAngle(0, 80); 
  setServoAngle(3, 100);
  delay(80);

  setServoAngle(9, 80);  
  delay(80);

  setServoAngle(5,70);  
  delay(100);

  setServoAngle(9, 140); 
  delay(100);

  // ===== FAZA 3: zadnja desna =====
  setServoAngle(0, 85); 
  setServoAngle(3, 95);
  delay(80);

  setServoAngle(11, 50); 
  delay(110);

  setServoAngle(7, 40);  
  delay(100);

  setServoAngle(11, 180);
  delay(120);

  // ===== FAZA 4: prednja lijeva =====
  setServoAngle(1, 100); 
  setServoAngle(2, 85);
  delay(80);

  setServoAngle(8, 145); 
  delay(80);

  setServoAngle(4, 110);  
  delay(100);

  setServoAngle(8, 80);  
  delay(100);

  // ===== POVRATAK =====
  setServoAngle(0, 90);
  setServoAngle(1, 90);
  setServoAngle(2, 90);
  setServoAngle(3, 80);

  delay(150);
  SSS();
      break;

    case 'B': 
 // ===== POČETNA STABILIZACIJA =====
setServoAngle(0, 90); 
setServoAngle(1, 90);
setServoAngle(2, 90);
setServoAngle(3, 70);
delay(60);

// ===== FAZA A (FL + BR) =====

// 1. SHIFT TEŽINE (max 2 serva)
setServoAngle(0, 80);
setServoAngle(3, 85);
delay(80);

// 2. PODIGNI FL (2 serva max)
setServoAngle(8, 150);   // FL gore
delay(70);

// 3. POMAKNI FL NAPRIJED (1 servo)
setServoAngle(4, 140);
delay(80);

// 4. SPUSTI FL
setServoAngle(8, 70);
delay(70);

// 5. PODIGNI BR (2 serva max)
setServoAngle(11, 60);
delay(70);

// 6. POMAKNI BR NAPRIJED
setServoAngle(7, 20);
delay(80);

// 7. SPUSTI BR
setServoAngle(11, 140);
delay(80);

// ===== GURANJE TIJELA =====
setServoAngle(4, 110);
setServoAngle(7, 20);
delay(100);


// ===== FAZA B (FR + BL) =====

// 1. SHIFT TEŽINE
setServoAngle(1, 100);
setServoAngle(2, 80);
delay(80);

// 2. PODIGNI FR
setServoAngle(9, 50);
delay(70);

// 3. POMAKNI FR
setServoAngle(5, 40);
delay(80);

// 4. SPUSTI FR
setServoAngle(9, 140);
delay(70);

// 5. PODIGNI BL
setServoAngle(10, 130);
delay(70);

// 6. POMAKNI BL
setServoAngle(6, 180);
delay(80);

// 7. SPUSTI BL
setServoAngle(10, 50);
delay(80);

// ===== GURANJE TIJELA =====
setServoAngle(5, 60);
setServoAngle(6, 160);
delay(100);


// ===== POVRATAK CENTAR =====
setServoAngle(0, 90);
setServoAngle(1, 90);
delay(60);
setServoAngle(2, 90);
setServoAngle(3, 70);
delay(60);


      break;

    case 'L': 
          // ================== FAZA A ==================
// podigni prednju lijevu i zadnju desnu
setServoAngle(8, 130);
setServoAngle(11, 70);
delay(80);

// pomjeri naprijed i blago u lijevo
setServoAngle(4, 150);  // p lijeva
setServoAngle(7, 25);   // z desna
delay(160);

// spusti noge
setServoAngle(8, 80);
setServoAngle(11, 100);
delay(120);

// lagano guranje tijela
setServoAngle(0, 85);   
setServoAngle(3, 95);
delay(100);

// ================== FAZA B ==================
// podigni prednju desnu i zadnju lijevu
setServoAngle(9, 60);
setServoAngle(10, 120);
delay(80);

// pomjeri naprijed i blago u lijevo
setServoAngle(5, 65);   // p desna
setServoAngle(6, 180);  // z lijeva
delay(160);

// spusti noge
setServoAngle(9, 90);
setServoAngle(10, 70);
delay(120);

// guranje tijela
setServoAngle(1, 95);
setServoAngle(2, 85);
delay(100);

// povratak u neutralu
setServoAngle(4, 125);
setServoAngle(5, 30);
setServoAngle(6, 155);
setServoAngle(7, 15);
delay(200);
         SSS();
           
        
      break;

    case 'R': 
         // ================== FAZA A ==================
// podigni prednju desnu i zadnju lijevu
setServoAngle(9, 70);
setServoAngle(10, 120);
delay(100);

// pomjeri naprijed i blago u desno
setServoAngle(5, 55);   // p desna
setServoAngle(6, 165);  // z lijeva
delay(160);

// spusti noge
setServoAngle(9, 90);
setServoAngle(10, 70);
delay(120);

// lagano guranje tijela
setServoAngle(1, 95);
setServoAngle(2, 85);
delay(120);

// ================== FAZA B ==================
// podigni prednju lijevu i zadnju desnu
setServoAngle(8, 130);
setServoAngle(11, 70);
delay(110);

// pomjeri naprijed i blago u desno
setServoAngle(4, 125);  // p lijeva
setServoAngle(7, 15);   // z desna
delay(160);

// spusti noge
setServoAngle(8, 80);
setServoAngle(11, 100);
delay(120);

// guranje tijela
setServoAngle(0, 85);   
setServoAngle(3, 95);
delay(110);

// povratak u neutralu
setServoAngle(4, 150);
setServoAngle(5, 25);
setServoAngle(6, 180);
setServoAngle(7, 30);
delay(200);
       
         
      break;

    case 'a': 
       
  // ===== POČETNA POZA =====
  setServoAngle(0, 90); setServoAngle(1, 90);
  setServoAngle(2, 90); setServoAngle(3, 90);
   delay(60);
  setServoAngle(4, 110); setServoAngle(5, 60);
  setServoAngle(6, 150); setServoAngle(7, 30);
   delay(60);
  setServoAngle(8, 70); setServoAngle(9, 140);
  delay(100);
  setServoAngle(10, 40); setServoAngle(11, 150);
  delay(400);
  SSS();

  // ===== DANCE 1: BODY SWAY L-R =====
  for (int i = 0; i < 2; i++) {
    // lijevo
    setServoAngle(0, 70); setServoAngle(1, 70); delay(90);
    setServoAngle(2, 110); setServoAngle(3, 110);
       
    delay(450);



    // desno
    setServoAngle(0, 110); setServoAngle(1, 110); delay(90);
    setServoAngle(2, 70); setServoAngle(3, 70);
      
    delay(450);
  }

  // ===== DANCE 2: FRONT PAW TAP =====
  // prednja lijeva
  setServoAngle(8, 160); delay(270);
  setServoAngle(4, 120); delay(250);
  setServoAngle(8, 90);  delay(290);
   
  // prednja desna
  setServoAngle(9, 40);  delay(250);
  setServoAngle(5, 50);  delay(270);
  setServoAngle(9, 120); delay(290);

  // ===== DANCE 3: BACK KICK =====
  // zadnja lijeva
  setServoAngle(10, 130); delay(250);
  setServoAngle(6, 160);  delay(250);
  setServoAngle(10, 40);  delay(290);

  // zadnja desna
  setServoAngle(11, 50); delay(220);
  setServoAngle(7, 20);   delay(220);
  setServoAngle(11, 150);delay(290);
     
  // ===== DANCE 4: BOUNCE (čučanj) =====
  for (int i = 0; i < 2; i++) {
    setServoAngle(8, 20); setServoAngle(9, 160);
   
    
    delay(420);

    setServoAngle(8, 90); setServoAngle(9, 90);
    
    
    delay(420);
  }

  SSS();




for (int i = 0; i < 2; i++) {
    // lijevo
    setServoAngle(0, 70); setServoAngle(1, 70);
    
    delay(450);

    // desno
    setServoAngle(0, 110); setServoAngle(1, 110);
  
    delay(470);
  }
  // ===== POVRATAK U STOJ =====
  setServoAngle(8, 180);   //spusta kod lakta
         setServoAngle(9, 0);
         delay(150);
         setServoAngle(10, 10);
         setServoAngle(11, 170);
         delay(150);

         setServoAngle(4, 110);   //vraca na pocetak

         setServoAngle(5, 75);   //vraca na pocetak
        delay(600);   
  SSS();
delay(450);

    // ===== DANCE 1: BODY SWAY L-R =====
  for (int i = 0; i < 3; i++) {
    // lijevo
    setServoAngle(0, 70); setServoAngle(1, 70);
    delay(60);
    setServoAngle(2, 110); setServoAngle(3, 110);
    delay(450);

    // desno
    setServoAngle(0, 110); setServoAngle(1, 110);
    delay(60);
    setServoAngle(2, 70); setServoAngle(3, 70);
    delay(450);
  }

 SSS();

  // ===== POVRATAK U STOJ =====
  setServoAngle(8, 180);   //spusta kod lakta
         setServoAngle(9, 0);
         delay(100);
         setServoAngle(10, 10);
         delay(60);
         setServoAngle(11, 170);
         delay(100);

         setServoAngle(4, 120);   //vraca na pocetak
         delay(60);
         setServoAngle(5, 50);   //vraca na pocetak
        delay(600);   
  SSS();
 


      break;

    case 'A': 
      setServoAngle(8, 0); setServoAngle(9, 170);  setServoAngle(10, 10); delay(200);
       setServoAngle(8, 180); setServoAngle(1, 105); setServoAngle(6, 155); delay(40); setServoAngle(4, 10); delay(510);
      for(int j=0; j<3; j++) { setServoAngle(8, 130); delay(400); setServoAngle(8, 180); delay(400); }
      
      break;



       case 'X': 
       setServoAngle(0, 120);  
         setServoAngle(1, 120); 
         delay(60); 
         setServoAngle(2, 120);  
         setServoAngle(3, 110);  
      
      break;




       case 'Y': 
        setServoAngle(0, 55);  
         setServoAngle(1, 55);  
         delay(50);
         setServoAngle(2, 55);  
         setServoAngle(3, 55);  
      
      break;




    case 'S': SSS(); break;
    case 'D': 
        setServoAngle(8, 180);   //spusta kod lakta
         setServoAngle(9, 0);
         delay(100);
         setServoAngle(10, 10);
         setServoAngle(11, 170);
         delay(100);

         setServoAngle(4, 120);   //vraca na pocetak

         setServoAngle(5, 50);   //vraca na pocetak
    
    ; break;
    case '1': senz=1;break;
    case '0': senz = 0; 
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
    
    break;
    case 'Q': digitalWrite(13, HIGH); break;
    case 'T': digitalWrite(12, HIGH); break;
    

    
  }
}