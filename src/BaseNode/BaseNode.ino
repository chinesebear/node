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
#include "node.h"

#define RF24_PAYLOAD  32
RF24 radio(7,8);
byte data[RF24_PAYLOAD];
byte channel;

/*##################################################################################################*/
void setup(){
  Serial.begin(115200); 
  GetAddress();
  radio.begin();
  channel = 76;
  radio.setPALevel(RF24_PA_LOW);
  radio.setChannel(channel);
  radio.openWritingPipe(RemotePhyAddress);
  radio.openReadingPipe(0,BroadCastAddress);
  radio.openReadingPipe(1,LocalPhyAddress);
  radio.startListening();
}

void loop(){
   
  #if 1
  if( radio.available())
  {
                                                                    // Variable for the received timestamp
      while (radio.available())                                      // While there is data ready
      {                                   
        radio.read( data, RF24_PAYLOAD);             // Get the payload
      }
      radio.stopListening();                                        // First, stop listening so we can talk   
      BlockPorcess(data,data); 
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
