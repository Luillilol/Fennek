#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include<allegro5/allegro.h>
#include<allegro5/allegro_primitives.h>
#include<allegro5/allegro_font.h>
#include<allegro5/allegro_ttf.h>
#include<allegro5/allegro_image.h>
#include<allegro5/allegro_audio.h>
#include<allegro5/allegro_acodec.h>
#include<allegro5/allegro_color.h>
//al_resize_display(display, width, height);
#define KNIGHT 11
#define ARCHER 12
#define ORC 13
#define WIZARD 14
#define FEMKNIGHT 15
#define FEMARCHER 16
#define FEMWIZARD 17

#define BIOMPLANICIE 1
#define BIOMDESIERTO 2
#define BIOMSAVANA 3
#define BIOMBOSQUE 4
#define BIOMBOSQOSCURO 5
#define DUNGEON 6

#define GAME 77

struct potion
{
    float lifeMult;
    float xpMult;
    float damageMult;
    int type;
    int space;
};

ALLEGRO_DISPLAY *screen;

ALLEGRO_EVENT_QUEUE *events;
ALLEGRO_EVENT event;

ALLEGRO_TIMER *clouds;
ALLEGRO_TIMER *timer1;

ALLEGRO_FONT *menuFont;
ALLEGRO_FONT *dialogueFont;
ALLEGRO_FONT *indicationsFont;
ALLEGRO_FONT *itemsFont;
ALLEGRO_FONT *GO;
ALLEGRO_BITMAP *imgMenu;
ALLEGRO_BITMAP *imgClouds;
ALLEGRO_BITMAP *imgCredits;
ALLEGRO_BITMAP *imgInstructions;
ALLEGRO_BITMAP *escReturn;
ALLEGRO_BITMAP *charSelection;
ALLEGRO_BITMAP *mage1;
ALLEGRO_BITMAP *mage2;
ALLEGRO_BITMAP *mage3;
ALLEGRO_BITMAP *femMage1;
ALLEGRO_BITMAP *femMage2;
ALLEGRO_BITMAP *femMage3;
ALLEGRO_BITMAP *arch1;
ALLEGRO_BITMAP *arch2;
ALLEGRO_BITMAP *arch3;
ALLEGRO_BITMAP *femArch1;
ALLEGRO_BITMAP *femArch2;
ALLEGRO_BITMAP *femArch3;
ALLEGRO_BITMAP *knight1;
ALLEGRO_BITMAP *knight2;
ALLEGRO_BITMAP *knight3;
ALLEGRO_BITMAP *femKnight1;
ALLEGRO_BITMAP *femKnight2;
ALLEGRO_BITMAP *femKnight3;
ALLEGRO_BITMAP *orc1;
ALLEGRO_BITMAP *orc2;
ALLEGRO_BITMAP *orc3;
ALLEGRO_BITMAP *sel;
ALLEGRO_BITMAP *pausa;
ALLEGRO_BITMAP *options;

ALLEGRO_BITMAP *potionDamage;
ALLEGRO_BITMAP *potionLife;
ALLEGRO_BITMAP *potionXp;
ALLEGRO_BITMAP *legendPotion;

ALLEGRO_BITMAP *inventory;

ALLEGRO_BITMAP *ataque;
ALLEGRO_BITMAP *sprite;
ALLEGRO_BITMAP *paisaje;
ALLEGRO_BITMAP *paisaje1;
ALLEGRO_BITMAP *paisaje2;
ALLEGRO_BITMAP *dungeon_boss;
ALLEGRO_BITMAP *enen;
ALLEGRO_BITMAP *enemie;
ALLEGRO_BITMAP *boss;
ALLEGRO_BITMAP *flecha_derecha;
ALLEGRO_BITMAP *flecha_arriba;
ALLEGRO_BITMAP *magia_derecha;
ALLEGRO_BITMAP *magia_arriba;
ALLEGRO_FONT *nombre;
ALLEGRO_SAMPLE *sword;
ALLEGRO_SAMPLE *sword2;
ALLEGRO_SAMPLE * disparo_flecha;
ALLEGRO_SAMPLE *gemido;
ALLEGRO_SAMPLE *gemido2;
ALLEGRO_SAMPLE *gemido_muerte;
ALLEGRO_SAMPLE *gemido_mujer1;
ALLEGRO_SAMPLE *gemido_mujer2;
int out=0, redraw=1, end=0, pantalla=1, selected=1, loaded=0, cloudX=0, cloudY=0, cSelect=0, selectedChar=0, selectGO = 1, cont_boss, final_boss_cont=0, cont_exp, num_enemies=0, cont_anuncio=0;
int saved=0, pause=0, pauseSelected=0, mSelect=0,iSelect=0, pocionOcupada=0, potionDropped=0;
float width=1280, height=720;
float dx_org, dy_org;

//Se incluyen las mecánicas después de la inicialización para evitar hacerlo 2 veces y ambos archivos manejen las mismas variables.
#include "Hitbox2.c"

