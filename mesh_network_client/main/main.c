#include <nvs_flash.h>
#include "bluetooth_mesh.h"
#include "ble.h"

#define MAIN_TAG "MAIN"

#ifdef DEVICE_NODE
#include "board.h"
#endif

void app_main(void)
{
    nvs_flash_init();
    bluetooth_init();
    ble_mesh_get_dev_uuid(dev_uuid);
    ble_mesh_init();

#ifdef DEVICE_NODE
    board_init();
    float lux;
    int hum;
    int temp;
    while (1) {
        lux = read_lux();
        readDHT(&hum, &temp);
        ESP_LOGI(MAIN_TAG,"LUX: %f, TEMP: %d, HUM: %d\n",lux,temp,hum);
        _server_model_state.humidity = hum;
        _server_model_state.lux = lux;
        _server_model_state.temperature = temp;
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
#endif
#ifdef DEVICE_PROVISIONER
    while(1){
            //ESP_LOGI("MAIN", "Unicast address %x",nodes[i].unicast);
            ble_mesh_custom_sensor_client_model_message_get();
       vTaskDelay(pdMS_TO_TICKS(5000));
    }
#endif

}

