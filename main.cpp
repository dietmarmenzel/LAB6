//****************************************************************************
// Universidad del Valle de Guatemala
// BE3015 - Electrónica Digital 2
// Gunther Dietmar Menzel - 19106
// LAB6
//*****************************************************************************

//*****************************************************************************
// Librerías
//*****************************************************************************
//Librería para la pantalla LCD
#include <Arduino.h>
#include <LiquidCrystal.h>

//*****************************************************************************
// Definición de pines
//*****************************************************************************
//Definición de pines para la pantalla LCD
#define d4 14
#define d5 27
#define d6 26
#define d7 25
#define en 12
#define rs 13
//Definición del pin para el potenciómetro
#define pot1 34

//*****************************************************************************
// Prototipos de funciones
//*****************************************************************************

//*****************************************************************************
// Variables Globales
//*****************************************************************************
// Create An LCD Object. Signals: [ RS, EN, D4, D5, D6, D7 ]
LiquidCrystal LCD(rs, en, d4, d5, d6, d7);

int adcRaw;
int voltaje; //Voltaje para el primer potenciómetro
int Potenciometro2=0;
int ContadorBoton1=0;

long LastTime;
long SampleTime = 250;

long LastTime2;
long SampleTime2 = 250;

long LastTime3;
long SampleTime3 = 250;

//*****************************************************************************
// Configuración
//*****************************************************************************
void setup() {
  Serial2.begin(115200); //Configuración serial
  //LCD_Init(rs, en, d4, d5, d6, d7);
  // Initialize The LCD. Parameters: [ Columns, Rows ]
  LCD.begin(16, 2); //Pantalla LCD 16*2
  // Clears The LCD Display

  LastTime = millis();

}

//*****************************************************************************
// Loop Principal
//*****************************************************************************
void loop() {
  if (millis()-LastTime2 >= SampleTime2){
    //Asignando los valores del voltaje, decenas, unidades y decimales
    voltaje = analogReadMilliVolts(pot1) / 10.0; //Voltaje para el potenciómetro 
    voltaje = (voltaje, 0,3300,0,255);
    //Imprimiendo voltaje 
    Serial2.write(voltaje);
    //Serial2.write("\t");
    if (Serial2.available()>=0){
      if (Serial2.read()== '\t' ){
      ContadorBoton1 = Serial2.read();  
      }

          else if(Serial2.read() == '\n'){
      Potenciometro2 = Serial2.read();
      }
    }

    LastTime2=millis();
  }
  if (millis()-LastTime >= SampleTime){
  //Asignando lo que tiene que decir la pantalla LCD
  LCD.clear();
  LCD.print("Rojo:");
  LCD.print("");
  LCD.print("Azul:");
  LCD.print("");
  LCD.print("Verde:");

  LCD.setCursor(1,1);
  LCD.print(voltaje);
  LCD.print("  ");
  LCD.print(Potenciometro2);
  LCD.print("   ");
  LCD.print(ContadorBoton1);

  LastTime=millis();
  }
}