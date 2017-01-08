
#include <EEPROM.h>

#define EEPROM_PHY_ADDR_START 0

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
  LocalPhyAddress[0] = EEPROM.read(EEPROM_PHY_ADDR_START);
  LocalPhyAddress[1] = EEPROM.read(EEPROM_PHY_ADDR_START+1);
  LocalPhyAddress[2] = EEPROM.read(EEPROM_PHY_ADDR_START+2);
  LocalPhyAddress[3] = EEPROM.read(EEPROM_PHY_ADDR_START+3);
  LocalPhyAddress[4] = EEPROM.read(EEPROM_PHY_ADDR_START+4);
  Serial.write(LocalPhyAddress,5);
  return 0;
}

int GetAddress(void)
{
  LocalPhyAddress[0] = EEPROM.read(EEPROM_PHY_ADDR_START);
  LocalPhyAddress[1] = EEPROM.read(EEPROM_PHY_ADDR_START+1);
  LocalPhyAddress[2] = EEPROM.read(EEPROM_PHY_ADDR_START+2);
  LocalPhyAddress[3] = EEPROM.read(EEPROM_PHY_ADDR_START+3);
  LocalPhyAddress[4] = EEPROM.read(EEPROM_PHY_ADDR_START+4);
  memcpy( RemotePhyAddress,LocalPhyAddress,5);
  RemotePhyAddress[0] = 0x00;
  return 0;
}
