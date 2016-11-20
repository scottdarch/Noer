/**
 * @file
 * Exports Private lwIP MIB 
 */

#ifndef LWIP_HDR_PRIVATE_MIB_H
#define LWIP_HDR_PRIVATE_MIB_H

#include "../../../../../../SDK_2.1_FRDM-K66F-GCC-Full/middleware/lwip_2.0.0/src/include/lwip/apps/snmp_core.h"
#include "../../../../../../SDK_2.1_FRDM-K66F-GCC-Full/middleware/lwip_2.0.0/src/include/lwip/apps/snmp_opts.h"

#ifdef __cplusplus
extern "C" {
#endif

/* export MIB */
extern const struct snmp_mib mib_private;

void lwip_privmib_init(void);

#ifdef __cplusplus
}
#endif

#endif
