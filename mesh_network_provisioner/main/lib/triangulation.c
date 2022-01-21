#include "triangulation.h"

 void update_distance(uint8_t *uuid, float d){
        for(int i = 0; i<3; i++){
            if(memcmp(uuid,fixed_nodes[i].uuid,16) == 0) {
                fixed_nodes[i].distance = d;
                //ESP_LOG_BUFFER_HEX("TRILA",fixed_nodes[i].uuid,16);
                //ESP_LOG_BUFFER_HEX("TRILA",uuid,16);
                ESP_LOGI("TRILA","Dispositivo: %d Distance: %f",i,d);
            }
        }
}

void estimate_position(){
    float a[3], b[3], c[3];
    float x;
    float y;
    for (int i = 0; i < 3; i++) {
        a[i] = -2 * fixed_nodes[i].x;
        b[i] = -2 * fixed_nodes[i].y;
        c[i] = fixed_nodes[i].x * fixed_nodes[i].x + fixed_nodes[i].y * fixed_nodes[i].y -
               fixed_nodes[i].distance * fixed_nodes[i].distance;
    }
    x = ((c[1] - c[0]) * (b[1] - b[2]) - (c[2] - c[1]) * (b[0] - b[1])) /
        ((a[0] - a[1]) * (b[1] - b[2]) - (a[1] - a[2]) * (b[0] - b[1]));
    y = ((c[2] - c[1]) * (a[0] - a[1]) - (c[1] - c[0]) * (a[1] - a[2])) /
        ((a[0] - a[1]) * (b[1] - b[2]) - (a[1] - a[2]) * (b[0] - b[1]));
    /*float A = 2*fixed_nodes[1].x - 2*fixed_nodes[0].x;
    float B = 2*fixed_nodes[1].y - 2*fixed_nodes[0].y;
    float C = fixed_nodes[0].distance*fixed_nodes[0].distance - fixed_nodes[1].distance*fixed_nodes[1].distance - fixed_nodes[0].x*fixed_nodes[0].x +
            fixed_nodes[1].x*fixed_nodes[1].x - fixed_nodes[0].y * fixed_nodes[0].y + fixed_nodes[1].y*fixed_nodes[1].y;
    float D = 2*fixed_nodes[2].x - 2*fixed_nodes[1].x;
    float E = 2*fixed_nodes[2].y- 2*fixed_nodes[1].y;
    float F =  fixed_nodes[1].distance*fixed_nodes[1].distance -  fixed_nodes[2].distance*fixed_nodes[2].distance - fixed_nodes[1].x*fixed_nodes[1].x +
            fixed_nodes[2].x*fixed_nodes[2].x - fixed_nodes[1].y*fixed_nodes[1].y + fixed_nodes[2].y*fixed_nodes[2].y;
    x = (C*E - F*B) / (E*A - B*D);
    y = (C*D - A*F) / (B*D - A*E);

    if( x >= 1.8f){
        ESP_LOGW("TRILAT","After the table");
    }else if (x <0){
        ESP_LOGW("TRILAT", "Before the table");
    }

    if (y > 1.6f){
        ESP_LOGW("TRILAT","After the table");
    } else if (y < 0){
        ESP_LOGW("TRILAT","Before the table");
    }*/

    ESP_LOGI("TRILAT", "Estimated Beacon position: X: %f, Y: %f", x, y);
    mqtt_publish(x, y);
}