//
// Created by itsmeayoub on 03/03/24.
//

#include "SecOC/SecOC_Lcfg.h"
#include "SecOC/SecOC_Cfg.h"

/* [SWS_SecOC_00057]  The SecOC module shall provide sufficient buffers to store the Authentic I-PDUs and the Secured I-PDUs and the outgoing secured I-PUD.*/
/* [SWS_SecOC_00058]  The SecOC module shall allocate internal buffer capacities to store the Authentic I-PDU and the Authentication Information in a consecutive memory location. */
/* [SWS_SecOC_00146]  The SecOC module shall provide separate buffers for the Authentic I-PDU and the Secured I-PDU. */

uint8 SecOC_AuthenticBufferTx[SECOC_AUTHENTIC_PDU_MAX_LENGTH];
uint8 SecOC_SecuredBufferTx[SECOC_SECURED_PDU_MAX_LENGTH];

uint8 SecOC_AuthenticBufferRx[SECOC_AUTHENTIC_PDU_MAX_LENGTH];
uint8 SecOC_SecuredBufferRx[SECOC_SECURED_PDU_MAX_LENGTH];

PduInfoType SecOC_PduBufferRx = {
    SecOC_SecuredBufferRx,
    NULL,
    0
};

PduInfoType SecOC_PduBufferTx = {
    SecOC_SecuredBufferTx,
    NULL,
    0
};

PduInfoType SecOC_AuthenticPduBufferTx = {
    SecOC_AuthenticBufferTx,
    NULL,
    0
};

PduInfoType SecOC_AuthenticPduBufferRx = {
    SecOC_AuthenticBufferRx,
    NULL,
    0
};
/*
* Start Of General
 */

SecOC_MainFunctionTxType SecOC_MainFunctionTxConf =
    {
        SECOC_MAIN_FUNCTION_PERIOD_TX,
        SECOC_MAIN_FUNCTION_TX_PARTITION_REF, /* NOT SURE ABOUT THAT TYPE */

};


SecOC_MainFunctionRxType SecOCMainFunctionRx =
    {
        SECOC_MAIN_FUNCTION_PERIOD_RX,
        SECOC_MAIN_FUNCTION_RX_PARTITION_REF, /* NOT SURE ABOUT THAT TYPE */

};



SecOC_GeneralType SecOC_General =
    {
        SECOC_DEFAULT_AUTHENTICATION_INFORAMTION_PATTERN_VALUE,
        SECOC_DEV_ERROR_DETECT,
        SECOC_ENABLE_FORCED_PASS_OVERRIDE,
        SECOC_ENABLE_SECURITY_EVENT_REPORTING,
        SECOC_IGNORE_VERIFICATION_RESULT,
        SECOC_MAX_ALIGN_SCALAR_TYPE,
        SECOC_OVERRIDE_STATUS_WITH_DATA_ID,
        SECOC_PROPAGATE_ONLY_FINAL_VERIFICATION_STATUS,
        SECOC_QUERY_FRESHNESS_VALUE,
        /* SECOC_VERIFICATION_STATUS_CALLOUT,*/
        SECOC_VERSION_INFO_API,
        /*SECOC_SECURITY_EVENT_REFS,*/ /* can't have the container of it */

};

SecOCRxAuthenticPduLayer_Type SecOC_RxAuthenticPdu[] = {
    {
        SECOC_RX_PDU_TYPE,
        &SecOC_AuthenticPduBufferRx,
    }
};

SecOCRxSecuredPdu_Type SecOC_RxSecuredPdu[] = {
    {
        SECOC_AUTH_PDU_HEADER_LENGTH,
        SECOC_RX_SECURED_LAYER_PDU_ID,
        SECOC_SECURED_RX_PDU_VERIFICATION,
        &SecOC_PduBufferRx,
    }
};

SecOCRxSecuredPduLayer_Type SecOC_RxSecuredPduLayer[] = {
    {
        &SecOC_RxSecuredPdu[0],
        NULL
    }
};

CsmJob_Type CsmJob = {
    CSM_JOB_ID,
};

SecOCRxAuthServiceConfigRef_Type SecOCRxAuthServiceConfigRef = {
    &CsmJob,
};

