//
// Created by itsmeayoub on 02/04/24.
//

/********************************************************************************************************/
/************************************************INCLUDES************************************************/
/********************************************************************************************************/

#include "FVM.h"
#include "Rte_SecOC_Type.h"
#include "SecOC_Lcfg.h"
#include <string.h>


/********************************************************************************************************/
/*****************************************Global Variables**********************************************/
/********************************************************************************************************/
static SecOC_FreshnessArrayType Freshness_Counter[SecOC_FreshnessValue_ID_MAX] = {0};
static uint32 FreshnessCounterLength[SecOC_FreshnessValue_ID_MAX] = {0};


/********************************************************************************************************/
/*****************************************Global Variables**********************************************/
/********************************************************************************************************/
uint8 countBits(uint8 n) {
    uint8 count = 0;
    uint8 n_ = n;
    while (n_ > 0)
    {
        count++;
        n_ >>= 1;
    }
    return count;
}

/*
Count the Number of bit in array of bytes */
uint8 countSizeBits(const uint8* arrayBytes, uint8 maxSize)
{
    sint8 INDEX;
    uint8 length = 0;
    for (INDEX = maxSize - 1; INDEX >= 0; INDEX--) {
        if(arrayBytes[INDEX] != 0)
        {
            length = countBits(arrayBytes[INDEX]) + (INDEX * 8);
            break;
        }
    }
    return length;
}

/********************************************************************************************************/
/*****************************************FunctionPrototype**********************************************/
/********************************************************************************************************/

/********************************************************
 *          * Function Info *                           *
 *                                                      *
 * Function_Name        : FVM_IncreaseCounter           *
 * Function_Index       :                               *
 * Function_File        :                               *
 * Function_Description  : This API Increase the counter *
 *                                                      *
 *******************************************************/
Std_ReturnType FVM_IncreaseCounter(uint16 SecOCFreshnessValueID) {
    if (SecOCFreshnessValueID < SecOC_FreshnessValue_ID_MAX) {
        for (uint8 i = 0; i < 4; i++) {
            Freshness_Counter[SecOCFreshnessValueID][i] ++;
            if (Freshness_Counter[SecOCFreshnessValueID][i] != 0) {
                break;
            }
        }
        return E_OK;
    } else {
        return E_NOT_OK;
    }
}


/********************************************************
 *          * Function Info *                           *
 *                                                      *
 * Function_Name        : FVM_UpdateCounter             *
 * Function_Index       :                               *
 * Function_File        :                               *
 * Function_Description  : Set the Counter Value to      *
 * new Value                                            *
 *                                                      *
 *******************************************************/
Std_ReturnType FVM_UpdateCounter(uint16 SecOCFreshnessValueID, uint8* SecOCFreshnessValue,
                                 uint32 SecOCFreshnessValueLength) {
    if (SecOCFreshnessValueID < SecOC_FreshnessValue_ID_MAX) {
        uint32 SecOCFreshnessValueLengthBytes = BIT_TO_BYTES(SecOCFreshnessValueLength);
        memcpy(Freshness_Counter[SecOCFreshnessValueID], SecOCFreshnessValue, SecOCFreshnessValueLengthBytes);
        //calculate the number of bits in the counter
        FreshnessCounterLength[SecOCFreshnessValueID] = countSizeBits(Freshness_Counter[SecOCFreshnessValueID], SecOCFreshnessValueLengthBytes);
        return E_OK;
    } else {
        return E_NOT_OK;
    }
}

/********************************************************
 *          * Function Info *                           *
 *                                                      *
 * Function_Name        : FVM_GetTxFreshness            *
 * Function_Index       : 8.5.3 [SWS_SecOC_00126]       *
 * Function_File        : SWS of SecOC                  *
 * Function_Description  : This API returns the freshness*
 * value from the Most Significant Bits in the first    *
 * byte in the array (SecOCFreshnessValue),             *
 * in big endian format.                                *
 *******************************************************/
