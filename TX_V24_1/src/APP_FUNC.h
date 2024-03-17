
/*======================================================
              FIRMWARE TX 8CH V24.1
========================================================*/

#ifndef __APP_FUNCTION__
#define __APP_FUNCTION__

/*======================================================
              Include Files
========================================================*/
#include <Arduino.h>
#include <avr/interrupt.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <SimpleKalmanFilter.h>
/*======================================================*/

/*======================================================
              Defines & Macros
========================================================*/
#define SCK   13
#define MOSI  11
#define MISO  12
#define CE    9
#define CSN   10
#define X1    A0 
#define Y1    A1 
#define X2    A2 
#define Y2    A3 
#define Button_1 5
#define Button_2 6
#define Switch_3POS A5 
#define Switch_1    3
#define COI         2
#define BienTro     A4

/* Config RX Address */
#define RX_ADDRESS (39563) /* 0-65536 */
#define RF_CHANNEL (111)    /* 0-124 */

/*======================================================*/

/*======================================================
              ENUMS
========================================================*/
typedef enum MODE
{
  MODE_FULL,
  MODE_ADD_SUB
}MODE_enum;
/*======================================================*/

/*======================================================
              TYPEDEFS & STRUCTURES
========================================================*/
typedef struct ChannelData
{
  uint8_t CH1; /* Aileron */
  uint8_t CH2; /* Elevator */
  uint8_t CH3; /* Throttle */
  uint8_t CH4; /* Rudder */
  uint8_t CH5; /* Bien tro */
  uint8_t CH6; /* Switch 3 vi tri */
  uint8_t CH7; /* Button phai: nhan nha */
  uint8_t CH8; /* Button trai: nhan tu giu */
}ChannelData_Typedef;

typedef struct DataRead
{
  uint8_t u8_Button1;
  uint8_t u8_Button2;
  uint8_t u8_ButtonMode;
  uint16_t u16_X1;
  uint16_t u16_Y1;
  uint16_t u16_X2;
  uint16_t u16_Y2;
  uint16_t u16_Bientro;
  uint16_t u16_Switch;
}DataRead_typedef;


/*======================================================*/

/*======================================================
              GLOBAL VARIABLES DECLARATIONS
========================================================*/
extern DataRead_typedef Read_Button_Potentionmeter;
/*======================================================*/

/*======================================================
              GLOBAL FUNCTION DECLARATIONS
========================================================*/
void F_Init(void);
void F_Main(void);
/*======================================================*/

#endif /* __APP_FUNCTION__ */

