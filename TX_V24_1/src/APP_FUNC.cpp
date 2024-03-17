
/*======================================================
              Include Files
========================================================*/
#include "APP_FUNC.h"
/*======================================================*/

/*======================================================
              VARIABLES DECLARATIONS
========================================================*/
static DataRead_typedef Read_Button_Potentionmeter;
static ChannelData_Typedef Data_Send;
static RF24 radio(CE, CSN);

static SimpleKalmanFilter KALMAN_1(4, 2, 0.01);
static SimpleKalmanFilter KALMAN_2(4, 2, 0.01);
static SimpleKalmanFilter KALMAN_3(4, 2, 0.01);
static SimpleKalmanFilter KALMAN_4(4, 2, 0.01);
static SimpleKalmanFilter KALMAN_5(4, 2, 0.01);
static SimpleKalmanFilter KALMAN_6(4, 2, 0.01);

/*======================================================*/

/*======================================================
              LOCAL FUNCTION
========================================================*/

static void F_Peripheral_Init(void)
{
  pinMode(X1,INPUT);
  pinMode(Y1,INPUT);
  pinMode(X2,INPUT);
  pinMode(Y2,INPUT);
  pinMode(BienTro,INPUT);
  pinMode(Switch_3POS,INPUT_PULLUP);
  pinMode(Button_1,INPUT_PULLUP);
  pinMode(Button_2,INPUT_PULLUP);
  pinMode(Switch_1,INPUT_PULLUP);
  pinMode(COI,OUTPUT);

  digitalWrite(COI,LOW);
  delay(100);
  digitalWrite(COI,HIGH);
  delay(100);
  digitalWrite(COI,LOW);
  delay(100);
  digitalWrite(COI,HIGH);
}

static volatile void F_PrintDataPeri(void)
{
  char DataPrint[100];
  sprintf(DataPrint,"X1: %d - Y1: %d - X2: %d - Y2: %d - Pote: %d - SW3: %d - BT1: %d - BT2: %d - SW1: %d\n", 
          Read_Button_Potentionmeter.u16_X1, Read_Button_Potentionmeter.u16_Y1,
          Read_Button_Potentionmeter.u16_X2, Read_Button_Potentionmeter.u16_Y2,
          Read_Button_Potentionmeter.u16_Bientro, Read_Button_Potentionmeter.u16_Switch,
          Read_Button_Potentionmeter.u8_Button1, Read_Button_Potentionmeter.u8_Button2, Read_Button_Potentionmeter.u8_ButtonMode);
  Serial.print(DataPrint);
}

static volatile void F_PrintDataSend(void)
{
  char DataPrint[100];
  sprintf(DataPrint,"CH1: %d - CH2: %d - CH3: %d - CH4: %d - CH5: %d - CH6: %d - CH7: %d - CH8: %d \n", 
          Data_Send.CH1, Data_Send.CH2, Data_Send.CH3, Data_Send.CH4, Data_Send.CH5, Data_Send.CH6, Data_Send.CH7, Data_Send.CH8);
  Serial.print(DataPrint);
}

static void F_ReadButton(void)
{
  Read_Button_Potentionmeter.u16_X1 = analogRead(X1);
  Read_Button_Potentionmeter.u16_X1 = KALMAN_1.updateEstimate((float)Read_Button_Potentionmeter.u16_X1);

  Read_Button_Potentionmeter.u16_Y1 = analogRead(Y1);
  Read_Button_Potentionmeter.u16_Y1 = KALMAN_2.updateEstimate((float)Read_Button_Potentionmeter.u16_Y1);

  Read_Button_Potentionmeter.u16_X2 = analogRead(X2);
  Read_Button_Potentionmeter.u16_X2 = KALMAN_3.updateEstimate((float)Read_Button_Potentionmeter.u16_X2);

  Read_Button_Potentionmeter.u16_Y2 = analogRead(Y2);
  Read_Button_Potentionmeter.u16_Y2 = KALMAN_4.updateEstimate((float)Read_Button_Potentionmeter.u16_Y2);

  Read_Button_Potentionmeter.u16_Bientro = analogRead(BienTro);
  Read_Button_Potentionmeter.u16_Bientro = KALMAN_5.updateEstimate((float)Read_Button_Potentionmeter.u16_Bientro);

  Read_Button_Potentionmeter.u16_Switch = analogRead(Switch_3POS);
  Read_Button_Potentionmeter.u16_Switch = KALMAN_6.updateEstimate((float)Read_Button_Potentionmeter.u16_Switch);

  Read_Button_Potentionmeter.u8_Button1 = digitalRead(Button_1);
  Read_Button_Potentionmeter.u8_Button2 = digitalRead(Button_2);
  Read_Button_Potentionmeter.u8_ButtonMode = digitalRead(Switch_1);

  // F_PrintDataPeri();
}