//Función que hace todo lo que necesite ser inicializado o asignado antes de empezar la ejecución del resto
int initialize()
{
    int check=0;
    if(!al_init())
    {
        printf("Allegro wasn't initialized");
        check=1;
    }
    if(!al_init_font_addon()||!al_init_ttf_addon())
    {
        printf("text is not working");
        check=1;
    }
    if(!al_init_primitives_addon())
    {
        printf("There are not figures");
        check=1;
    }
    if(!al_install_keyboard())
    {
        printf("There's no imput");
        check=1;
    }
    if(!al_init_image_addon())
    {
        printf("There are not images");
        check=1;
    }
    menuFont=al_load_font("Fonts/Goldman/Goldman-Regular.ttf",width/35,0);
    dialogueFont=al_load_font("Fonts/Oldenburg/Oldenburg-Regular.ttf", width/55,0);
    indicationsFont=al_load_font("Fonts/Satisfy/Satisfy-Regular.ttf", width/45,0);
    itemsFont=al_load_font("Fonts/Simonetta/Simonetta-Italic.ttf", width/35,0);
    GO = al_load_font("Fonts/Satisfy/Satisfy-Regular.ttf", width/20,0);
    if(!menuFont||!dialogueFont||!indicationsFont||!itemsFont||!GO)
    {
        printf("One or many fonts are not working");
        check=1;
    }
    if(!al_init_image_addon())
    {
        printf("Image complement is not loaded");
        check=1;
    }
    if(!al_install_audio())
    {
        printf("Theres no audio");
        check=1;
    }
    //
    if(!al_init_acodec_addon())
    {
        printf("No se instaló un codificador");
        check=1;
    }
    imgMenu=al_load_bitmap("Images/Menu.png");
    imgClouds=al_load_bitmap("Images/clouds.png");
    imgCredits=al_load_bitmap("Images/Creditos.jpg");
    imgInstructions=al_load_bitmap("Images/Instrucciones.jpg");
    escReturn=al_load_bitmap("Images/Back.png");
    charSelection=al_load_bitmap("Images/CharacterSelection.png");
    mage1=al_load_bitmap("Images/Mago1.png");
    mage2=al_load_bitmap("Images/mago2.png");
    mage3=al_load_bitmap("Images/Mago3.png");
    femMage1=al_load_bitmap("Images/maga1.png");
    femMage2=al_load_bitmap("Images/maga2.png");
    femMage3=al_load_bitmap("Images/maga3.png");
    orc1=al_load_bitmap("Images/Orco1.png");
    orc2=al_load_bitmap("Images/Orco2.png");
    orc3=al_load_bitmap("Images/Orco3.png");
    arch1=al_load_bitmap("Images/arqueroA.png");
    arch2=al_load_bitmap("Images/arqueroD.png");
    arch3=al_load_bitmap("Images/arqueroW.png");
    knight1=al_load_bitmap("Images/caballeroA.png");
    knight2=al_load_bitmap("Images/caballeroD.png");
    knight3=al_load_bitmap("Images/caballeroW.png");
    femArch1=al_load_bitmap("Images/femarcher1.png");
    femArch2=al_load_bitmap("Images/femarcher2.png");
    femArch3=al_load_bitmap("Images/femarcher3.png");
    femKnight1=al_load_bitmap("Images/femknight1.png");
    femKnight2=al_load_bitmap("Images/femknight2.png");
    femKnight3=al_load_bitmap("Images/femknight3.png");
    pausa=al_load_bitmap("Images/Pause.png");
    options=al_load_bitmap("Images/Options.png");
    inventory=al_load_bitmap("Images/Inventory.png");

    potionDamage=al_load_bitmap("Images/PocionDamage.png");
    potionLife=al_load_bitmap("Images/PocionVida.png");
    potionXp=al_load_bitmap("Images/PocionXp.png");
    legendPotion=al_load_bitmap("Images/SuperPocion.png");

    sel=al_load_bitmap("Images/Selection.png");
    if(!legendPotion||!potionXp||!potionLife||!potionDamage||!inventory||!imgMenu||!imgClouds||!imgCredits||!imgInstructions||!escReturn||!mage1||!mage2||!mage3||!femMage1||!femMage2||!femMage3||!orc1||!orc2||!orc3||!arch1||!arch2||!arch3||!knight1||!knight2||!knight3||!femKnight1||!femKnight2||!femKnight3||!femArch1||!femArch2||!femArch3||!sel||!pausa||!options)
    {
        printf("Images Not Found");
        check=1;
    }
    clouds=al_create_timer(0.4);

        if(!al_reserve_samples(2))
    {
        printf("no se pudo cargar los canales de audio");
        check = 1;
    }
    gemido_mujer1 = al_load_sample("Sound/Grunt_mujer1.mp3");
    gemido_mujer2 = al_load_sample("Sound/Grunt_mujer2.mp3");
    gemido = al_load_sample("Sound/Grunt.mp3");
    gemido2 = al_load_sample("Sound/Grunt2.mp3");
    gemido_muerte = al_load_sample("Sound/Gemido_muerte.mp3");
    sword = al_load_sample("Sound/Espadas.mp3");
    sword2 = al_load_sample("Sound/Espadas2.mp3");
    disparo_flecha = al_load_sample("Sound/Bow.mp3");
    sprite = checkPersonaje();
    nombre = al_load_font("Fonts/Oldenburg/Oldenburg-Regular.ttf", 20, 0);
    paisaje = al_load_bitmap("Images/Map.png");
    dungeon_boss = al_load_bitmap("Images/Dungeon_boss.png");
    enen = al_load_bitmap("Images/Esqueleto.png");
    enemie = al_load_bitmap("Images/Robot2.png");
    boss = al_load_bitmap("Images/Dragon.png");
    ataque = al_load_bitmap("Images/Ataque.png");
    flecha_derecha = al_load_bitmap("Images/Flecha_derecha.png");
    flecha_arriba = al_load_bitmap("Images/Flecha_arriba.png");
    magia_derecha = al_load_bitmap("Images/magiaA.png");
    magia_arriba = al_load_bitmap("Images/magiaW.png");
    if(!(sword||sword2||disparo_flecha||gemido||gemido2||gemido_muerte||gemido_mujer1||gemido_mujer2))
    {
        printf("no swords");
        check = 1;
    }
    if(!(sprite||paisaje||enemie||dungeon_boss||boss))
    {
        printf("no hay imagen");
        check = 1;
        out=1;
    }
    if(!ataque)
    {
        printf("no hay ataque");
        check = 1;
    }
    if(!nombre)
    {
        printf("no se pudo texto");
        check = 1;
    }

    return check;
}
int loadRecord()
{

}
void resetAll()
{
    out=0;
    redraw=1;
    end=0;
    pantalla=1;
    selected=1;
    loaded=0;
    cSelect=0;
    selectedChar=0;
    saved=0;
    pause=0;
    pauseSelected=0;
    mSelect=0;
    iSelect=0;
    pocionOcupada=0;
    potionDropped=0;
    width=1280;
    height=720;
    fin = 0;
    redibujar = 1;
    i = 2;
    ran = 0;
    enem_generados = 0;
    colision=0;
    cont_son_f=0;
    cont_damage=1;
    cont_arrow2=1;
    velocidad = 10;
    num_enemies = 0;
    chec_pers_golpe=0;
    dx = 0.0;
    dy = 0.00;
    x=0;
    y=0;
    espada.ID=2;
    espada.ID=1.5;
    arco.ID = 1;
    arco.multiplier = 2;
    character.direccion = 4;
    character.vida = 10;
    character.damage = 0;
    character.magia = 10;
    character.exp=0;
}
//Función encargada de la generación aleatorea de pociones con atributos aleatorios
//Su parametro de entrada es si el enemigo murió, para que solo en caso de que estos mueran, se genere una poción en el inventario.
int potionDrop(int enemyDead)
{
    int atribute1=0, atribute2=0,atribute3=0, probability=0, probability2=0;
    struct potion stat;

    //Se establece el valor inicial de 1 para no modificar los atributos naturales del personaje.
    stat.damageMult=1;
    stat.lifeMult=1;
    stat.xpMult=1;



    FILE *potionLoad;

    srand(time(NULL));
    potionDropped=0;
    //Si un enemigo murió, empieza el proceso lógico de generar una poción.
    if(enemyDead==1&&stat.space<=12)
    {
        probability=rand()%100;
        //hay un 33% de probabilidades de que se genere una poción.
        if(probability%3==0)
        {
            //una vez que se sabe que se generará una poción, se establece una nueva probabilidad para determinar qué tipo de poción se generará
            probability=rand()%100;
            //Hay un 4% de probabilidad de ganar una poción especial que te boostea en todos
            if(probability==4||probability==8||probability==57||probability==81)
            {
                stat.damageMult*=1.5;
                stat.lifeMult*=1.5;
                stat.xpMult*=1.5;

                stat.type=4;
                stat.space++;
            }
            //33% de posibilidad de obtener una poción que boostee el daño
            else if(probability%3==0)
            {
                //Además hay una probabilidad de que el tamaño del boost sea distinto
                probability2=rand()%10;
                if(probability2>=0&&probability2<=2)
                {
                    stat.damageMult*=1.2;
                }
                if(probability2>=3&&probability2<=5)
                {
                    stat.damageMult*=1.3;
                }
                if(probability2>=6&&probability2<=8)
                {
                    stat.damageMult*=1.5;
                }
                if(probability2==9)
                {
                    stat.damageMult*=1.7;
                }

                stat.type=1;
                stat.space++;
            }
            //33% de posibilidad de obtener una poción que boostee la experiencia
            else if(probability%3==1)
            {
                //Además hay una probabilidad de que el tamaño del boost sea distinto
                probability2=rand()%10;
                if(probability2>=0&&probability2<=2)
                {
                    stat.xpMult*=1.2;
                }
                if(probability2>=3&&probability2<=5)
                {
                    stat.xpMult*=1.3;
                }
                if(probability2>=6&&probability2<=8)
                {
                    stat.xpMult*=1.5;
                }
                if(probability2==9)
                {
                    stat.xpMult*=1.7;
                }

                stat.type=2;
                stat.space++;
            }
            //33% de posibilidad de obtener una poción que boostee la vida
            else if(probability%3==2)
            {
                //Además hay una probabilidad de que el tamaño del boost sea distinto
                probability2=rand()%10;
                if(probability2>=0&&probability2<=2)
                {
                    stat.lifeMult*=1.2;
                }
                if(probability2>=3&&probability2<=5)
                {
                    stat.lifeMult*=1.3;
                }
                if(probability2>=6&&probability2<=8)
                {
                    stat.lifeMult*=1.5;
                }
                if(probability2==9)
                {
                    stat.lifeMult*=1.7;
                }

                stat.type=3;
                stat.space++;
            }
            potionDropped=1;
        }
    }
    else if (stat.space==12)
    {
        potionDropped=3;
    }
    //Se guardan los datos de la poción para que se pueda acceder a través del inventario.
    if(potionDropped==1)
    {
        potionLoad=fopen("generatedPotion.fn", "ab+");
        fwrite(&stat, sizeof(stat), 1, potionLoad);
        fclose(potionLoad);
    }
    return potionDropped;
}

void mov_boss()
{
    int control, velocidad =5;
    dragon.x_boss;
    if(dragon.x_boss < 850 && cont_mov_boss==0)
    {
        dragon.x_boss+=velocidad;
        if(dragon.x_boss == 850)
        {
            cont_mov_boss =1;
        }
    }
    else if(dragon.x_boss>450 && cont_mov_boss == 1)
    {
        dragon.x_boss-=velocidad;
        if(dragon.x_boss<=450)
        {
            cont_mov_boss =2;
        }
    }
    else if(dragon.x_boss<640 && cont_mov_boss ==2)
    {
        dragon.x_boss+=velocidad;
        if(dragon.x_boss == 640)
        {
            cont_mov_boss =3;
        }
    }
    if(dragon.y_boss>0 && cont_mov_boss == 3)
    {
        dragon.y_boss-=velocidad;
        if(dragon.y_boss == 0)
        {
            cont_mov_boss =4;
        }
    }
    else if(dragon.y_boss<440 && cont_mov_boss == 4)
    {
        dragon.y_boss +=velocidad;
        if(dragon.y_boss == 440)
        {
            cont_mov_boss =5;
        }
    }
    else if(dragon.y_boss>280 && cont_mov_boss == 5)
    {
        dragon.y_boss -= velocidad;
        if(dragon.y_boss == 280)
        {
            cont_mov_boss =0;
        }
    }
}

