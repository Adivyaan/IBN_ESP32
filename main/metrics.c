#include "metrics.h"
#include "wifi_manager.h"
#include <string.h>                 
#include "freertos/FreeRTOS.h"      
#include "freertos/task.h"
#include "esp_timer.h"

static net_metrics_t metrics;

void metrics_init(void)
{
    memset(&metrics, 0, sizeof(metrics));
}

void measure_rtt(void)
{
    // Send UDP/ICMP probe
    // metrics.rtt_ms = recv_time - send_time;
}

void measure_bandwidth(void)
{
    // bytes_sent / time_window
    metrics.bandwidth_mbps = 8.2; // placeholder
}

void detect_flow_type(void)
{
    if (metrics.bandwidth_mbps > 5)
        metrics.flow_type = 1; // VIDEO
    else
        metrics.flow_type = 0; // IOT
}

void metrics_task(void *arg)
{
    while (1) {
        metrics.rssi = wifi_manager_get_rssi();
        measure_rtt();
        measure_bandwidth();
        detect_flow_type();
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}


net_metrics_t get_metrics(void)
{
    return metrics;
}
