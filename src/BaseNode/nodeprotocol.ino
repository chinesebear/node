
#define BLOCK_S 0x40
#define BLOCK_R 0x80
#define BLOCK_I 0xC0
#define BLOCK_S_RESQUEST              0x00
#define BLOCK_S_REPLY                 0x01
#define BLOCK_S_CMD_CONNECT           0x00
#define BLOCK_S_CMD_DISCONNECT        0x01
#define BLOCK_S_CMD_WAKEUP            0x02
#define BLOCK_S_CMD_SYNC              0x03
#define BLOCK_S_CMD_LINK              0x04
#define BLOCK_S_CMD_CELL_PARAM        0x05

static byte GetCRC(byte *ptr,int len)
{
  byte crc;
  byte i;
    crc = 0;
    while(len--)
    {
       crc ^= *ptr++;
       for(i = 0;i < 8;i++)
       {
           if(crc & 0x01)
           {
               crc = (crc >> 1) ^ 0x8C;
           }else crc >>= 1;
       }
    }
    return crc;
}

int BlockPorcess(byte* datain, byte* dataout)
{
  byte CTL = *datain;
  byte LEN = *(datain + 1);
  byte CRC = *(datain + LEN + 1);
  byte BlockType;
  byte cmd;
  byte link;// more 1, last 0
  byte reqp;//request 0 , reply 1
  
  BlockType = (CTL&0xC0);
  if(BLOCK_S == BlockType)
  {
    cmd = (CTL&0x1F);
    reqp= (CTL&(1<<5));
    switch(cmd)
    {
      case BLOCK_S_CMD_CONNECT:
            
           break;
      default:
           break;
    }
  }
  else if(BLOCK_R == BlockType)
  {    
    
  }
  else if(BLOCK_I == BlockType)
  {

  }
  else
  {
    // block type error
  }
}
