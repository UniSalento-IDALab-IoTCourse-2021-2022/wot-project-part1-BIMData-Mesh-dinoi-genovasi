#include "freertos/FreeRTOS.h"
#include <freertos/task.h>
#include "board.h"

void check_efuse(void)
{
#if CONFIG_IDF_TARGET_ESP32
    //Check if TP is burned into eFuse
    if (esp_adc_cal_check_efuse(ESP_ADC_CAL_VAL_EFUSE_TP) == ESP_OK) {
        printf("eFuse Two Point: Supported\n");
    } else {
        printf("eFuse Two Point: NOT supported\n");
    }
    //Check Vref is burned into eFuse
    if (esp_adc_cal_check_efuse(ESP_ADC_CAL_VAL_EFUSE_VREF) == ESP_OK) {
        printf("eFuse Vref: Supported\n");
    } else {
        printf("eFuse Vref: NOT supported\n");
    }
#elif CONFIG_IDF_TARGET_ESP32S2
    if (esp_adc_cal_check_efuse(ESP_ADC_CAL_VAL_EFUSE_TP) == ESP_OK) {
        printf("eFuse Two Point: Supported\n");
    } else {
        printf("Cannot retrieve eFuse Two Point calibration values. Default calibration values will be used.\n");
    }
#else
#error "This example is configured for ESP32/ESP32S2."
#endif
}

void board_init(){
    check_efuse();

    adc1_config_width(width);
    adc1_config_channel_atten(channel, atten);
    adc_chars = calloc(1, sizeof(esp_adc_cal_characteristics_t));
    esp_adc_cal_value_t val_type = esp_adc_cal_characterize(unit, atten, width, DEFAULT_VREF, adc_chars);

    DHT11_init(GPIO_NUM_4);
    vTaskDelay(pdMS_TO_TICKS(500));
}

float read_lux() {
    uint32_t adc_reading = 0;
    //Multisampling
    for (int i = 0; i < NO_OF_SAMPLES; i++) {
        if (unit == ADC_UNIT_1) {
            adc_reading += adc1_get_raw((adc1_channel_t) channel);
        } else {
            int raw;
            adc2_get_raw((adc2_channel_t) channel, width, &raw);
            adc_reading += raw;
        }
    }
    adc_reading /= NO_OF_SAMPLES;
    //Convert adc_reading to voltage in mV
    uint32_t voltage = esp_adc_cal_raw_to_voltage(adc_reading, adc_chars);
    float RLDR = (10000 * (3300 - voltage)) / voltage;
    float lux = 500 / (RLDR / 1000);
    return lux;
}

int readDHT(int *temp, int *hum){
    *hum = DHT11_read().humidity;
    *temp = DHT11_read().temperature;
    return DHT11_read().status;
}