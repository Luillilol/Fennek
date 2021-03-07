    int fin = 0, redibujar = 1, i = 2, ran = 0, enem_generados = 0, colision=0, colision_dragon = 0, sonido1, cont_son_f=0, cont_damage=1,arrowx, arrowy, disp_flecha, cont_arrow2=1, cont_mov_boss=0, cont_iterate_boss=0;
    int velocidad = 10;

struct enemies
{
    float vida;
    int x_enem;
    int y_enem;
    float damage;
    int id_ataque;
    int id_flecha;
    int estado;
    int tipo;
};
struct enemies enemies_pantalla[10];

struct weapon
{
    float multiplier;
    int ID;
};
struct weapon arco;
struct weapon espada;

struct arrow
{
    int id;
    int life;
    int arco_x;
    int arco_y;
};
struct arrow arrows;

struct characters
{
    int personaje;
    int direccion;
    float vida, damage;
    float magia;
    float dano;
    int exp;
    int tipo;
};
struct characters character;


struct Boss
{
    int x_boss;
    int y_boss;
    float vida;
    float damage;
    int estado;
};
struct Boss dragon;

int chec_pers_golpe=0, dir_arrow;
float dx = 0.0, dy = 0.00;
float x=0 , y=0;


void numACadena(int numero, char numeros[])
{
  int i = 7, modulo;
  while(numero != 0)
  {
    modulo = numero%10;
    numero = numero/10;
    numeros[i-1] = modulo + '0';
    i--;
  }
}


int direccion_flecha()
{
    if(character.direccion == 4)
    {
        arrows.arco_x = x;
        arrows.arco_y = y;
        dir_arrow = 4;
    }
    if(character.direccion == 1)
    {
        arrows.arco_x = x;
        arrows.arco_y = y;
        dir_arrow = 1;
    }
    if(character.direccion == 2)
    {
        arrows.arco_x = x;
        arrows.arco_y = y;
        dir_arrow = 2;
    }
    if(character.direccion == 3)
    {
        arrows.arco_x = x;
        arrows.arco_y = y;
        dir_arrow = 3;
    }
    arrows.life = 1;
    return 0;
}

int checar_colision_damage(struct enemies enemies_pantalla[], int num_enemies)
{
    int i;
    for(i=0; i<num_enemies; i++)
    {
        if(enemies_pantalla[i].vida>0)
        {
            if(( x-15 < enemies_pantalla[i].x_enem+85 &&  x+105 > enemies_pantalla[i].x_enem && (height-131)+y-10 < enemies_pantalla[i].y_enem+100 && (height-131)+y+105 > enemies_pantalla[i].y_enem-10))
            {
                /*al_clear_to_color(al_map_rgb(255,0,0));
                al_flip_display();*/
                character.damage += enemies_pantalla[i].damage;
            }
        }
    }
    return 0;
}

int checar_limite_pantalla(int a, int b, int c, int d)
{
    //va a ser la x del arco            a                   b               c                   d
    //al_draw_rectangle(arrows.arco_x+55, arrows.arco_y+610, arrows.arco_x+130, arrows.arco_y+645, al_map_rgb(255,255,255), 2);

    if((arrows.arco_x+a < 0 || arrows.arco_x+c > 1280 || arrows.arco_y+b < 0 || arrows.arco_y+d > 720))
       {
            arrows.life =0;
            //printf("SI QUEDA");
       }

    return 0;
}

/*int checar_colision_flecha(int cont2)
{
     int i, x, y;
     //printf("\nPTM\n");
     for(i=0; i<num_enemies; i++)
     {
         if(enemies_pantalla[i].vida>0)
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
            //printf("\nPTM\n");
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
            else if (final_boss_cont == 1)
            {
                //printf("\nPTM\n");
                if((x+70 < dragon.x_boss+450 && x+135 > dragon.x_boss-30 && (height-131)+y+30 < dragon.y_boss+600 && (height-131)+y+55 > dragon.y_boss-50))
                {
                    //printf("\nFLECHA SIRVE\n");
                }
            }
        }
     }

    return cont2;
}*/

