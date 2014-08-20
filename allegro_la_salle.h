#ifndef _ALLEGRO_LA_SALLE_H_
#define _ALLEGRO_LA_SALLE_H_

/*
    Mòdul de simplificació i adaptació de l'API de la llibreria
    Allegro 5 per al desenvolupament senzill de jocs 2D a l'assignatura
    de Programació 1. Aquesta adaptació només facilita el desenvolupament
    estalviant a l'alumne haver de tenir coneixements avançats sobre
    listeners i events que utilitza aquesta llibreria per realitzar tasques
    com l'escoltat del teclat, la inicialització o el pintat de la pantalla.

    Autor : Albert Lloveras Carbonell
    Data Última Revisió : 20/08/2014
    CopyRight : Distribució lliure sense cap limitació

*/


//Includes Allegro5
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

int LS_allegro_init(int nAmplitud,int nAltura,char *sNombreVentana);

void LS_allegro_paint();

void LS_listen_keyboard();

void LS_allegro_clear_keybuffer();

int LS_isKeyPressed(int nKey);
int LS_clearKey(int nKey);

void LS_allegro_exit();


#endif // _ALLEGRO_LA_SALLE_H_
