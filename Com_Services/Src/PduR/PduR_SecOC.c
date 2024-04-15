//
// Created by itsmeayoub on 25/02/24.
//
#include "PduR_SecOC.h"
#include "CanIf.h"
#include "Com.h"
#include "main.h"
//extern HAL_UART_HandleTypeDef huart3;
/****************************************************************************************************************
 * Service name : PduR_SecOCTransmit                                                                            *
 * Sws_Index : [SWS_PduR_00406]                                                                                 *
 * Service ID[hex]: 0x49                                                                                        *
 * Sync/Async: Synchronous                                                                                      *
 * Reentrancy: Reentrant for different PduIds, Non reentrant for the same PduId.                                *
 * Parameters (in): TxPduId    - Identifier of the Pdu to be transmitted                                        *
 *                  PduInfoPtr - Length of and pointer to the PDU data and pointer to MetaData.                 *
 * Parameters (inout): None                                                                                     *
 * Parameters (out): None                                                                                       *
 * Return value: Std_ReturnType - E_OF : Transmit request has been accepted.                                    *
 *                                E_NOT_OK : Transmit request has not been accepted.                            *
 * Description: This service requests transmission of a PDU.                                                    *
 ***************************************************************************************************************/
Std_ReturnType PduR_SecOCTransmit(PduIdType TxPduId, const PduInfoType* PduInfoPtr) {
    PrintToTerminal((uint8*)"PduR_SecOCTransmit\n", 19);
    return CanIf_Transmit(TxPduId, PduInfoPtr);
}

/****************************************************************************************************************
 * Service name : PduR_SecOCCancelTransmit                                                                            *
 * Sws_Index : [SWS_PduR_00769]                                                                                 *
 * Service ID[hex]: 0x4a                                                                                        *
 * Sync/Async: Synchronous                                                                                      *
 * Reentrancy: Reentrant for different PduIds, Non reentrant for the same PduId.                                *
 * Parameters (in): TxPduId - Identifier of the Pdu to be cancelled.                                            *
 * Parameters (inout): None                                                                                     *
 * Parameters (out): None                                                                                       *
 * Return value: Std_ReturnType - E_OF : Cancellation was executed successfully by the destination module       *
 *                                E_NOT_OK : Cancellation was rejected by the destination module.               *
 * Description: Request cancellation of an ongoing transmission of a PDU in a lower layer communication module. *
 ***************************************************************************************************************/
Std_ReturnType PduR_SecOCCancelTransmit(PduIdType TxPduId);


/****************************************************************************************************************
 * Service name : PduR_SecOCIfRxIndication                                                                            *
 * Sws_Index : [SWS_PduR_00362]                                                                                 *
 * Service ID[hex]: 0x42                                                                                        *
 * Sync/Async: Synchronous                                                                                      *
 * Reentrancy: Reentrant for different PduIds, Non reentrant for the same PduId.                                *
 * Parameters (in): RxPduId    - Identifier of the received Pdu.                                                *
 *                  PduInfoPtr - Contains the length (SduLength) of the received PDU, a pointer to a buffer     *
 *                              (SduDataPtr) containing the PDU, and the MetaData related to this PDU.          *
 * Parameters (inout): None                                                                                     *
 * Parameters (out): None                                                                                       *
 * Return value: None                                                                                           *
 * Description: Indication of a received PDU from a lower layer communication interface module.                 *
 ***************************************************************************************************************/
void PduR_SecOCIfRxIndication(PduIdType RxPduId, const PduInfoType* PduInfoPtr) {
    Com_RxIndication(RxPduId, PduInfoPtr);
}

/****************************************************************************************************************
 * Service name : PduR_SecOCIfTxConfirmation                                                                    *
 * Sws_Index : [SWS_PduR_00365]                                                                                 *
 * Service ID[hex]: 0x40                                                                                        *
 * Sync/Async: Synchronous                                                                                      *
 * Reentrancy: Reentrant for different PduIds, Non reentrant for the same PduId.                                *
 * Parameters (in): TxPduId  - Identifier of the PDU that has been transmitted Pdu.                             *
 *                  result   - E_OF : The PDU was transmitted                                                   *
 *                           - E_NOT_OK : The transmission of the PDU failed.                                   *
 * Parameters (inout): None                                                                                     *
 * Parameters (out): None                                                                                       *
 * Return value: None                                                                                           *
 * Description: The lower layer communication interface module confirms the transmission of a PDU, or the       *
 *              failure to transmit a PDU.                                                                      *
 ***************************************************************************************************************/
void PduR_SecOCIfTxConfirmation(PduIdType TxPduId, Std_ReturnType result) {
    Com_TxConfirmation(TxPduId, result);
    // I need to print successful transmission on the serial monitor
    if( result == E_OK )
    {
        PrintToTerminal((uint8*)"PduR_SecOCIfTxConfirmation 'E_OK' \n", 36);
    }
    else
    {
        PrintToTerminal((uint8*)"PduR_SecOCIfTxConfirmation 'E_NOT_OK' \n", 40);
    }
}
