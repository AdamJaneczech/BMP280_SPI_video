#include <Arduino.h>
//knihovna SPI
#include <SPI.h>

//definice Chip Select pinu (někdy označován jako Slave Select)
#define CS 10

void setup() {
  Serial.begin(115200);

  //nastavit CS pin jako výstup
  pinMode(CS, OUTPUT);
  digitalWrite(CS, HIGH);
  //inicializace komunikace SPI
  SPI.begin();
  //nastavení stylu přenosu na MSB first (Most Significant Bit First)
  SPI.setBitOrder(MSBFIRST);
  //nastavení módu SPI (BMP280 podporuje módy '00' (SPI_MODE0) a '11' (SPI_MODE3))
  SPI.setDataMode(SPI_MODE3);
  //nastavení dělení periody pro CLK na 2 (16 MHz / 2 = 8 MHz pro SPI)
  SPI.setClockDivider(SPI_CLOCK_DIV16);
  //nastavení samplování senzoru
  digitalWrite(CS, LOW);
  //registr "id" - kontrola funkčnosti čipu; pomocí OR ( | ) odesíláme požadavek na čtení z registru
  SPI.transfer(0xD0 | 0x80);
  //pro přenos dat zpět je nutný signál na CLK - odesíláme "prázdný" byte
  uint8_t recv_test = (uint8_t)SPI.transfer(0xff);
  //po ukončení komunikace nastavíme CS pin na stav 1 (HIGH)
  digitalWrite(CS, HIGH);
  //ověříme správnost přijetého ID vytištěním hodnoty přes sériovou linku
  Serial.println(recv_test, HEX);

  while(1);
}

void loop() {
  
}