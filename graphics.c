#include "graphics.h"

void GRAPHICS_drawLeftMenu(){

    //Secció Game Statistics
    al_draw_line(620,65,780,65,LS_allegro_getColor(WHITE),1);
    al_draw_textf(LS_allegro_getFont(NORMAL),LS_allegro_getColor(WHITE),620,70,ALLEGRO_ALIGN_LEFT,"Game Statistics");
    al_draw_line(620,86,780,86,LS_allegro_getColor(WHITE),1);
    al_draw_textf(LS_allegro_getFont(NORMAL),LS_allegro_getColor(WHITE),620,100,ALLEGRO_ALIGN_LEFT,"Time: %d",10);

    //Secció Ranking
    al_draw_line(620,395,780,395,LS_allegro_getColor(WHITE),1);
    al_draw_textf(LS_allegro_getFont(NORMAL),LS_allegro_getColor(WHITE),620,400,ALLEGRO_ALIGN_LEFT,"Ranking");
    al_draw_line(620,416,780,416,LS_allegro_getColor(WHITE),1);
}

