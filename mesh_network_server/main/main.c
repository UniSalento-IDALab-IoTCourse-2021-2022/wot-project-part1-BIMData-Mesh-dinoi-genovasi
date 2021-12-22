#include <nvs_flash.h>
#include "bluetooth_mesh.h"
#include "ble.h"

#define MAIN_TAG "MAIN"


#include "board.h"
#include "wifi.h"
#include "ota.h"


void app_main(void)
{
    float lux;
    int hum;
    int temp;
    esp_err_t err;

    ESP_LOGI(MAIN_TAG, "Initializing...");

    err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }

    ESP_ERROR_CHECK(err);

    board_init();

    wifi_init_sta();

    err = bluetooth_init();
    if (err) {
        ESP_LOGE(MAIN_TAG, "esp32_bluetooth_init failed (err %d)", err);
        return;
    }

    ble_mesh_get_dev_uuid();

    /* Initialize the Bluetooth Mesh Subsystem */
    err = ble_mesh_init();
    if (err) {
        ESP_LOGE(MAIN_TAG, "Bluetooth mesh init failed (err %d)", err);
    }

    xTaskCreate(&ota_task, "ota_update_task", 8192, NULL, 5, NULL);

//    while (1) {
//        lux = read_lux();
//        readDHT(&temp, &hum);
//        ESP_LOGI(MAIN_TAG,"ACQUIRED SENSOR VALUES - DEVICE: %s, LUX: %f, TEMP: %d, HUM: %d\n", DEVICE_ID, lux, temp, hum);
//        update_state(lux, hum, temp);
//        vTaskDelay(pdMS_TO_TICKS(5000));
//    }

}

