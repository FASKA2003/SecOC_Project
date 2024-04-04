/***********************************************************************************************************************
************************************************ INCLUDES
***************************************************************
***********************************************************************************************************************/
#include "SecOC.h"
#include "SecOC_Cbk.h"
#include "SecOC_Types.h"
#include "FVM.h"
#include "Csm.h"
#include <string.h>

/***********************************************************************************************************************
*****************************************  GlobalVariables
**************************************************************
***********************************************************************************************************************/
SecOCGeneral_Type* SecOCGeneral;
const SecOCTxPduProcessing_Type* SecOCTxPduProcessing;
const SecOCRxPduProcessing_Type* SecOCRxPduProcessing;

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
        SecOCGeneral = ConfigPtr->SecOCGeneral;
        SecOCTxPduProcessing = ConfigPtr->SecOCTxPduProcessing;
        SecOCRxPduProcessing = ConfigPtr->SecOCRxPduProcessing;
        SecOCState = SECOC_INIT;

        // Increase freshness counter
        FVM_IncreaseCounter(SecOCTxPduProcessing[0].SecOCFreshnessValueId);
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
    if (SecOCTxPduProcessing != NULL)
    {
        memset(
            (void*)SecOCTxPduProcessing->SecOCTxAuthenticPduLayer
                ->SecOCTxAuthenticLayerPduRef->SduDataPtr,
            0,
            SecOCTxPduProcessing->SecOCTxAuthenticPduLayer->SecOCTxAuthenticLayerPduRef
                ->SduLength);
        SecOCTxPduProcessing->SecOCTxAuthenticPduLayer->SecOCTxAuthenticLayerPduRef
            ->SduLength = 0;
    }
    if (SecOCRxPduProcessing != NULL)
    {
        memset(
            (void*)SecOCRxPduProcessing->SecOCRxSecuredPduLayer->SecOCRxSecuredPdu
                ->SecOCRxSecuredLayerPduRef->SduDataPtr,
            0,
            SecOCRxPduProcessing->SecOCRxSecuredPduLayer->SecOCRxSecuredPdu
                ->SecOCRxSecuredLayerPduRef->SduLength);
        SecOCRxPduProcessing->SecOCRxSecuredPduLayer->SecOCRxSecuredPdu
            ->SecOCRxSecuredLayerPduRef->SduLength = 0;
    }
    // De-initialize the Global pointers
    SecOCGeneral = NULL;
    SecOCTxPduProcessing = NULL;
    SecOCRxPduProcessing = NULL;
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
        (void*)SecOCTxPduProcessing[TxPduId]
            .SecOCTxAuthenticPduLayer->SecOCTxAuthenticLayerPduRef->SduDataPtr,
        PduInfoPtr->SduDataPtr,
        PduInfoPtr->SduLength);
    SecOCTxPduProcessing[TxPduId]
        .SecOCTxAuthenticPduLayer->SecOCTxAuthenticLayerPduRef->SduLength =
        PduInfoPtr->SduLength;
    SecOCTxPduProcessing[TxPduId]
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
static void constructDataToAuthenticatorTx(const PduIdType TxPduId, SecOC_TxIntermediateType* SecOCIntermediate, const PduInfoType* AuthPdu ) {
    uint8 *DataToAuthenticate = SecOCIntermediate->DataToAuth;
    uint32 DataToAuthenticateLen = 0;

    // Copy the PduId to the DataToAuthenticate
    memcpy(&DataToAuthenticate[DataToAuthenticateLen], &SecOCTxPduProcessing[TxPduId].SecOCDataId, sizeof(SecOCTxPduProcessing[TxPduId].SecOCDataId));
    DataToAuthenticateLen += sizeof(SecOCTxPduProcessing[TxPduId].SecOCDataId);

    // Copy the Authentic PDU to the DataToAuthenticate
    memcpy(&DataToAuthenticate[DataToAuthenticateLen], AuthPdu->SduDataPtr, AuthPdu->SduLength);
    DataToAuthenticateLen += AuthPdu->SduLength;

    // Copy the Freshness Value to the DataToAuthenticate
    uint32 FreshnessLenBytes = BIT_TO_BYTES(SecOCIntermediate->FreshnessLenBits);
    memcpy(&DataToAuthenticate[DataToAuthenticateLen], SecOCIntermediate->Freshness, FreshnessLenBytes);
    DataToAuthenticateLen += FreshnessLenBytes;

    // Set the DataToAuthenticateLen
    SecOCIntermediate->DataToAuthLen = DataToAuthenticateLen;
}



/***************************************************************************************************************
 *          * Function Info *                                                                                  *
 *                                                                                                             *
 * Function_Name        : SecOC_GetRxFreshness                                                                 *
 * Function_Index       : 8.5.1 [SWS_SecOC_91007]                                                              *
 * Function_File        : SWS of SecOC                                                                         *
 * Function_Description  : This interface is used by the                                                        *
 * SecOC to obtain the current freshness value                                                                 *
 **************************************************************************************************************/