Std_ReturnType FVM_GetTxFreshness(uint16 SecOCFreshnessValueID, uint8* SecOCFreshnessValue,
                                  uint32* SecOCFreshnessValueLength) {
    if (SecOCFreshnessValueID > SecOC_FreshnessValue_ID_MAX) {
        return E_NOT_OK;
    } else if (*(SecOCFreshnessValueLength) > SECOC_FRESHNESS_MAX_LENGTH) {
        return E_NOT_OK;
    } else {
        uint32 actualFreshnessValLength = (*SecOCFreshnessValueLength <= FreshnessCounterLength[SecOCFreshnessValueID]) ? (*SecOCFreshnessValueLength ) :  (FreshnessCounterLength[SecOCFreshnessValueID]);
        uint32 actualfreshnessValLenBytes = BIT_TO_BYTES(actualFreshnessValLength);
        (void)memcpy(SecOCFreshnessValue, Freshness_Counter[SecOCFreshnessValueID], actualfreshnessValLenBytes);

        /* Update Length */
        *SecOCFreshnessValueLength = actualFreshnessValLength;
        return E_OK;
    }
}



/*******************************************************
 *          * Function Info *                           *
 *                                                      *
 * Function_Name        : SecOC_GetRxFreshness          *
 * Function_Index       : 8.5.1 [SWS_SecOC_91007]       *
 * Function_File        : SWS of SecOC                  *
 * Function_Description  : This interface is used by the *
 *  SecOC to obtain the current freshness value.        *
 *******************************************************/
