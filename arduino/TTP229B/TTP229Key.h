#ifndef TTP229KEY_H
#define TTP229KEY_H
#include <SPI.h>

#if 0
#define DEBUG_BUTTON16(a) (a)
#else
#define DEBUG_BUTTON16(a)
#endif

#if 1
#define DEBUG_STATUS(a) (a)
#else
#define DEBUG_STATUS(a)
#endif


#pragma pack(push, 0)

// TBD: Replace with proper interrupt pin macros. It does not seem to be defined for atmega328p or I am incapable of finding it
#ifndef INT0_PIN
#ifdef __AVR_ATmega328P__
#define INT0_PIN 2
#else
#warning Define INT0_PIN for this microcontroller to use interrupt
#endif
#endif

#ifndef INT1_PIN
#ifdef __AVR_ATmega328P__
#define INT1_PIN 3
#else
#warning Define INT1_PIN for this microcontroller to use interrupt
#endif
#endif

#define LEDPin    5  // Digital pin 4 is a test LED output to respond high/low as button 6 is pressed/released
#define SCLPin    4  // Serial data pins between touch sensor board and Arduino
#define SDAPin    3

//uint32_t g_intCount = 0;

struct CTtp229ButtonEvent
{
  uint8_t ButtonNumber : 5;         // ButtonNumber != 0 : Event is present. if equals 0, no event is received
  uint8_t IsButtonReleased : 1;     // True = Button is pressed. False = Button is released
};
//class CTtP229TouchButton;

class CTtP229TouchButton{
  struct CTtp229Prop;
  static CTtp229Prop g_prop;
  static uint16_t GetPressedButton();
  static void HandleButtonEvent();
  static void SetInterruptHandler();
  static void RemoveInterruptHandler();
  static uint8_t GetButtonNumberFromFlag(uint16_t buttonsChanged);
  public:
    static void Configure(int sclPin, int sdoPin, bool is16Button = true);
    static CTtp229ButtonEvent GetButtonEvent();
    static uint16_t GetButtonStatus();
    static bool HasEvent();
};

//CTtP229TouchButton g_ttp229Button;
//#define TTP16Button g_ttp229Button
#pragma pack(pop);
// your code
#endif
