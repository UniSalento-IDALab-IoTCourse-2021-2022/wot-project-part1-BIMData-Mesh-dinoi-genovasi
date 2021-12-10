#include <nvs_flash.h>
#include "bluetooth_mesh.h"
#include "ble.h"

#define MAIN_TAG "MAIN"

void app_main(void)
{
    nvs_flash_init();
    bluetooth_init();
    ble_mesh_get_dev_uuid(dev_uuid);
    ble_mesh_init();

    while(1){
        if(!isProvisioning())
            ble_mesh_custom_sensor_client_model_message_get();
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}