int checar_colision_flecha(int cont2)
{
     int i, x, y;
     //printf("\nPTMasdad\n");
     for(i=0; i<num_enemies; i++)
     {
         if(enemies_pantalla[i].vida>0 || final_boss_cont == 1)
         {
            if(dir_arrow == 4)
            {
                x = arrows.arco_x-10;
                y = arrows.arco_y;
            }
            if(dir_arrow == 2)
            {
                x = arrows.arco_x-95;
                y = arrows.arco_y+10;
            }
            if(dir_arrow == 1)
            {
                x = arrows.arco_x-60;
                y = arrows.arco_y-60;
            }
            if(dir_arrow == 3)
            {
                x = arrows.arco_x-35;
                y = arrows.arco_y+20;
            }
            if(final_boss_cont == 0)
            {
                if(( x+70 < enemies_pantalla[i].x_enem+140 &&  x+135 > enemies_pantalla[i].x_enem-50 && (height-131)+y+30 < enemies_pantalla[i].y_enem+140 && (height-131)+y+55 > enemies_pantalla[i].y_enem-50))
                {
                    //printf("HOLAA");
                    enemies_pantalla[i].id_flecha = 1;
                }
                else
                {
                    enemies_pantalla[i].id_flecha = 0;
                }
                if(enemies_pantalla[i].id_flecha ==1 && cont2 == 1 && arrows.life == 1)
                {
                    enemies_pantalla[i].vida-=50;
                    //al_clear_to_color(al_map_rgb(0,0,255));
                    //al_flip_display();
                    cont2=0;
                    arrows.life = 0;
                }
            }
            if(final_boss_cont == 1)
            {
                //printf("HOLCACASDA\n");
                if(x+70 < dragon.x_boss+450 && x+135 > dragon.x_boss-30 && (height-131)+y+30 < dragon.y_boss+600 && (height-131)+y+55 > dragon.y_boss-50)
                {
                    dragon.vida-=8;
                    arrows.life = 0;
                }
            }
            if(dragon.vida ==0)
            {
                pantalla = 8;
            }

        }
     }

    return cont2;
}



