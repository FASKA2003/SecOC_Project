//
// Created by itsmeayoub on 03/03/24.
//

#ifndef SECOC_MODULE_SECOC_CFG_H
#define SECOC_MODULE_SECOC_CFG_H

#include "Std_Types.h"

#include "Std_Types.h"
#include "SecOC_Types.h"
#include "SecOC_Lcfg.h"

/*****************************************************************************************************************/
/*******************************************SecOC_General*********************************************************/
#define SECOC_DEFAULT_AUTHENTICATION_INFORMATION_PATTERN_MULTIPLICITY (uint8)0
#define SECOC_DEFAULT_AUTHENTICATION_INFORAMTION_PATTERN_VALUE        (uint8)0
#define SECOC_DEV_ERROR_DETECT                                        (boolean)FALSE
#define SECOC_ENABLE_FORCED_PASS_OVERRIDE                             (boolean)FALSE
#define SECOC_ENABLE_SECURITY_EVENT_REPORTING                         (boolean)FALSE
#define SECOC_IGNORE_VERIFICATION_RESULT                              (boolean)FALSE
#define SECOC_MAIN_FUNCTION_PERIOD_TX                                 (float64)0.5
#define SECOC_MAIN_FUNCTION_TX_PARTITION_REF                          (NULL)
#define SECOC_MAIN_FUNCTION_PERIOD_RX                                 (float64)0.5
#define SECOC_MAIN_FUNCTION_RX_PARTITION_REF                          (NULL)
#define SECOC_MAX_ALIGN_SCALAR_TYPE                                   (uint8)0
#define SECOC_OVERRIDE_STATUS_WITH_DATA_ID                            (boolean)FALSE
#define SECOC_PROPAGATE_ONLY_FINAL_VERIFICATION_STATUS                ((boolean)FALSE)
#define SECOC_QUERY_FRESHNESS_VALUE                                   (SecOCQueryFreshnessValue_Type)SecOC_CFUNC
#define SECOC_VERIFICATION_STATUS_CALLOUT                             ((SecOC_VerificationStatusCalloutType*)NULL)
#define SECOC_VERSION_INFO_API                                        (boolean)FALSE
//Configuration Parameter for SecOCBufferLength
#define SECOC_BUFFERLENGTH                                            ((uint32)100)
/*****************************************************************************************************************/
/*****************************************************************************************************************/

/*****************************************************************************************************************/
/*******************************************SecOCRxPduProcessing**************************************************/
#define SECOC_AUTH_DATA_FRESHNESS_LENGTH                              ((uint16)0)
#define SECOC_AUTH_DATA_FRESHNESS_START_POSITION                      ((uint16)5)
#define SECOC_AUTHENTICATION_BUILD_ATTEMPTS                           ((uint16)5)
#define SECOC_AUTHENTICATION_VERIFY_ATTEMPTS                          ((uint16)5)
#define SECOC_RX_AUTH_INFO_TRUNC_LENGTH                               ((uint16)24)
#define SECOC_RX_DATA_ID                                              ((uint16)0)
#define SECOC_RX_FRESHNESS_VALUE_ID                                   ((uint16)20)
#define SECOC_RX_FRESHNESS_VALUE_LENGTH                               ((uint8)24)
#define SECOC_RX_FRESHNESS_VALUE_TRUNC_LENGTH                            ((uint8)24)
#define SECOC_RECEPTION_OVERFLOW_STRATEGY                             (SecOCReceptionOverflowStrategy_Type)SecOC_QUEUE
#define SECOC_RECEPTION_QUEUE_SIZE                                    ((uint16)10)
#define SECOC_USE_AUTH_DATA_FRESHNESS                                 (boolean)FALSE
#define SECOC_VERIFICATION_STATUS_PROPAGATION_MODE                    (SecOCVerificationStatusPropagationMode_Type)SecOC_BOTH
#define CSM_JOB_ID                                                     ((CsmJob_Type)0)
#define SECOC_CLIENT_SERVER_VERIFICATION_STATUS_PROPAGATION_MODE      (SecOCVerificationStatusPropagationMode_Type)SecOC_BOTH
/*--------------------------------------SecOCRxSecuredPduLayer---------------------------------------------------*/
//-->Configuration Parameter for SecOCRxSecuredPdu
#define SECOC_AUTH_PDU_HEADER_LENGTH                                  ((uint8)1)
#define SECOC_RX_SECURED_LAYER_PDU_ID                                 ((uint16)10)
#define SECOC_RX_SECURED_RX_PDU_VERIFICATION                          (boolean)FALSE
//-->Configuration parameter for SecOCRxSecuredPduCollection
#define SECOC_SECURED_RX_PDU_VERIFICATION                             (boolean)FALSE
//---->Configuration parameter for SecOCRxCryptographicPdu
#define SECOC_RX_CRYPTOGRAPHIC_PDU_ID                                 ((uint16)0)
//---->Configuration parameter for SecOCRxAuthenticPdu
#define SECOC_RX_AUTH_PDU_HEADER_LENGTH                               ((uint8)1)
#define SECOC_RX_AUTHENTIC_PDU_ID                                     ((uint16)0)
/*---------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------SecOCRxPduSecuredArea----------------------------------------------------*/
#define SECOC_SECURED_RX_PDU_OFFSET                                   ((uint16)0)
/*---------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------SecOCRxAuthenticPduLayer-------------------------------------------------*/
//Configuration Parameter for SecOCRxAuthenticPduLayer
#define SECOC_RX_PDU_TYPE                                             (SecOCPduType)SECOC_IFPDU
/*---------------------------------------------------------------------------------------------------------------*/
/*****************************************************************************************************************/
/*************************************************SecOC_TxPduProcessing*******************************************/

