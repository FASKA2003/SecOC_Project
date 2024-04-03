/***********************************************************************************************************************
************************************************ INCLUDES
***************************************************************
***********************************************************************************************************************/
#include "SecOC.h"
#include "SecOC_Cbk.h"
#include "SecOC_Types.h"
#include <string.h>

/***********************************************************************************************************************
*****************************************  GlobalVariables
**************************************************************
***********************************************************************************************************************/
SecOCGeneral_Type* SecOCGeneralPtr;
const SecOCTxPduProcessing_Type* SecOCTxPduProcessingPtr;
const SecOCRxPduProcessing_Type* SecOCRxPduProcessingPtr;

static SecOC_StateType SecOCState = SECOC_UNINIT;

extern SecOC_TxCounter_Type SecOCTxCounter;
extern SecOC_RxCounter_Type SecOCRxCounter;

/**********************************************************************************************************************
                                                   Initialization
 *********************************************************************************************************************/
/****************************************************************************************************************
 * Service name: SecOC_Init * Sws_Index : 8.3.1 [SWS_SecOC_00106] * Service ID[hex]: 0x01 *
 * Sync/Async: Synchronous * Reentrancy: Non Reentrant * Parameters (in): ConfigPtr - Pointer
 *to a selected configuration structure                                   * Parameters (inout):
 *None                                                                                     *
 * Parameters (out): None * Return value: None * Description: This service initializes the
 *SecOC module, Successful initialization leads to state SecOC_INIT. *
 ***************************************************************************************************************/
void SecOC_Init(const SecOC_ConfigType* ConfigPtr)
{
    // [SWS_SecOC_00054] SecOC_Init shall initialize all internal variables and the buffers of
    // the SecOC I-PDUs.
    if (ConfigPtr != NULL)
    {
        SecOCGeneralPtr = ConfigPtr->SecOCGeneral;
        SecOCTxPduProcessingPtr = ConfigPtr->SecOCTxPduProcessing;
        SecOCRxPduProcessingPtr = ConfigPtr->SecOCRxPduProcessing;
        SecOCState = SECOC_INIT;

        // Increase freshness counter
        FVM_IncreaseCounter(SecOCTxPduProcessingPtr[0].SecOCFreshnessValueId);
    }
    else
    {
        SecOCState = SECOC_UNINIT;
    }
}

/***************************************************************************************************************
 * Service name: SecOC_DeInit * Sws_Index : 8.3.2 [SWS_SecOC_00161] * Service ID[hex]: 0x05 *
 * Sync/Async: Synchronous * Reentrancy: Non Reentrant * Parameters (in): None * Parameters
 *(inout): None * Parameters (out): None * Return value: None * Description:This service stops
 *the secure onboard communication. All buffered I-PDU are removed and have to  * be obtained
 *again, if needed, after SecOC_Init has been called. By a call to SecOC_DeInit,the AUTOSAR
 *SecOC  * module is put into the state SECOC_UNINIT. *
 ***************************************************************************************************************/
void SecOC_DeInit(void)
{
    // Check if the module is initialized
    if (SecOCState != SECOC_INIT)
    {
        return;
    }
    SecOCState = SECOC_UNINIT;
    /* [SWS_SecOC_00157] */
    /* Clear the Tx/Rx Buffers */
    if (SecOCTxPduProcessingPtr != NULL)
    {
        memset(
            (void*)SecOCTxPduProcessingPtr->SecOCTxAuthenticPduLayer
                ->SecOCTxAuthenticLayerPduRef->SduDataPtr,
            0,
            SecOCTxPduProcessingPtr->SecOCTxAuthenticPduLayer->SecOCTxAuthenticLayerPduRef
                ->SduLength);
        SecOCTxPduProcessingPtr->SecOCTxAuthenticPduLayer->SecOCTxAuthenticLayerPduRef
            ->SduLength = 0;
    }
    if (SecOCRxPduProcessingPtr != NULL)
    {
        memset(
            (void*)SecOCRxPduProcessingPtr->SecOCRxSecuredPduLayer->SecOCRxSecuredPdu
                ->SecOCRxSecuredLayerPduRef->SduDataPtr,
            0,
            SecOCRxPduProcessingPtr->SecOCRxSecuredPduLayer->SecOCRxSecuredPdu
                ->SecOCRxSecuredLayerPduRef->SduLength);
        SecOCRxPduProcessingPtr->SecOCRxSecuredPduLayer->SecOCRxSecuredPdu
            ->SecOCRxSecuredLayerPduRef->SduLength = 0;
    }
    // De-initialize the Global pointers
    SecOCGeneralPtr = NULL;
    SecOCTxPduProcessingPtr = NULL;
    SecOCRxPduProcessingPtr = NULL;
}

