 #include "DHT.h"
 #include <LiquidCrystal.h>
 #include <EEPROM.h>
 #define clk, 3
 #define data, 4
 #define DHTPIN, 5
 #define btn, 6  
 #define DHTTYPE DHT11 
 
 DHT dht(DHTPIN, DHTTYPE);
 LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

 byte customChar[] = {
  B00111,B00101,B00111,B00000,B00000,B00000,B00000,B00000,};

 int relay=0; 
 int counter = 0; 
 int State;
 int LastState;  
 int menu = 0;
 int sh;
 int st;
 int st2;
 int timer = 0;
 int reset = 0;
 int hstep;
 int tstep;
 int hmin;
 float st2d;
 float t2;
 float temp;
 float tmin;
 float ts;
 float tsdisplay;
 void setup() { 
   lcd.begin(16, 2);
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("LOADING...");
   lcd.createChar(1, customChar);
   delay(500); 
   pinMode (7, OUTPUT);
   pinMode (6, INPUT_PULLUP);
   pinMode (clk,INPUT_PULLUP);
   pinMode (data,INPUT_PULLUP);   
   Serial.begin (9600);
   dht.begin();
   EEPROM.get(10,sh);
   EEPROM.get(20,st);
   EEPROM.get(30,hstep);
   EEPROM.get(40,tstep);
   EEPROM.get(50,st2);
   // Reads the initial state of the clock pin
   LastState = digitalRead(clk);
    
 } 

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();


   while(digitalRead(6) == LOW)
   {
    delay(500); 
    if(digitalRead(6) == HIGH){ 
  menu ++;
  lcd.clear();
} 

    else{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("writing data");
  EEPROM.put(10,sh);
  EEPROM.put(20,st);
  EEPROM.put(30,hstep);
  EEPROM.put(40,tstep);
  EEPROM.put(50,st2);
  delay(500);
  menu = 0;
  lcd.begin(16, 2);
  lcd.clear();
  lcd.createChar(1, customChar);
  lcd.setCursor(0,0);
  lcd.print("data saved");
  delay(500);

}
    }    
    

if (menu > 5){
  menu = 0;
}
if (menu == 0){
  if (timer > 10000){
  lcd.setCursor(0,0);
  lcd.print("Temp=");
  lcd.print(t);
  lcd.write(1);
  lcd.print("C     ");
  lcd.setCursor(0,1);
  lcd.print("Humidity=");
  lcd.print(h);
  lcd.print("%     "); 
  Serial.println();
  Serial.print(",");
  Serial.print(h);
  Serial.print(",");
  Serial.print(t);
  Serial.print(",");
  Serial.print(relay);
  Serial.print(",");
  timer = 0;
  }
  timer ++;

}
if (menu == 1) {

     lcd.setCursor(0,0);
     lcd.print("SETTINGS:");
     lcd.setCursor(0,1);
     lcd.print("set humidity=");
     lcd.print(sh);
     lcd.print("%    "); 
  
   State = digitalRead(clk); // Reads the "current" state of the clock pin
   // If the previous and the current state of the clock are different, that means a step has occured
   if (State != LastState){     
   // If the data state is different to the clock state, that means the encoder is rotating clockwise
     if (digitalRead(data) != State) { 
       sh ++;
     } else {
       sh --;
     }
     if(sh>100){
      sh = 0;
     }
     if(sh<0){
      sh = 100;
     }
      
   LastState = State; // Updates the previous state of the clock with the current state 
   }
}

if (menu == 2) {

     lcd.setCursor(0,0);
     lcd.print("SETTINGS:");
     lcd.setCursor(0,1); 
     lcd.print("set temp=");
     lcd.print(st);
     lcd.print(".");
     lcd.print(st2);
     lcd.write (1);
     lcd.print("C    "); 
  
   State = digitalRead(clk); // Reads the "current" state of the clock pin
   // If the previous and the current state of the clock are different, that means a step has occured
   if (State != LastState){     
   // If the data state is different to the clock state, that means the encoder is rotating clockwise
     if (digitalRead(data) != State) { 
       st ++;
     } else {
       st --;
     }
     if(st>100){
      st = -20;
     }
     if(st<-20){
      st = 100;
     }
      
   LastState = State; // Updates the previous state of the clock with the current state 
   }
}

if (menu == 3) {

     lcd.setCursor(0,0);
     lcd.print("SETTINGS:");
     lcd.setCursor(0,1); 
     lcd.print("set temp=");
     lcd.print(st);
     lcd.print(".");
     lcd.print(st2);
     lcd.write (1);
     lcd.print("C    "); 
  
   State = digitalRead(clk); // Reads the "current" state of the clock pin
   // If the previous and the current state of the clock are different, that means a step has occured
   if (State != LastState){     
   // If the data state is different to the clock state, that means the encoder is rotating clockwise
     if (digitalRead(data) != State) { 
       st2 ++;
     } else {
       st2 --;
     }
     if(st2>9){
      st2 = 0;
     }
     if(st2<0){
      st2 = 9;
     }
      
   LastState = State; // Updates the previous state of the clock with the current state 
   }
}

    
    if (menu == 4) {

     lcd.setCursor(0,0);
     lcd.print("SETTINGS:");
     lcd.setCursor(0,1);
     lcd.print("humidity step=");
     lcd.print(hstep);
     lcd.print("    "); 
  
   State = digitalRead(clk); // Reads the "current" state of the clock pin
   // If the previous and the current state of the clock are different, that means a step has occured
   if (State != LastState){     
   // If the data state is different to the clock state, that means the encoder is rotating clockwise
     if (digitalRead(data) != State) { 
       hstep ++;
     } else {
       hstep --;
     }
     if(hstep>20){
      hstep = 0;
     }
     if(hstep<0){
      hstep = 20;
     }
      
   LastState = State; // Updates the previous state of the clock with the current state 
   }
}
    
    if (menu == 5) {

     lcd.setCursor(0,0);
     lcd.print("SETTINGS:");
     lcd.setCursor(0,1);
     lcd.print("temp step=");
     lcd.print(tsdisplay);
     lcd.print("    "); 
  
   State = digitalRead(clk); // Reads the "current" state of the clock pin
   // If the previous and the current state of the clock are different, that means a step has occured
   if (State != LastState){     
   // If the data state is different to the clock state, that means the encoder is rotating clockwise
     if (digitalRead(data) != State) { 
       tstep ++;
     } else {
       tstep --;
     }
     if(tstep>200){
      tstep = 0;
     }
     if(tstep<0){
      tstep = 200;
     }
      
   LastState = State; // Updates the previous state of the clock with the current state 
   }
}



ts=tstep;
tsdisplay=ts/10;
hmin=sh-hstep;
tmin=st-ts/10; 

st2d=st2;
t2=st2d/10;
temp=st+t2;
    
if ((h>sh)||(t>temp)){
  relay = 1;
  reset ++;
 }
else if ((h<hmin)&&(t<temp)){
  relay = 0;
  reset = 0;
}

if (relay == 1){
  digitalWrite(7, LOW);
}
if (relay == 0){
  digitalWrite(7, HIGH);
}
if (reset == 1){
  delay(500);
  lcd.begin(16, 2);
  lcd.clear();
  lcd.createChar(1, customChar);
  reset = 2;
}
if (reset == 3){
  reset = 2;
}
}
"# Termostat" 