Std_ReturnType FVM_GetRxFreshness( uint16 SecOCFreshnessValueID, const uint8* SecOCTruncatedFreshnessValue, uint32 SecOCTruncatedFreshnessValueLength, uint16 SecOCAuthVerifyAttempts, uint8* SecOCFreshnessValue, uint32* SecOCFreshnessValueLength) {
    Std_ReturnType result = E_OK;
    if (SecOCFreshnessValueID > SecOC_FreshnessValue_ID_MAX) {
        result = E_NOT_OK;
    } else if (SecOCTruncatedFreshnessValueLength > SECOC_FRESHNESS_MAX_LENGTH) {
        result = E_NOT_OK;
    } else {
        uint32 freshnessValLenBytes = BIT_TO_BYTES(FreshnessCounterLength[SecOCFreshnessValueID]);

        // Update Truncated FV length
        uint32 truncatedFreshnessValLenBytes = BIT_TO_BYTES(SecOCTruncatedFreshnessValueLength);
        SecOCTruncatedFreshnessValueLength = countSizeBits(SecOCTruncatedFreshnessValue, truncatedFreshnessValLenBytes);
        truncatedFreshnessValLenBytes = BIT_TO_BYTES(SecOCTruncatedFreshnessValueLength);

        uint32 maxTruncatedIndex = (truncatedFreshnessValLenBytes > 0) ? (truncatedFreshnessValLenBytes - 1) : (0);

        if (FreshnessCounterLength[SecOCFreshnessValueID] == SecOCTruncatedFreshnessValueLength && SecOCTruncatedFreshnessValueLength != 0) {
            (void)memcpy(SecOCFreshnessValue, SecOCTruncatedFreshnessValue, truncatedFreshnessValLenBytes);
            *SecOCFreshnessValueLength = SecOCTruncatedFreshnessValueLength;
        } else
        {
            SecOCAuthVerifyAttempts = 0;
            /* Put the Current Freshness in the FreshnessValue */
            (void)memcpy(SecOCFreshnessValue, Freshness_Counter[SecOCFreshnessValueID], freshnessValLenBytes);
            /* construction of Freshness Value */
            sint16 index;
            sint8 equalityFlag = memcmp(SecOCTruncatedFreshnessValue, Freshness_Counter[SecOCFreshnessValueID], truncatedFreshnessValLenBytes);
            for(index = maxTruncatedIndex; index >= 0; index--)
            {
                if(SecOCTruncatedFreshnessValue[index] > Freshness_Counter[SecOCFreshnessValueID][index] && SecOCTruncatedFreshnessValueLength != 0)
                {
                    /* most significant bits of FreshnessValue corresponding to FreshnessValueID |
                    FreshnessValue parsed from Secured I-PDU */
                    (void)memcpy(SecOCFreshnessValue, SecOCTruncatedFreshnessValue, maxTruncatedIndex);
                    uint8 remainingBitsTrunc = 8 - ((truncatedFreshnessValLenBytes * 8) - SecOCTruncatedFreshnessValueLength);
                    SecOCFreshnessValue[maxTruncatedIndex] = (SecOCTruncatedFreshnessValue[maxTruncatedIndex] & (~(0xFF << remainingBitsTrunc))) | (Freshness_Counter[SecOCFreshnessValueID][maxTruncatedIndex] & (0xFF << remainingBitsTrunc));
                    uint8 maxLength = (freshnessValLenBytes > truncatedFreshnessValLenBytes) ? (freshnessValLenBytes) : (truncatedFreshnessValLenBytes);
                    *SecOCFreshnessValueLength = countSizeBits(SecOCFreshnessValue,  maxLength);
                }
                else if ((SecOCTruncatedFreshnessValue[index] < Freshness_Counter[SecOCFreshnessValueID][index]) || (equalityFlag == 0))
                {
                    /*  most significant bits of (FreshnessValue corresponding to SecOCFreshnessValueID + 1) |
                    FreshnessValue parsed from payload */

                    (void)memcpy(SecOCFreshnessValue, SecOCTruncatedFreshnessValue, maxTruncatedIndex);
                    uint8 remainingBitsTrunc = 8 - ((truncatedFreshnessValLenBytes * 8) - SecOCTruncatedFreshnessValueLength);
                    if(remainingBitsTrunc == 0 || SecOCTruncatedFreshnessValueLength == 0)
                    {
                        SecOCFreshnessValue[maxTruncatedIndex] = Freshness_Counter[SecOCFreshnessValueID][maxTruncatedIndex] + 1;
                        if(Freshness_Counter[SecOCFreshnessValueID][maxTruncatedIndex] > SecOCFreshnessValue[maxTruncatedIndex])
                        {
                            for (index = maxTruncatedIndex + 1; index < freshnessValLenBytes+1; index ++)
                            {
                                SecOCFreshnessValue[index] ++;
                                if(SecOCFreshnessValue[index] != 0)
                                {
                                    break;
                                }
                            }
                        }
                    }
                    else if(remainingBitsTrunc == 8)
                    {
                        SecOCFreshnessValue[maxTruncatedIndex] = SecOCTruncatedFreshnessValue[maxTruncatedIndex];
                        for (index = maxTruncatedIndex + 1; index < freshnessValLenBytes+1; index ++)
                        {
                            SecOCFreshnessValue[index] ++;
                            if(SecOCFreshnessValue[index] != 0)
                            {
                                break;
                            }
                        }
                    }
                    else
                    {
                        uint8 MSBsCounter = (Freshness_Counter[SecOCFreshnessValueID][maxTruncatedIndex] >> remainingBitsTrunc) + 1;
                        uint8 MSBsCounterShift = MSBsCounter << remainingBitsTrunc;
                        uint8 index;
                        SecOCFreshnessValue[maxTruncatedIndex] = (SecOCTruncatedFreshnessValue[maxTruncatedIndex] & (~(0xFF << remainingBitsTrunc))) | (MSBsCounterShift);
                        if((MSBsCounterShift == 0) && (MSBsCounter > 0))
                        {
                            for (index = maxTruncatedIndex + 1; index < freshnessValLenBytes+1; index ++)
                            {
                                SecOCFreshnessValue[index] ++;
                                if(SecOCFreshnessValue[index] != 0)
                                {
                                    break;
                                }
                            }
                        }

                    }
                    *SecOCFreshnessValueLength = countSizeBits(SecOCFreshnessValue, freshnessValLenBytes + 1);
                }
                else
                {
                    continue;
                }
                break;
            }
        }

        /* verified that the constructed FreshnessVerifyValue is larger than the last stored notion of the Freshness Value */
        /* If it is not larger than the last stored notion of the Freshness Value,
         the FVM shall stop the verification and drop the Secured I-PDU */
        sint16 index = BIT_TO_BYTES(*SecOCFreshnessValueLength) - 1;
        sint8 equalityFlag = memcmp(SecOCFreshnessValue, Freshness_Counter[SecOCFreshnessValueID], index + 1);
        for(; index >= 0; index --)
        {
            if (Freshness_Counter[SecOCFreshnessValueID][index] < SecOCFreshnessValue[index])
            {
                result = E_OK;
            }
            else if (Freshness_Counter[SecOCFreshnessValueID][index] > SecOCFreshnessValue[index] || equalityFlag == 0)
            {
                result= E_NOT_OK;
            }
            else
            {
                continue;
            }
            break;
        }
    }
    return result;
}

