
/*=====================================
        FIRMWARE RX 8CH V24.1
=======================================*/

#include "RX_FUNC.h"

/*======================================================
              VARIABLES DECLARATIONS
========================================================*/
ChannelData_Typedef DataRead;
RF24 radio(CE, CSN);
Servo OUTCH1;
Servo OUTCH2;
Servo OUTCH3;
Servo OUTCH4;
Servo OUTCH5;
Servo OUTCH6;
Servo OUTCH7;
Servo OUTCH8;
/*======================================================*/

static void F_PrintDataRead(void)
{
  char DataPrint[100];
  sprintf(DataPrint,"CH1: %d - CH2: %d - CH3: %d - CH4: %d - CH5: %d - CH6: %d - CH7: %d - CH8: %d \n", 
          DataRead.CH1, DataRead.CH2, DataRead.CH3, DataRead.CH4, DataRead.CH5, DataRead.CH6, DataRead.CH7, DataRead.CH8);
  Serial.print(DataPrint);
}

static void F_ServoInit(void)
{
  OUTCH1.attach(PinCH1,500,2500);
  OUTCH2.attach(PinCH2,500,2500);
  OUTCH3.attach(PinCH3,500,2500);
  OUTCH4.attach(PinCH4,500,2500);
  OUTCH5.attach(PinCH5,500,2500);
  OUTCH6.attach(PinCH6,500,2500);
  OUTCH7.attach(PinCH7,500,2500);
  OUTCH8.attach(PinCH8,500,2500);
}

static void F_ControlServo(void)
{
  OUTCH1.write( map(DataRead.CH1,0,255,0,180) );
  OUTCH2.write( map(DataRead.CH2,0,255,0,180) );
  OUTCH3.write( map(DataRead.CH3,0,255,0,180) );
  OUTCH4.write( map(DataRead.CH4,0,255,0,180) );
  OUTCH5.write( map(DataRead.CH5,0,255,0,180) );
  OUTCH6.write( map(DataRead.CH6,0,255,0,180) );
  OUTCH7.write( map(DataRead.CH7,0,255,0,180) );
  OUTCH8.write( map(DataRead.CH8,0,255,0,180) );
}

static void F_RF_INIT(void)
{
  radio.begin();
  radio.openReadingPipe(1,RX_ADDRESS);
  radio.setPALevel(RF24_PA_MIN);
  radio.setChannel(RF_CHANNEL);                  
  radio.setDataRate(RF24_250KBPS);                              
  radio.startListening(); 
}

static void F_RF_READ(void)
{
  if (radio.available()) 
  {
    radio.read(&DataRead, sizeof(DataRead));
    // F_PrintDataRead();
  }
}

/*======================================================
              APP MAIN
========================================================*/
void F_Init(void)
{
  Serial.begin(115200);

  F_ServoInit();
  F_RF_INIT();

}

void F_Main(void)
{
  F_RF_READ();
  F_ControlServo();
}
/*======================================================*/
