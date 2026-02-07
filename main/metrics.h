#ifndef METRICS_H
#define METRICS_H

typedef struct {
    float bandwidth_mbps;
    float rtt_ms;
    float packet_loss;
    int   rssi;
    int   latency_ms;
    int   load;
    int   flow_type;
} net_metrics_t;

/* Function declarations only */
void metrics_init(void);
void metrics_task(void *arg);
net_metrics_t get_metrics(void);

#endif // METRICS_H
