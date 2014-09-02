#include "allegro_la_salle.h"

//Constants internes del mòdul
#define MAX_KEYS 128
#define MAX_COLORS 17
#define MAX_FONTS 4

//Variables internes del mòdul
static ALLEGRO_DISPLAY *pDisplay = NULL;                    //Variable que  emmagatzema els detalls de la finestra gràfica
static ALLEGRO_EVENT_QUEUE *pEventQueue = NULL;             //Variable que emmagatzema la cua d'events succeïts esperant a ser tractats
static int KEYS[MAX_KEYS];                                  //Variable que emmagatzema els flags de les tecles del teclat que han estat premudes
static char sFontPath[500];                                 //Variable que emmagatzema la ruta absoluta cap al fitxer de definició de la font per defecte
static ALLEGRO_COLOR aColors[MAX_COLORS];                   //Variable que  emmagatzema les variables del tipus ALLEGRO_COLOR dels colors predeterminats
static ALLEGRO_FONT *aFonts[MAX_FONTS];                     //Variable que emmagatzema la informació de la font predeterminada del framework.

//------------ Prototipus Privades ------- //
void LS_allegro_init_default_colors();
void LS_allegro_paint();
void LS_allegro_process_events();

//Pre : Cap
//Post: Retorna 1 (CERT) si s'ha pogut inicialitzar correctament el Framework d'Allegro5. En cas contrari es retornarà 0 (FALS).
int LS_allegro_init(int nAmplitud,int nAltura,char *sNombreVentana){
    int nCounter = 0;

    //Obtenim la ruta del fitxer de la font de text
    getcwd(sFontPath, sizeof(sFontPath));
    strcat(sFontPath,"/font.ttf");

    //Provem d'inicialitzar la llibreria Allegro 5
    if(!al_init()){
		printf("LS_Allegro_Error: No s'ha pogut inicialitzar la llibreria Allegro 5! Comprova que tot esta correctament instal·lat al teu ordinador.\n");
		getchar();
		return 0;
	} 

    //Intentem inicialitzar una finestra gràfica de les mides rebudes
    pDisplay = al_create_display(nAmplitud,nAltura);

    //Posem el nom rebut a la finestra. Si no es reb cap nom, aquest dependrà del sistema operatiu
    if(sNombreVentana != NULL) al_set_window_title(pDisplay,sNombreVentana);

    //Comprovem que s'hagi pogut crear la finestra gràfica
    if(!pDisplay){
		printf("LS_Allegro_Error: No s'ha pogut crear la finestra gràfica d'Allegro 5! Hi ha hagut algún problema de comuncicació amb el hardware de la gràfica.\n");
		getchar();
		return 0;
	}

    //Inicialitzem els addons necessàris d'Allegro5
    al_init_primitives_addon();     //Dibuix de figures simples (Rectangles, Quadrats, Triangles...)
    al_install_keyboard();          //Driver de teclat
    al_init_font_addon();           //Gestor de fonts de text
    al_init_ttf_addon();            //Gestor de fitxers .ttf per les fonts de text

    //Creem una cua d'esdeveniments (necessària pel listener del teclat)
    pEventQueue = al_create_event_queue();

    //Comprovem si la cua d'esdeveniments s'ha creat correctament
    if(!pEventQueue){
		printf("LS_Allegro_Error: Error durant la creació de la cua d'esdeveniments!\n");
		getchar();
		return 0;
	} 


    //Fixem els events del teclat perquè siguin encuats a la cua que acabem de crear
	al_register_event_source(pEventQueue, al_get_keyboard_event_source());	
    //Inicialitzem els colors primitius
    LS_allegro_init_default_colors();

    //Carreguem la font de text
    aFonts[SMALL] = al_load_ttf_font(sFontPath,4,0);
    aFonts[NORMAL] = al_load_ttf_font(sFontPath,8,0);
    aFonts[LARGE] = al_load_ttf_font(sFontPath,32,0);
    aFonts[EXTRA_LARGE] = al_load_ttf_font(sFontPath,64,0);

    //Comprovem si alguna font s'ha carregat malament
    for(nCounter = 0 ; nCounter < MAX_FONTS ; nCounter++){
        if(aFonts[nCounter] == NULL){
			printf("LS_Allegro_Error: No s'ha pogut carregar la font predeterminada. Comprova que el fitxer de la font estigui col·locat al directori -> %s.\n",sFontPath);
			getchar();
			return 0;
		}
    }

	//Netegem la finestra gràfica posant el color negre de color de fons
    al_clear_to_color(LS_allegro_getColor(BLACK));
	
	//Pintem el buffer que tenim en memòria
	al_flip_display();

    //Netegem el buffer de tecles premudes
    for(nCounter = 0 ; nCounter < MAX_KEYS ; nCounter++) KEYS[nCounter] = 0;

    //Si arribem aquí, tot ha anat bé, per tant retornem 1.
    return 1;
}

