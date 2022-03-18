// DCC декодер для стрелок v.2.00
// Edit Alexmit 11.01.16 and many others after
// DCC reading PIN = 2 (from opto coupler) 

// Подключаем библиотеку DCC Decoder
#include <DCC_Decoder.h>

// Параметры декодера для настройки:
//#define DECODER_ADDRESS_1 1     // Адрес декодера 1 (5-8)
//#define DECODER_ADDRESS_2 2     // Адрес декодера 2 (9-12)

#define DECODER_ADDRESS_1 3     // Адрес декодера 3 (13-16)
#define DECODER_ADDRESS_2 4     // Адрес декодера 4 (17-20)

//Прерывание для DCC библиотеки 
#define kDCC_INTERRUPT 0

#define TURNOUT_DELAY 100 // Задержка на время срабатывания соленоида привода стрелок

///////////////////////////////////////////////////////////////////////////////////////////////////////// 
void setup()//обязательная функция для любого скетча: настраивает программу, запускается 1 раз при старте. 
{  
  Serial.begin(9600); // Debug via terminal window at 9600 or 115200 
  Serial.print("Start decoders ");
  Serial.print(DECODER_ADDRESS_1);
  Serial.print(" and ");
  Serial.println(DECODER_ADDRESS_2);
  
  //Выставляем управляющие пины на вывод: 
  pinMode(3,OUTPUT);
  digitalWrite(3,LOW);
  pinMode(4,OUTPUT);
  digitalWrite(4,LOW);
  pinMode(5,OUTPUT);
  digitalWrite(5,LOW);
  pinMode(6,OUTPUT);
  digitalWrite(6,LOW);
  pinMode(7,OUTPUT);
  digitalWrite(7,LOW);
  pinMode(8,OUTPUT);
  digitalWrite(8,LOW);
  pinMode(9,OUTPUT);
  digitalWrite(9,LOW);
  pinMode(10,OUTPUT);
  digitalWrite(10,LOW);
  pinMode(11,OUTPUT);
  digitalWrite(11,LOW);
  pinMode(12,OUTPUT);
  digitalWrite(12,LOW);
  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);

  // Инициализируем декодер: 

  DCC.SetBasicAccessoryDecoderPacketHandler(BasicAccDecoderPacket_Handler, true); 
  DCC.SetupDecoder(0x00, 0x00, kDCC_INTERRUPT);
  
  // Выставляем стрелки прямо
  BasicAccDecoderPacket_Handler(DECODER_ADDRESS_1, true, 0x00);
  delay(TURNOUT_DELAY);
  BasicAccDecoderPacket_Handler(DECODER_ADDRESS_1, true, 0x03);
  delay(TURNOUT_DELAY);
  BasicAccDecoderPacket_Handler(DECODER_ADDRESS_1, true, 0x05);
  delay(TURNOUT_DELAY);
  BasicAccDecoderPacket_Handler(DECODER_ADDRESS_1, true, 0x07);
  delay(TURNOUT_DELAY);
  BasicAccDecoderPacket_Handler(DECODER_ADDRESS_2, true, 0x00);
  delay(TURNOUT_DELAY);

} 
//////////////////////////////////////////////////////////////////////////////////////// 
void loop()   // Оновная функция, повторяющаяся бесконечно. 
{ 
  DCC.loop(); // постоянно крутим DCC библиотеку, что бы не пропускать пакеты. 
} 
// end of loop   /////////////////////////////////////////////////////////////////////// 

// Обработчик стрелочных пакетов. Эта функция запускается, когда библиотека ловит пакет: 

void BasicAccDecoderPacket_Handler(int address, boolean activate, byte data) 
{ 
Serial.print("    ");
Serial.print(address);
Serial.print(" - ");
Serial.print(data);
Serial.print(" - ");
Serial.println(activate);

  // Обрабатываем адрес стрелки: 
  if (address == DECODER_ADDRESS_1) {// Если адрес в пакете == адресу декодера #1, то обрабатываем
    switch (data) { 
    case 0:
      digitalWrite(3, LOW);  // на всякий случай 
      digitalWrite(4, HIGH); // включаем реле стрелки 
      delay(TURNOUT_DELAY);  // задержка чтобы отработал соленоид
      digitalWrite(4, LOW);  // выключаем реле стрелки
      break;
      
    case 1: 
      digitalWrite(4, LOW); 
      digitalWrite(3, HIGH);
      delay(TURNOUT_DELAY);
      digitalWrite(3, LOW);
      break;
      
    case 2: 
      digitalWrite(5, LOW);
      digitalWrite(6, HIGH);
      delay(TURNOUT_DELAY);
      digitalWrite(6, LOW);
      break;
      
    case 3: 
      digitalWrite(6, LOW);
      digitalWrite(5, HIGH);
      delay(TURNOUT_DELAY);
      digitalWrite(5, LOW);
      break;
      
    case 4: 
      digitalWrite(7, LOW);
      digitalWrite(8, HIGH);
      delay(TURNOUT_DELAY);
      digitalWrite(8, LOW);
      break;
      
    case 5: 
      digitalWrite(8, LOW);
      digitalWrite(7, HIGH);
      delay(TURNOUT_DELAY);
      digitalWrite(7, LOW);
      break;
      
    case 6: 
      digitalWrite(9, LOW);
      digitalWrite(10, HIGH);
      delay(TURNOUT_DELAY);
      digitalWrite(10, LOW);
      break;
      
    case 7: 
      digitalWrite(10, LOW);
      digitalWrite(9, HIGH);
      delay(TURNOUT_DELAY);
      digitalWrite(9, LOW);
      break;
    } 
  } 

  if (address == DECODER_ADDRESS_2) {// Если адрес в пакете == адресу декодера #2, то обрабатываем. 
    switch (data) { 
    case 0:
      digitalWrite(11, LOW);  // на всякий случай 
      digitalWrite(12, HIGH); // включаем реле стрелки 
      delay(TURNOUT_DELAY); 
      digitalWrite(12, LOW);  // выключаем реле стрелки
      break;
      
    case 1: 
      digitalWrite(12, LOW);
      digitalWrite(11, HIGH);
      delay(TURNOUT_DELAY);
      digitalWrite(11, LOW); 
      break;
    } 
  }
}// end of handler 
