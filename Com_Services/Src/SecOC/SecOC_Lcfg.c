//
// Created by itsmeayoub on 03/03/24.
//

#include "SecOC/SecOC_Lcfg.h"

/* [SWS_SecOC_00057]  The SecOC module shall provide sufficient buffers to store the Authentic I-PDUs and the Secured I-PDUs and the outgoing secured I-PUD.*/
/* [SWS_SecOC_00058]  The SecOC module shall allocate internal buffer capacities to store the Authentic I-PDU and the Authentication Information in a consecutive memory location. */
/* [SWS_SecOC_00146]  The SecOC module shall provide separate buffers for the Authentic I-PDU and the Secured I-PDU. */

uint8 SecOC_AuthenticBufferTx[SECOC_AUTHENTIC_PDU_MAX_LENGTH];
uint8 SecOC_SecuredBufferTx[SECOC_SECURED_PDU_MAX_LENGTH];

uint8 SecOC_AuthenticBufferRx[SECOC_AUTHENTIC_PDU_MAX_LENGTH];
uint8 SecOC_SecuredBufferRx[SECOC_SECURED_PDU_MAX_LENGTH];
