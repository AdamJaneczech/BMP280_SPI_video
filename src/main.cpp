#include <Arduino.h>
//knihovna SPI
#include <SPI.h>

//definice Chip Select pinu (někdy označován jako Slave Select)
#define CS 10

void setup() {
  Serial.begin(115200);

  //nastavit CS pi jako výstup
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
  //registr "id" - kontrola funkčnosti čipu
  SPI.transfer(0xD0 | 0x80);
  uint8_t recv_test = (uint8_t)SPI.transfer(0xff);
  digitalWrite(CS, HIGH);
  Serial.println(recv_test, HEX);

  while(1);

  digitalWrite(CS, LOW);
  //adresa "ctrl_meas" registru - datasheet str. 25
  SPI.transfer(B01110100);
  //nastavit temperature oversampling (7:5); nastavit pressure oversampling (4:2); nastavit power mode (1:0) - datasheet str. 25
  SPI.transfer((1 << 7) |(1 << 5) | (1 << 4) | (1 << 2) | (1 << 1) | (1 << 0));

  digitalWrite(CS, HIGH);
}

void loop() {
  
}