Std_ReturnType SecOC_GetRxFreshness(uint16 SecOCFreshnessValueID, const uint8* SecOCTruncatedFreshnessValue,
                                    uint32 SecOCTruncatedFreshnessValueLength, uint16 SecOCAuthVerifyAttempts, uint8* SecOCFreshnessValue,
                                    uint32* SecOCFreshnessValueLength) {
    Std_ReturnType result = FVM_GetRxFreshness(SecOCFreshnessValueID, SecOCTruncatedFreshnessValue, SecOCTruncatedFreshnessValueLength, SecOCAuthVerifyAttempts, SecOCFreshnessValue, SecOCFreshnessValueLength);
    return result;
}


/********************************************************
 *          * Function Info *                           *
 *                                                      *
 * Function_Name        : SecOC_GetTxFreshness          *
 * Function_Index       : 8.5.3 [SWS_SecOC_00126]       *
 * Function_File        : SWS of SecOC                  *
 * Function_Description  : This API returns the freshness*
 * value from the Most Significant Bits in the first    *
 * byte in the array (SecOCFreshnessValue),             *
 * in big endian format.                                *
 *******************************************************/

Std_ReturnType SecOC_GetTxFreshness(uint16 SecOCFreshnessValueID, uint8* SecOCFreshnessValue,
                                    uint32* SecOCFreshnessValueLength) {
    Std_ReturnType result = FVM_GetTxFreshness(SecOCFreshnessValueID, SecOCFreshnessValue, SecOCFreshnessValueLength);
    return result;
}


/********************************************************
 *          * Function Info *                           *
 *                                                      *
 * Function_Name        : SecOC_GetTxFreshnessTruncData *
 * Function_Index       : 8.5.4 [SWS_SecOC_91003]       *
 * Function_File        : SWS of SecOC                  *
 * Function_Description  : This interface is used by the *
 * SecOC to obtain the current freshness value          *
 * The interface function provides also the truncated   *
 * freshness transmitted in the secured I-PDU.          *
 *******************************************************/

Std_ReturnType SecOC_GetTxFreshnessTruncData( uint16 SecOCFreshnessValueID, uint8* SecOCFreshnessValue, uint32* SecOCFreshnessValueLength, uint8* SecOCTruncatedFreshnessValue, uint32* SecOCTruncatedFreshnessValueLength) {
    Std_ReturnType result = FVM_GetTxFreshnessTruncData(SecOCFreshnessValueID, SecOCFreshnessValue, SecOCFreshnessValueLength, SecOCTruncatedFreshnessValue, SecOCTruncatedFreshnessValueLength);
    return result;
}


/************************************************************
*          * Function Info *                                *
*                                                           *
* Function_Name       : prepareFreshnessTx                  *
* Function_Index      : SecOC internal                      *
* Parameter in        : TxPduId, SecOCIntermediate          *
* Parameter out       : SecOCIntermediate                   *
* Function_Description : This function prepares the          *
* freshnes value for the secure communication. It           *
* will query freshness data using SecOC_GetTxFreshness or   *
* SecOC_GetTxFreshnessTruncData API based on configuration  *
* and store it in Intermediate structure                    *
************************************************************/
static Std_ReturnType prepareFreshnessTx(const PduIdType TxPduId, SecOC_TxIntermediateType *SecOCIntermediate)
{
    Std_ReturnType result = E_OK;

    /* [SWS_SecOC_00220] */
    (void)memset(SecOCIntermediate->Freshness, 0, sizeof(SecOCIntermediate->Freshness));
    (void)memset(SecOCIntermediate->FreshnessTrunc, 0, sizeof(SecOCIntermediate->FreshnessTrunc));

    SecOCIntermediate->FreshnessLenBits = SecOCTxPduProcessing[TxPduId].SecOCFreshnessValueLength;
    SecOCIntermediate->FreshnessTruncLenBits = SecOCTxPduProcessing[TxPduId].SecOCFreshnessValueTruncLength;

    if(SecOCGeneral->SecOCQueryFreshnessValue == SecOC_CFUNC)
    {
        /* [SWS_SecOC_00221] */
        if(SecOCTxPduProcessing[TxPduId].SecOCProvideTxTruncatedFreshnessValue == TRUE)
        {

            /* [SWS_SecOC_00094] */
            result = SecOC_GetTxFreshnessTruncData(
                SecOCTxPduProcessing[TxPduId].SecOCFreshnessValueId,
                SecOCIntermediate->Freshness,
                &SecOCIntermediate->FreshnessLenBits,
                SecOCIntermediate->FreshnessTrunc,
                &SecOCIntermediate->FreshnessTruncLenBits
            );

        }
        /* [SWS_SecOC_00222] */
        else
        {

            result = SecOC_GetTxFreshness(
                SecOCTxPduProcessing[TxPduId].SecOCFreshnessValueId,
                SecOCIntermediate->Freshness,
                &SecOCIntermediate->FreshnessLenBits
            );

        }
    }
    return result;
}


