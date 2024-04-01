//
// Created by itsmeayoub on 22/02/24.
//

#ifndef SECOC_MODULE_SECOC_CBK_H
#define SECOC_MODULE_SECOC_CBK_H
#include "Std_Types.h"
#include "ComStack_Types.h"

/**********************************************************************************************************************
                                                   Reception Callbacks
 *********************************************************************************************************************/

/***************************************************************************************************************
* Service name: SecOC_RxIndication                                                                             *
* Sws_Index : 8.4.1 [SWS_SecOC_00124]                                                                          *
* Service ID[hex]: 0x42                                                                                        *
* Sync/Async: Synchronous                                                                                      *
* Reentrancy: Reentrant for different PduIds, Non reentrant for the same PduId                                 *
* Parameters (in): RxPduId - Identifier of the received PDU.                                                   *
*                  PduInfoPtr - Length (SduLength) of the received PDU, a pointer to as buffer(SduDataPtr)     *
*                               containing the PDU, and the metaData related to this PDU.                      *
* Parameters (inout): None                                                                                     *
* Parameters (out):   None                                                                                     *
* Return value: None                                                                                           *
* Description: Indication of a received PDU from a lower layer communication interface module.                 *
***************************************************************************************************************/
void SecOC_RxIndication(PduIdType RxPduId, const PduInfoType* PduInfoPtr);

/***************************************************************************************************************
* Service name: SecOC_TpRxIndication                                                                           *
* Sws_Index : 8.4.2 [SWS_SecOC_00124]                                                                          *
* Service ID[hex]: 0x45                                                                                        *
* Sync/Async: Synchronous                                                                                      *
* Reentrancy: Reentrant.                                                                                       *
* Parameters (in): id - Identification of the received PDU.                                                    *
*                  result - Result of the reception.                                    .                      *
* Parameters (inout): None                                                                                     *
* Parameters (out):   None                                                                                     *
* Return value: None                                                                                           *
* Description: Called after an I-PDU has been received via the TP API, the result indicates whether the        *
*              reception was successful or not.                                                                *
***************************************************************************************************************/
void SecOC_TpRxIndication(PduIdType id, Std_ReturnType result);

/***************************************************************************************************************
* Service name: SecOC_CopyRxData                                                                               *
* Sws_Index : 8.4.6 [SWS_SecOC_00128]                                                                          *
* Service ID[hex]: 0x44                                                                                        *
* Sync/Async: Synchronous                                                                                      *
* Reentrancy: Reentrant.                                                                                       *
* Parameters (in):  id - Identification of the received I-PDU.                                                 *
*                   info - Provides the source buffer(SduDataPtr) and the number of bytes to be copied         *
*                          (SduLength). An SduLength of 0 can used to query the current amount of available in *
*                          buffer the upper layer module. In this case, the SduDataPtr can be a null pointer.  *
* Parameters (inout): None                                                                                     *
* Parameters (out): bufferSizePtr - Available receive buffer after data has been copied.                       *
* Return value: BufReq_ReturnType - BUFREQ_OK : Data copied successfully.                                      *
*                                 - BUFREQ_E_NOT_OK : Data was not copied because an error occurred.           *
* Description: This function is called to provide the received data of an I-PDU segment (N-PDU) to the upper   *
*              layer. Each call to this function provides the next part of the I-PDU data. The size of the     *
*              remaining buffer is written to the position indicated by bufferSizePtr.                         *
***************************************************************************************************************/
BufReq_ReturnType SecOC_CopyRxData(PduIdType id, const PduInfoType* info, PduLengthType* bufferSizePtr);

