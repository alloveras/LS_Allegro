/*
    M�dul de simplificaci� i adaptaci� de l'API de la llibreria
    Allegro 5 per al desenvolupament senzill de jocs 2D a l'assignatura
    de Programaci� 1. Aquesta adaptaci� nom�s facilita el desenvolupament
    estalviant a l'alumne haver de tenir coneixements avan�ats sobre
    listeners i events que utilitza aquesta llibreria per realitzar tasques
    com l'escoltat del teclat, la inicialitzaci� o el pintat de la pantalla.

    Autor : Albert Lloveras Carbonell
    Data �ltima Revisi� : 23/08/2014
    CopyRight : Distribuci� lliure sense cap limitaci�

*/

#ifndef _ALLEGRO_LA_SALLE_H_
#define _ALLEGRO_LA_SALLE_H_

//Operating System Includes
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdio.h>

//Includes Allegro5
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

//--------------- COLORS DISPONIBLES -------- //
#define BLACK 0
#define DARK_BLUE 1
#define DARK_GREEN 2
#define CYAN 3
#define RED 4
#define PINK 5
#define ORANGE 6
#define LIGHT_GRAY 7
#define GRAY 8
#define BLUE 9
#define LIGHT_GREEN 10
#define LIGHT_BLUE 11
#define GARNET 12
#define LIGHT_PINK 13
#define YELLOW 14
#define WHITE 15
#define GREEN 16
//--------------- TAMANYS DE FONT DISPONIBLES ---- //
#define SMALL 0
#define NORMAL 1
#define LARGE 2
#define EXTRA_LARGE 3


//Pre : Cap
//Post: Retorna 1 (CERT) si s'ha pogut inicialitzar correctament el Framework d'Allegro5. En cas contrari es retornar� 0 (FALS).
int LS_allegro_init(int nAmplitud,int nAltura,char *sNombreVentana);

//Pre : El valor del par�metre nKey ha de ser una constant del tipus ALLEGRO_KEY_XXXXXX
//Post : Retorna 1 (Cert) si s'ha premut la tecla rebuda al par�metre nKey. En cas contrari, es retornar� 0 (FALS). ATENCI�!! LECTURA DESTRUCTIVA!
int LS_allegro_key_pressed(int nKey);

//Pre: Cap
//Post: Executa les tasques necess�ries perqu� Allegro funcioni correctament. Aquest procediment s'ha de cridar sempre dins del bucle infinit
//del joc que estiguem implementant, ja que sin�, no podrem escoltar el teclat ni veurem els canvis a la finestra gr�fica.
void LS_allegro_executiu();

//Pre : El valor de nColor ha d'estar entre 0 i 16 ambd�s inclosos.
//Post : Retorna una variable del tipus ALLEGRO_COLOR corresponent al color demanat.
ALLEGRO_COLOR LS_allegro_getColor(int nColor);

//Pre : //Pre : El valor de nSize ha d'estar dins l'interval [0,MAX_FONTS)
//Post : Retorna una variable del tipus ALLEGRO_FONT * per poder usar la funci� al_draw_textf m�s facilment.
ALLEGRO_FONT* LS_allegro_getFont(int nSize);

//Pre : El framework d'Allegro 5 ha d'estar inicialitzat pr�viament. (LS_allegro_init() ha d'haver retornat 1)
//Post : Allibera la mem�ria que s'havia reservat per a les variables necess�ries per fer funcionar Allegro5.
void LS_allegro_exit();


#endif // _ALLEGRO_LA_SALLE_H_
