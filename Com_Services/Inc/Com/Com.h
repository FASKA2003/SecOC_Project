//
// Created by itsmeayoub on 25/02/24.
//

#ifndef SECOC_MODULE_COM_H
#define SECOC_MODULE_COM_H
#include "Std_Types.h"
#include "ComStack_Types.h"

/**********************************************************************************************************************
                                                 FUNCTION PROTOTYPES
 *********************************************************************************************************************/
/***************************************************************************************************************
* Service name: Com_TxConfirmation                                                                             *
* Sws_Index : 8.4.4 [SWS_Com_00124]                                                                            *
* Service ID[hex]: 0x40                                                                                        *
* Sync/Async: Synchronous                                                                                      *
* Reentrancy: Reentrant for different PduIds. Non reentrant for the same PduId.                                *
* Parameters (in): TxPduId - ID of the PDU that has been transmitted.                                          *
*                  result - E_OK : The PDU was transmitted.                                                    *
*                           E_NOT_OK : The transmission of the PDU failed.                                     *
* Parameters (inout): None                                                                                     *
* Parameters (out): None                                                                                       *
* Return value: None                                                                                           *
* Description: The lower layer communication interface module confirms the transmission of a PDU, or the       *
*              failure to transmit a PDU.                                                                      *
***************************************************************************************************************/
void Com_TxConfirmation(PduIdType TxPduId, Std_ReturnType result);

/***************************************************************************************************************
* Service name: Com_RxIndication                                                                             *
* Sws_Index : 8.4.2 [SWS_SecOC_00123]                                                                          *
* Service ID[hex]: 0x42                                                                                        *
* Sync/Async: Synchronous                                                                                      *
* Reentrancy: Reentrant for different PduIds, Non reentrant for the same PduId                                 *
* Parameters (in): RxPduId - Identifier of the received PDU.                                                   *
*                  PduInfoPtr - Length (SduLength) of the received PDU, a pointer to as buffer(SduDataPtr)     *
*                               containing the PDU, and the metaData related to this PDU.                      *
* Parameters (inout): None                                                                                     *
* Parameters (out): None                                                                                       *
* Return value: None                                                                                           *
* Description: Indication of a received PDU from a lower layer communication interface module.                 *
***************************************************************************************************************/
void Com_RxIndication(PduIdType RxPduId, const PduInfoType* PduInfoPtr);


void Com_MainTx(void);
#endif //SECOC_MODULE_COM_H
