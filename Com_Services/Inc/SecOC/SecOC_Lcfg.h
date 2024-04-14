//
// Created by itsmeayoub on 03/03/24.
//

#ifndef SECOC_MODULE_SECOC_LCFG_H
#define SECOC_MODULE_SECOC_LCFG_H

#include "Com.h"
#include "SecOC_Types.h"
#include "Std_Types.h"
#include "SecOC_Cfg.h"
/********************************************************************************************************/
/************************************************MACROS**************************************************/
#define SECOC_AUTHENTIC_PDU_MAX_LENGTH                      ((uint32)20)
#define SECOC_AUTHENTICATION_HEADER_MAX_LENGTH              ((uint8)4)
#define SECOC_TX_FRESHNESS_VALUE_LENGTH                               ((uint32)24)
#define SECOC_TX_DATA_TO_AUTHENTICATOR_LENGTH               (sizeof(PduIdType) + SECOC_AUTHENTIC_PDU_MAX_LENGTH + SECOC_TX_FRESHNESS_VALUE_LENGTH)

#define SECOC_FRESHNESS_MAX_LENGTH                          ((uint8)32)

#define SECOC_SECURED_PDU_MAX_LENGTH                        ((uint32)64)
#define SECOC_AUTHENTICATOR_MAX_LENGTH                      ((uint8)32)

#define SECOC_RX_DATA_TO_AUTHENTICATOR_LENGTH               (sizeof(PduIdType) + SECOC_AUTHENTIC_PDU_MAX_LENGTH + (SECOC_FRESHNESS_MAX_LENGTH/8 + 1))

#define SECOC_NUM_TX_PDU_PROCESSING                         6
#define SECOC_NUM_RX_PDU_PROCESSING                         6
/********************************************************************************************************/

// ECUC_SecOC_00048 : SecOCRxAuthServiceConfigRef
typedef CsmJob_Type SecOCRxAuthServiceConfigRef_Type;

typedef CsmJob_Type SecOCTxAuthServiceConfigRef_Type;

/* [SWS_SecOC_00057] The SecOC module shall provide sufficient buffers to store all intermediate data */
typedef struct
{

    uint8                   Freshness[SECOC_FRESHNESS_MAX_LENGTH/8];  /* Complete Freshness Value */
    uint32                  FreshnessLenBits;

    uint8                   FreshnessTrunc[SECOC_FRESHNESS_MAX_LENGTH/8];   /* Truncated freshness value */
    uint32                  FreshnessTruncLenBits;

    uint8                   DataToAuth[SECOC_TX_DATA_TO_AUTHENTICATOR_LENGTH];
    uint32                  DataToAuthLen;

    uint8                   AuthenticatorPtr[SECOC_AUTHENTICATOR_MAX_LENGTH];
    uint32                  AuthenticatorLen;

} SecOC_TxIntermediateType;

/* [SWS_SecOC_00057] The SecOC module shall provide sufficient buffers to store all intermediate data */
typedef struct
{
    uint8                   authenticPdu[SECOC_AUTHENTIC_PDU_MAX_LENGTH ];
    uint32                  authenticPduLen;

    uint8                   freshness[SECOC_FRESHNESS_MAX_LENGTH / 8];
    uint32                  freshnessLenBits;
    Std_ReturnType          freshnessResult;

    uint8                   mac[SECOC_AUTHENTICATOR_MAX_LENGTH / 8];
    uint32                  macLenBits;

    uint8                   DataToAuth[SECOC_RX_DATA_TO_AUTHENTICATOR_LENGTH];
    uint32                  DataToAuthLen;

} SecOC_RxIntermediateType;

typedef struct {
    SecOC_PduCollection_Type Type;
    uint16 CollectionId;
    uint16 AuthId;
    uint16 CryptId;
    Std_ReturnType status;
}SecOC_PduCollection;


// SecOC authentication Tx and Rx build counters.
typedef struct
{
    uint16 SecOCAuthenticationBuildCounter;
} SecOC_TxCounter_Type;

typedef struct
{
    uint16 SecOCAuthenticationVerifyCounter;
    uint16 SecOCAuthenticationBuildCounter;
} SecOC_RxCounter_Type;

// ECUC_SecOC_00009 : SecOCSameBufferPduCollection
typedef struct
{
    uint32 SecOCBufferLength;
} SecOCSameBufferPduCollection_Type;

