#include <nvs_flash.h>
#include "bluetooth_mesh.h"
#include "ble.h"

#define MAIN_TAG "MAIN"


#include "board.h"


void app_main(void)
{
    nvs_flash_init();
    bluetooth_init();
    ble_mesh_get_dev_uuid(dev_uuid);
    ble_mesh_init();

    board_init();
    float lux;
    int hum;
    int temp;
    while (1) {
        lux = read_lux();
        readDHT(&temp, &hum);
        ESP_LOGI(MAIN_TAG,"ACQUIRED SENSOR VALUES - LUX: %f, TEMP: %d, HUM: %d\n", lux, temp, hum);
        update_state(lux, hum, temp);
        vTaskDelay(pdMS_TO_TICKS(5000));
    }

}

