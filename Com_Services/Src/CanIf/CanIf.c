//
// Created by itsmeayoub on 25/02/24.
//
#include "Std_Types.h"
#include "ComStack_Types.h"
#include "PduR_CanIf.h"
#include "CanIf.h"
#include "main.h"
//#include "stm32h7xx_hal_fdcan.h"

//extern HAL_UART_HandleTypeDef huart3;

/***************************************************************************************************************
* Service name: CanIf_Transmit                                                                               *
* Sws_Index : 8.3.4 [SWS_CANIF_00005]                                                                          *
* Service ID[hex]: 0x49                                                                                        *
* Sync/Async: Synchronous                                                                                      *
* Reentrancy: Reentrant for different PduIds, Non reentrant for the same PduId                                 *
* Parameters (in): TxPduId - Identifier of the PDU to be transmitted                                           *
*                  PduInfoPtr - Length of and pointer to the PDU data and pointer to Meta Data                 *
* Parameters (inout): None                                                                                     *
* Parameters (out):   None                                                                                     *
* Return value: Std_ReturnType - E_OK : Transmit request has been accepted                                     *
*                              - E_NOT_OK : Transmit request has not been accepted                             *
* Description: This service requests the transmission of PDU                                                   *
***************************************************************************************************************/
Std_ReturnType CanIf_Transmit(PduIdType TxPduId, const PduInfoType* PduInfoPtr) {
    PrintToTerminal((uint8*)"CanIf_Transmit\n", 16);
    //uint8 buff = PduInfoPtr->SduLength;
    //PrintToTerminal((uint8*)&buff, 1);
    HAL_Delay(500);
    if (PrintToTerminal((uint8*)PduInfoPtr->SduDataPtr, PduInfoPtr->SduLength) != HAL_OK) {
        PduR_CanIfTxConfirmation(TxPduId, E_NOT_OK);
        return E_NOT_OK;
    }
    PrintToTerminal((uint8*)"\n\r", 2);
    PduR_CanIfTxConfirmation(TxPduId, E_OK);
    return E_OK;
}
