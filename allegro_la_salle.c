#include "allegro_la_salle.h"

//Constants internes del mòdul
#define MAX_KEYS 20

//Variables internes del mòdul
static ALLEGRO_DISPLAY *pDisplay = NULL;
static ALLEGRO_EVENT_QUEUE *pEventQueue = NULL;
static int KEYS[MAX_KEYS];


int LS_allegro_init(int nAmplitud,int nAltura,char *sNombreVentana){
    if(!al_init()) return 0;
    pDisplay = al_create_display(nAmplitud,nAltura);
    if(sNombreVentana != NULL) al_set_window_title(pDisplay,sNombreVentana);
    if(!pDisplay) return 0;
    al_init_primitives_addon();
    al_install_keyboard();
    pEventQueue = al_create_event_queue();
    if(!pEventQueue) return 0;
	al_register_event_source(pEventQueue, al_get_keyboard_event_source());
	al_register_event_source(pEventQueue, al_get_display_event_source(pDisplay));
    al_clear_to_color(al_map_rgb(0,0,0));
    al_flip_display();
    LS_allegro_clear_keybuffer();
    return 1;
}

void LS_allegro_clear_keybuffer(){
    int nCounter = 0;
    for(nCounter = 0 ; nCounter < MAX_KEYS ; nCounter++) KEYS[nCounter] = 0;
}

void LS_allegro_exit(){
    al_destroy_display(pDisplay);
}

void LS_listen_keyboard(){
    ALLEGRO_EVENT ev;
    if(al_peek_next_event(pEventQueue,&ev)){
       if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch(ev.keyboard.keycode)
            {
                case ALLEGRO_KEY_ESCAPE:
                    KEYS[0] = 1;
                    break;
            }
            al_drop_next_event(pEventQueue);
        }
    }
}

int LS_isKeyPressed(int nKey){
    return KEYS[nKey] == 1;
}

int LS_clearKey(int nKey){
    KEYS[nKey] = 0;
}

void LS_allegro_paint(){
    al_flip_display();
}