/***************************************************************************************************************
* Service name: SecOC_StartOfReception                                                                         *
* Sws_Index : 8.4.6 [SWS_SecOC_00130]                                                                          *
* Service ID[hex]: 0x46                                                                                        *
* Sync/Async: Synchronous                                                                                      *
* Reentrancy: Reentrant.                                                                                       *
* Parameters (in):  id - Identification of the I-PDU.                                                          *
*                   info - Pointer to a PduInfoType structure containing the payload data (without protocol    *
*                         information) and payload length of the first frame or single frame of a transport    *
*                         protocol I-PDU reception, and the MetaData related to this PDU. If neither           *
*                         first/single frame data nor MetaData are available, this parameter is set to         *
*                         NULL_PTR.                                                                            *
* Parameters (inout): None                                                                                     *
* Parameters (out): bufferSizePtr - Available receive buffer in the receiving module. This parameter will be   *
*                                  used to compute the Block Size (BS) in the transport protocol module.       *
* Return value: BufReq_ReturnType - BUFREQ_OK: Connection has been accepted. bufferSizePtr indicates the       *
*                                             available receive buffer; reception is continued. If no buffer   *
*                                             of the requested size is available, a receive buffer size of 0   *
*                                             shall be indicated by bufferSizePtr.                             *
*                                   BUFREQ_E_NOT_OK : Connection has been rejected; reception is aborted.      *
*                                                     bufferSizePtr remains unchanged.                         *
*                                   BUFREQ_E_OVFL : No buffer of the required length can be provided, reception*
*                                                   is aborted. bufferSizePtr remains unchanged.               *
* Description: This function is called at the start of receiving an N-SDU. The N-SDU might be fragmented into  *
*              multiple N-PDUs (FF with one or more following CFs) or might consist of a single N-PDU (SF).    *
*              The service shall provide the currently available maximum buffer size when invoked with         *
*              TpSduLength equal to 0.                                                                         *
***************************************************************************************************************/
BufReq_ReturnType SecOC_StartOfReception(PduIdType id, const PduInfoType* info, PduLengthType TpSduLength, PduLengthType* bufferSizePtr);


/**********************************************************************************************************************
                                                   Transmission Callbacks
 *********************************************************************************************************************/

/***************************************************************************************************************
* Service name: SecOC_TxIndication                                                                             *
* Sws_Index : 8.4.3 [SWS_SecOC_00126]                                                                          *
* Service ID[hex]: 0x40                                                                                        *
* Sync/Async: Synchronous                                                                                      *
* Reentrancy: Reentrant for different PduIds, Non reentrant for the same PduId                                 *
* Parameters (in): TxPduId - Id of the PDU that has been transmitted.                                          *
*                  result  - E_OK : the PDU was transmitted successfully.                                      *
*                          - E_NOT_OK : Transmission of the PDU failed.                                        *
* Parameters (inout): None                                                                                     *
* Parameters (out):   None                                                                                     *
* Return value: None                                                                                           *
* Description: The lower layer communication interface module confirms the transmission of a PDU, or the       *
*              failure to transmit a PDU.                                                                      *
***************************************************************************************************************/
void SecOC_TxConfirmation(PduIdType TxPduId, Std_ReturnType result);

/***************************************************************************************************************
* Service name: SecOC_TpTxConfirmation                                                                         *
* Sws_Index : 8.4.4 [SWS_SecOC_00126]                                                                          *
* Service ID[hex]: 0x43                                                                                        *
* Sync/Async: Synchronous                                                                                      *
* Reentrancy: Reentrant.                                                                                       *
* Parameters (in): id - Identification of the transmitted I-PDU.                                               *
*                  result - Result of the transmission of the I-PDU.                                           *
* Parameters (inout): None                                                                                     *
* Parameters (out):   None                                                                                     *
* Return value: None                                                                                           *
* Description: This function is Called after The I-PDU has been transmitted on its network, the result         *
*              indicates whether the transmission was successful or not.                                       *
***************************************************************************************************************/
void SecOC_TpTxConfirmation(PduIdType id, Std_ReturnType result);

