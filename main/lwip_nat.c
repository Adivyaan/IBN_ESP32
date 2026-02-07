#include "lwip/ip4.h"
#include "lwip/netif.h"
#include "lwip_nat.h"


void lwip_nat_init(void)
{
    ip4_nat_init();
    ip4_nat_enable(1);
}
