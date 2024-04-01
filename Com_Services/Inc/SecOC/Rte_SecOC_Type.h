//
// Created by itsmeayoub on 11/03/24.
//

#ifndef SECOC_MODULE_RTE_SECOC_TYPE_H
#define SECOC_MODULE_RTE_SECOC_TYPE_H

/********************************************************************************************************/
/************************************************INCLUDES************************************************/
/********************************************************************************************************/

#include "Std_Types.h"
#include "FVM.h"

/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/

#define GET_TXFRESHNESS_CALLBACK_PTR FVM_GetTxFreshness

/* SWS_SecOC_91012 : SecOC_FreshnessArrayType*/
/* Index : 8.8.5.1*/
#define SECOC_MAX_FRESHNESS_SIZE 32
typedef uint8                 SecOC_FreshnessArrayType[SECOC_MAX_FRESHNESS_SIZE];


/* SWS_SecOC_00149 : SecOC_VerificationResultType*/
/* Index : 8.8.5.2*/
typedef enum {
    SECOC_VERIFICATIONSUCCESS = 0x00,
    SECOC_VERIFICATIONFAILURE = 0x01,
    SECOC_FRESHNESSFAILURE = 0x02,
    SECOC_AUTHENTICATIONBUILDFAILURE = 0x03,
    SECOC_NO_VERIFICATION = 0x04,
    SECOC_VERIFICATIONFAILURE_OVERWRITTEN = 0x05
}SecOC_VerificationResultType;

/* SWS_SecOC_00160 : SecOC_VerificationStatusType*/
/* Index : 8.8.5.3*/
typedef struct {
    uint16 freshnessValueID;
    SecOC_VerificationResultType verificationStatus;
    uint16 secOCDataId;
}SecOC_VerificationStatusType

/* SWS_SecOC_00991 : SecOC_OverrideStatusType*/
/* Index : 8.8.5.4*/
typedef enum {
    SECOC_OVERRIDE_DROP_UNTIL_NOTICE = 0x00,
    SECOC_OVERRIDE_DROP_UNTIL_LIMIT = 0x01,
    SECOC_OVERRIDE_CANCEL= 0x02,
    SECOC_OVERRIDE_PASS_UNTIL_NOTICE = 0x40,
    SECOC_OVERRIDE_SKIP_UNTIL_LIMIT = 0x41,
    SECOC_OVERRIDE_PASS_UNTIL_LIMIT = 0x42,
    SECOC_OVERRIDE_SKIP_UNTIL_NOTICE = 0x43
}SecOC_OverrideStatusType

typedef Std_ReturnType(*SecOC_GetTxFreshnessCalloutType)(uint16 , uint8* , uint32*);


#endif //SECOC_MODULE_RTE_SECOC_TYPE_H
