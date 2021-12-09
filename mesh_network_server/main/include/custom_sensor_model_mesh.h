#ifndef TEST_MESH_NETWORK_CUSTOM_SENSOR_MODEL_MESH_H
#define TEST_MESH_NETWORK_CUSTOM_SENSOR_MODEL_MESH_H

#include "esp_ble_mesh_common_api.h"

//* Definicao dos IDs dos Models (Server e Client)
#define ESP_BLE_MESH_CUSTOM_SENSOR_MODEL_ID_SERVER      0x1414  /*!< Custom Server Model ID */
#define ESP_BLE_MESH_CUSTOM_SENSOR_MODEL_ID_CLIENT      0x1415  /*!< Custom Client Model ID */

//* Definimos os OPCODES das mensagens (igual no server)
#define ESP_BLE_MESH_CUSTOM_SENSOR_MODEL_OP_GET         ESP_BLE_MESH_MODEL_OP_3(0x00, CID_ESP)
#define ESP_BLE_MESH_CUSTOM_SENSOR_MODEL_OP_SET         ESP_BLE_MESH_MODEL_OP_3(0x01, CID_ESP)
#define ESP_BLE_MESH_CUSTOM_SENSOR_MODEL_OP_STATUS      ESP_BLE_MESH_MODEL_OP_3(0x02, CID_ESP)

#define ESP_BLE_MESH_GROUP_PUB_ADDR                     0xC100

typedef struct __attribute__((packed)) {
    float lux;
    int temperature;
    int humidity;
    char device_name[6];
} model_sensors_data_t;

typedef struct __attribute__((packed)) {
//  iBeacon fields for beacon compatibility
    uint8_t uuid[16];
    uint16_t major;
    uint16_t minor;
    int rssi;
} model_ibeacon_data_t;

#endif //TEST_MESH_NETWORK_CUSTOM_SENSOR_MODEL_MESH_H