SecOCSameBufferPduCollection_Type SecOC_SameBufferPduRef = {
    SECOC_BUFFERLENGTH
};

SecOCTxAuthServiceConfigRef_Type SecOCTxAuthServiceConfigRef = {
    &CsmJob,
};

SecOCTxAuthenticPduLayer_Type SecOC_TxAuthenticPduLayer[] = {
    {
        SECOC_TX_PDUTYPE,
        SECOC_TX_AUTHENTIC_LAYER_PDUID,
        &SecOC_AuthenticPduBufferTx,
    }
};

SecOCTxSecuredPdu_Type SecOCTxSecuredPdu[] = {
    {
        SECOC_AUTH_PDU_HEADER_LENGTH,
        SECOC_TX_SECURED_LAYER_PDUID,
        &SecOC_PduBufferTx,
    }
};

SecOCTxAuthenticPdu_Type SecOC_TxAuthenticPdu[] = {
    {
        SECOC_AUTH_PDU_HEADER_LENGTH,
        6,
        &SecOC_AuthenticPduBufferTx

    }
};

SecOCTxSecuredPduLayer_Type SecOC_TxSecuredPduLayer[] = {
    {
        &SecOCTxSecuredPdu[0],
        NULL
    }
};

SecOCTxPduProcessing_Type SecOC_TxPduProcessing[] = {
    {
        SECOC_AUTHENTICATION_BUILD_ATTEMPTS,
        SECOC_TX_AUTH_INFO_TRUNC_LENGTH,
        SECOC_TX_DATA_ID,
        SECOC_TX_FRESHNESS_VALUE_ID,
        SECOC_TX_FRESHNESS_VALUE_LENGTH,
        SECOC_TX_FRESHNESS_VALUE_TRUNC_LENGTH,
        SECOC_PROVIDE_TX_TRUNCATED_FRESHNESS_VALUE,
        SECOC_RE_AUTHENTICATE_AFTER_TRIGGER_TRANSMIT,
        SECOC_TX_PDU_UNUSED_AREAS_DEFAULT,
        SECOC_USE_TX_CONFIRMATION,
        &SecOC_SameBufferPduRef,
        NULL,
        &SecOC_TxSecuredPduLayer[0],
        &SecOC_TxAuthenticPduLayer[0],
        NULL,
    }
};

SecOCRxPduProcessing_Type SecOC_RxPduProcessing[] = {
    {
        SECOC_AUTH_DATA_FRESHNESS_LENGTH,
        SECOC_AUTH_DATA_FRESHNESS_START_POSITION,
        SECOC_AUTHENTICATION_BUILD_ATTEMPTS,
        SECOC_AUTHENTICATION_VERIFY_ATTEMPTS,
        SECOC_RX_AUTH_INFO_TRUNC_LENGTH,
        SECOC_RX_DATA_ID,
        SECOC_RX_FRESHNESS_VALUE_ID,
        SECOC_RX_FRESHNESS_VALUE_LENGTH,
        SECOC_RX_FRESHNESS_VALUE_TRUNC_LENGTH,
        SECOC_RECEPTION_OVERFLOW_STRATEGY,
        SECOC_RECEPTION_QUEUE_SIZE,
        SECOC_USE_AUTH_DATA_FRESHNESS,
        SECOC_VERIFICATION_STATUS_PROPAGATION_MODE,
        &SecOCRxAuthServiceConfigRef,
        &SecOC_SameBufferPduRef,
        &SecOC_RxSecuredPduLayer[0],
        &SecOC_RxAuthenticPdu[0],
        NULL,
    }
};


SecOC_ConfigType SecOC_Config = {
    &SecOC_General,
    &SecOC_RxPduProcessing[0],
    &SecOC_TxPduProcessing[0],
    SecOC_SameBufferPduRef
};

SecOC_TxCounter_Type SecOCTxCounters[SECOC_NUM_TX_PDU_PROCESSING] = {
    {
        .SecOCAuthenticationBuildCounter = (uint16)0
    }
};

SecOC_RxCounter_Type SecOCRxCounters[SECOC_NUM_RX_PDU_PROCESSING] = {
    {
        .SecOCAuthenticationBuildCounter = (uint16)0,
        .SecOCAuthenticationVerifyCounter = (uint16)0
    }
};