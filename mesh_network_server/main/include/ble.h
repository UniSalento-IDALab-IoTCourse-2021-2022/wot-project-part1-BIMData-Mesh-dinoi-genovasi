#ifndef TEST_MESH_NETWORK_BLE_H
#define TEST_MESH_NETWORK_BLE_H
#include "esp_err.h"
#include <esp_bt.h>
#include <esp_log.h>
#include <esp_bt_main.h>
#define BLE_TAG "BLE"

esp_err_t bluetooth_init(void);

#endif //TEST_MESH_NETWORK_BLE_H
