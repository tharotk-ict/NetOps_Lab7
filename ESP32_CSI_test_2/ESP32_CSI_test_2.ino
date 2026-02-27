#include "esp_wifi.h"
#include "WiFi.h"

void wifi_csi_rx_cb(void *ctx, wifi_csi_info_t *data) {
  Serial.print("CSI,");
  for (int i = 0; i < data->len; i++) {
    Serial.print(data->buf[i]);
    Serial.print(",");
  }
  Serial.println();
}

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.begin("muict_iot_ap1", "muIOTict");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
  esp_wifi_init(&cfg);

  wifi_csi_config_t csi_config = {
    .lltf_en = 1,
    .htltf_en = 1,
    .stbc_htltf2_en = 1,
    .ltf_merge_en = 1,
    .channel_filter_en = 0,
    .manu_scale = 0,
    .shift = 0,
  };

  esp_wifi_set_csi_config(&csi_config);
  esp_wifi_set_csi_rx_cb(&wifi_csi_rx_cb, NULL);
  esp_wifi_set_csi(true);
}

void loop() {}