//Pre : El framework d'Allegro 5 ha d'estar inicialitzat prèviament. (LS_allegro_init() ha d'haver retornat 1)
//Post : Allibera la memòria que s'havia reservat per a les variables necessàries per fer funcionar Allegro5.
void LS_allegro_exit(){
    int nCounter = 0;
    al_destroy_display(pDisplay);
    al_destroy_event_queue(pEventQueue);
    for(nCounter = 0 ; nCounter < MAX_FONTS ; nCounter++){
        al_destroy_font(aFonts[nCounter]);
    }
}

//Pre : El framework d'Allegro 5 ha d'estar inicialitzat prèviament. (LS_allegro_init() ha d'haver retornat 1)
//Post : Posa a 1 (CERT) el flag corresponent a la tecla premuda a l'array de flags anomenada KEYS.
void LS_allegro_process_events(){
    ALLEGRO_EVENT ev;
    if(al_peek_next_event(pEventQueue,&ev) == 1){
		if(ev.type == ALLEGRO_EVENT_KEY_DOWN){	//Event de Key_Down	
            KEYS[ev.keyboard.keycode - 1] = 1;
            al_drop_next_event(pEventQueue);
        }else{	//Altres Events que no necessiten tractament
			al_drop_next_event(pEventQueue);
		}
    }
}

//Pre : El valor del paràmetre nKey ha de ser una constant del tipus ALLEGRO_KEY_XXXXXX
//Post : Retorna 1 (Cert) si s'ha premut la tecla rebuda al paràmetre nKey. En cas contrari, es retornarà 0 (FALS). ATENCIÓ!! LECTURA DESTRUCTIVA!
int LS_allegro_key_pressed(int nKey){
    if(KEYS[nKey - 1] == 1){
        KEYS[nKey - 1] = 0;
        return 1;
    }
    return 0;
}

//Pre : El valor de nSize ha d'estar dins l'interval [0,MAX_FONTS)
//Post : Retorna una variable del tipus ALLEGRO_FONT * per poder usar la funció al_draw_textf més facilment.
ALLEGRO_FONT * LS_allegro_getFont(int nSize){
    return aFonts[nSize];
}

//Pre : El valor de nColor ha d'estar entre 0 i 16 ambdós inclosos.
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
//Post : Pinta el contingut del buffer temporal a la finestra gràfica.
void LS_allegro_paint(){
	al_flip_display();
}

//Pre: Cap
//Post: Executa les tasques necessàries perquè Allegro funcioni correctament. Aquest procediment s'ha de cridar sempre dins del bucle infinit
//del joc que estiguem implementant, ja que sinó, no podrem escoltar el teclat ni veurem els canvis a la finestra gràfica.
void LS_allegro_executiu(){
    LS_allegro_process_events();
	LS_allegro_paint();
}

//Pre : Cap	
//Post: Neteja els buffers del teclat perquè no hi quedi cap tecla emmagatzemada.
void LS_allegro_console_fflush(){
	fflush(stdout);
	stdin->_IO_read_ptr = stdin->_IO_read_base;
	stdin->_IO_read_end = stdin->_IO_read_base;
	fflush(stdin);
}

//Pre : Cap
//Post: Neteja la pantalla de la consola
void LS_allegro_console_clear_screen(){
	#if defined(__linux__) || (defined(__APPLE__) && defined(__MACH__))
		system("clear");	
	#endif
	#if defined(_WIN64) || defined(_WIN32)
		system("cls");
	#endif
}
