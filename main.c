#include <stdio.h>
#include "allegro_la_salle.h"

int main(){

    int nVertical = 100;
    int nHorizontal = 0;
    int bSortir = 0;

    if(LS_allegro_init(800,600,"Pacman")){
        while(bSortir == 0){
            LS_listen_keyboard();
            LS_allegro_paint();

            while(nHorizontal < 800){
                while(nVertical < 600){
                    al_draw_rectangle(nHorizontal,nVertical,nHorizontal+10,nVertical+10,al_map_rgb(255,0,0),1.0);
                    nVertical += 10;
                }
                nVertical = 100;
                nHorizontal += 10;
            }
            if(LS_isKeyPressed(0) == 1){
                bSortir = 1;
                LS_clearKey(0);
            }
        }

        LS_allegro_exit();

    }
    return 0;
}
