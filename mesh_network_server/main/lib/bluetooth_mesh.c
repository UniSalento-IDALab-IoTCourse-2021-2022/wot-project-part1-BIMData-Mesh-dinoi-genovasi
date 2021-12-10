#include "bluetooth_mesh.h"
#define BLUETOOTH_MESH_TAG "BLE_MESH"

esp_err_t ble_mesh_init(){

    esp_err_t err;

    ESP_LOGI("MESH_INIT", "BLE Mesh Node initialization");

    esp_ble_mesh_register_prov_callback(provisioning_callback);
    esp_ble_mesh_register_config_server_callback(config_server_callback);
    esp_ble_mesh_register_custom_model_callback(custom_sensors_server_callback);

    err = esp_ble_mesh_init(&provision, &composition);
    if (err != ESP_OK) {
        ESP_LOGE(BLUETOOTH_MESH_TAG, "Failed to initialize mesh stack");
        return err;
    }

    err = esp_ble_mesh_node_prov_enable(ESP_BLE_MESH_PROV_ADV);
    if (err != ESP_OK) {
        ESP_LOGE(BLUETOOTH_MESH_TAG, "Failed to enable mesh node");
        return err;
    }

    ESP_LOGI(BLUETOOTH_MESH_TAG, "BLE Mesh Node initialization complete");
    return ESP_OK;
}

static void provisioning_callback(esp_ble_mesh_prov_cb_event_t event, esp_ble_mesh_prov_cb_param_t *param){
    struct ble_mesh_provisioner_prov_comp_param complete = param->provisioner_prov_complete;
    struct ble_mesh_provisioner_recv_unprov_adv_pkt_param unprov = param->provisioner_recv_unprov_adv_pkt;
    switch(event) {
        case ESP_BLE_MESH_PROVISIONER_PROV_COMPLETE_EVT:
            break;
        case ESP_BLE_MESH_PROVISIONER_RECV_UNPROV_ADV_PKT_EVT:
            break;
        case ESP_BLE_MESH_PROVISIONER_ADD_LOCAL_APP_KEY_COMP_EVT:
            break;
        default:
            break;
    }
}

void config_server_callback(esp_ble_mesh_cfg_server_cb_event_t event, esp_ble_mesh_cfg_server_cb_param_t *param){

}

void ble_mesh_get_dev_uuid(){
    memcpy(dev_uuid +2, esp_bt_dev_get_address(),BD_ADDR_LEN);
    ESP_LOG_BUFFER_HEX("dev_uuid", dev_uuid, 16);
}

void custom_sensors_server_callback(esp_ble_mesh_model_cb_event_t event,esp_ble_mesh_model_cb_param_t *param){
    switch(event){

        case ESP_BLE_MESH_MODEL_OPERATION_EVT:
            switch(param->model_operation.opcode){
                case ESP_BLE_MESH_CUSTOM_SENSOR_MODEL_OP_GET: ;
                    model_sensors_data_t  response = *(model_sensors_data_t *)param->model_operation.model->user_data;
                    esp_ble_mesh_server_model_send_msg(param->model_operation.model,param->model_operation.ctx,ESP_BLE_MESH_CUSTOM_SENSOR_MODEL_OP_STATUS,sizeof(response),(uint8_t *)&response);
                    ESP_LOGI(BLUETOOTH_MESH_TAG,"MESH MESSAGE SENT - DEVICE: %s, LUX: %f, TEMP: %d, HUM: %d\n", response.device_name, response.lux, response.temperature, response.humidity);
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}

void update_state(float lux, int hum, int temp){
    _server_model_state.humidity = hum;
    _server_model_state.lux = lux;
    _server_model_state.temperature = temp;

}