// ECUC_SecOC_00064 : SecOCRxCryptographicPdu
typedef struct
{
    uint16 SecOCRxSecuredPduId;
    PduInfoType* SecOCRxCryptographicPdu;
} SecOCRxCryptographicPdu_Type;

// ECUC_SecOC_00061 : SecOCRxAuthenticPdu
typedef struct
{
    uint8 SecOCAuthPduHeaderLength;
    uint16 SecOCRxSecuredLayerPduId;
    PduInfoType* SecOCRxAuthenticLayerPduRef;
} SecOCRxAuthenticPdu_Type;

// ECUC_SecOC_00074 : SecOCUseMessageLink
typedef struct
{
    uint16 SecOCMessageLinkLen;
    uint16 SecOCMessageLinkPos;
} SecOCUseMessageLink_Type;

// ECUC_SecOC_00067 : SecOCRxSecuredPduCollection
typedef struct
{
    boolean SecOCSecuredRxPduVerification;
    SecOCRxAuthenticPdu_Type* SecOCRxAuthenticPdu;
    SecOCRxCryptographicPdu_Type* SecOCRxCryptographicPdu;
    SecOCUseMessageLink_Type* SecOCUseMessageLink;
} SecOCRxSecuredPduCollection_Type;

// ECUC_SecOC_00069 : SecOCRxSecuredPdu
typedef struct
{
    uint8 SecOCAuthPduHeaderLength;
    uint16 SecOCRxSecuredLayerPduId;
    boolean SecOCSecuredRxPduVerification;
    PduInfoType* SecOCRxSecuredLayerPduRef;
} SecOCRxSecuredPdu_Type;

// ECUC_SecOC_00041 : SecOCRxSecuredPduLayer
typedef struct
{
    SecOCRxSecuredPdu_Type* SecOCRxSecuredPdu;
    SecOCRxSecuredPduCollection_Type* SecOCRxSecuredPduCollection;
} SecOCRxSecuredPduLayer_Type;

// ECUC_SecOC_00075 : SecOCRxAuthenticPduLayer
typedef struct
{
    SecOCPduType SecOCPduType;
    PduInfoType* SecOCRxAuthenticLayerPduRef;
} SecOCRxAuthenticPduLayer_Type;

// ECUC_SecOC_00089 : SecOCRxPduSecuredArea
typedef struct
{
    uint32 SecOCRxSecuredRxPduLength;
    uint32 SecOCRxSecuredRxPduOffset;
} SecOCRxPduSecuredArea_Type;

// ECUC_SecOC_00011 : SecOCRxPduProcessing
typedef struct
{
    uint16 SecOCAuthDataFreshnessLen;
    uint16 SecOCAuthDataFreshnessStartPosition;
    uint16 SecOCAuthenticationBuildAttempts;
    uint16 SecOCAuthenticationVerifyAttempts;
    uint16 SecOCAuthInfoTruncLength;
    uint16 SecOCDataId;
    uint16 SecOCFreshnessValueId;
    uint8 SecOCFreshnessValueLength;
    uint8 SecOCFreshnessValueTruncLength;
    SecOCReceptionOverflowStrategy_Type SecOCReceptionOverflowStrategy;
    uint16 SecOCReceptionQueueSize;
    boolean SecOCUseAuthDataFreshness;
    SecOCVerificationStatusPropagationMode_Type SecOCVerificationStatusPropagationMode;
    SecOCRxAuthServiceConfigRef_Type* SecOCRxAuthServiceConfigRef;
    SecOCSameBufferPduCollection_Type* SecOCSameBufferPduRef;
    SecOCRxSecuredPduLayer_Type* SecOCRxSecuredPduLayer;
    SecOCRxAuthenticPduLayer_Type* SecOCRxAuthenticPduLayer;
    SecOCRxPduSecuredArea_Type* SecOCRxPduSecuredArea;
} SecOCRxPduProcessing_Type;

// ECUC_SecOC_00070 : SecOCTxSecuredPdu
typedef struct
{
    uint8 SecOCAuthPduHeaderLength;
    uint16 SecOCTxSecuredLayerPduId;
    PduInfoType* SecOCTxSecuredLayerPduRef;
} SecOCTxSecuredPdu_Type;