/**********************************************************************************************************************
                                                   Transmission
 *********************************************************************************************************************/

/***************************************************************************************************************
 * Service name: SecOC_IfTransmit * Sws_Index : 8.3.4 [SWS_SecOC_00112] * Service ID[hex]: 0x49
 ** Sync/Async: Synchronous * Reentrancy: Reentrant for different PduIds, Non reentrant for the
 *same PduId                                 * Parameters (in): TxPduId - Identifier of the PDU
 *to be transmitted                                           * PduInfoPtr - Length of and
 *pointer to the PDU data and pointer to Meta Data                 * Parameters (inout): None *
 * Parameters (out):   None * Return value: Std_ReturnType - E_OK : Transmit request has been
 *accepted                                     *
 *                              - E_NOT_OK : Transmit request has not been accepted *
 * Description: This service requests the transmission of PDU *
 ***************************************************************************************************************/
Std_ReturnType SecOC_IfTransmit(PduIdType TxPduId, const PduInfoType* PduInfoPtr)
{
    if (SecOCState != SECOC_INIT)
    {
        return E_NOT_OK;
    }
    if (PduInfoPtr == NULL)
    {
        return E_NOT_OK;
    }
    /*[SWS_SecOC_00252] :
     * The SecOC module shall copy the complete Authentic I-PDU to its internal memory
     * before starting transmission of the corresponding Secured I-PDU.
     * */
    memcpy(
        (void*)SecOCTxPduProcessingPtr[TxPduId]
            .SecOCTxAuthenticPduLayer->SecOCTxAuthenticLayerPduRef->SduDataPtr,
        PduInfoPtr->SduDataPtr,
        PduInfoPtr->SduLength);
    SecOCTxPduProcessingPtr[TxPduId]
        .SecOCTxAuthenticPduLayer->SecOCTxAuthenticLayerPduRef->SduLength =
        PduInfoPtr->SduLength;
    SecOCTxPduProcessingPtr[TxPduId]
        .SecOCTxAuthenticPduLayer->SecOCTxAuthenticLayerPduRef->MetaDataPtr =
        PduInfoPtr->MetaDataPtr;
    /* [SWS_SecOC_00225] :
     * -->For every transmission request that is queued to SecOC an authentication build
     * counter shall be maintained [SWS_SecOC_00226] :
     * -->Upon the initial processing of a transmission request of a secured I-PDU SecOC shall
     * set the authentication build counter to 0.
     */
    SecOCTxCounter.SecOCAuthenticationBuildCounter = 0;

    return E_OK;
}

/***************************************************************************************************************
 * Service name: constructDataToAuthenticatorTx                                                                *
 * Parameters (in): TxPduId - Identifier of the PDU to be transmitted                                          *
 * PduInfoPtr - Length of and pointer to the PDU data and pointer to Meta Data                                 *
 * Parameters (in): TxPduId                                                                                    *
 *                  AuthPdu                                                                                    *
 *                  SecOCIntermediate
 * Parameters (out):   None                                                                                    *
 * Return value: None
 * Description: This service requests the transmission of PDU *
 ***************************************************************************************************************/
static void constructDataToAuthenticator(const PduIdType TxPduId, SecOC_TxIntermediateType* SecOCIntermediate, const PduInfoType* AuthPdu ) {
    uint8 *DataToAuthenticate = SecOCIntermediate->DataToAuth;
    uint32 DataToAuthenticateLen = 0;

    // Copy the PduId to the DataToAuthenticate
    memcpy(&DataToAuthenticate[DataToAuthenticateLen], &SecOCTxPduProcessingPtr[TxPduId].SecOCDataId, sizeof(SecOCTxPduProcessingPtr[TxPduId].SecOCDataId));
    DataToAuthenticateLen += sizeof(SecOCTxPduProcessingPtr[TxPduId].SecOCDataId);

    // Copy the Authentic PDU to the DataToAuthenticate
    memcpy(&DataToAuthenticate[DataToAuthenticateLen], AuthPdu->SduDataPtr, AuthPdu->SduLength);
    DataToAuthenticateLen += AuthPdu->SduLength;

    // Copy the Freshness Value to the DataToAuthenticate
    uint32 FreshnessLenBytes = BIT_TO_BYTES(SecOCIntermediate->FreshnessLenBits);
    memcpy(&DataToAuthenticate[DataToAuthenticateLen], SecOCIntermediate->Freshness, SecOCIntermediate->FreshnessLenBytes);
    DataToAuthenticateLen += FreshnessLenBytes;

    // Set the DataToAuthenticateLen
    SecOCIntermediate->DataToAuthLen = DataToAuthenticateLen;
}