/**************************************************************
 *          * Container Info *                                *
 *                                                            *
 * Container_Name        : SecOC_TxAuthenticPduLayer          *
 * Parent_Container_Name : SecOC_TxPduProcessing              *
 * Container_Index       : 10.1.14                            *
 **************************************************************/

#define SECOC_TX_PDUTYPE                    ((SecOCPduType)SECOC_IFPDU)
#define SECOC_TX_AUTHENTIC_LAYER_PDUID      ((uint16)0)


/**************************************************************
 *          * Container Info *                                *
 *                                                            *
 * Container_Name        : SecOC_TxSecuredPdu                 *
 * Parent_Container_Name : SecOC_TxSecuredPduLayer             *
 * Container_Index       : 10.1.16                            *
 **************************************************************/

#define SECOC_AUTH_PDUHEADER_LENGTH        ((uint8)1)
#define SECOC_TX_SECURED_LAYER_PDUID        ((uint16)0)


/************************************************************
 *          * Container Info *                              *
 *                                                          *
 * Container_Name        : SecOC_UseMessageLink             *
 * Parent_Container_Name : SecOC_TxSecuredPduCollection     *
 * Container_Index       : 10.1.20                          *
 ***********************************************************/

#define SECOC_MESSAGE_LINKLEN               ((uint16)3)
#define SECOC_MESSAGE_LINKPOS               ((uint16)5)

/************************************************************
 *          * Container Info *                              *
 *                                                          *
 * Container_Name        : SecOC_TxCryptographicPdu         *
 * Parent_Container_Name : SecOC_TxSecuredPduCollection     *
 * Container_Index       : 10.1.19                          *
 ***********************************************************/

#define SECOC_TX_CRYPTOGRAPHIC_PDUID        ((uint16)0)
//#define SECOC_TX_CRYPTOGRAPHIC_PDUREF       (NULL) /*((EcuC_PduType*)&EcuC_Pdu)*/

/************************************************************
 *          * Container Info *                              *
 *                                                          *
 * Container_Name        : SecOC_TxAuthenticPdu             *
 * Parent_Container_Name : SecOC_TxSecuredPduCollection     *
 * Container_Index       : 10.1.18                          *
 ***********************************************************/

#define SECOC_CRYPTO_AUTH_PDUHEADER_LENGTH         ((uint8)1)
#define SECOC_CRYPTO_TX_AUTHENTIC_PDUID            ((uint16)0)
//#define SECOC_CRYPTO_TX_AUTHENTIC_PDUREF



/****************************************************
 *          * Container Info *                      *
 *                                                  *
 * Container_Name        : SecOC_RxPduSecuredArea   *
 * Parent_Container_Name : SecOC_RxPduProcessing    *
 * Container_Index       : 10.1.22                  *
 ***************************************************/

#define SECOC_SECURED_RX_PDULENGTH          ((uint32)0)
#define SECOC_SECURED_RX_PDUOFFSET          ((uint32)0)



/****************************************************
 *          * Container Info *                      *
 *                                                  *
 * Container_Name        : SecOC_TxPduSecuredArea   *
 * Parent_Container_Name : SecOC_TxPduProcessing    *
 * Container_Index       : 10.1.21                  *
 ***************************************************/

#define SECOC_SECURED_TX_PDULENGTH          ((uint32)0)
#define SECOC_SECURED_TX_PDUOFFSET          ((uint32)0)


/****************************************************
 *          * Container Info *                      *
 *                                                  *
 * Container_Name        : SecOC_TxPduProcessing    *
 * Parent_Container_Name :                          *
 * Container_Index       : 10.1.11                  *
 ***************************************************/

#define SECOC_TX_AUTHENTICATION_BUILD_ATTEMPTS                        ((uint16)5)
#define SECOC_TX_AUTH_INFO_TRUNC_LENGTH                               ((uint32)32)
#define SECOC_TX_DATA_ID                                              ((uint16)0)
#define SECOC_TX_FRESHNESS_VALUE_ID                                   ((uint32)10)
#define SECOC_TX_FRESHNESS_VALUE_LENGTH                               ((uint32)24)
#define SECOC_TX_FRESHNESS_VALUE_TRUNC_LENGTH                         ((uint32)8)
#define SECOC_PROVIDE_TX_TRUNCATED_FRESHNESS_VALUE                    (boolean)TRUE
#define SECOC_RE_AUTHENTICATE_AFTER_TRIGGER_TRANSMIT                  (boolean)TRUE
#define SECOC_TX_PDU_UNUSED_AREAS_DEFAULT                             (uint8)0
#define SECOC_USE_TX_CONFIRMATION                                     (boolean)FALSE
/*****************************************************************************************************************/

#endif //SECOC_MODULE_SECOC_CFG_H