// ECUC_SecOC_00072 : SecOCTxAuthenticPdu
typedef struct
{
    uint8 SecOCAuthPduHeaderLength;
    uint16 SecOCTxAuthenticPduId;
    PduInfoType* SecOCTxAuthenticPduRef;
} SecOCTxAuthenticPdu_Type;

// ECUC_SecOC_00073 : SecOCTxCryptographicPdu
typedef struct
{
    uint16 SecOCTxCryptographicPduId;
    PduInfoType* SecOCTxCryptographicPduRef;
} SecOCTxCryptographicPdu_Type;

// ECUC_SecOC_00071 : SecOCTxSecuredPduCollection
typedef struct
{
    SecOCTxAuthenticPdu_Type* SecOCTxAuthenticPdu;
    SecOCTxCryptographicPdu_Type* SecOCTxCryptographicPdu;
    SecOCUseMessageLink_Type* SecOCUseMessageLink;
} SecOCTxSecuredPduCollection_Type;

// ECUC_SecOC_00024 : SecOCTxSecuredPduLayer
typedef struct
{
    SecOCTxSecuredPdu_Type* SecOCTxSecuredPdu;
    SecOCTxSecuredPduCollection_Type* SecOCTxSecuredPduCollection;
} SecOCTxSecuredPduLayer_Type;

// ECUC_SecOC_00086 : SecOCTxPduSecuredArea
typedef struct
{
    uint32 SecOCTxSecuredTxPduLength;
    uint32 SecOCTxSecuredTxPduOffset;
} SecOCTxPduSecuredArea_Type;

// ECUC_SecOC_00023 : SecOCTxAuthenticPduLayer
typedef struct
{
    SecOCPduType SecOCPduType;
    uint16 SecOCTxAuthenticLayerPduId;
    PduInfoType* SecOCTxAuthenticLayerPduRef;
} SecOCTxAuthenticPduLayer_Type;
// ECUC_SecOC_00012 : SecOCTxPduProcessing
typedef struct
{
    uint16 SecOCAuthenticationBuildAttempts;
    uint16 SecOCAuthInfoTruncLength;
    uint16 SecOCDataId;
    uint16 SecOCFreshnessValueId;
    uint8 SecOCFreshnessValueLength;
    uint8 SecOCFreshnessValueTruncLength;
    boolean SecOCProvideTxTruncatedFreshnessValue;
    boolean SecOCReAuthenticateAfterTriggerTransmit;
    uint8 SecOCTxPduUnusedAreasDefault;
    boolean SecOCUseTxConfirmation;
    SecOCSameBufferPduCollection_Type* SecOCSameBufferPduRef;
    SecOCTxAuthServiceConfigRef_Type* SecOCTxAuthServiceConfigRef;
    SecOCTxSecuredPduLayer_Type* SecOCTxSecuredPduLayer;
    SecOCTxAuthenticPduLayer_Type* SecOCTxAuthenticPduLayer;
    SecOCTxPduSecuredArea_Type* SecOCTxPduSecuredArea;
} SecOCTxPduProcessing_Type;

// ECUC_SecOC_00002 : SecOCGeneral
typedef struct
{
    uint8 SecOCDefaultAuthenticationInformationPattern;
    boolean SecOCDevErrorDetect;
    boolean SecOCEnableForcedPassOverride;
    boolean SecOCIgnoreVerificationResult;
    float64 SecOCMainFunctionPeriodRx;
    float64 SecOCMainFunctionPeriodTx;
    uint8 SecOCMaxAlignScalarType[100];
    boolean SecOCOverrideStatusWithDataId;
    boolean SecOCVersionInfoApi;
    SecOCQueryFreshnessValue_Type SecOCQueryFreshnessValue;
    // To be implemented SecOCVerificationStatusCallout
} SecOCGeneral_Type;

// ECUC_SecOC_00001 : SecOC_ConfigType
typedef struct
{
    SecOCGeneral_Type* SecOCGeneral;
    SecOCRxPduProcessing_Type* SecOCRxPduProcessing;
    SecOCTxPduProcessing_Type* SecOCTxPduProcessing;
    SecOCSameBufferPduCollection_Type SecOCSameBufferPduCollection;
} SecOC_ConfigType;

#endif // SECOC_MODULE_SECOC_LCFG_H