int colision_dragon_ataque()
{
    int cont = 0;
    if((x-15 < dragon.x_boss+450 && x+105 > dragon.x_boss-30 && (height-131)+y-10 < dragon.y_boss+600 && (height-131)+y+105 > dragon.y_boss-50))
    {
        al_draw_text(indicationsFont, al_map_rgb(255,0,0), width/2, 0, ALLEGRO_ALIGN_CENTER, "pulsa F para atacar");
        cont =1;
        //printf("\n\nSI\n\n");
    }
    al_draw_rectangle(x-30, (height-131)+y-30, 105+x, (height-131)+y+105, al_map_rgb(255,255,255), 2);
    return cont;
}

int checar_colision_ataque(struct enemies enemies_pantalla[], int num_enemies)
{
    int cont=0, i;
    for(i=0; i<num_enemies; i++)
    {
        if(enemies_pantalla[i].vida>0)
        {
            if(( x-15 < enemies_pantalla[i].x_enem+140 &&  x+105 > enemies_pantalla[i].x_enem-50 && (height-131)+y-10 < enemies_pantalla[i].y_enem+140 && (height-131)+y+105 > enemies_pantalla[i].y_enem-50))
            {
                enemies_pantalla[i].id_ataque= 1;
                cont=1;
            }
            else
            {
                enemies_pantalla[i].id_ataque = 0;
            }
        }
        else if(enemies_pantalla[i].estado == 0)
        {
            enemies_pantalla[i].estado =1;
        }
    }
        return cont;
}

int golpear(int colision, struct enemies enemies_pantalla[])
{
    int golpe=0, i;
    if(colision==1)
    {
        if(character.personaje == KNIGHT||character.personaje == FEMKNIGHT||character.personaje == ORC)
        {
            for(i=0; i<num_enemies; i++)
            {
                if(enemies_pantalla[i].id_ataque == 1)
                {
                    enemies_pantalla[i].vida -= 25;

                }
            }
        }
            //al_clear_to_color(al_map_rgb(255,0,0));
            //al_flip_display();

            golpe=1;
    }
    return golpe;
}

void checar_exp(int num_enemies)
{
    for(int i=0; i<num_enemies; i++)
    {
        if(enemies_pantalla[i].estado == 1)
        {
            enemies_pantalla[i].estado =2;
            character.exp +=50;
        }
    }
    //printf("EXP = %i", (character.exp)- num_enemies*50);
}



void logica_bot(struct enemies enemies_pantalla[], int longitud, ALLEGRO_BITMAP *enen, ALLEGRO_BITMAP *enemie)
{
    int i = 0;
    int velocidad = 2, cont_muertes = 0, cont_org = 0;
    if(pause==0)
    {
        for(i=0; i<longitud; i++)
        {
            if(enemies_pantalla[i].vida>0)
            {
                if(enemies_pantalla[i].x_enem < x)
                {
                    enemies_pantalla[i].x_enem += velocidad;
                }
                if(enemies_pantalla[i].x_enem > x)
                {
                    enemies_pantalla[i].x_enem -= velocidad;
                }

                if(enemies_pantalla[i].y_enem < (height-131)+y)
                {
                    enemies_pantalla[i].y_enem += velocidad;
                }
                if(enemies_pantalla[i].y_enem > (height-131)+y)
                {
                    enemies_pantalla[i].y_enem -= velocidad;
                }
                if(enemies_pantalla[i].tipo == 1)
                    al_draw_scaled_bitmap(enen, 0,0, al_get_bitmap_width(enen), al_get_bitmap_height(enen), enemies_pantalla[i].x_enem, enemies_pantalla[i].y_enem, 0.05*width, 0.1*height, 0);
                if(enemies_pantalla[i].tipo == 2)
                    al_draw_scaled_bitmap(enemie, 0,0, al_get_bitmap_width(enemie), al_get_bitmap_height(enemie), enemies_pantalla[i].x_enem, enemies_pantalla[i].y_enem, 0.05*width, 0.1*height, 0);
            }
            else
            {
                cont_muertes++;
                if(character.magia < 10 && (character.personaje == WIZARD || character.personaje == FEMWIZARD))
                    character.magia += 0.001;
                if(cont_muertes == num_enemies)
                {
                    num_enemies = 0;
                    for(int k=0; k<longitud; k++)
                    {
                        character.exp += rand()%21+30;
                    }
                }
            }
        }
    }
}

