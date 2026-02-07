#include "telemetry.h"
#include "metrics.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


void telemetry_init(void)
{
    // MQTT / HTTP init
}

void telemetry_task(void *arg)
{
    while (1) {
        net_metrics_t m = get_metrics();

        // Example JSON
        /*
        {
          "bw": m.bandwidth_mbps,
          "rtt": m.rtt_ms,
          "loss": m.packet_loss,
          "rssi": m.rssi,
          "flow": m.flow_type
        }
        */

        void send_to_server(net_metrics_t metrics);
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}
