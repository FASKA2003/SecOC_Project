//
// Created by itsmeayoub on 18/02/24.
//
#ifndef SECOC_MODULE_COMSTACK_TYPES_H
#define SECOC_MODULE_COMSTACK_TYPES_H
#include "Std_Types.h"

typedef uint16 PduIdType;

// SWS_COMTYPE_00008 : PduLengthType
typedef uint32 PduLengthType;

// SWS_COMTYPE_00011 : PduInfoType
typedef struct
{
    uint8* SduDataPtr;
    uint8* MetaDataPtr;
    PduLengthType SduLength;
} PduInfoType;

// SWS_COMTYPE_00027 : TpDataStateType
typedef enum
{
    TP_DATACONF = 0x00u,
    TP_DATARETRY = 0x01u,
    TP_CONFPENDING = 0x02
} TpDataStateType;

// SWS_COMTYPE_00012 : BufReq_ReturnType
typedef enum
{
    BUFREQ_OK = 0x00u,
    BUFREQ_E_NOT_OK = 0x01u,
    BUFREQ_E_BUSY = 0x02u,
    BUFREQ_E_OVFL = 0x03
} BufReq_ReturnType;

// SWS_COMTYPE_00037 : RetryInfoType
typedef struct
{
    TpDataStateType TpDataState;
    PduLengthType TxTpDataCnt;
} RetryInfoType;

#endif // SECOC_MODULE_COMSTACK_TYPES_H
