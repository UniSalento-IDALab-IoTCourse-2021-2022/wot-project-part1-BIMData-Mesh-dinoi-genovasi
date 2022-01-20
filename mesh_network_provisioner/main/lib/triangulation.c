#include <esp_log.h>
#include "triangulation.h"

 void update_distance(uint8_t *uuid, float d){
        for(int i = 0; i<3; i++){
            if(memcmp(uuid,fixed_nodes[i].uuid,16))
                fixed_nodes[i].distance = d;
        }
}

void estimate_position(){
    //float a[3],b[3],c[3];
    float x;
    float y;
    /*for(int i=0 ; i<3; i++){
        a[i]=-2*fixed_nodes[i].x;
        b[i]=-2*fixed_nodes[i].y;
        c[i]=fixed_nodes[i].x*fixed_nodes[i].x + fixed_nodes[i].y*fixed_nodes[i].y - fixed_nodes[i].distance*fixed_nodes[i].distance;
    }*/
   /* x = ((c[3] - c[2])*(b[1]-b[3]) - (c[3]-c[1])*(b[2]-b[3]))/((a[2]-a[3])*(b[1]-b[3]) - (a[1]-a[3])*(b[2]-b[3]));
    y = (-(c[3]-c[2])*(a[1]-a[3]))/((a[2]-a[3])*(b[1]-b[3]) - (a[1]-a[3])*(b[2]-b[3]));*/
    float A = 2*fixed_nodes[1].x - 2*fixed_nodes[0].x;
    float B = 2*fixed_nodes[1].y - 2*fixed_nodes[0].y;
    float C = fixed_nodes[0].distance*fixed_nodes[0].distance - fixed_nodes[1].distance*fixed_nodes[1].distance - fixed_nodes[0].x*fixed_nodes[0].x +
            fixed_nodes[1].x*fixed_nodes[1].x - fixed_nodes[0].y * fixed_nodes[0].y + fixed_nodes[1].y*fixed_nodes[1].y;
    float D = 2*fixed_nodes[2].x - 2*fixed_nodes[1].x;
    float E = 2*fixed_nodes[2].y- 2*fixed_nodes[1].y;
    float F =  fixed_nodes[1].distance*fixed_nodes[1].distance -  fixed_nodes[2].distance*fixed_nodes[2].distance - fixed_nodes[1].x*fixed_nodes[1].x +
            fixed_nodes[2].x*fixed_nodes[2].x - fixed_nodes[1].y*fixed_nodes[1].y + fixed_nodes[2].y*fixed_nodes[2].y;
    x = (C*E - F*B) / (E*A - B*D);
    y = (C*D - A*F) / (B*D - A*E);

    ESP_LOGI("TRILAT","Estimated Beacon position: X: %f, Y: %f",x,y);
    mqtt_publish(x,y);
}