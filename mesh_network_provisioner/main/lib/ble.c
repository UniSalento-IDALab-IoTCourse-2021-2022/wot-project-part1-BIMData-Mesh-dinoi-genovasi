#include "ble.h"

esp_err_t bluetooth_init(void){
    esp_err_t ret;
    ESP_LOGI(BLE_TAG,"Initializing BT (BLE MODE)");
    ESP_ERROR_CHECK(esp_bt_controller_mem_release(ESP_BT_MODE_CLASSIC_BT));

    esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
    ret = esp_bt_controller_init(&bt_cfg);
    if (ret) {
        ESP_LOGE(BLE_TAG, "%s initialize controller failed", __func__);
        return ret;
    }

    ret = esp_bt_controller_enable(ESP_BT_MODE_BLE);
    if (ret) {
        ESP_LOGE(BLE_TAG, "%s enable controller failed", __func__);
        return ret;
    }
    ret = esp_bluedroid_init();
    if (ret) {
        ESP_LOGE(BLE_TAG, "%s init bluetooth failed", __func__);
        return ret;
    }
    ret = esp_bluedroid_enable();
    if (ret) {
        ESP_LOGE(BLE_TAG, "%s enable bluetooth failed", __func__);
        return ret;
    }

    ret = esp_ble_gap_register_callback(esp_gap_cb);
    if (ret){
        ESP_LOGE(BLE_TAG, "%s gap register failed, error code = %x\n", __func__, ret);
        return ret;
    }
    ret = esp_ble_gap_set_scan_params(&ble_scan_params);
    if(ret){
        ESP_LOGE(BLE_TAG,"Oh nooo\n");
        return ret;
    }

    ESP_LOGI(BLE_TAG,"BT (BLE MODE) init complete");
    return ret;
}

static void esp_gap_cb(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param)
{
    switch (event) {
        case ESP_GAP_BLE_SCAN_PARAM_SET_COMPLETE_EVT: {
            //the unit of the duration is second
            uint32_t duration = 0; //if 0 scan forever
            esp_ble_gap_start_scanning(duration);
            break;
        }
        case ESP_GAP_BLE_SCAN_START_COMPLETE_EVT:
            //scan start complete event to indicate scan start successfully or failed
            if (param->scan_start_cmpl.status != ESP_BT_STATUS_SUCCESS) {
                ESP_LOGE(BLE_TAG, "scan start failed, error status = %x", param->scan_start_cmpl.status);
                break;
            }
            ESP_LOGI(BLE_TAG, "scan start success");

            break;
        case ESP_GAP_BLE_SCAN_RESULT_EVT: {
            esp_ble_gap_cb_param_t *scan_result = (esp_ble_gap_cb_param_t *)param;
            switch (scan_result->scan_rst.search_evt) {
                case ESP_GAP_SEARCH_INQ_RES_EVT:
                    if(esp_ble_is_ibeacon_packet(scan_result->scan_rst.ble_adv,scan_result->scan_rst.adv_data_len)){
                        esp_ble_ibeacon_t *beacon_data= (esp_ble_ibeacon_t *) scan_result->scan_rst.ble_adv;
                        ESP_LOGI(BLE_TAG,"----- TROVATO IL BEACON ----");
                                esp_log_buffer_hex("UUID: ",beacon_data->ibeacon_vendor.proximity_uuid,ESP_UUID_LEN_128);
                        ESP_LOGI(BLE_TAG,"Measured Power: %d",beacon_data->ibeacon_vendor.measured_power);

                        uint16_t major = ENDIAN_CHANGE_U16(beacon_data->ibeacon_vendor.major);
                        uint16_t minor = ENDIAN_CHANGE_U16(beacon_data->ibeacon_vendor.minor);

                        ESP_LOGI(BLE_TAG,"Major: %d Minor: %d",major,minor);
                        ESP_LOGI(BLE_TAG,"RSSI: %d",scan_result->scan_rst.rssi);
                        ESP_LOGI(BLE_TAG,"\n");
                    }

                    break;
                case ESP_GAP_SEARCH_INQ_CMPL_EVT:
                    break;
                default:
                    break;
            }
            break;
        }

        case ESP_GAP_BLE_SCAN_STOP_COMPLETE_EVT:
            if (param->scan_stop_cmpl.status != ESP_BT_STATUS_SUCCESS){
                ESP_LOGE(BLE_TAG, "scan stop failed, error status = %x", param->scan_stop_cmpl.status);
                break;
            }
            ESP_LOGI(BLE_TAG, "stop scan successfully");
            break;

        case ESP_GAP_BLE_ADV_STOP_COMPLETE_EVT:
            if (param->adv_stop_cmpl.status != ESP_BT_STATUS_SUCCESS){
                ESP_LOGE(BLE_TAG, "adv stop failed, error status = %x", param->adv_stop_cmpl.status);
                break;
            }
            ESP_LOGI(BLE_TAG, "stop adv successfully");
            break;
        case ESP_GAP_BLE_UPDATE_CONN_PARAMS_EVT:
            ESP_LOGI(BLE_TAG, "update connection params status = %d, min_int = %d, max_int = %d,conn_int = %d,latency = %d, timeout = %d",
                     param->update_conn_params.status,
                     param->update_conn_params.min_int,
                     param->update_conn_params.max_int,
                     param->update_conn_params.conn_int,
                     param->update_conn_params.latency,
                     param->update_conn_params.timeout);
            break;
        default:
            break;
    }
}
