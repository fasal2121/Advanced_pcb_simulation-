
const int MoteurRelais = 7;  // Pin du relais connecté au moteur
int CapteurHumidite = A0; // pour le capteur de l'humidité du sol

int sec = 580;
int humide = 240;
int state=0;

int latchPin2 = 11;  //Pin conn9ected to ST_CP of 1st 74595
int clockPin2 = 12;  //Pin connected to SH_CP of 1st 74595
int dataPin2 = 13;   //Pin connected to DS of 1st 74595

int latchPin = 3;  //Pin connected to ST_CP of 2nd 74595
int clockPin = 4;  //Pin connected to SH_CP of 2nd 74595
int dataPin = 2;  //Pin connected to DS of 2nd 74595



void setup() {
    Serial.begin(9600);
    pinMode(MoteurRelais, OUTPUT);
    pinMode(CapteurHumidite, INPUT);
    digitalWrite(MoteurRelais, LOW); 

    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(dataPin, OUTPUT);
    
    pinMode(latchPin2, OUTPUT);
    pinMode(clockPin2, OUTPUT);
    pinMode(dataPin2, OUTPUT);
 
}

void loop() {
    int Humidite = analogRead(CapteurHumidite); // lire la valeur retournée par le capteur d'humidité
    int pourcentage_humidite = map(Humidite, sec, humide, 0, 100);
    Serial.println(pourcentage_humidite);
    if (Serial.available() > 0) {
      // Lire la donnée reçue du port série
      int data = Serial.parseInt();
      if (data != 0) state = data;
      Serial.print(data);
    }
    if (state == 1){
        state1_ON();
       
        if (pourcentage_humidite >= 60 && pourcentage_humidite <= 70) {
          digitalWrite(MoteurRelais, HIGH);
        }
        else if (pourcentage_humidite < 60) {
           digitalWrite(MoteurRelais, LOW);
        }
      }
      else if (state == 2){
         state2_ON();
        if (pourcentage_humidite >= 50 && pourcentage_humidite < 60) {
          // Action pour l'état 2
          digitalWrite(MoteurRelais, HIGH);
        }
        else if (pourcentage_humidite < 50){
          digitalWrite(MoteurRelais, LOW);
          }
      }
        
      else if (state == 3){
        state3_ON();
        if (pourcentage_humidite >= 30 && pourcentage_humidite < 50) {
          // Action pour l'état 2
          digitalWrite(MoteurRelais, HIGH);
        }
        else if (pourcentage_humidite < 30){
          digitalWrite(MoteurRelais, LOW);
          
        }
      }
 

    delay(100);


}


void state1_ON() {
  // take the latchPin low so the LEDs don't change while you're sending in bits:     
    digitalWrite(latchPin, LOW);
    //Send 1 1 1 1 1 1 1 0 (254) to Q7 Q6 Q5 Q4 Q3 Q2 Q1 Q0 of 2nd 74595
    //shiftOut(dataPin, clockPin, MSBFIRST, 0x29); //3); // leds rouges
    //shiftOut(dataPin, clockPin, MSBFIRST, 0x62); //3); // leds bleus
    shiftOut(dataPin, clockPin, MSBFIRST, 0x32); //3); // leds vertes
    //Send 1 1 1 1 1 1 1 1 (255) to Q7 Q6 Q5 Q4 Q3 Q2 Q1 Q0 of 1st 74595
    //shiftOut(dataPin, clockPin, MSBFIRST, 0); //3);
    // shift out the bits:    
    digitalWrite(latchPin, HIGH);
          
    // take the latchPin low so the LEDs don't change while you're sending in bits:    
    digitalWrite(latchPin2, LOW);
    //Send 1 1 1 1 0 1 1 1 (247) to Q7 Q6 Q5 Q4 Q3 Q2 Q1 Q0 of 3rd 74595
    shiftOut(dataPin2, clockPin2, MSBFIRST, 0x00);
    // shift out the bits:  
    digitalWrite(latchPin2, HIGH); 
    
    Serial.println("leds VV ON");

}

void state2_ON() {
   // take the latchPin low so the LEDs don't change while you're sending in bits:     
    digitalWrite(latchPin, LOW);
    //Send 1 1 1 1 1 1 1 0 (254) to Q7 Q6 Q5 Q4 Q3 Q2 Q1 Q0 of 2nd 74595
    shiftOut(dataPin, clockPin, MSBFIRST, 0x59); //3); // leds rouges
    //shiftOut(dataPin, clockPin, MSBFIRST, 0x62); //3); // leds bleus
    //shiftOut(dataPin, clockPin, MSBFIRST, 0x94); //3); // leds vertes
    //Send 1 1 1 1 1 1 1 1 (255) to Q7 Q6 Q5 Q4 Q3 Q2 Q1 Q0 of 1st 74595
    //shiftOut(dataPin, clockPin, MSBFIRST, 0); //3);
    // shift out the bits:    
    digitalWrite(latchPin, HIGH);
          
    // take the latchPin low so the LEDs don't change while you're sending in bits:    
    digitalWrite(latchPin2, LOW);
    //Send 1 1 1 1 0 1 1 1 (247) to Q7 Q6 Q5 Q4 Q3 Q2 Q1 Q0 of 3rd 74595
    shiftOut(dataPin2, clockPin2, MSBFIRST, 0x00);
    // shift out the bits:  
    digitalWrite(latchPin2, HIGH); 
    
    Serial.println("leds RR ON");

}

void state3_ON() {
    // take the latchPin low so the LEDs don't change while you're sending in bits:     
    digitalWrite(latchPin, LOW);
    //Send 1 1 1 1 1 1 1 0 (254) to Q7 Q6 Q5 Q4 Q3 Q2 Q1 Q0 of 2nd 74595
    //shiftOut(dataPin, clockPin, MSBFIRST, 0x29); //3); // leds rouges
    shiftOut(dataPin, clockPin, MSBFIRST, 0x6b); //3); // leds bleus
    //shiftOut(dataPin, clockPin, MSBFIRST, 0x94); //3); // leds vertes
    //Send 1 1 1 1 1 1 1 1 (255) to Q7 Q6 Q5 Q4 Q3 Q2 Q1 Q0 of 1st 74595
    //shiftOut(dataPin, clockPin, MSBFIRST, 0); //3);
    // shift out the bits:    
    digitalWrite(latchPin, HIGH);
          
    // take the latchPin low so the LEDs don't change while you're sending in bits:    
    digitalWrite(latchPin2, LOW);
    //Send 1 1 1 1 0 1 1 1 (247) to Q7 Q6 Q5 Q4 Q3 Q2 Q1 Q0 of 3rd 74595
    shiftOut(dataPin2, clockPin2, MSBFIRST, 0x00);
    // shift out the bits:  
    digitalWrite(latchPin2, HIGH); 
    
    Serial.println("leds BB ON");

}
