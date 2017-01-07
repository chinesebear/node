/**
 *
 *
 * Pins:
 * Hardware SPI:
 * MISO -> 12
 * MOSI -> 11
 * SCK -> 13
 *
 * Configurable:
 * CE -> 8
 * CSN -> 7
 *
 */

#include <SPI.h>
#include "RF24.h"
#include <EEPROM.h>

#define EEPROM_PHY_ADDR_START 0
#define RF24_PAYLOAD 32

RF24 radio(7,8);
byte LocalPhyAddress[5];
byte RemotePhyAddress[5];
const byte BroadCastAddress[5]={0x00,0x00,0x00,0x00,0x00};
byte data[RF24_PAYLOAD];

int SendAck(void)
{
  Serial.print('B');//ack
  return 0;
}
int UpdateLocalPhyAddress(void)
{
  int iRet;
  Serial.setTimeout(1000);// 1000ms timeout
  iRet = Serial.readBytes(LocalPhyAddress,5);
  if(iRet <  5) return (-1);
  EEPROM.update(EEPROM_PHY_ADDR_START, LocalPhyAddress[0]);
  EEPROM.update(EEPROM_PHY_ADDR_START+1, LocalPhyAddress[1]);
  EEPROM.update(EEPROM_PHY_ADDR_START+2, LocalPhyAddress[2]);
  EEPROM.update(EEPROM_PHY_ADDR_START+3, LocalPhyAddress[3]);
  EEPROM.update(EEPROM_PHY_ADDR_START+4, LocalPhyAddress[4]);
  SendAck();
  return 0;
}
int ReadLocalPhyAddress(void)
{
  int iRet;
  SendAck();
  Serial.write(EEPROM.read(EEPROM_PHY_ADDR_START));
  Serial.write(EEPROM.read(EEPROM_PHY_ADDR_START+1));
  Serial.write(EEPROM.read(EEPROM_PHY_ADDR_START+2));
  Serial.write(EEPROM.read(EEPROM_PHY_ADDR_START+3));
  Serial.write(EEPROM.read(EEPROM_PHY_ADDR_START+4));
  return 0;
}
/*##################################################################################################*/
void setup(){
  Serial.begin(115200); 

  LocalPhyAddress[0] = EEPROM.read(EEPROM_PHY_ADDR_START);
  LocalPhyAddress[1] = EEPROM.read(EEPROM_PHY_ADDR_START+1);
  LocalPhyAddress[2] = EEPROM.read(EEPROM_PHY_ADDR_START+2);
  LocalPhyAddress[3] = EEPROM.read(EEPROM_PHY_ADDR_START+3);
  LocalPhyAddress[4] = EEPROM.read(EEPROM_PHY_ADDR_START+4);
  memcpy( RemotePhyAddress,LocalPhyAddress,5);
  RemotePhyAddress[0] = 0x00;
 
  radio.openWritingPipe(RemotePhyAddress);
  radio.openReadingPipe(0,BroadCastAddress);
  radio.openReadingPipe(1,LocalPhyAddress);
  #if 0
  radio.begin();
  #endif
}

void loop(){
   
  #if 0
  if( radio.available())
  {
                                                                    // Variable for the received timestamp
      while (radio.available())                                      // While there is data ready
      {                                   
        radio.read( data, RF24_PAYLOAD);             // Get the payload
      }
     
      radio.stopListening();                                        // First, stop listening so we can talk   
      radio.write( data, RF24_PAYLOAD);              // Send the final one back.      
      radio.startListening();                                       // Now, resume listening so we catch the next packets.     
   }
   #endif
   //delay(1000);
  /****************** Change Roles via Serial Commands ***************************/
  if ( Serial.available() )
  {
    char c = toupper(Serial.read());
    switch(c)
    {
      case 'A':
        SendAck();
        break;
      case 'W':
        UpdateLocalPhyAddress();
        break;
      case 'R':
        ReadLocalPhyAddress();
        break;
      default:
        break;
    }
  }


}
