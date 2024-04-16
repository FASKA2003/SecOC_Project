//
// Created by itsmeayoub on 18/02/24.
//
#include "ComStack_Types.h"
#include "Com.h"
#include "PduR_Com.h"
#include "main.h"

//extern HAL_UART_HandleTypeDef huart3;

void Com_TxConfirmation(PduIdType TxPduId, Std_ReturnType result) {

    if( result == E_OK )
    {

        PrintToTerminal((uint8*)"Com_TX confirmation :: 'E_OK' \n", 30);
    }
    else
    {

        PrintToTerminal((uint8*)"Com_TX confirmation ::'E_NOT_OK' \n", 34);
    }
}


void Com_RxIndication(PduIdType RxPduId, const PduInfoType* PduInfoPtr)
{
    PrintToTerminal((uint8*)"Received Indication \n", 30);
    PrintToTerminal((uint8*)PduInfoPtr->SduDataPtr, PduInfoPtr->SduLength);
}

void Com_MainTx(uint8* data, uint8 length)
{
    PrintToTerminal((uint8*)"COM Tx\n", 8);
    PduInfoType SPDU;
    SPDU.SduDataPtr = data;
    SPDU.SduLength = length;
    SPDU.MetaDataPtr = NULL;
    PduR_ComTransmit(0, &SPDU);
}