//Función que detecta todos los eventos necesarios antes del juego.
int registerEvents(int selection)
{
    int cont_gemido, cont_gemido2;
    if(event.type == ALLEGRO_EVENT_TIMER)
    {
        if(event.timer.source==clouds)
        {
            if(cloudX>(-width))
            {
                cloudX-=1;
            }
            else
            {
                cloudX=width;
            }
            redraw=1;
        }
    }
    //Menú
    if(pantalla==1)
    {
        //Detecta las teclas que accionan cambios en el menú
        if(event.type == ALLEGRO_EVENT_KEY_CHAR)
        {
            if(event.keyboard.keycode == ALLEGRO_KEY_UP)
            {
                if(selection>1)
                {
                    selection--;
                }
                else
                {
                    selection=5;
                }
                redraw=1;
            }
            else if(event.keyboard.keycode == ALLEGRO_KEY_DOWN)
            {
                if(selection<6)
                {
                    selection++;
                }
                else
                {
                    selection=1;
                }
                redraw=1;
            }
            //Detecta si el usuario ha activado una opción.
            else if(event.keyboard.keycode==ALLEGRO_KEY_ENTER||event.keyboard.keycode==ALLEGRO_KEY_PAD_ENTER)
            {
                if(selection==1)
                {
                    resetAll();
                    pantalla=6;
                    redraw=1;
                    loaded=0;

                }
                if(selection==2)
                {
                    if(selectedChar!=0)
                    {
                        pantalla=GAME;
                        redraw=1;
                        loaded=1;
                    }
                }
                if(selection==3)
                {
                    pantalla=3;
                    redraw=1;
                }
                if(selection==4)
                {
                    end=1;
                }
                if(selection==5)
                {
                    pantalla=5;
                    redraw=1;
                }
            }
        }
    }
    //Prejuego, abre o crea un archivo donde se guarda el personaje y su posición.
    if(pantalla==2)
    {

        FILE *data;

        if(loaded==1)
        {

        }
        else
        {
            if(loaded=0)
            {
                data=fopen("save.fk", "wb+");
                fwrite(&selectedChar, sizeof(selectedChar),1,data);
                fclose(data);
            }
        }
        if(selectedChar!=0&&out!=1)
        {
            pantalla=GAME;
        }
    }
    //Creditos
    if(pantalla==3)
    {
        if(event.keyboard.keycode==ALLEGRO_KEY_ESCAPE)
        {
            pantalla=1;
            redraw=1;
        }
    }
    //Instrucciones
    if(pantalla==5)
    {
        if(pause==0)
        {
            if(event.keyboard.keycode==ALLEGRO_KEY_ESCAPE)
            {
                pantalla=1;
                redraw=1;
            }
        }
        if(pause==3)
        {
            if(event.keyboard.keycode==ALLEGRO_KEY_ESCAPE)
            {
                pause=0;
                pantalla=GAME;
                redraw=1;
            }
        }
    }
    //Selección de personaje
    if(pantalla==6)
    {
        if(event.type == ALLEGRO_EVENT_KEY_CHAR)
        {
            if(event.keyboard.keycode==ALLEGRO_KEY_LEFT)
            {
                if(cSelect>1)
                {
                    cSelect--;
                }
                else
                {
                    cSelect=7;
                }
                redraw=1;

            }
            if(event.keyboard.keycode==ALLEGRO_KEY_RIGHT)
            {
                if(cSelect<8)
                {
                    cSelect++;
                }
                else
                {
                    cSelect=1;
                }
                redraw=1;
            }
            if(event.keyboard.keycode==ALLEGRO_KEY_ENTER)
            {
                if(cSelect==1)
                {
                    character.personaje=WIZARD;
                    selectedChar=WIZARD;
                    pantalla=2;
                }
                if(cSelect==2)
                {
                    character.personaje=FEMWIZARD;
                    selectedChar=FEMWIZARD;
                    pantalla=2;
                }
                if(cSelect==5)
                {
                    character.personaje=ARCHER;
                    selectedChar=ARCHER;
                    pantalla=2;
                }
                if(cSelect==6)
                {
                    character.personaje=FEMARCHER;
                    selectedChar=FEMARCHER;
                    pantalla=2;
                }
                if(cSelect==4)
                {
                    character.personaje=KNIGHT;
                    selectedChar=KNIGHT;
                    pantalla=2;
                }
                if(cSelect==3)
                {

                    character.personaje=FEMKNIGHT;
                    selectedChar=FEMKNIGHT;
                    pantalla=2;
                }
                if(cSelect==7)
                {
                    character.personaje=ORC;
                    selectedChar=ORC;
                    pantalla=2;
                }
            }
        }
    }
    /*if(pantalla==8)
    {
        if(event.type==ALLEGRO_EVENT_KEY_CHAR)
        {
            if(event.keyboard.keycode==ALLEGRO_KEY_RIGHT)
            {
                if(mSelect<5)
                {
                    mSelect++;
                }
                else
                {
                    mSelect=1;
                }
                redraw=1;
            }
            if(event.keyboard.keycode==ALLEGRO_KEY_LEFT)
            {
                if(mSelect>1)
                {
                    mSelect--;
                }
                else
                {
                    mSelect=4;
                }
                redraw=1;
            }
            if(event.keyboard.keycode==ALLEGRO_KEY_ENTER)
            {
                if(mSelect==1)
                {
                    width=1280;
                    height=720;
                    al_resize_display(screen, width, height);
                    redraw=1;
                }
                if(mSelect==2)
                {
                    width=1920;
                    height=1080;
                    al_resize_display(screen, width, height);
                    redraw=1;
                }
            }

            if(event.keyboard.keycode==ALLEGRO_KEY_ESCAPE)
            {
                pause=0;
                pantalla=GAME;
                redraw=1;
            }
        }
    }*/
    //Inventario
    if(pantalla==9)
    {
        if(event.type==ALLEGRO_EVENT_KEY_CHAR)
        {
            if(event.keyboard.keycode==ALLEGRO_KEY_ESCAPE)
            {
                pause=0;
                pantalla=GAME;
                redraw=1;
            }
            else if (event.keyboard.keycode==ALLEGRO_KEY_RIGHT)
            {
                if(iSelect<13)
                {
                    iSelect++;
                }
                else
                {
                    iSelect=1;
                }
                redraw=1;
            }
            else if (event.keyboard.keycode==ALLEGRO_KEY_LEFT)
            {
                if(iSelect>1)
                {
                    iSelect--;
                }
                else
                {
                    iSelect=12;
                }
                redraw=1;
            }
            else if (event.keyboard.keycode==ALLEGRO_KEY_UP)
            {
               if(iSelect>1)
                {
                    iSelect-=3;
                }
                else
                {
                    iSelect=12;
                }
                redraw=1;
            }
            else if (event.keyboard.keycode==ALLEGRO_KEY_DOWN)
            {
                if(iSelect<13)
                {
                    iSelect+=3;
                }
                else
                {
                    iSelect=1;
                }
                redraw=1;
            }

        }
    }
    //Eventos del videojuego
    if(pantalla==GAME&&pause==0)
    {
        if(character.damage>cont_damage && character.damage<10)
        {
            if(character.personaje == ARCHER || character.personaje == WIZARD || character.personaje == ORC || character.personaje == KNIGHT)
            {
                cont_gemido = rand()%2+1;
                if(cont_gemido ==1){
                    al_play_sample(gemido, 1.0, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
                }
                else if(cont_gemido==2)
                {
                    al_play_sample(gemido2, 1.0, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
                }
            }
            else if(character.personaje == FEMARCHER || character.personaje == FEMKNIGHT || character.personaje == FEMWIZARD)
            {
                cont_gemido2 = rand()%2+1;
                if(cont_gemido2 ==1){
                    al_play_sample(gemido_mujer1, 1.0, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
                }
                else if(cont_gemido2==2)
                {
                    al_play_sample(gemido_mujer2, 1.0, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
                }
            }
            cont_damage++;
        }
        if(num_enemies == 0)
        {
            num_enemies = rand()%6+1;
            enem_generados = 0;
        }
        if(final_boss_cont == 1)
        {
            colision_dragon = colision_dragon_ataque();

            // colision_dragon_daño();
        }
        colision = checar_colision_ataque(enemies_pantalla, num_enemies);
        checar_colision_damage(enemies_pantalla, num_enemies);///
        checar_exp(num_enemies);
        checkPantalla(x, (height-131)+y);
        cont_exp = character.exp- num_enemies*50;
        switch(event.type)
        {
            case ALLEGRO_EVENT_TIMER:
                if(event.timer.source == timer1)
                {
                    redraw = 1;
                }
                break;
            case ALLEGRO_EVENT_KEY_CHAR:
                if(event.keyboard.keycode == ALLEGRO_KEY_W)
                {
                    character.direccion = 1;
                    if(y-velocidad > -600)
                        y -= velocidad;
                    //printf("x:%f\n y:%f\n", dx+x, dy+y);
                }
                else if(event.keyboard.keycode == ALLEGRO_KEY_S)
                {
                    character.direccion = 3;
                    if(y+velocidad < 100)
                        y += velocidad;
                    //printf("x:%f\n y:%f\n", dx+x, dy+y);
                }
                else if(event.keyboard.keycode == ALLEGRO_KEY_A)
                {
                    character.direccion = 2;
                    if(x-velocidad > -10)
                        x -= velocidad;
                    //printf("x:%f\n y:%f\n", dx+x, dy+y);
                }
                else if(event.keyboard.keycode == ALLEGRO_KEY_D)
                {
                    character.direccion = 4;
                    if(x+velocidad < 1250)
                        x += velocidad;
                    //printf("x:%f\n y:%f\n", dx+x, dy+y);
                }
                else if(event.keyboard.keycode == ALLEGRO_KEY_F)
                {
                    if(final_boss_cont == 0){
                        sonido1 = golpear(colision, enemies_pantalla);
                    }
                    else if(final_boss_cont == 1){
                        sonido1 = colision_dragon;
                    }
                    if(character.personaje == KNIGHT||character.personaje == FEMKNIGHT||character.personaje == ORC)
                    {
                        if(sonido1 == 1)
                        {
                            if(cont_son_f == 0)
                            {
                                al_play_sample(sword, 1.0, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
                            }
                            else if(cont_son_f ==1)
                            {
                                al_play_sample(sword2, 1.0, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
                            }
                            cont_son_f = rand()%2;
                            if(final_boss_cont==1)
                            {
                                dragon.vida-=50;
                            }
                        }
                    }
                    else if(character.personaje == ARCHER||character.personaje == FEMARCHER||character.personaje == WIZARD||character.personaje == FEMWIZARD)
                    {
                        if(arrows.life == 0)
                        {
                            direccion_flecha();
                            al_play_sample(disparo_flecha, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
                            disp_flecha=1;
                            cont_arrow2=1;
                        }
                    }
                }
                else if(event.keyboard.keycode == ALLEGRO_KEY_E)
                {
                    if(cont_boss == 1)
                    {
                        printf("\nEXP2 = %i\n", (character.exp)- num_enemies*50);
                        if(cont_exp < 2500)
                        {
                            cont_anuncio = 1;
                            al_draw_text(nombre, al_map_rgb(0,0,255), width/2, 0, ALLEGRO_ALIGN_CENTER, "Presiona E para entrar");
                            al_clear_to_color(al_map_rgb(41, 23, 41));
                            al_flip_display();
                        }
                        if(cont_exp > 2500)
                        {
                            cont_anuncio = 0;
                            final_boss_cont = 1;
                        }
                    }
                }
                else if(event.keyboard.keycode==ALLEGRO_KEY_ESCAPE)
                {
                    if(pause==0)
                    {
                        pause=1;
                        redraw=1;
                    }
                }
                break;
        }

    }
    else if(pause==1||pause==3)
        {

            if(event.type==ALLEGRO_EVENT_KEY_CHAR)
            {
                if(event.keyboard.keycode == ALLEGRO_KEY_UP)
            {

                if(pauseSelected>1)
                {
                    pauseSelected--;
                }
                else
                {
                    pauseSelected=5;
                }
                redraw=1;
            }
            else if(event.keyboard.keycode == ALLEGRO_KEY_DOWN)
            {
                if(pauseSelected<6)
                {
                    pauseSelected++;
                }
                else
                {
                    pauseSelected=1;
                }
                redraw=1;
            }
                else if(event.keyboard.keycode==ALLEGRO_KEY_ESCAPE)
                {
                    if(pause==1)
                    {
                        pause=0;
                        redraw=1;
                    }
                }
            }
            else if(event.keyboard.keycode == ALLEGRO_KEY_ENTER)
            {
                //Continuar
                if(pauseSelected==1)
                {
                    pause=0;
                    redraw=1;
                }
                //Inventario
                if(pauseSelected==2)
                {
                    pantalla=9;
                    pause=3;
                    redraw=1;
                }
                //Guardar
                if(pauseSelected==3)
                {
                    loadRecord();

                    /*pantalla=8;
                    pause=3;
                    redraw=1;*/
                }
                //Salir
                if(pauseSelected==4)
                {
                    //Guardar
                    //uvgvbu
                    pantalla=1;
                    out=1;
                    pause=0;
                    selection=0;
                }
                //Instrucciones
                if(pauseSelected==5)
                {
                    pantalla=5;
                    pause=3;
                    redraw=1;
                }
            }
        }
        if(pantalla == 7)
        {
            if(event.type==ALLEGRO_EVENT_KEY_CHAR)
            {
                if(event.keyboard.keycode==ALLEGRO_KEY_W)
                {
                    if(selectGO-1 <= 0)
                        selectGO = 2;
                    else
                        selectGO--;
                    printf("%i", selectGO);
                }
                else if(event.keyboard.keycode==ALLEGRO_KEY_S)
                {
                    if(selectGO+1 >= 3)
                        selectGO = 1;
                    else
                        selectGO++;
                    printf("%i", selectGO);
                }
                else if(event.keyboard.keycode==ALLEGRO_KEY_ENTER)
                {
                    if(selectGO == 1)
                    {
                        ;
                    }
                    if(selectGO == 2)
                    {
                        pantalla=1;
                        character.damage = 0;
                    }
                }
            }
        }
    return selection;
}
//Función que hace todos los cambios gráficos
int drawEvents()
{
    ALLEGRO_COLOR backgroundMenu;
    ALLEGRO_COLOR credits;
    ALLEGRO_COLOR instructions;
    ALLEGRO_COLOR option1;
    ALLEGRO_COLOR option2;
    ALLEGRO_COLOR option3;
    ALLEGRO_COLOR option4;
    ALLEGRO_COLOR option5;

    ALLEGRO_COLOR square;

    float rectangleX1,rectangleY1,rectangleX2,rectangleY2,rectangleY3,rectangleY4,rectangleY5,rectangleY6,rectangleY7,rectangleY8,rectangleY9,rectangleY10;

    float sqX1=0, sqX2=0, sqY1=0, sqY2=0;
    float posX1,posX2,posX3,posX4,posX5,posX6, posY1,posY2,posY3,posY4,posY5,posY6,posY7,posY8;

    posX1=(width/10)*6;
    posX2=(width/10)*7;
    posX3=((width/10)*7)+width/40;
    posX4=((width/10)*8)+width/40;
    posX5=((width/10)*8)+width/20;
    posX6=((width/10)*9)+width/20;

    posY1=(height/6)+height/75;
    posY2=(height/6)+width/10;
    posY3=((height/6)*2)+height/40;
    posY4=((height/6)*2)+width/10+height/80;
    posY5=((height/6)*3)+height/20;
    posY6=((height/6)*3)+width/10+height/30;
    posY7=((height/6)*4)+height/13;
    posY8=((height/6)*4)+width/10+height/15;


    rectangleX1=(width/2)-((width/3)/2);
    rectangleX2=(width/2)+((width/3)/2);

    rectangleY1=((height/7)*2)+(height/95);
    rectangleY2=((height/7)*2)+(height/17);
    rectangleY3=((height/7)*3)+(height/95);
    rectangleY4=((height/7)*3)+(height/17);
    rectangleY5=((height/7)*4)+(height/95);
    rectangleY6=((height/7)*4)+(height/17);
    rectangleY7=((height/7)*5)+(height/95);
    rectangleY8=((height/7)*5)+(height/17);
    rectangleY9=((height/7)*6)+(height/95);
    rectangleY10=((height/7)*6)+(height/17);


    backgroundMenu=al_color_html("#de445f");
    credits=al_color_html("#0677fd");
    instructions=al_color_html("#9877ff");
    square=al_color_html("#d6b80b");
    //Menu
    if(pantalla==1)
    {
        if(selected==1)
        {
            option1=al_color_html("#350b7d");
        }
        else
        {
            option1=al_color_html("#ffffff");
        }
        if(selected==2)
        {
            option2=al_color_html("#350b7d");
        }
        else
        {
            option2=al_color_html("#ffffff");
        }
        if(selected==3)
        {
            option3=al_color_html("#350b7d");
        }
        else
        {
            option3=al_color_html("#ffffff");
        }
        if(selected==4)
        {
            option4=al_color_html("#350b7d");
        }
        else
        {
            option4=al_color_html("#ffffff");
        }
        if(selected==5)
        {
            option5=al_color_html("#350b7d");
        }
        else
        {
            option5=al_color_html("#ffffff");
        }
        al_draw_scaled_bitmap(imgMenu,0,0,al_get_bitmap_width(imgMenu),al_get_bitmap_height(imgMenu),0,0,width,height,0);
        al_draw_scaled_bitmap(imgClouds,0,0,al_get_bitmap_width(imgClouds),al_get_bitmap_height(imgClouds),cloudX,0,width,height,0);

        al_draw_filled_rectangle(rectangleX1,rectangleY1,rectangleX2,rectangleY2,al_color_html("#585759"));
        al_draw_filled_rectangle(rectangleX1,rectangleY3,rectangleX2,rectangleY4,al_color_html("#585759"));
        al_draw_filled_rectangle(rectangleX1,rectangleY5,rectangleX2,rectangleY6,al_color_html("#585759"));
        al_draw_filled_rectangle(rectangleX1,rectangleY7,rectangleX2, rectangleY8,al_color_html("#585759"));
        al_draw_filled_rectangle(rectangleX1,rectangleY9,rectangleX2,rectangleY10,al_color_html("#585759"));

        al_draw_rectangle(rectangleX1+(width/320),rectangleY1+(height/180),rectangleX2-(width/320),rectangleY2-(height/180), al_color_html("#49484a"),height/360);
        al_draw_rectangle(rectangleX1+(width/320),rectangleY3+(height/180),rectangleX2-(width/320),rectangleY4-(height/180), al_color_html("#49484a"),height/360);
        al_draw_rectangle(rectangleX1+(width/320),rectangleY5+(height/180),rectangleX2-(width/320),rectangleY6-(height/180), al_color_html("#49484a"),height/360);
        al_draw_rectangle(rectangleX1+(width/320),rectangleY7+(height/180),rectangleX2-(width/320),rectangleY8-(height/180), al_color_html("#49484a"),height/360);
        al_draw_rectangle(rectangleX1+(width/320),rectangleY9+(height/180),rectangleX2-(width/320),rectangleY10-(height/180), al_color_html("#49484a"),height/360);


        al_draw_text(menuFont,option1,width/2,(height/7)*2, ALLEGRO_ALIGN_CENTER, "Jugar Nuevo");
        al_draw_text(menuFont,option2,width/2,(height/7)*3,ALLEGRO_ALIGN_CENTER, "Jugar guardado");
        al_draw_text(menuFont,option3,width/2,(height/7)*4,ALLEGRO_ALIGN_CENTER, "Créditos");
        al_draw_text(menuFont,option4,width/2,(height/7)*5,ALLEGRO_ALIGN_CENTER, "Salir");
        al_draw_text(menuFont,option5,width/2,(height/7)*6,ALLEGRO_ALIGN_CENTER, "Instrucciones");

    }
    //Creditos
    if(pantalla==3)
    {
        al_draw_scaled_bitmap(imgCredits,0,0,al_get_bitmap_width(imgCredits),al_get_bitmap_height(imgCredits),0,0,width,height,0);
        al_draw_scaled_bitmap(escReturn,0,0,al_get_bitmap_width(escReturn),al_get_bitmap_height(escReturn),(width/15),(height/7)*6,(al_get_bitmap_width(escReturn))/5,(al_get_bitmap_height(escReturn))/6,0);
    }
    //Instrucciones
    if(pantalla==5)
    {
       al_draw_scaled_bitmap(imgInstructions,0,0,al_get_bitmap_width(imgInstructions),al_get_bitmap_height(imgInstructions),0,0,width,height,0);
        al_draw_scaled_bitmap(escReturn,0,0,al_get_bitmap_width(escReturn),al_get_bitmap_height(escReturn),(width/15),(height/7)*6,(al_get_bitmap_width(escReturn))/5,(al_get_bitmap_height(escReturn))/6,0);
    }
    //Selección de personajes
    if(pantalla==6)
    {
        al_draw_scaled_bitmap(charSelection,0,0,al_get_bitmap_width(charSelection),al_get_bitmap_height(charSelection),0,0,width,height,0);
        al_draw_filled_rectangle(width/4,height/6,(width/4)*3,(height/6)+(height/15),al_color_html("#585759"));
        al_draw_rectangle((width/4)+width/200,(height/6)+height/100,((width/4)*3)-width/200,((height/6)+(height/15))-height/100,al_color_html("#3d3d3d"),width/380);
        al_draw_text(menuFont,al_color_html("#0d0040"),width/2,(height/6), ALLEGRO_ALIGN_CENTER, "Selecciona tu personaje");

        //Selección Mago
        if(cSelect==1)
        {
            al_draw_scaled_bitmap(sel,0,0,al_get_bitmap_width(sel),al_get_bitmap_height(sel),width/9,(height/2)+height/20,width/7,height/5,0);
        }
        //Selección Maga
        if(cSelect==2)
        {
            al_draw_scaled_bitmap(sel,0,0,al_get_bitmap_width(sel),al_get_bitmap_height(sel),(width/9)*2,(height/2)+height/20,width/7,height/5,0);
        }
        //Selección caballero
        if(cSelect==3)
        {
            al_draw_scaled_bitmap(sel,0,0,al_get_bitmap_width(sel),al_get_bitmap_height(sel),((width/7)*2)-width/14,((height/8)*6)+(height/115),width/7,height/5,0);
        }
        //Selección caballera xd
        if(cSelect==4)
        {
            al_draw_scaled_bitmap(sel,0,0,al_get_bitmap_width(sel),al_get_bitmap_height(sel),((width/7)*2)+width/40,((height/8)*6)+(height/115),width/7,height/5,0);
        }
        //Selección Arquero
        if(cSelect==5)
        {
            al_draw_scaled_bitmap(sel,0,0,al_get_bitmap_width(sel),al_get_bitmap_height(sel),((width/7)*4)+width/40,((height/10)*7)+(height/35),width/7,height/5,0);
        }
        //Selección Arquera
        if(cSelect==6)
        {
            al_draw_scaled_bitmap(sel,0,0,al_get_bitmap_width(sel),al_get_bitmap_height(sel),((width/7)*4)+width/8,((height/10)*7)+(height/35),width/7,height/5,0);
        }
        //Selección Orco
        if(cSelect==7)
        {

            al_draw_scaled_bitmap(sel,0,0,al_get_bitmap_width(sel),al_get_bitmap_height(sel),((width/9)*7)+width/40,(height/2)+height/15,width/7,height/5,0);
        }

        al_draw_scaled_bitmap(mage1,0,0,al_get_bitmap_width(mage1),al_get_bitmap_height(mage1),width/14,height/2,width/5,height/5,0);
        al_draw_scaled_bitmap(femMage1,0,0,al_get_bitmap_width(femMage1),al_get_bitmap_height(femMage1),(width/14)+(width/8),height/2,width/5,height/5,0);
        al_draw_scaled_bitmap(orc1,0,0,al_get_bitmap_width(orc1),al_get_bitmap_height(orc1),(width/9)*7,height/2,width/5,height/5,0);
        al_draw_scaled_bitmap(arch1,0,0,al_get_bitmap_width(arch1),al_get_bitmap_height(arch1),(width/9)*5,(height/3)*2,width/5,height/5,0);
        al_draw_scaled_bitmap(knight1,0,0,al_get_bitmap_width(knight1),al_get_bitmap_height(knight1),(width/7)*2,(height/2)+(height/5),width/5,height/5,0);
        al_draw_scaled_bitmap(femKnight1,0,0,al_get_bitmap_width(femKnight1),al_get_bitmap_height(femKnight1),((width/7)*2)-width/10,(height/2)+(height/5),width/5,height/5,0);
        al_draw_scaled_bitmap(femArch1,0,0,al_get_bitmap_width(femArch1),al_get_bitmap_height(femArch1),((width/9)*5)+width/10,(height/3)*2,width/5,height/5,0);
    }
    //Todos los dibujos del juego
    if(pantalla==GAME)
    {
        sprite = checkPersonaje();
            al_clear_to_color(al_map_rgb(0,0,0));
            if(final_boss_cont == 0)
            {
                for(i = 0; i<num_enemies; i++)
                {
                    al_draw_rectangle(enemies_pantalla[i].x_enem-50, enemies_pantalla[i].y_enem-50, enemies_pantalla[i].x_enem+120, enemies_pantalla[i].y_enem+120, al_map_rgb(255,255,255), 2);
                    al_draw_rectangle(enemies_pantalla[i].x_enem-5, enemies_pantalla[i].y_enem-5, enemies_pantalla[i].x_enem+70, enemies_pantalla[i].y_enem+80, al_map_rgb(255,255,255), 2);
                }
            }
            al_draw_rectangle(x-30, (height-131)+y-30, 105+x, (height-131)+y+105, al_map_rgb(255,255,255), 2);
            if(final_boss_cont == 0){
                al_draw_scaled_bitmap(paisaje,7+dx, 4800+dy, al_get_bitmap_width(paisaje), al_get_bitmap_height(paisaje),0, 0, 12.0*width, 9.0*height, 0);
            }
            else if(final_boss_cont == 1){
                al_draw_scaled_bitmap(dungeon_boss,0, 0, al_get_bitmap_width(dungeon_boss), al_get_bitmap_height(dungeon_boss),0, 0, width, height, 0);
            }
            if(final_boss_cont == 1)
            {
                al_draw_scaled_bitmap(boss, 0, 0, al_get_bitmap_width(boss), al_get_bitmap_height(boss), dragon.x_boss, dragon.y_boss, 400, 280, 0);
            }
            al_draw_scaled_bitmap(sprite, 0,0, al_get_bitmap_width(sprite), al_get_bitmap_height(sprite), x, (height-131)+y, 0.05*width, 0.1*height, 0);
            if((num_enemies != 0) && final_boss_cont == 0)
            {
                //printf("\nenter");
                generateEnemies(enemies_pantalla, num_enemies, enen, enemie);
                enem_generados = 1;
            }
            if(colision_dragon == 1)
            {
                al_draw_filled_rectangle((width/2)-width/9,0,(width/2)+width/9,height/15, al_color_html("#666666"));
                al_draw_text(itemsFont, al_color_html("#591cff"), width/2, 0, ALLEGRO_ALIGN_CENTER, "pulsa F para atacar");
            }
            if(colision == 1 )
            {
                al_draw_filled_rectangle((width/2)-width/9,0,(width/2)+width/9,height/15, al_color_html("#666666"));
                al_draw_text(itemsFont, al_color_html("#591cff"), width/2, 0, ALLEGRO_ALIGN_CENTER, "pulsa F para atacar");
            }
            if((dx+x >= 6880 && dx+x <= 7360 && dy+y <= -5160 && dy+y >= -5400)&& final_boss_cont == 0)
            {
                al_draw_filled_rectangle((width/2)-width/9,0,(width/2)+width/9,height/15, al_color_html("#666666"));
                al_draw_text(itemsFont, al_color_html("#591cff"), width/2, 0, ALLEGRO_ALIGN_CENTER, "Presiona E para entrar");
                cont_boss = 1;
            }
            else{
                cont_boss=0;
            }
            if(cont_anuncio == 1)
            {
                al_draw_text(nombre, al_map_rgb(0,255,0), 210, 70, ALLEGRO_ALIGN_CENTER, "Para entrar se requiere\n3000 de exp.");
            }
            if(final_boss_cont==1 && dragon.estado == 1)
            {
                mov_boss();
            }

            //al_draw_rectangle(dragon.x_boss-30, dragon.y_boss-30, dragon.x_boss+400, dragon.y_boss+330, al_map_rgb(255,255,255), 0);
            if(disp_flecha == 1 && arrows.life == 1)
            {
                if(character.personaje == WIZARD || character.personaje == FEMWIZARD)
                {
                    if(dir_arrow==4 && character.magia > 0)
                    {
                        al_draw_scaled_bitmap(magia_derecha, 0,0, al_get_bitmap_width(flecha_derecha), al_get_bitmap_height(flecha_derecha), arrows.arco_x+60, (height-108)+arrows.arco_y, (width*0.05), (height*0.05), 0);
                        arrows.arco_x+=30;
                        cont_arrow2 = checar_colision_flecha(cont_arrow2);
                        checar_limite_pantalla(55, 610, 130, 645);
                    }
                    if(dir_arrow == 1  && character.magia > 0)
                    {
                        al_draw_scaled_bitmap(magia_arriba, 0,0, al_get_bitmap_width(flecha_arriba), al_get_bitmap_height(flecha_arriba), arrows.arco_x+20, (height-200)+arrows.arco_y, (height*0.05), (width*0.05), 0);
                        arrows.arco_y-=30;
                        cont_arrow2 = checar_colision_flecha(cont_arrow2);
                        checar_limite_pantalla(20, 515, 50, 590);
                    }
                    if(dir_arrow == 2  && character.magia > 0)
                    {
                        al_draw_scaled_bitmap(magia_derecha, 0,0, al_get_bitmap_width(flecha_derecha), al_get_bitmap_height(flecha_derecha), arrows.arco_x-60, (height-108)+arrows.arco_y, (width*0.05), (height*0.05), ALLEGRO_FLIP_HORIZONTAL);                    arrows.arco_x-=30;
                        cont_arrow2 = checar_colision_flecha(cont_arrow2);
                        checar_limite_pantalla(-65, 610, 5, 645);
                    }
                    if(dir_arrow == 3  && character.magia > 0)
                    {
                        al_draw_scaled_bitmap(magia_arriba, 0,0, al_get_bitmap_width(flecha_arriba), al_get_bitmap_height(flecha_arriba), arrows.arco_x+30, (height-88)+arrows.arco_y, (height*0.05), (width*0.05), ALLEGRO_FLIP_VERTICAL);
                        arrows.arco_y+=30;
                        cont_arrow2 = checar_colision_flecha(cont_arrow2);
                        checar_limite_pantalla(30, 625, 70, 700);
                    }
                    if(character.magia<=0)
                    {
                        //printf("Magia insuficiente");
                    }
                    character.magia -= 0.01;
                }
                else
                {
                    if(dir_arrow==4)
                    {
                        al_draw_scaled_bitmap(flecha_derecha, 0,0, al_get_bitmap_width(flecha_derecha), al_get_bitmap_height(flecha_derecha), arrows.arco_x+60, (height-108)+arrows.arco_y, (width*0.05), (height*0.05), 0);
                        arrows.arco_x+=30;
                        cont_arrow2 = checar_colision_flecha(cont_arrow2);
                        checar_limite_pantalla(55, 610, 130, 645);
                    }
                    if(dir_arrow == 1)
                    {
                        al_draw_scaled_bitmap(flecha_arriba, 0,0, al_get_bitmap_width(flecha_arriba), al_get_bitmap_height(flecha_arriba), arrows.arco_x+20, (height-200)+arrows.arco_y, (height*0.05), (width*0.05), 0);
                        arrows.arco_y-=30;
                        cont_arrow2 = checar_colision_flecha(cont_arrow2);
                        checar_limite_pantalla(20, 515, 50, 590);
                    }
                    if(dir_arrow == 2)
                    {
                        al_draw_scaled_bitmap(flecha_derecha, 0,0, al_get_bitmap_width(flecha_derecha), al_get_bitmap_height(flecha_derecha), arrows.arco_x-60, (height-108)+arrows.arco_y, (width*0.05), (height*0.05), ALLEGRO_FLIP_HORIZONTAL);                    arrows.arco_x-=30;
                        cont_arrow2 = checar_colision_flecha(cont_arrow2);
                        checar_limite_pantalla(-65, 610, 5, 645);
                    }
                    if(dir_arrow == 3)
                    {
                        al_draw_scaled_bitmap(flecha_arriba, 0,0, al_get_bitmap_width(flecha_arriba), al_get_bitmap_height(flecha_arriba), arrows.arco_x+30, (height-88)+arrows.arco_y, (height*0.05), (width*0.05), ALLEGRO_FLIP_VERTICAL);
                        arrows.arco_y+=30;
                        cont_arrow2 = checar_colision_flecha(cont_arrow2);
                        checar_limite_pantalla(30, 625, 70, 700);
                    }
                     if(dragon.vida ==0)
                    {
                        pantalla = 8;
                    }
                }

            }
            HUD(nombre, paisaje);
            redraw=1;
            if(dragon.vida ==0)
            {
                pantalla = 8;
            }
    }
    //Pausa
    if(pause==1)
    {
        al_draw_scaled_bitmap(pausa,0,0,al_get_bitmap_width(pausa),al_get_bitmap_height(pausa),0,0,width,height,0);
        if(pauseSelected==1)
        {
            option1=al_color_html("#350b7d");
        }
        else
        {
            option1=al_color_html("#ffffff");
        }
        if(pauseSelected==2)
        {
            option2=al_color_html("#350b7d");
        }
        else
        {
            option2=al_color_html("#ffffff");
        }
        if(pauseSelected==3)
        {
            option3=al_color_html("#350b7d");
        }
        else
        {
            option3=al_color_html("#ffffff");
        }
        if(pauseSelected==4)
        {
            option4=al_color_html("#350b7d");
        }
        else
        {
            option4=al_color_html("#ffffff");
        }
        if(pauseSelected==5)
        {
            option5=al_color_html("#350b7d");
        }
        else
        {
            option5=al_color_html("#ffffff");
        }
        al_draw_filled_rectangle(rectangleX1,rectangleY1,rectangleX2,rectangleY2,al_color_html("#585759"));
        al_draw_filled_rectangle(rectangleX1,rectangleY3,rectangleX2,rectangleY4,al_color_html("#585759"));
        al_draw_filled_rectangle(rectangleX1,rectangleY5,rectangleX2,rectangleY6,al_color_html("#585759"));
        al_draw_filled_rectangle(rectangleX1,rectangleY7,rectangleX2, rectangleY8,al_color_html("#585759"));
        al_draw_filled_rectangle(rectangleX1,rectangleY9,rectangleX2,rectangleY10,al_color_html("#585759"));

        al_draw_rectangle(rectangleX1+(width/320),rectangleY1+(height/180),rectangleX2-(width/320),rectangleY2-(height/180), al_color_html("#49484a"),height/360);
        al_draw_rectangle(rectangleX1+(width/320),rectangleY3+(height/180),rectangleX2-(width/320),rectangleY4-(height/180), al_color_html("#49484a"),height/360);
        al_draw_rectangle(rectangleX1+(width/320),rectangleY5+(height/180),rectangleX2-(width/320),rectangleY6-(height/180), al_color_html("#49484a"),height/360);
        al_draw_rectangle(rectangleX1+(width/320),rectangleY7+(height/180),rectangleX2-(width/320),rectangleY8-(height/180), al_color_html("#49484a"),height/360);
        al_draw_rectangle(rectangleX1+(width/320),rectangleY9+(height/180),rectangleX2-(width/320),rectangleY10-(height/180), al_color_html("#49484a"),height/360);


        al_draw_text(menuFont,option1,width/2,(height/7)*2, ALLEGRO_ALIGN_CENTER, "Continuar");
        al_draw_text(menuFont,option2,width/2,(height/7)*3,ALLEGRO_ALIGN_CENTER, "Inventario");
        al_draw_text(menuFont,option3,width/2,(height/7)*4,ALLEGRO_ALIGN_CENTER, "Guardar");
        al_draw_text(menuFont,option4,width/2,(height/7)*5,ALLEGRO_ALIGN_CENTER, "Salir");
        al_draw_text(menuFont,option5,width/2,(height/7)*6,ALLEGRO_ALIGN_CENTER, "Instrucciones");

        redraw=1;
    }
    //In game options
    /*if(pantalla==8)
    {
        al_draw_scaled_bitmap(options,0,0,al_get_bitmap_width(options),al_get_bitmap_height(options),0,0,width,height,0);
        if(pauseSelected==1)
        {
            option1=al_color_html("#350b7d");
        }
        else
        {
            option1=al_color_html("#ffffff");
        }
        if(pauseSelected==2)
        {
            option2=al_color_html("#350b7d");
        }
        else
        {
            option2=al_color_html("#ffffff");
        }
        if(pauseSelected==3)
        {
            option3=al_color_html("#350b7d");
        }
        else
        {
            option3=al_color_html("#ffffff");
        }
        if(pauseSelected==4)
        {
            option4=al_color_html("#350b7d");
        }
        else
        {
            option4=al_color_html("#ffffff");
        }
        al_draw_filled_rectangle(((width/20)*11)-width/9,height/18,((width/20)*11)+width/9,(height/18)*2,al_color_html("#585759"));
        al_draw_filled_rectangle(((width/20)*12)-width/16,(height/6),((width/20)*12)+width/16,(height/6)+(height/18),al_color_html("#585759"));
        al_draw_filled_rectangle(((width/20)*16)-width/16,(height/6),((width/20)*16)+width/16,(height/6)+(height/18),al_color_html("#585759"));
        al_draw_filled_rectangle((width/2)-width/9,(height/2),(width/2)+width/9,(height/2)+(height/18),al_color_html("#585759"));
        al_draw_filled_rectangle((width/2)-width/9,(height/7)*6,(width/2)+width/9,((height/7)*6)+(height/18),al_color_html("#585759"));

        al_draw_rectangle((((width/20)*11)-width/9)+(width/320),(height/18)+(height/180),(((width/20)*11)+width/9)-(width/320),((height/18)*2)-(height/180), al_color_html("#49484a"),height/360);
        al_draw_rectangle((((width/20)*12)-width/16)+(width/320),(height/6)+(height/180),(((width/20)*12)+width/16)-(width/320),((height/6)+(height/18))-(height/180), al_color_html("#49484a"),height/360);
        al_draw_rectangle((((width/20)*16)-width/16)+(width/320),(height/6)+(height/180),(((width/20)*16)+width/16)-(width/320),((height/6)+(height/18))-(height/180), al_color_html("#49484a"),height/360);
        al_draw_rectangle(((width/2)-width/9)+width/320,(height/2)+height/180,((width/2)+width/9)-width/320,((height/2)+(height/18))-height/180, al_color_html("#49484a"),height/360);
        al_draw_rectangle(((width/2)-width/9)+width/320,((height/7)*6)+height/180,((width/2)+width/9)-width/320,(((height/7)*6)+(height/18))-height/180, al_color_html("#49484a"),height/360);


        al_draw_text(menuFont,al_color_html("#ffffff"),(width/20)*11,(height/20), ALLEGRO_ALIGN_CENTER, "Resolución");
        al_draw_text(indicationsFont,option1,(width/20)*12,(height/6),ALLEGRO_ALIGN_CENTER, "1280x720");
        al_draw_text(indicationsFont,option2,(width/20)*16,(height/6),ALLEGRO_ALIGN_CENTER, "1920x1080");
        al_draw_text(indicationsFont,option3,width/2,(height/2),ALLEGRO_ALIGN_CENTER, "Guardar");
        al_draw_text(indicationsFont,option4,width/2,(height/7)*6,ALLEGRO_ALIGN_CENTER, "Regresar");

        redraw=1;
    }*/
    if(pantalla == 7)
    {
        if(selectGO==1)
        {
            option1=al_color_html("#350b7d");
        }
        else
        {
            option1=al_color_html("#ffffff");
        }
        if(selectGO==2)
        {
            option2=al_color_html("#350b7d");
        }
        else
        {
            option2=al_color_html("#ffffff");
        }
        al_clear_to_color(al_map_rgb(230,38,19));
        al_draw_text(GO,al_map_rgb(0,0,0),width/2,50,ALLEGRO_ALIGN_CENTER, "GAME OVER");
        al_draw_text(menuFont,option1,width/2,height/2,ALLEGRO_ALIGN_CENTER, "Continuar");
        al_draw_text(menuFont,option2,width/2,height/2+30,ALLEGRO_ALIGN_CENTER, "Salir");
    }
    if(pantalla == 8)
    {
        if(selectGO==1)
        {
            option1=al_color_html("#350b7d");
        }
        else
        {
            option1=al_color_html("#ffffff");
        }
        if(selectGO==2)
        {
            option2=al_color_html("#350b7d");
        }
        else
        {
            option2=al_color_html("#ffffff");
        }
        al_clear_to_color(al_map_rgb(40,240, 140));
        al_draw_text(GO, al_map_rgb(0,0,0), width/2, height/2-60, ALLEGRO_ALIGN_CENTER, "!!  YOU WIN  ¡¡");
        al_draw_text(menuFont,option2,width/2,height/2+80,ALLEGRO_ALIGN_CENTER, "Salir");
    }
    //Inventario
    if(pantalla==9)
    {
        if(iSelect==1||iSelect==4||iSelect==7||iSelect==10)
        {
            sqX1=posX1;
            sqX2=posX2;
        }
        if(iSelect==2||iSelect==5||iSelect==8||iSelect==11)
        {
            sqX1=posX3;
            sqX2=posX4;
        }
        if(iSelect==3||iSelect==6||iSelect==9||iSelect==12)
        {
            sqX1=posX5;
            sqX2=posX6;
        }

        if(iSelect==1||iSelect==2||iSelect==3)
        {
            sqY1=posY1;
            sqY2=posY2;
        }
        if(iSelect==4||iSelect==5||iSelect==6)
        {
            sqY1=posY3;
            sqY2=posY4;
        }
        if(iSelect==7||iSelect==8||iSelect==9)
        {
            sqY1=posY5;
            sqY2=posY6;
        }
        if(iSelect==10||iSelect==11||iSelect==12)
        {
            sqY1=posY7;
            sqY2=posY8;
        }

        al_draw_scaled_bitmap(inventory,0,0,al_get_bitmap_width(inventory),al_get_bitmap_height(inventory),0,0,width,height,0);
        if(iSelect!=0)
        {
            al_draw_filled_rectangle(sqX1,sqY1,sqX2,sqY2,square);
        }

        if(selectedChar==WIZARD)
        {
            al_draw_scaled_bitmap(mage1,0,0,al_get_bitmap_width(mage1),al_get_bitmap_height(mage1),width/25,(height/9)*2,(al_get_bitmap_width(mage1))*1.35,(al_get_bitmap_height(mage1))*1.35,0);
        }
        if(selectedChar==FEMWIZARD)
        {
            al_draw_scaled_bitmap(femMage1,0,0,al_get_bitmap_width(femMage1),al_get_bitmap_height(femMage1),width/25,(height/9)*2,(al_get_bitmap_width(femMage1))*1.35,(al_get_bitmap_height(femMage1))*1.35,0);
        }
        if(selectedChar==ARCHER)
        {
            al_draw_scaled_bitmap(arch1,0,0,al_get_bitmap_width(arch1),al_get_bitmap_height(arch1),width/25,(height/9)*2,(al_get_bitmap_width(arch1))*1.35,(al_get_bitmap_height(arch1))*1.35,0);
        }
        if(selectedChar==FEMARCHER)
        {
            al_draw_scaled_bitmap(femArch1,0,0,al_get_bitmap_width(femArch1),al_get_bitmap_height(femArch1),width/25,(height/9)*2,(al_get_bitmap_width(femArch1))*1.35,(al_get_bitmap_height(femArch1))*1.35,0);
        }
        if(selectedChar==KNIGHT)
        {
            al_draw_scaled_bitmap(knight1,0,0,al_get_bitmap_width(knight1),al_get_bitmap_height(knight1),width/25,(height/9)*2,(al_get_bitmap_width(knight1))*1.35,(al_get_bitmap_height(knight1))*1.35,0);
        }
        if(selectedChar==FEMKNIGHT)
        {
            al_draw_scaled_bitmap(femKnight1,0,0,al_get_bitmap_width(femKnight1),al_get_bitmap_height(femKnight1),width/25,(height/9)*2,(al_get_bitmap_width(femKnight1))*1.35,(al_get_bitmap_height(femKnight1))*1.35,0);
        }
        if(selectedChar==ORC)
        {
            al_draw_scaled_bitmap(orc1,0,0,al_get_bitmap_width(orc1),al_get_bitmap_height(orc1),width/25,(height/9)*2,(al_get_bitmap_width(orc1))*1.35,(al_get_bitmap_height(orc1))*1.35,0);
        }
        redraw=1;
    }
}
int main ()
{
    int count=0;


    dx_org = dx;


    end=initialize();
    screen=al_create_display(width,height);
    al_set_window_title(screen, "Fennek");
    events=al_create_event_queue();
    al_register_event_source(events,al_get_display_event_source(screen));
    al_register_event_source(events,al_get_keyboard_event_source());
    al_register_event_source(events,al_get_timer_event_source(clouds));

    timer1 = al_create_timer(1.0/30.0);

    al_register_event_source(events, al_get_timer_event_source(timer1));
    al_register_event_source(events, al_get_keyboard_event_source());

    al_start_timer(timer1);

    al_start_timer(clouds);


    espada.ID=2;
    espada.ID=1.5;
    arco.ID = 1;
    arco.multiplier = 2;
    character.direccion = 4;
    character.vida = 10;
    character.damage = 0;
    character.magia = 10.0;
    dragon.x_boss = width/2;
    dragon.y_boss = height/3;
    dragon.vida = 1000.0;
    dragon.estado = 1;
    dragon.damage = 0.15;

    while(end!=1)
    {
        if(redraw==1&&al_event_queue_is_empty(events))
        {
            drawEvents();
            al_flip_display();
            redraw=0;
        }

        if(num_enemies == 0 || (dx_org+2560 <= dx+x || dx_org-2560 >= dx+x || dy_org+1440 <= dy+y || dy_org-1440 >= dy+y))
        {
            //printf("entro");
            num_enemies = rand()%6+1;
            enem_generados = 0;
            dx_org = dx+x;
            dy_org = dy+y;
        }
        if(character.vida-character.damage <= 0)
        {
            pantalla = 7;
        }
        /*if(dragon.vida ==0)
        {
            pantalla = 8;
        }*/

        al_wait_for_event(events,&event);

        selected=registerEvents(selected);
        if(event.type==ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            end=1;
            out=1;
        }
        if(event.type==ALLEGRO_EVENT_DISPLAY_SWITCH_IN)
        {
            redraw=1;
        }

    }
    al_destroy_event_queue(events);
    al_destroy_display(screen);
    al_destroy_sample(sword);
    return 0;
}
