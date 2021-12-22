#ifndef TEST_MESH_NETWORK_CUSTOM_SENSOR_MODEL_MESH_H
#define TEST_MESH_NETWORK_CUSTOM_SENSOR_MODEL_MESH_H

#include "esp_ble_mesh_common_api.h"

#define ESP_BLE_MESH_CUSTOM_SENSOR_MODEL_ID_SERVER      0x1414  /*!< Custom Server Model ID */
#define ESP_BLE_MESH_CUSTOM_SENSOR_MODEL_ID_CLIENT      0x1415  /*!< Custom Client Model ID */

#define ESP_BLE_MESH_CUSTOM_SENSOR_MODEL_OP_GET         ESP_BLE_MESH_MODEL_OP_3(0x00, CID_ESP)
#define ESP_BLE_MESH_CUSTOM_SENSOR_MODEL_OP_SET         ESP_BLE_MESH_MODEL_OP_3(0x01, CID_ESP)
#define ESP_BLE_MESH_CUSTOM_SENSOR_MODEL_OP_STATUS      ESP_BLE_MESH_MODEL_OP_3(0x02, CID_ESP)

#define ESP_BLE_MESH_GROUP_PUB_ADDR                     0xC100

typedef struct __attribute__((packed)) {
    float lux;
    int temperature;
    int humidity;
    char device_name[7];
} model_sensors_data_t;

#endif //TEST_MESH_NETWORK_CUSTOM_SENSOR_MODEL_MESH_H
