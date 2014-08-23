#include "allegro_la_salle.h"

//Constants internes del m�dul
#define MAX_KEYS 20
#define MAX_COLORS 17
#define MAX_FONTS 4

//Variables internes del m�dul
static ALLEGRO_DISPLAY *pDisplay = NULL;                    //Variable que  emmagatzema els detalls de la finestra gr�fica
static ALLEGRO_EVENT_QUEUE *pEventQueue = NULL;             //Variable que emmagatzema la cua d'events succe�ts esperant a ser tractats
static int KEYS[MAX_KEYS];                                  //Variable que emmagatzema els flags de les tecles del teclat que han estat premudes
static char sFontPath[500];                                 //Variable que emmagatzema la ruta absoluta cap al fitxer de definici� de la font per defecte
static ALLEGRO_COLOR aColors[MAX_COLORS];                   //Variable que  emmagatzema les variables del tipus ALLEGRO_COLOR dels colors predeterminats
static ALLEGRO_FONT *aFonts[MAX_FONTS];                     //Variable que emmagatzema la informaci� de la font predeterminada del framework.


//------------ Prototipus Privades ------- //
void LS_allegro_init_default_colors();
void LS_allegro_paint();
void LS_allegro_listen_keyboard();

//Pre : Cap
//Post: Retorna 1 (CERT) si s'ha pogut inicialitzar correctament el Framework d'Allegro5. En cas contrari es retornar� 0 (FALS).
int LS_allegro_init(int nAmplitud,int nAltura,char *sNombreVentana){
    int nCounter = 0;

    //Obtenim la ruta del fitxer de la font de text
    getcwd(sFontPath, sizeof(sFontPath));
    strcat(sFontPath,"/font.ttf");

    //Provem d'inicialitzar la llibreria Allegro 5
    if(!al_init()) return 0;

    //Intentem inicialitzar una finestra gr�fica de les mides rebudes
    pDisplay = al_create_display(nAmplitud,nAltura);

    //Posem el nom rebut a la finestra. Si no es reb cap nom, aquest dependr� del sistema operatiu
    if(sNombreVentana != NULL) al_set_window_title(pDisplay,sNombreVentana);

    //Comprovem que s'hagi pogut crear la finestra gr�fica
    if(!pDisplay) return 0;

    //Inicialitzem els addons necess�ris d'Allegro5
    al_init_primitives_addon();     //Dibuix de figures simples (Rectangles, Quadrats, Triangles...)
    al_install_keyboard();          //Driver de teclat
    al_init_font_addon();           //Gestor de fonts de text
    al_init_ttf_addon();            //Gestor de fitxers .ttf per les fonts de text

    //Creem una cua d'esdeveniments (necess�ria pel listener del teclat)
    pEventQueue = al_create_event_queue();

    //Comprovem si la cua d'esdeveniments s'ha creat correctament
    if(!pEventQueue) return 0;

    //Fixem els events del teclat perqu� siguin encuats a la cua que acabem de crear
	al_register_event_source(pEventQueue, al_get_keyboard_event_source());
	al_register_event_source(pEventQueue, al_get_display_event_source(pDisplay));

    //Inicialitzem els colors primitius
    LS_allegro_init_default_colors();

    //Carreguem la font de text
    aFonts[SMALL] = al_load_ttf_font(sFontPath,4,0);
    aFonts[NORMAL] = al_load_ttf_font(sFontPath,8,0);
    aFonts[LARGE] = al_load_ttf_font(sFontPath,32,0);
    aFonts[EXTRA_LARGE] = al_load_ttf_font(sFontPath,64,0);

    //Comprovem si alguna font s'ha carregat malament
    for(nCounter = 0 ; nCounter < MAX_FONTS ; nCounter++){
        if(aFonts[nCounter] == NULL) return 0;
    }

	//Netegem la finestra gr�fica posant el color negre de color de fons
    al_clear_to_color(LS_allegro_getColor(BLACK));

    //Pintem el buffer gr�fic per visualitzar els canvis a la finestra gr�fica
    al_flip_display();

    //Netegem el buffer de tecles premudes
    for(nCounter = 0 ; nCounter < MAX_KEYS ; nCounter++) KEYS[nCounter] = 0;

    //Si arribem aqu�, tot ha anat b�, per tant retornem 1.
    return 1;
}

