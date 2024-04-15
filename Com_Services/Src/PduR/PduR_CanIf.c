//
// Created by itsmeayoub on 25/02/24.
//
#include "PduR_CanIf.h"
#include "SecOC_Cbk.h"
#include "main.h"
//#include "CanIf.h"
//extern HAL_UART_HandleTypeDef huart3;
/**********************************************************************************************************************
                                                 FUNCTION PROTOTYPES
 *********************************************************************************************************************/
/****************************************************************************************************************
 * Service name : PduR_TxConfirmation                                                                           *
 * Sws_Index : [SWS_PduR_00365]                                                                                 *
 * Service ID[hex]: 0x40                                                                                        *
 * Sync/Async: Synchronous                                                                                      *
 * Reentrancy: Reentrant for different PduIds, Non reentrant for the same PduId.                                *
 * Parameters (in): TxPduId  - Identifier of the Pdu to be transmitted                                          *
 *                  result   - E_OF : The PDU was transmitted                                                   *
 *                           - E_NOT_OK : The transmission of the PDU failed.                                   *
 * Parameters (inout): None                                                                                     *
 * Parameters (out): None                                                                                       *
 * Return value: None                                                                                           *
 * Description: The lower layer communication interface module confirms the transmission of a PDU, or the       *
 *              failure to transmit a PDU.                                                                      *
 ***************************************************************************************************************/
void PduR_CanIfTxConfirmation(PduIdType TxPduId, Std_ReturnType result) {
    HAL_Delay(2000);
    PrintToTerminal((uint8*)"PduR_CanIfTxConfirmation\n", 26);
    SecOC_TxConfirmation(TxPduId, result);
}


/****************************************************************************************************************
 * Service name : PduR_CanIfRxIndication                                                                            *
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
void PduR_CanIfRxIndication(PduIdType RxPduId, const PduInfoType* PduInfoPtr) {
    SecOC_RxIndication(RxPduId, PduInfoPtr);
}