/***************************************************************************************************************
* Service name: SecOC_CopyTxData                                                                               *
* Sws_Index : 8.4.7 [SWS_SecOC_00129]                                                                          *
* Service ID[hex]: 0x43                                                                                        *
* Sync/Async: Synchronous                                                                                      *
* Reentrancy: Reentrant.                                                                                       *
* Parameters (in): id - Identification of the transmitted I-PDU.                                               *
*                  info - Provides the destination buffer (SduDataPtr) and the number of bytes to be copied    *
*                         (SduLength). If not enough transmit data is available, no data is copied by the      *
*                         upper layer module and BUFREQ_E_BUSY is returned. The lower layer module may retry   *
*                         the call. An SduLength of 0 can be used to indicate state changes in the retry       *
*                         parameter or to query the current amount of available data in the upper layer        *
*                         module. In this case, the SduDataPtr may be a NULL_PTR.                              *
*                 retry - This parameter is used to acknowledge transmitted data or to retransmit data after   *
*                         transmission problems. If the retry parameter is a NULL_PTR, it indicates that the   *
*                         transmit data can be removed from the buffer immediately after it has been copied.   *
*                         Otherwise, the retry parameter must point to a valid RetryInfoType element. If       *
*                         TpDataState indicates TP_CONFPENDING, the previously copied data must remain in the  *
*                         TP buffer to be available for error recovery. TP_DATACONF indicates that all data    *
*                         that has been copied before this call is confirmed and can be removed from the TP    *
*                         buffer. Data copied by this API call is excluded and will be confirmed later.        *
*                         TP_DATARETRY indicates that this API call shall copy previously copied data in       *
*                         order to recover from an error. In this case TxTpDataCnt specifies the offset in     *
*                         bytes from the current data copy position.                                           *
* Parameters (inout): None                                                                                     *
* Parameters (out): availableDataPtr - Indicates the remaining number of bytes that are available in the       *
*                                      upper layer module's Tx buffer. availableDataPtr can be used by TP      *
*                                      modules that support dynamic payload lengths (e.g. FrIsoTp) to          *
*                                      determine the size of the following CFs                                 *
* Return value: BufReq_ReturnType - BUFREQ_OK : Data has been copied to the transmit buffer completely as      *
*                                               requested.                                                     *
*                                 - BUFREQ_E_NOT_OK : Data was not copied because an error occurred.           *
*                                 - BUFREQ_E_BUSY : Request could not be fulfilled, because the required       *
*                                                   amount of Tx data is not available. The lower layer        *
*                                                   module may retry this call later on. No data has been      *
*                                                   copied.                                                    *
* Description: This function is called to acquire the transmit data of an I-PDU segment (N-PDU). Each call to  *
*              this function provides the next part of the I-PDU data unless retry->Tp DataState is            *
*              TP_DATARETRY. In this case the function restarts to copy the data beginning at the offset from  *
*              the current position indicated by retry->TxTpDataCnt. The size of the remaining data is written *
*              to the position indicated by availableDataPtr.                                                  *
***************************************************************************************************************/
BufReq_ReturnType SecOC_CopyTxData(PduIdType id, const PduInfoType* info, RetryInfoType* retry, PduLengthType* availableDataPtr);


/***************************************************************************************************************
* Service name: SecOC_TriggerTransmit                                                                               *
* Sws_Index : 8.4.5 [SWS_SecOC_00127]                                                                          *
* Service ID[hex]: 0x41                                                                                        *
* Sync/Async: Synchronous                                                                                      *
* Reentrancy: Reentrant for different PduIds, Non reentrant for the same PduId                                 *
* Parameters (in): TxPduId - Id of the SDU is requested to be transmitted                                      *
* Parameters (inout): PduInfoPtr - Contains a pointer to a buffer (SduDataPtr) to where the SDU data shall be  *
*                                  copied, and the available buffer size in SduLength. On return, the service  *
*                                  will indicate the length of the copied SDU data in SduLength.               *                                                                     *
* Parameters (out):   None                                                                                     *
* Return value: Std_ReturnType - E_OK: SDU has been copied and SduLength indicates the number of copied bytes. *
*                              - E_NOT_OK: No SDU data has been copied. PduInfoPtr must not be used since it   *
*                                          may contain a NULL pointer or point to invalid data                 *
* Description: Within this API, the upper layer module (called module) shall check whether the available data  *
*              fits into the buffer size reported by PduInfoPtr->SduLength. If it fits, it shall copy its data *
*              into the buffer provided by PduInfoPtr->SduDataPtr and update the length of the actual copied   *
*              data in PduInfoPtr->SduLength. If not, it returns E_NOT_OK without changing PduInfoPtr.         *
***************************************************************************************************************/
Std_ReturnType SecOC_TriggerTransmit(PduIdType TxPduId, PduInfoType* PduInfoPtr);


#endif //SECOC_MODULE_SECOC_CBK_H