void generateEnemies(struct enemies enemies_pantalla[], int longitud, ALLEGRO_BITMAP *enen, ALLEGRO_BITMAP *enemie)
 {
    int i, spwnRatio;
    srand(time(NULL));
    if(enem_generados == 0)
    {
        for(i = 0; i<longitud; i++)
        {
            enemies_pantalla[i].x_enem = rand()%1281;
            enemies_pantalla[i].y_enem = rand()%721;
            enemies_pantalla[i].damage = .01;
            enemies_pantalla[i].vida = 100.0;
            spwnRatio = rand()%5+1;
            if(spwnRatio <= 4)
            {
                al_draw_scaled_bitmap(enen, 0,0, al_get_bitmap_width(enen), al_get_bitmap_height(enen), enemies_pantalla[i].x_enem, enemies_pantalla[i].y_enem, 0.05*width, 0.1*height, 0);
                enemies_pantalla[i].tipo = 1;
            }
            if(spwnRatio == 5)
            {
                al_draw_scaled_bitmap(enemie, 0,0, al_get_bitmap_width(enemie), al_get_bitmap_height(enemie), enemies_pantalla[i].x_enem, enemies_pantalla[i].y_enem, 0.05*width, 0.1*height, 0);
                enemies_pantalla[i].tipo = 2;
                enemies_pantalla[i].vida = 200.0;
                enemies_pantalla[i].damage = .05;
            }
            enemies_pantalla[i].estado = 0;
        }

    }
    else
    {
        logica_bot(enemies_pantalla,longitud, enen, enemie);
    }
}


void HUD(ALLEGRO_FONT *nombre, ALLEGRO_BITMAP *mapa)
{
    char expCad[8] = {'0','0','0','0','0','0','0','\0'};

    numACadena((character.exp), expCad);
    al_draw_text(nombre, al_map_rgb(17,128,232), 0, 0, ALLEGRO_ALIGN_LEFT, "XP");
    al_draw_text(nombre, al_map_rgb(17,128,232), 0+35, 0, ALLEGRO_ALIGN_LEFT, expCad);
    al_draw_rectangle(0,40,((float)character.vida*(float)10),50,al_map_rgb(255,255,255), 2);
    al_draw_filled_rectangle(0,40,(((float)character.vida-(float)character.damage)*(float)10),50, al_map_rgb(0,204,0));
    if(character.personaje==WIZARD||character.personaje==FEMWIZARD)
    {
        al_draw_rectangle(0,60,((float)character.vida*(float)10),70,al_map_rgb(255,255,255), 2);
        al_draw_filled_rectangle(0,60,(((float)character.magia)*(float)10),70, al_map_rgb(17,128,232));
    }
    al_draw_scaled_bitmap(mapa, 0,0,al_get_bitmap_width(mapa), al_get_bitmap_height(mapa),width-258, 0, .20*width, .275*height, 0);
    al_draw_rectangle(width-258,0,width,200,al_map_rgb(245,224,19),3);
    al_draw_filled_circle(width-259+((x+(dx*2.25))*.0165),200+(((dy*.7)+y)*.05),4,al_map_rgb(245,43,19));
    if(final_boss_cont==1)
    {
        al_draw_filled_rectangle(350,30,(((dragon.vida)/(float)2)+350),50, al_map_rgb(255,0,0));
        al_draw_rectangle(350,30,(((1000)/(float)2)+350),50, al_map_rgb(255,255,255), 0);

    }
    else
    {
        al_draw_scaled_bitmap(mapa, 0,0,al_get_bitmap_width(mapa), al_get_bitmap_height(mapa),width-258, 0, .20*width, .275*height, 0);
        al_draw_rectangle(width-258,0,width,200,al_map_rgb(245,224,19),3);
        al_draw_filled_circle(width-259+((x+(dx*2.25))*.0165),200+(((dy*.7)+y)*.05),4,al_map_rgb(245,43,19));}
}

