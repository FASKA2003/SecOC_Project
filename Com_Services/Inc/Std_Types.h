//
// Created by itsmeayoub on 17/02/24.
//
#ifndef SECOC_MODULE_STD_TYPES_H
#define SECOC_MODULE_STD_TYPES_H

#define BIT_TO_BYTES(NUMBITS) ((NUMBITS  % 8 == 0) ? (NUMBITS/8) :  (((NUMBITS / 8) + 1)))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

// Boolean Values
#ifndef FALSE
#define FALSE 0x00u
#endif

#ifndef TRUE
#define TRUE 0x01u
#endif

#ifndef SUCCESS
#define SUCCESS 0x01u
#endif

#ifndef FAILURE
#define FAILURE 0x00u
#endif

// SWS_Std_00005 :Standard Return Type
#ifndef STATUSTYPEDEFINED
#define STATUSTYPEDEFINED
// #define E_OK 0x00u
// #define E_NOT_OK 0x01u
// #define E_BUSY 0x02u
typedef unsigned char StatusType; /* OSEK compliance */
#endif

// SWS_Std_00007
#define STD_HIGH 0x01u // Physical state 5V or 3.3V
#define STD_LOW 0x00u  // Physical state 0V

// SWS_Std_000013
#define STD_ACTIVE 0x01u // Logical state active
#define STD_IDLE 0x00u   // Logical state idle

// SWS_Std_00010
#define STD_ON 0x01u
#define STD_OFF 0x00u

#ifndef NULL
#define NULL ((void*)0)
#endif

// Standard Types
typedef unsigned char boolean;
typedef unsigned char uint8;   /*           0 .. 255             */
typedef unsigned short uint16; /*           0 .. 65535           */
typedef unsigned long uint32;  /*           0 .. 4294967295      */
typedef signed char sint8;     /*        -128 .. +127            */
typedef signed short sint16;   /*      -32768 .. +32767          */
typedef signed long sint32;    /* -2147483648 .. +2147483647     */
typedef signed long long sint64;
typedef unsigned long long uint64; /*       0..18446744073709551615  */
typedef float float32;
typedef double float64;

// SWS_Std_00005
typedef enum
{
    E_OK = 0x00u,
    E_NOT_OK = 0x01u,
    E_BUSY = 0x02u,
    E_QUEUE_FULL = 0x03u,
    CRYPTO_E_ENTROPY_EXHAUSTED = 0x04u,
    CRYPTO_E_KEY_READ_FAIL = 0x06u,
    CRYPTO_E_KEY_WRITE_FAIL = 0x07u,
    CRYPTO_E_KEY_NOT_AVAILABLE = 0x08u,
    CRYPTO_E_KEY_NOT_VALID = 0x09u,
    CRYPTO_E_KEY_SIZE_MISMATCH = 0x0Au,
    CRYPTO_E_JOB_CANCELED = 0x0Cu,
    CRYPTO_E_KEY_EMPTY = 0x0Du,
    CRYPTO_E_CUSTOM_ERROR = 0x0Eu
} Std_ReturnType;

// SWS_Std_00015
typedef struct
{
    uint16 vendorID;
    uint16 moduleID;
    uint8 sw_major_version;
    uint8 sw_minor_version;
    uint8 sw_patch_version;
} Std_VersionInfoType;
#endif // SECOC_MODULE_STD_TYPES_H