static void F_ConvertData(void)
{
  F_ReadButton();

  Data_Send.CH1 = map(Read_Button_Potentionmeter.u16_X1,0,1023,0,255);
  Data_Send.CH2 = map(Read_Button_Potentionmeter.u16_Y1,0,1023,0,255);
  Data_Send.CH4 = map(Read_Button_Potentionmeter.u16_X2,0,1023,0,255);
  Data_Send.CH5 = map(Read_Button_Potentionmeter.u16_Bientro,0,1023,0,255);

  if(Read_Button_Potentionmeter.u8_ButtonMode == MODE_FULL)
  {
    Data_Send.CH3 = map(Read_Button_Potentionmeter.u16_Y2,0,1023,0,255);
  }
  else 
  {
    if(Read_Button_Potentionmeter.u16_Y2>=600) 
    {
      if(Data_Send.CH3<255) Data_Send.CH3+=1;
    }
    else if(Read_Button_Potentionmeter.u16_Y2<=400)
    {
      if(Data_Send.CH3>0) Data_Send.CH3-=1;
    }
    else {}
  }

  if(Read_Button_Potentionmeter.u16_Switch>=200 && Read_Button_Potentionmeter.u16_Switch<=300) Data_Send.CH6=125;
  if(Read_Button_Potentionmeter.u16_Switch>=600 && Read_Button_Potentionmeter.u16_Switch<=700) Data_Send.CH6=0;
  if(Read_Button_Potentionmeter.u16_Switch>=500 && Read_Button_Potentionmeter.u16_Switch<=600) Data_Send.CH6=255;

  if(Read_Button_Potentionmeter.u8_Button1==0) Data_Send.CH7=255;
  else Data_Send.CH7=0;

  if(Read_Button_Potentionmeter.u8_Button2==0) 
  {
    if(Data_Send.CH8==255) Data_Send.CH8=0;
    else Data_Send.CH8=255;
    delay(200);
  }

  F_PrintDataSend();
}

ISR (TIMER1_OVF_vect) 
{
  F_ConvertData();
  TCNT1 = 59286u;
}

static void TIMER1_Init(void) /* 25ms */
{
  cli(); 
  TCCR1A = 0;
  TCCR1B = 0;
  TIMSK1 = 0;
  TCCR1B |= (1u<<1u) | (1u<<0u); 
  TCNT1 = 59286u;
  TIMSK1 = (1u<<0u);
  sei();    
}

static void F_RF_INIT(void)
{
  while (!radio.begin()) 
  {
    digitalWrite(COI,LOW);
  } 
  digitalWrite(COI,HIGH);
  
  radio.openWritingPipe(RX_ADDRESS);
  radio.setPALevel(RF24_PA_MAX,1); 
  radio.setChannel(RF_CHANNEL);                  
  radio.setDataRate(RF24_250KBPS);                              
  radio.stopListening(); 
}

static void F_RF_SEND(void)
{
  radio.write(&Data_Send, sizeof(Data_Send));
}

/*======================================================*/

/*======================================================
              APP MAIN
========================================================*/
void F_Init(void)
{
  Serial.begin(115200);
  
  F_Peripheral_Init();
  TIMER1_Init();
  F_RF_INIT();

}

void F_Main(void)
{
  F_RF_SEND();
  delay(2);
}
/*======================================================*/
