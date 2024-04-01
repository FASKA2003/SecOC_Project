//
// Created by itsmeayoub on 03/03/24.
//

#ifndef SECOC_MODULE_SECOC_TYPES_H
#define SECOC_MODULE_SECOC_TYPES_H

typedef struct {
    uint32 CsmJobId;
}CsmJob_Type;

// SWS_SecOC_00162 : SecOC_StateType
typedef enum {
    SECOC_UNINIT,
    SECOC_INIT
}SecOC_StateType;

// ECUC_SecOC_00046 : SecOCVerificationStatusPropagationMode
typedef enum {
    SecOC_BOTH = 0,
    SecOC_FAILURE_ONLY,
    SecOC_NONE
}SecOCVerificationStatusPropagationMode_Type;

// ECUC_SecOC_00076 : SecOCReceptionOverflowStrategy
typedef enum {
    SecOC_QUEUE = 0,
    SecOC_REJECT,
    SecOC_REPLACE
}SecOCReceptionOverflowStrategy_Type;

//ECUC_SecOC_00078 : SecOCQueryFreshnessValue
typedef enum {
    SecOC_CFUNC,
    SecOC_RTE
}SecOCQueryFreshnessValue_Type;

//ECUC_SecOC_00044 : SecOCPduType
typedef enum {
    SECOC_IFPDU,
    SecOC_TPPDU
}SecOCPduType;


#endif //SECOC_MODULE_SECOC_TYPES_H