/********************************************************
 *          * Function Info *                           *
 *                                                      *
 * Function_Name        : authenticate                  *
 * Function_Index       : SecOC internal                *
 * Parameter in         : TxPduId                       *
 * Parameter in         : AuthPdu                       *
 * Parameter out        : SecPdu                        *
 * Function_Description  : This function generates the   *
 * secured PDU using authenticator, payload, freshness  *
 *  value                                               *
 *******************************************************/
static Std_ReturnType authenticate(const PduIdType TxPduId, PduInfoType* AuthPdu, PduInfoType* SecPdu)
{
    /* [SWS_SecOC_00031] authentication steps */
    Std_ReturnType result = E_NOT_OK;

    /* [SWS_SecOC_00033] */
    SecOC_TxIntermediateType SecOCIntermediate;

    //Clear the SecOCIntermediate
    (void)memset(&SecOCIntermediate, 0, sizeof(SecOCIntermediate));

    result = prepareFreshnessTx(TxPduId, &SecOCIntermediate);
    /* [SWS_SecOC_00227] */
    if(( result == E_BUSY) ||  (result == E_NOT_OK))
    {
        return result;
    }

    /* [SWS_SecOC_00034] */
    constructDataToAuthenticatorTx(TxPduId, &SecOCIntermediate, AuthPdu);
    /* Authenticator generation */
    SecOCIntermediate.AuthenticatorLen = BIT_TO_BYTES(SecOCTxPduProcessing[TxPduId].SecOCAuthInfoTruncLength);

    /* [SWS_SecOC_00035], [SWS_SecOC_00036]  [SWS_SecOC_00012]*/
    result = Csm_MacGenerate(
        SecOCTxPduProcessing[TxPduId].SecOCDataId,
        0,
        SecOCIntermediate.DataToAuth,
        SecOCIntermediate.DataToAuthLen,
        SecOCIntermediate.AuthenticatorPtr,
        &SecOCIntermediate.AuthenticatorLen
    );

    /* [SWS_SecOC_00227] */
    if( (result == E_NOT_OK) || (result == E_BUSY) || (result == E_QUEUE_FULL) )
    {
        return result;
    }

    /* [SWS_SecOC_00037] SECURED = HEADER(OPTIONAL) + AuthPdu + TruncatedFreshnessValue(OPTIONAL) + Authenticator */
    PduLengthType SecPduLen = 0;

    /* [SWS_SecOC_00262] Header */
    uint32 headerLen = SecOCTxPduProcessing[TxPduId].SecOCTxSecuredPduLayer->SecOCTxSecuredPdu->SecOCAuthPduHeaderLength;
    if(headerLen > 0)
    {
        /* [SWS_SecOC_00261] The Secured I-PDU Header shall indicate the length of the Authentic I-PDU in bytes */
        (void)memcpy(&SecPdu->SduDataPtr[SecPduLen], &AuthPdu->SduLength, headerLen);
        SecPduLen += headerLen;
    }

    /* AuthPdu */
    (void)memcpy(&SecPdu->SduDataPtr[SecPduLen], AuthPdu->SduDataPtr, AuthPdu->SduLength);
    SecPduLen += AuthPdu->SduLength;

    /* [SWS_SecOC_00230], [SWS_SecOC_00231] */
    boolean IsFreshnessTruncated = (SecOCTxPduProcessing[TxPduId].SecOCProvideTxTruncatedFreshnessValue == TRUE);
    uint8 *MsgFreshness = (IsFreshnessTruncated) ? SecOCIntermediate.FreshnessTrunc : SecOCIntermediate.Freshness;
    uint32 FreshnesslenBytes = BIT_TO_BYTES(SecOCTxPduProcessing[TxPduId].SecOCFreshnessValueTruncLength);

    /* [SWS_SecOC_00094] TruncatedFreshnessValue */
    (void)memcpy(&SecPdu->SduDataPtr[SecPduLen], MsgFreshness, FreshnesslenBytes);
    SecPduLen += FreshnesslenBytes;

    /* Authenticator */
    (void)memcpy(&SecPdu->SduDataPtr[SecPduLen], SecOCIntermediate.AuthenticatorPtr, SecOCIntermediate.AuthenticatorLen);
    SecPduLen += SecOCIntermediate.AuthenticatorLen;

    SecPdu->SduLength = SecPduLen;

    /* [SWS_SecOC_00212] */
    SecPdu->MetaDataPtr = AuthPdu->MetaDataPtr;

    /* Clear Auth */
    AuthPdu->SduLength = 0;

    return result;
}

