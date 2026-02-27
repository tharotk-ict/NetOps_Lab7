# NetOps_Lab7 :📡 ESP32 CSI Wireless Sensing Lab
### ITCS372 – Wireless & IoT (The Edge)

---

## 📖 Overview

This project demonstrates how to capture **Channel State Information (CSI)** using an **ESP32-Devkit-V1**.

CSI allows us to observe how Wi-Fi signals propagate through the environment and how they are affected by:

- Human movement
- Obstacles
- Multipath reflections
- Signal attenuation

This lab connects:

- 📶 Wireless Networking Theory (OFDM, multipath fading)
- 🔬 Physical Layer concepts
- 🤖 IoT Edge sensing
- 🧠 Foundations for ML-based detection

---

# 🧠 What is CSI?

## Channel State Information (CSI)

In Wi-Fi communication, the receiver estimates the wireless channel before decoding data.

Mathematically:

y = Hx + n

Where:

- **H** = Channel response matrix
- **x** = Transmitted signal
- **n** = Noise

CSI is an estimate of **H**, the wireless channel.

---

## Why CSI Changes

Wi-Fi signals reflect off:

- Walls
- Furniture
- Human bodies
- Objects

This creates **multipath propagation**.

When the environment changes (e.g., someone moves), the channel response changes.

Therefore:

Movement → Channel variation → CSI variation

---

# 🧰 Hardware Requirements

- ESP32-Devkit-V1 (ESP32-WROOM-32)
- USB data cable (must support data transfer)
- Laptop
- 2.4 GHz Wi-Fi Access Point

⚠ ESP32 does **not** support 5 GHz Wi-Fi.

---

# 💻 Software Requirements

- Arduino IDE
- ESP32 Board Support Package
- CP2102 or CH340 USB Driver

---

# ⚙️ Installation

## 1️⃣ Install ESP32 Board Package

In Arduino IDE:

**File → Preferences**

Add this URL to *Additional Board Manager URLs*:
[https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json](https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json)


Then:

**Tools → Board → Boards Manager → Install "ESP32 by Espressif Systems"**

---

## 2️⃣ Install USB Driver

Depending on your board:

- CP2102 → Install Silicon Labs CP210x driver
- CH340 → Install CH340 driver

After installation:

- Verify COM port appears in Device Manager
- Select correct COM port in Arduino

---

# 🚀 CSI Capture Code

```cpp
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
  WiFi.begin("YOUR_SSID", "YOUR_PASSWORD");

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