/********************************************************
 *          * Function Info *                           *
 *                                                      *
 * Function_Name        : FVM_GetTxFreshnessTruncData   *
 * Function_Index       : 8.5.4 [SWS_SecOC_91003]       *
 * Function_File        : SWS of SecOC                  *
 * Function_Description  : This interface is used by the *
 * SecOC to obtain the current freshness value. The     *
 * interface function provides also the truncated       *
 * freshness transmitted in the secured I-PDU.          *
 *******************************************************/
Std_ReturnType FVM_GetTxFreshnessTruncData (uint16 SecOCFreshnessValueID, uint8* SecOCFreshnessValue,
                                           uint32* SecOCFreshnessValueLength, uint8* SecOCTruncatedFreshnessValue, uint32* SecOCTruncatedFreshnessValueLength) {
    Std_ReturnType result = E_OK;
    if (SecOCFreshnessValueID > SecOC_FreshnessValue_ID_MAX) {
        return E_NOT_OK;
    }
    else if (*SecOCFreshnessValueLength > SECOC_FRESHNESS_MAX_LENGTH) {
        return E_NOT_OK;
    }
    else {
        uint32 actualFreshnessValLength = (*SecOCFreshnessValueLength <= FreshnessCounterLength[SecOCFreshnessValueID]) ? (*SecOCFreshnessValueLength ) :  (FreshnessCounterLength[SecOCFreshnessValueID]);
        uint32 actualFreshnessValLenBytes = BIT_TO_BYTES(actualFreshnessValLength);
        uint32 truncatedFreshnessValLenBytes = BIT_TO_BYTES(*SecOCTruncatedFreshnessValueLength);
        uint32 actualFreshnessTruncatedValLen = (truncatedFreshnessValLenBytes <= actualFreshnessValLenBytes) ? (truncatedFreshnessValLenBytes) : (actualFreshnessValLenBytes);

        // get the freshness from the counter
        (void)memcpy(SecOCFreshnessValue, Freshness_Counter[SecOCFreshnessValueID], actualFreshnessValLenBytes);
        *SecOCFreshnessValueLength = actualFreshnessValLength;

        //trunc the LSBs from Freshness and store it in SecOCTruncatedFreshnessValue
        if (actualFreshnessTruncatedValLen > 0) {
            (void)memcpy(SecOCTruncatedFreshnessValue, SecOCFreshnessValue, actualFreshnessTruncatedValLen);
            uint8 bitTrunc = 8 - ((acctualFreshnessTruncVallength * 8) - *SecOCTruncatedFreshnessValueLength);
            SecOCTruncatedFreshnessValue[acctualFreshnessTruncVallength - 1] = (SecOCFreshnessValue[acctualFreshnessTruncVallength - 1] & (~(0xFF << bitTrunc)));
        }
        *SecOCTruncatedFreshnessValueLength = countSizeBits(SecOCTruncatedFreshnessValue, truncatedFreshnessValLenBytes);
    }
    return result;
}

#endif //SECOC_MODULE_FVM_H
