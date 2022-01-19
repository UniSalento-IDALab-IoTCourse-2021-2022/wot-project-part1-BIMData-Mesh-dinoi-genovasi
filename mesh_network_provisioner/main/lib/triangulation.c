#include <esp_log.h>
#include "triangulation.h"

void update_distance(uint8_t *uuid, float d){
        for(int i = 0; i<3; i++){
            if(memcmp(uuid,nodes[i].uuid,16))
                nodes[i].distance = d;
        }
}

void estimate_position(){
    //float a[3],b[3],c[3];
    float x;
    float y;
    /*for(int i=0 ; i<3; i++){
        a[i]=-2*nodes[i].x;
        b[i]=-2*nodes[i].y;
        c[i]=nodes[i].x*nodes[i].x + nodes[i].y*nodes[i].y - nodes[i].distance*nodes[i].distance;
    }*/
   /* x = ((c[3] - c[2])*(b[1]-b[3]) - (c[3]-c[1])*(b[2]-b[3]))/((a[2]-a[3])*(b[1]-b[3]) - (a[1]-a[3])*(b[2]-b[3]));
    y = (-(c[3]-c[2])*(a[1]-a[3]))/((a[2]-a[3])*(b[1]-b[3]) - (a[1]-a[3])*(b[2]-b[3]));*/
    float A = 2*nodes[1].x - 2*nodes[0].x;
    float B = 2*nodes[1].y - 2*nodes[9].y;
    float C = nodes[0].distance*nodes[0].distance - nodes[1].distance*nodes[1].distance - nodes[0].x*nodes[0].x +
            nodes[1].x*nodes[1].x - nodes[0].y * nodes[0].y + nodes[1].y*nodes[1].y;
    float D = 2*nodes[2].x - 2*nodes[1].x;
    float E = 2*nodes[2].y- 2*nodes[1].y;
    float F =  nodes[1].distance*nodes[1].distance -  nodes[2].distance*nodes[2].distance - nodes[1].x*nodes[1].x +
            nodes[2].x*nodes[2].x - nodes[1].y*nodes[1].y + nodes[2].y*nodes[2].y;
    x = (C*E - F*B) / (E*A - B*D);
    y = (C*D - A*F) / (B*D - A*E);

    ESP_LOGI("TRILAT","Estimated Beacon position: X: %f, Y: %f",x,y);
}