#ifndef TELEMETRY_H
#define TELEMETRY_H

#include "metrics.h"

void telemetry_init(void);
void telemetry_task(void *arg);

// send metrics to AI controller (MQTT / HTTP)
void send_to_server(net_metrics_t metrices);

#endif // TELEMETRY_H
