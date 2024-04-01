#ifndef SECOC_H
#define SECOC_H
#include "Std_Types.h"
#include "ComStack_Types.h"
#include "SecOC_Types.h"
#include "SecOC_Cfg.h"
#include "SecOC_Lcfg.h"
#include "SchM_SecOC.h"
/**********************************************************************************************************************
                                            GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
                                                   Initialization
 *********************************************************************************************************************/
/****************************************************************************************************************
 * Service name: SecOC_Init                                                                                     *
 * Sws_Index : 8.3.1 [SWS_SecOC_00106]                                                                          *
 * Service ID[hex]: 0x01                                                                                        *
 * Sync/Async: Synchronous                                                                                      *
 * Reentrancy: Non Reentrant                                                                                    *
 * Parameters (in): ConfigPtr - Pointer to a selected configuration structure                                   *
 * Parameters (inout): None                                                                                     *
 * Parameters (out): None                                                                                       *
 * Return value: None                                                                                           *
 * Description: This service initializes the SecOC module, Successful initialization leads to state SecOC_INIT. *
 ***************************************************************************************************************/
 void SecOC_Init(const SecOC_ConfigType* ConfigPtr);

/***************************************************************************************************************
* Service name: SecOC_DeInit                                                                                   *
* Sws_Index : 8.3.2 [SWS_SecOC_00161]                                                                          *
* Service ID[hex]: 0x05                                                                                        *
* Sync/Async: Synchronous                                                                                      *
* Reentrancy: Non Reentrant                                                                                    *
* Parameters (in): None                                                                                        *
* Parameters (inout): None                                                                                     *
* Parameters (out): None                                                                                       *
* Return value: None                                                                                           *
* Description:This service stops the secure onboard communication. All buffered I-PDU are removed and have to  *
* be obtained again, if needed, after SecOC_Init has been called. By a call to SecOC_DeInit,the AUTOSAR SecOC  *
* module is put into the state SECOC_UNINIT.                                                                   *
***************************************************************************************************************/
void SecOC_DeInit(void);

/***************************************************************************************************************
* Service name: SecOC_GetVersionInfo                                                                           *
* Sws_Index : 8.3.3 [SWS_SecOC_00107]                                                                          *
* Service ID[hex]: 0x02                                                                                        *
* Sync/Async: Synchronous                                                                                      *
* Reentrancy: Reentrant                                                                                        *
* Parameters (in): None                                                                                        *
* Parameters (inout): None                                                                                     *
* Parameters (out): VersionInfo - Pointer to where to store the version information of this module             *
* Return value: None                                                                                           *
* Description:This service returns the version information of this module                                      *                                                                   *
***************************************************************************************************************/
void SecOC_GetVersionInfo(Std_VersionInfoType* VersionInfo);


/**********************************************************************************************************************
                                                   Transmission
 *********************************************************************************************************************/

/***************************************************************************************************************
* Service name: SecOC_IfTransmit                                                                               *
* Sws_Index : 8.3.4 [SWS_SecOC_00112]                                                                          *
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
Std_ReturnType SecOC_IfTransmit(PduIdType TxPduId, const PduInfoType* PduInfoPtr);


/***************************************************************************************************************
* Service name: SecOC_TpTransmit                                                                               *
* Sws_Index : 8.3.5 [SWS_SecOC_91008]                                                                          *
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
Std_ReturnType SecOC_TpTransmit(PduIdType TxPduId, const PduInfoType* PduInfoPtr);


/***************************************************************************************************************
* Service name: SecOC_IfCancelTransmit                                                                               *
* Sws_Index : 8.3.6 [SWS_SecOC_00113]                                                                          *
* Service ID[hex]: 0x4a                                                                                        *
* Sync/Async: Synchronous                                                                                      *
* Reentrancy: Reentrant for different PduIds, Non reentrant for the same PduId                                 *
* Parameters (in): TxPduId - Identifier of the PDU to be transmitted                                           *
* Parameters (inout): None                                                                                     *
* Parameters (out):   None                                                                                     *
* Return value: Std_ReturnType - E_OK : Cancellation was executed successfully by the destination module       *
*                              - E_NOT_OK : Cancellation was rejected by the destination module.               *
* Description: This service requests cancellation of an ongoing transmission of a PDU in a lower layer         *
*              communication module                                                                            *
***************************************************************************************************************/
Std_ReturnType SecOC_IfCancelTransmit(PduIdType TxPduId);

/***************************************************************************************************************
* Service name: SecOC_TpCancelTransmit                                                                         *
* Sws_Index : 8.3.7 [SWS_SecOC_91009]                                                                          *
* Service ID[hex]: 0x4a                                                                                        *
* Sync/Async: Synchronous                                                                                      *
* Reentrancy: Reentrant for different PduIds, Non reentrant for the same PduId                                 *
* Parameters (in): TxPduId - Identifier of the PDU to be transmitted                                           *
* Parameters (inout): None                                                                                     *
* Parameters (out):   None                                                                                     *
* Return value: Std_ReturnType - E_OK : Cancellation was executed successfully by the destination module       *
*                              - E_NOT_OK : Cancellation was rejected by the destination module.               *
* Description: This service requests cancellation of an ongoing transmission of a PDU in a lower layer         *
*              communication module                                                                            *
***************************************************************************************************************/
Std_ReturnType SecOC_TpCancelTransmit(PduIdType TxPduId);

/**********************************************************************************************************************
                                                   Reception
 *********************************************************************************************************************/
/***************************************************************************************************************
* Service name: SecOC_IfRxIndication                                                                           *
* Sws_Index : 8.3.8 [SWS_SecOC_91010]                                                                          *
* Service ID[hex]: 0x4c                                                                                        *
* Sync/Async: Synchronous                                                                                      *
* Reentrancy: Non reentrant                                                                                    *
* Parameters (in): RxPduId - Identifier of the received Pdu                                                    *
* Parameters (inout): None                                                                                     *
* Parameters (out): None                                                                                       *
* Return value: Std_ReturnType - E_OK : Cancellation was executed successfully by the destination module.      *
                               - E_NOT_OK : Cancellation was rejected by the destination module.               *
* Description: Requests cancellation of an ongoing reception of a PDU in a lower layer communication module.   *
***************************************************************************************************************/
 Std_ReturnType TpCancelReceive(PduIdType RxPduId);

#endif // SECOC_H