void checkPantalla()
{
    int i;
    float Y1 = (height-131)+y;
    if(x<=5 && dx>0)
    {
        dx -= 20;
        x += 10;
        for(i=0; i<num_enemies; i++)
        {
            enemies_pantalla[i].x_enem+=10;
        }
    }
    if (x >= width-50 && dx < 6580)
    {
        dx += 20;
        x -= 10;
        for(i=0; i<num_enemies; i++)
        {
            enemies_pantalla[i].x_enem -=10;
        }
    }
    if(Y1<=5 && dy > -4820)
    {
        dy -= 20;
        y += 10;
        Y1 += 10;
        for(i=0; i<num_enemies; i++)
        {
            enemies_pantalla[i].y_enem += 10;
        }
    }
    if (Y1 >= height-70 && dy<0)
    {
        dy += 20;
        y -= 10;
        Y1 -= 10;
        for(i=0; i<num_enemies; i++)
        {
            enemies_pantalla[i].y_enem -= 10;
        }
    }
}

ALLEGRO_BITMAP* checkPersonaje()
{
    ALLEGRO_BITMAP *sprite;
    if(character.personaje == KNIGHT)
    {
        if(character.direccion == 1)
        {
            sprite = knight3;
        }
        if(character.direccion == 2)
        {
            sprite = knight1;
        }
        if(character.direccion == 3 || character.direccion == 4)
        {
            sprite = knight2;
        }
    }
    if(character.personaje == FEMKNIGHT)
    {
        if(character.direccion == 1)
        {
            sprite = femKnight3;
        }
        if(character.direccion == 2)
        {
            sprite = femKnight1;
        }
        if(character.direccion == 3 || character.direccion == 4)
        {
            sprite = femKnight2;
        }
    }
    if(character.personaje == ARCHER)
    {
        if(character.direccion == 1)
        {
            sprite = arch3;
        }
        if(character.direccion == 2)
        {
            sprite = arch1;
        }
        if(character.direccion == 3 || character.direccion == 4)
        {
            sprite = arch2;
        }
    }
    if(character.personaje == FEMARCHER)
    {
        if(character.direccion == 1)
        {
            sprite = femArch3;
        }
        if(character.direccion == 2)
        {
            sprite = femArch1;
        }
        if(character.direccion == 3 || character.direccion == 4)
        {
            sprite = femArch2;
        }
    }
    if(character.personaje == WIZARD)
    {
        if(character.direccion == 1)
        {
            sprite = mage3;
        }
        if(character.direccion == 2)
        {
            sprite = mage1;
        }
        if(character.direccion == 3 || character.direccion == 4)
        {
            sprite = mage2;
        }
    }
    if(character.personaje == FEMWIZARD)
    {
        if(character.direccion == 1)
        {
            sprite = femMage3;
        }
        if(character.direccion == 2)
        {
            sprite = femMage1;
        }
        if(character.direccion == 3 || character.direccion == 4)
        {
            sprite = femMage2;
        }
    }
    if(character.personaje == ORC)
    {
        if(character.direccion == 1)
        {
            sprite = orc3;
        }
        if(character.direccion == 2)
        {
            sprite = orc1;
        }
        if(character.direccion == 3 || character.direccion == 4)
        {
            sprite = orc2;
        }
    }
    return sprite;
}
