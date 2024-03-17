/*=====================================
        FIRMWARE RX 8CH V24.1
=======================================*/

#ifndef __RX_FUNCTION__
#define __RX_FUNCTION__

/*======================================================
              Include Files
========================================================*/
#include <Arduino.h>
#include <avr/interrupt.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>
/*======================================================*/

/*======================================================
              Defines & Macros
========================================================*/
#define SCK   13
#define MOSI  11
#define MISO  12
#define CE    9
#define CSN   10
#define PINCONNECT  3
#define PinCH1 A0
#define PinCH2 A1
#define PinCH3 A2
#define PinCH4 A3
#define PinCH5 A4
#define PinCH6 A5
#define PinCH7 4
#define PinCH8 5

/* Config RX Address */
#define RX_ADDRESS (39563) /* 0-65536 */
#define RF_CHANNEL (111)    /* 0-124 */

/*======================================================*/

/*======================================================
              ENUMS
========================================================*/
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
/*======================================================*/

/*======================================================
              GLOBAL VARIABLES DECLARATIONS
========================================================*/
/*======================================================*/

/*======================================================
              GLOBAL FUNCTION DECLARATIONS
========================================================*/
void F_Init(void);
void F_Main(void);
/*======================================================*/

#endif /* __RX_FUNCTION__ */


