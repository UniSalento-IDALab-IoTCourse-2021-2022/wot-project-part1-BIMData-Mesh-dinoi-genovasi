#include <nvs_flash.h>
#include "bluetooth_mesh.h"
#include "ble.h"
#include "wifi.h"
#include "ota.h"

#define MAIN_TAG "MAIN"

void app_main(void)
{
    esp_err_t error;
    error = nvs_flash_init();
    if(error!=ESP_OK) {
        ESP_ERROR_CHECK(error);
        ESP_LOGE(MAIN_TAG, "NVS init erorr %d", error);
    }

    ESP_LOGI(MAIN_TAG,"OTA VERSION 6");

    wifi_init_sta();

    bluetooth_init();
    ble_mesh_get_dev_uuid(dev_uuid);
    ble_mesh_init();

    xTaskCreate(&ota_task, "ota_update_task", 8192, NULL, 5, NULL);

    while(1){
        ble_mesh_custom_sensor_client_model_message_get();
       // ble_mesh_ibeacon_model_client_message_get();
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}

