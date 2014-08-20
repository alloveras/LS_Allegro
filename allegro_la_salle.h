#ifndef _ALLEGRO_LA_SALLE_H_
#define _ALLEGRO_LA_SALLE_H_

/*
    M�dul de simplificaci� i adaptaci� de l'API de la llibreria
    Allegro 5 per al desenvolupament senzill de jocs 2D a l'assignatura
    de Programaci� 1. Aquesta adaptaci� nom�s facilita el desenvolupament
    estalviant a l'alumne haver de tenir coneixements avan�ats sobre
    listeners i events que utilitza aquesta llibreria per realitzar tasques
    com l'escoltat del teclat, la inicialitzaci� o el pintat de la pantalla.

    Autor : Albert Lloveras Carbonell
    Data �ltima Revisi� : 20/08/2014
    CopyRight : Distribuci� lliure sense cap limitaci�

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
