/*
  Serial Event example

 When new serial data arrives, this sketch adds it to a String.
 When a newline is received, the loop prints the string and
 clears it.

 A good test for this is to try it with a GPS receiver
 that sends out NMEA 0183 sentences.

 Created 9 May 2011
 by Tom Igoe

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/SerialEvent

 */
#include <SoftwareSerial.h>
SoftwareSerial novaSerial(10, 11);
String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete
String texto = "";
int tamanho=0;
int tipo;
float Potencia=0;
float hex;
int conta=0;
int expo=0;
String tint="";

void setup() {
  // initialize serial:
  Serial.begin(9600);
  // reserve 200 bytes for the inputString:
  inputString.reserve(56);
//novaSerial.begin(9600);
}

void loop() {

   while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    tamanho++; ///conta o tamanho da string
    if (inChar == '\n') {
      stringComplete = true;
    }
 
  // print the string when a newline arrives:
  if (stringComplete) {
    // Informação do escopo + Indice
      texto = inputString.substring(24,29);
      texto.replace(" ","");
    Serial.print(" ESCOPO + INDICE = ");
    Serial.print(texto);
    if(texto=="0A02"){
      Serial.println(" Energia Direta");
      tipo=1;
    }
        if(texto=="0A07"){
      Serial.println(" indutivo");
      tipo=2;
    }
        if(texto=="0A0C"){
      Serial.println(" capacitivo");
      tipo=3;
    }
        if(texto=="0A51"){
      Serial.println(" (energia reversa)");
      tipo=4;
    }
    if(texto!="0A51"&&texto!="0A0C"&&texto!="0A07"&&texto!="0A02"){
      tipo=5;
    }
    
    

      texto = inputString.substring(30,tamanho-6);
      texto.replace(" ","");
      conta=texto.length();
      Potencia=0;
      expo=0;
      int i;
      for(i=(conta-1); i > -1; i--){
        tint=texto[i];
        if(tint=="A"){ 
          tint="10";
          }
          if(tint=="B"){ 
          tint="11";
          }
          if(tint=="C"){ 
          tint="12";
          }
          if(tint=="D"){ 
          tint="13";
          }
          if(tint=="E"){ 
          tint="14";
          }
          if(tint=="F"){ 
          tint="15";
          }
        hex=tint.toFloat();
        Potencia= floor(Potencia + hex*pow(16,expo)+0.67);           //floor serve pra truncar o valor -4 do valor total   e 0.67 Soma 4 no valor     
        expo++;
 
      }
          if(tipo==1){
         Serial.print(" CONSUMO (kWh) = ");
        Serial.println(Potencia);
        Serial.println(texto);
  }
              if(tipo==2){
          Serial.print(" CONSUMO(kvarh) = ");
         Serial.println(Potencia);
         Serial.println(texto);
    }
              if(tipo==3){
          Serial.print(" CONSUMO (kvarh) = ");
      Serial.println(Potencia);
      Serial.println(texto);
    }
              if(tipo==4){
          Serial.print(" CONSUMO (kWh) = ");
        Serial.println(Potencia);
        Serial.println(texto);
    }             
          if(tipo==5){
          Serial.print(" CONSUMO INDEFINIDO ");
        Serial.println(Potencia);
        Serial.println(texto);
    }
    

texto="";
inputString = "";
stringComplete = false;
tamanho=0;
}////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////CODIGOS PARA A LEITURA\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
                      //AA 55 01 03 05 07 09 05 0A 02 02 22 22 B3 D0
                      //AA 55 01 03 05 07 09 05 0A 51 01 11 11 06 71
                      //AA 55 01 03 05 07 09 05 0A 07 03 33 33 2E 80
                      //AA 55 01 03 05 07 09 05 0A 0C 04 44 44 FA B3
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  }

}


