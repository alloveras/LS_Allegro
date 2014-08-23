#include "graphics.h"

void GRAPHICS_drawLeftMenu(){
    al_draw_textf(LS_allegro_getFont(EXTRA_LARGE),LS_allegro_getColor(WHITE),30,10,ALLEGRO_ALIGN_LEFT,"HOLA que ase");
    al_draw_textf(LS_allegro_getFont(NORMAL),LS_allegro_getColor(WHITE),10,10,ALLEGRO_ALIGN_LEFT,"%d",10);
}

