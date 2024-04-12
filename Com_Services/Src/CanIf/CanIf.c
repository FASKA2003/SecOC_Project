//
// Created by itsmeayoub on 25/02/24.
//
#include "Std_Types.h"
#include "ComStack_Types.h"
#include "PduR_CanIf.h"
#include "CanIf.h"
//#include "stm32h7xx_hal_fdcan.h"

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
    /*if (PduInfoPtr->SduLength > 8) {
        for (int i = 0; i < PduInfoPtr->SduLength; i+=8) {
            if(HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &TxPduId, PduInfoPtr->SduDataPtr + i, PduInfoPtr->SduLength - i) != HAL_OK) {
                return PduR_CanIfTxConfirmation(TxPduId, E_NOT_OK);
            }
            else {
                return PduR_CanIfTxConfirmation(TxPduId, E_OK);
            }
        }
    } else {
        if(HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &TxPduId, PduInfoPtr->SduDataPtr, PduInfoPtr->SduLength) != HAL_OK) {
            return PduR_CanIfTxConfirmation(TxPduId, E_NOT_OK);
        }
        else {
            return PduR_CanIfTxConfirmation(TxPduId, E_OK);
        }
    }*/
    PduR_CanIfTxConfirmation(TxPduId, E_OK);
    return E_OK;
}
