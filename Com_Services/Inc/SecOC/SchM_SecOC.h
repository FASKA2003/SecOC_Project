//
// Created by itsmeayoub on 22/02/24.
//

#ifndef SECOC_MODULE_SCHM_SECOC_H
#define SECOC_MODULE_SCHM_SECOC_H

/**********************************************************************************************************************
                                                 FUNCTION PROTOTYPES
 *********************************************************************************************************************/
/*********************************************************************************************************************
 * Service name : SecOC_MainFunctionRx                                                                          *
 * Sws_Index : [SWS_PduR_00171]                                                                                 *
 * Service ID[hex]: 0x06                                                                                        *
 * Parameters (in): None                                                                                        *
 * Parameters (inout): None                                                                                     *
 * Parameters (out): None                                                                                       *
 * Return value:None                                                                                            *
 * Description: This service performs the processing of the SecOC module's authentication and verification      *
 *              processing for the Rx path.                                                                     *
 ***************************************************************************************************************/
void SecOC_MainFunctionRx(void);

/*********************************************************************************************************************
 * Service name : SecOC_MainFunctionTx                                                                          *
 * Sws_Index : [SWS_PduR_00176]                                                                                 *
 * Service ID[hex]: 0x03                                                                                        *
 * Parameters (in): None                                                                                        *
 * Parameters (inout): None                                                                                     *
 * Parameters (out): None                                                                                       *
 * Return value: None                                                                                           *
 * Description: This service performs the processing of the SecOC module's authentication and verification      *
 *              processing for the Tx path.                                                                     *
 ***************************************************************************************************************/
void SecOC_MainFunctionTx(void);

#endif //SECOC_MODULE_SCHM_SECOC_H
