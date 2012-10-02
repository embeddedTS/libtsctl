#define CLASS System
#include CLASS_INC
#define CLASS Bus
#include CLASS_INC
#define CLASS Time
#include CLASS_INC
#define CLASS Pin
#ifdef ALLOW_PIN_OVERRIDE
#define CLASS_OVERRIDE
#undef ALLOW_PIN_OVERRIDE
#endif
#include CLASS_INC
#define CLASS DIORaw
#include CLASS_INC
#define CLASS DIO
#include CLASS_INC
#define CLASS TWI
#include CLASS_INC
#define CLASS CAN
#include CLASS_INC
#define CLASS SPI
#include CLASS_INC
#define CLASS EDIO
#include CLASS_INC
#define CLASS AIO
#include CLASS_INC
#undef CLASS_INC
