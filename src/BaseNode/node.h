#define NODE_OK       0
#define NODE_ERR      -1

byte LocalPhyAddress[5];
byte RemotePhyAddress[5];
const byte BroadCastAddress[5]={0x00,0x00,0x00,0x00,0x00};

int SendAck(void);
int ReadLocalPhyAddress(void);
int ReadLocalPhyAddress(void);
int GetAddress(void);
int BlockPorcess(byte* datain, byte* dataout);

