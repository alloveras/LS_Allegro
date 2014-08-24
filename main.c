#include <stdio.h>
#include "allegro_la_salle.h"
#include "graphics.h"

int main(){

    int nVertical = 50;
    int nHorizontal = 0;
    int bSortir = 0;

    if(LS_allegro_init(800,600,"Pacman")){
        while(bSortir == 0){

            //Cridem l'executiu
            LS_allegro_executiu();

            while(nHorizontal < 600){
                while(nVertical < 600){
                    al_draw_rectangle(nHorizontal,nVertical,nHorizontal+10,nVertical+10,al_map_rgb(255,0,0),1.0);
                    nVertical += 10;
                }
                nVertical = 50;
                nHorizontal += 10;
            }

            GRAPHICS_drawLeftMenu();

            if(LS_allegro_key_pressed(ALLEGRO_KEY_ESCAPE) == 1){
                bSortir = 1;
            }

        }

        LS_allegro_exit();

    }
    return 0;
}