//Pre : El framework d'Allegro 5 ha d'estar inicialitzat pr�viament. (LS_allegro_init() ha d'haver retornat 1)
//Post : Allibera la mem�ria que s'havia reservat per a les variables necess�ries per fer funcionar Allegro5.
void LS_allegro_exit(){
    int nCounter = 0;
    al_destroy_display(pDisplay);
    al_destroy_event_queue(pEventQueue);
    for(nCounter = 0 ; nCounter < MAX_FONTS ; nCounter++){
        al_destroy_font(aFonts[nCounter]);
    }
}

//Pre : El framework d'Allegro 5 ha d'estar inicialitzat pr�viament. (LS_allegro_init() ha d'haver retornat 1)
//Post : Posa a 1 (CERT) el flag corresponent a la tecla premuda a l'array de flags anomenada KEYS.
void LS_allegro_listen_keyboard(){
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

//Pre : Cap
//Post : Retorna 1 (Cert) si s'ha premut la tecla rebuda al par�metre nKey. En cas contrari, es retornar� 0 (FALS). ATENCI�!! LECTURA DESTRUCTIVA!
int LS_allegro_key_pressed(int nKey){
    if(KEYS[nKey] == 1){
        KEYS[nKey] = 0;
        return 1;
    }
    return 0;
}

//Pre : El valor de nSize ha d'estar dins l'interval [0,MAX_FONTS)
//Post : Retorna una variable del tipus ALLEGRO_FONT * per poder usar la funci� al_draw_textf m�s facilment.
ALLEGRO_FONT * LS_allegro_getFont(int nSize){
    return aFonts[nSize];
}

//Pre : El valor de nColor ha d'estar entre 0 i 16 ambd�s inclosos.
//Post : Retorna una variable del tipus ALLEGRO_COLOR corresponent al color demanat.
ALLEGRO_COLOR LS_allegro_getColor(int nColor){
    ALLEGRO_COLOR color_return;
    if(nColor >= 0 && nColor < MAX_COLORS){
        color_return = aColors[nColor];
    }
    return color_return;
}


//Pre : Cap
//Post : Inicialitza l'array de colors predeterminats que es poden obternir amb LS_allegro_getColor(nColor).
void LS_allegro_init_default_colors(){
    aColors[0] = al_map_rgb(0,0,0);
    aColors[1] = al_map_rgb(0,0,51);
    aColors[2] = al_map_rgb(21,51,0);
    aColors[3] = al_map_rgb(0, 176, 246);
    aColors[4] = al_map_rgb(255,0,0);
    aColors[5] = al_map_rgb(255,153,153);
    aColors[6] = al_map_rgb(255,128,0);
    aColors[7] = al_map_rgb(192,192,192);
    aColors[8] = al_map_rgb(128,128,128);
    aColors[9] = al_map_rgb(0,0,255);
    aColors[10] = al_map_rgb(51,255,51);
    aColors[11] = al_map_rgb(153,204,255);
    aColors[12] = al_map_rgb(153,0,0);
    aColors[13] = al_map_rgb(255,204,204);
    aColors[14] = al_map_rgb(255,255,0);
    aColors[15] = al_map_rgb(255,255,255);
    aColors[16] = al_map_rgb(0,255,0);
}


//Pre : Cap
//Post : Pinta el contingut del buffer temporal a la finestra gr�fica.
void LS_allegro_paint(){
    al_flip_display();
}

//Pre: Cap
//Post: Executa les tasques necess�ries perqu� Allegro funcioni correctament. Aquest procediment s'ha de cridar sempre dins del bucle infinit
//del joc que estiguem implementant, ja que sin�, no podrem escoltar el teclat ni veurem els canvis a la finestra gr�fica.
void LS_allegro_executiu(){
    LS_allegro_paint();
    LS_allegro_listen_keyboard();
}
