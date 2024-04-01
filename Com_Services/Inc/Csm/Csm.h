//
// Created by itsmeayoub on 20/02/24.
//
#ifndef SECOC_MODULE_CSM_H
#define SECOC_MODULE_CSM_H

#include "Std_Types.h"
#include "Rte_Csm_Type.h"

/***********************************************************************************************************************
* Service name: Csm_MacGenerate                                                                                        *
* Sws_Index : 8.3.3.1 [SWS_Csm_00982]                                                                                  *
* Service ID[hex]: 0x60                                                                                                *
* Sync/Async: Depends on configuration                                                                                 *
* Reentrancy: Reentrant                                                                                                *
* Parameters (in):     JobId        - Identifier of the job using the CSM service                                      *
*                      Mode         - Indicate which operation mode to perform.                                        *
*                      dataPtr      - Pointer to the data for which the MAC shall be computed.                         *
*                      dataLength   - Length of the data to be processed(Bytes).                                       *
* Parameters (inout):  macLengthPtr - Holds a pointer to the memory location in which the output length in bytes is    *
*                                     stored. On calling this function, this parameter shall contain the size of the   *
*                                     buffer provided by macPtr. When the request has finished, the actual length of   *
*                                     returned MAC shall be stored. If the provided length information is smaller than *
*                                     the total length of the MAC result, the macPtr will contain the truncated MAC    *
*                                    result.                                                                          *
* Parameters (out):    macPtc       - Contains pointer to the data where the MAC shall be stored.                      *
* Return value:     Std_ReturnType  - E_OK: Request successful                                                         *
*                                   - E_NOT_OK: Request failed                                                         *
*                                   - CRYPTO_E_BUSY: Request failed, service is still busy                             *
*                                   - CRYPTO_E_KEY_NOT_VALID: Request failed, the key's state is "invalid"             *
*                                   - CRYPTO_E_KEY_SIZE_MISMATCH: Request failed, a key element has the wrong size.    *
*                                   - CRYPTO_E_KEY_EMPTY: Request failed because of uninitialized source key element   *
* Description: Uses the given data to perform a MAC generation and stores the MAC in the memory location pointed by    *
*              the MAC pointer                                                                                         *
***********************************************************************************************************************/
Std_ReturnType Csm_MacGenerate(
    uint32 JobId,
    Crypto_OperationModeType Mode,
    const uint8 *dataPtr,
    uint32 dataLength,
    uint8 *macPtr,
    uint32 *macLengthPtr
);

/***********************************************************************************************************************
* Service name: Csm_MacVerify                                                                                          *
* Sws_Index : 8.3.3.2 [SWS_Csm_01050]                                                                                  *
* Service ID[hex]: 0x61                                                                                                *
* Sync/Async: Depends on configuration                                                                                 *
* Reentrancy: Reentrant                                                                                                *
* Parameters (in):     JobId        - Identifier of the job using the CSM service                                      *
*                      Mode         - Indicate which operation mode to perform.                                        *
*                      dataPtr      - Pointer to the data for which the MAC shall be verified.                         *
*                      dataLength   - Length of the data fo which MAC shall be verified (Bytes).                       *
*                      macPtr       - Pointer to the MAC value to be verified.                                         *
*                      macLength    - Contains the MAC length in BITS to be verified                                   *
* Parameters (inout):  None                                                                                            *
* Parameters (out):    verifyPtr    - Contains pointer to the memory location, which will hold the result of the MAC   *
*                                     Verification.                                                                    *
* Return value:     Std_ReturnType  - E_OK: Request successful                                                         *
*                                   - E_NOT_OK: Request failed                                                         *
*                                   - CRYPTO_E_BUSY: Request failed, service is still busy                             *
*                                   - CRYPTO_E_KEY_NOT_VALID: Request failed, the key's state is "invalid"             *
*                                   - CRYPTO_E_KEY_SIZE_MISMATCH: Request failed, a key element has the wrong size.    *
*                                   - CRYPTO_E_KEY_EMPTY: Request failed because of uninitialized source key element   *
* Description: Verifies the given MAC by comparing if the MAC is generated with the given data.                        *
***********************************************************************************************************************/
Std_ReturnType Csm_MacVerify(
    uint32 JobId,
    Crypto_OperationModeType Mode,
    const uint8 *dataPtr,
    uint32 dataLength,
    const uint8 *macPtr,
    const uint32 macLength,
    Crypto_VerifyResultType *verifyPtr
);

#endif //SECOC_MODULE_CSM_H
