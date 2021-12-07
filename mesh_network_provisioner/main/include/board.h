#ifndef TEST_MESH_NETWORK_BOARD_H
#define TEST_MESH_NETWORK_BOARD_H

#include "driver/gpio.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"
#include "dht11.h"

#define DEFAULT_VREF    1100        //Use adc2_vref_to_gpio() to obtain a better estimate
#define NO_OF_SAMPLES   64

static esp_adc_cal_characteristics_t *adc_chars;
static const adc_channel_t channel = ADC_CHANNEL_6;     //GPIO34 if ADC1, GPIO14 if ADC2
static const adc_bits_width_t width = ADC_WIDTH_BIT_12;
static const adc_atten_t atten = ADC_ATTEN_DB_11;
static const adc_unit_t unit = ADC_UNIT_1;

void check_efuse(void);
void board_init(void);
float read_lux(void);
int readDHT(int *temp,int *hum);

#endif //TEST_MESH_NETWORK_BOARD_H
