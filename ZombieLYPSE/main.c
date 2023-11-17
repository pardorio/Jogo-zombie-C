#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <stdlib.h>
#include <time.h>


#include "main.h"


const int AKPENTE           = 4;
const int   largura         = 717;
const int   altura          = 664;
const float FPS             = 60.0;
const float FPSsprite       = 5.0;
int i,z;
int zcur=0;
int ZOMBIES1;
int tempo ;
bool recarregando=false;

bool keys[7]= {false,false,false,false,false,false,false};
enum KEYS {UP, DOWN, LEFT, RIGHT, SPACE, ESCAPE, E};

enum FASES {MENU,TUTORIAL,APOCALIPSE,YOU_LOSE};

int main(void)
{
    bool redraw = true;
    bool acaba = false;
    int fases = MENU;


    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *fila = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_TIMER *timersprite = NULL;

    ALLEGRO_BITMAP *overimg = NULL;
    ALLEGRO_BITMAP *tutorialimg = NULL;
    ALLEGRO_BITMAP *becoimg = NULL;
    ALLEGRO_BITMAP *menuimg = NULL;
    ALLEGRO_BITMAP *Akplayer      = NULL;
    ALLEGRO_BITMAP *Akplayer_esquerda = NULL;
    ALLEGRO_BITMAP *zombie_direita = NULL;
    ALLEGRO_BITMAP *zombie_esquerda = NULL;
    ALLEGRO_BITMAP *zombie_direita_tiro = NULL;
    ALLEGRO_BITMAP *zombie_esquerda_tiro = NULL;

    ALLEGRO_SAMPLE *menusom = NULL;
    ALLEGRO_SAMPLE_INSTANCE *menusom1 = NULL;

    ALLEGRO_SAMPLE *fim = NULL;
    ALLEGRO_SAMPLE_INSTANCE *fim1 = NULL;

    ALLEGRO_SAMPLE *dor = NULL;
    ALLEGRO_SAMPLE_INSTANCE *dor1 = NULL;

    ALLEGRO_SAMPLE *tiro = NULL;
    ALLEGRO_SAMPLE_INSTANCE *tiro1 = NULL;

    ALLEGRO_SAMPLE *somapocalipse = NULL;
    ALLEGRO_SAMPLE_INSTANCE *somapocalipse1 = NULL;

    ALLEGRO_SAMPLE *zombie = NULL;
    ALLEGRO_SAMPLE_INSTANCE *zombie2 = NULL;
    if(!al_init())

    {
        fprintf(stderr, "falhou ao inicializar o Allegro!\n");
        return -1;
    }


    display = al_create_display(largura,altura);

    if(!display)
    {
        fprintf(stderr, "falhou ao inicializar o Allegro!\n");
        return -1;
    }

    al_init_primitives_addon();
    al_install_keyboard();
    al_init_image_addon();

    al_init_font_addon();
    al_init_ttf_addon();

    al_init_acodec_addon();
    al_install_audio();

    ALLEGRO_FONT *fonte2 = al_load_font("img/INVASION2000.TTF", 30, 0);

    fila = al_create_event_queue();
    timer = al_create_timer(1.0/FPS);
    timersprite = al_create_timer(1.0/FPSsprite);


    overimg = al_load_bitmap("img/fimimg.png");
    tutorialimg = al_load_bitmap("img/tutorialimg.png");
    becoimg = al_load_bitmap("img/becoimg.png");
    menuimg = al_load_bitmap("img/menuimg.png");
    Akplayer = al_load_bitmap("img/player_ak1.png");
    Akplayer_esquerda = al_load_bitmap("img/player_ak_esquerda.png");
    zombie_direita = al_load_bitmap("img/zombie1.png");
    zombie_esquerda = al_load_bitmap("img/zombie_esquerda.png");
    zombie_direita_tiro = al_load_bitmap("img/player_ak_tiro.png");
    zombie_esquerda_tiro = al_load_bitmap("img/player_ak_esquerdatiro.png");

    al_reserve_samples(10);

    menusom = al_load_sample("img/menusom.ogg");
    tiro = al_load_sample("img/tiro.ogg");
    somapocalipse = al_load_sample("img/bgmusic.ogg");
    dor = al_load_sample("img/dor.ogg");
    fim= al_load_sample("img/fim.ogg");
    zombie= al_load_sample("img/zombie.ogg");

    menusom1 = al_create_sample_instance(menusom);

    al_attach_sample_instance_to_mixer(menusom1, al_get_default_mixer());
    al_set_sample_instance_gain(menusom1,0.4);

    tiro1 = al_create_sample_instance(tiro);

    al_attach_sample_instance_to_mixer(tiro1, al_get_default_mixer());
    al_set_sample_instance_gain(tiro1,0.4);

    somapocalipse1 = al_create_sample_instance(somapocalipse);

    al_set_sample_instance_playmode(somapocalipse1, ALLEGRO_PLAYMODE_LOOP);
    al_set_sample_instance_gain(somapocalipse1,0.3);
    al_attach_sample_instance_to_mixer(somapocalipse1, al_get_default_mixer());

    dor1 = al_create_sample_instance(dor);

    al_attach_sample_instance_to_mixer(dor1, al_get_default_mixer());
    al_set_sample_instance_gain(dor1,0.3);

    fim1 = al_create_sample_instance(fim);

    al_set_sample_instance_gain(fim1,0.5);
    al_attach_sample_instance_to_mixer(fim1, al_get_default_mixer());

    zombie2 = al_create_sample_instance(zombie);

    al_set_sample_instance_gain(zombie2,0.6);
    al_attach_sample_instance_to_mixer(zombie2, al_get_default_mixer());



    al_register_event_source(fila,al_get_keyboard_event_source());
    al_register_event_source(fila,al_get_display_event_source(display));
    al_register_event_source(fila, al_get_timer_event_source(timer));
    al_register_event_source(fila, al_get_timer_event_source(timersprite));

    al_start_timer(timersprite);
    al_start_timer(timer);
    srand(time(NULL));

    for(i = 0; i < AKPENTE; i++)
    {

        akbala[i].v = 3;
        akbala[i].ativo = false;
    }

    if(swat.pontos>=0)
    {
        ZOMBIES1=10;
    }
    if(swat.pontos>=200)
    {
        ZOMBIES1=20;
    }
    if(swat.pontos>=600)
    {
        ZOMBIES1=30;
    }
    if(swat.pontos>=1000)
    {
        ZOMBIES1=40;
    }
    for(z=0; z<ZOMBIES1; z++)
    {
        if(swat.pontos>=0)
        {
            zombie1[z].v = 1 + (rand() % 2) + (rand() % 10)/10;
        }
        if(swat.pontos>=200)
        {
            zombie1[z].v = 2 + (rand() % 2) + (rand() % 10)/10;
        }
        if(swat.pontos>=600)
        {
            zombie1[z].v = 3 + (rand() % 2) + (rand() % 10)/10;
        }
        if(swat.pontos>=1000)
        {
            zombie1[z].v = 4 + (rand() % 2) + (rand() % 10)/10;
        }
        zombie1[z].larg_x = 10;
        zombie1[z].alt_y = 15;
        if(swat.pontos<800)
        {
            zombie1[z].vidas = 100;
        }

        if(swat.pontos >= 600)
        {
            zombie1[z].vidas= 150;
        }
        if(swat.pontos >= 2000)
        {
            zombie1[z].vidas = 200;
        }
        zombie1[z].dir = 1;
        zombie1[z].cur=0;
        zombie1[z].dano=10;


    }



    while(!acaba)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(fila,&ev);


        if(ev.type == ALLEGRO_EVENT_TIMER)
        {

            redraw = true;
            if(!(keys[RIGHT])&&!(keys[LEFT])&&!(keys[UP])&&!(keys[DOWN]))
            {
                swat.cur=0;
            }



            if(swat.vidas>0)
            {
                swat.y -= keys[UP] *swat.vup;
                swat.x -= keys[LEFT] *swat.vleft;
                swat.y += keys[DOWN] *swat.vdown;
                swat.x += keys[RIGHT] *swat.vright;
            }
            if(swat.y < 130)
            {
                swat.y = 130;
            }
            if(swat.y > 620)
            {
                swat.y = 620;
            }
            if(swat.x < 28)
            {
                swat.x = 28;
            }
            if(swat.x > 540)
            {
                swat.x = 540;
            }



        }

        if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch(ev.keyboard.keycode)
            {
            case ALLEGRO_KEY_ESCAPE:
                keys[ESCAPE] = true;
                break;

            case ALLEGRO_KEY_UP:
                keys[UP] = true;
                break;

            case ALLEGRO_KEY_E:
                keys[E] = true;
                break;

            case ALLEGRO_KEY_DOWN:
                keys[DOWN] = true;
                break;

            case ALLEGRO_KEY_RIGHT:
                keys[RIGHT] = true;
                swat.dir= 0;

                break;

            case ALLEGRO_KEY_LEFT:
                keys[LEFT] = true;
                swat.dir= 1;
                break;

            case ALLEGRO_KEY_SPACE:

                keys[SPACE]=true;
                for(i=0; i<AKPENTE; i++)
                {





                    if((!akbala[i].ativo) && (akbala[i].dir==1))
                    {
                        swat.disp = 1;
                        if(fases==APOCALIPSE)
                        {
                            al_stop_sample_instance(tiro1);
                            al_play_sample_instance(tiro1);
                        }

                        akbala[i].x = swat.x + 17;
                        akbala[i].y = swat.y + 18;
                        akbala[i].ativo = true;


                        break;
                    }
                    if((!akbala[i].ativo) && (akbala[i].dir==0))
                    {
                        swat.disp = 1;
                        if(fases==APOCALIPSE)
                        {
                            al_stop_sample_instance(tiro1);
                            al_play_sample_instance(tiro1);
                        }

                        akbala[i].x = swat.x + 17;
                        akbala[i].y = swat.y + 18;
                        akbala[i].ativo = true;


                        break;
                    }


                }

            }
        }

        else if (ev.type == ALLEGRO_EVENT_KEY_UP)
        {
            switch(ev.keyboard.keycode)
            {

            case ALLEGRO_KEY_UP:
                keys[UP] = false;
                break;

            case ALLEGRO_KEY_ESCAPE:
                keys[ESCAPE] = false;
                break;

            case ALLEGRO_KEY_E:
                keys[E] = false;
                break;

            case ALLEGRO_KEY_DOWN:
                keys[DOWN] = false;
                break;

            case ALLEGRO_KEY_RIGHT:
                keys[RIGHT] = false;
                break;

            case ALLEGRO_KEY_LEFT:
                keys[LEFT] = false;
                break;

            case ALLEGRO_KEY_SPACE:
                keys[SPACE] = false;
                swat.disp = 0;
                break;



            }
        }
        else if(ev.timer.source==timersprite)
        {

            swat.cur += keys[DOWN];
            swat.cur += keys[UP];
            swat.cur+= keys[LEFT];
            swat.cur+= keys[RIGHT];

            if(swat.cur>=4)
            {
                swat.cur=0;
            }

            zcur += 1;
            if(zcur >= 4)
            {
                zcur=0;
            }


        }


//PARA PODER FECHAR O JOGO
        else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            acaba=true;
        }
//=============================GAME STATES=======================================================//
        else if(ev.type==ALLEGRO_EVENT_TIMER)
        {
            if(ev.timer.source==timer)
            {

                if(fases == MENU)
                {
                    if(keys[SPACE])
                    {
                        fases = TUTORIAL;
                    }
                    if(keys[ESCAPE])
                    {
                        acaba=true;
                    }


                    al_play_sample_instance(menusom1);
                    al_draw_bitmap(menuimg,0,0,0);

                }

                if(fases == TUTORIAL)
                {
                    if(keys[E])
                    {
                        fases = APOCALIPSE;
                    }
                    if(keys[ESCAPE])
                    {
                        acaba=true;
                    }

                    al_draw_bitmap(tutorialimg,0,0,0);
                }


                if(fases == APOCALIPSE)
                {

                    if(swat.vidas<=0)
                    {
                        fases = YOU_LOSE;
                    }
                    al_draw_bitmap(becoimg,0,0,0);
                    swat.invul+=1;
                    al_play_sample_instance(somapocalipse1);






                    if(keys[ESCAPE])
                    {
                        acaba=true;
                    }

                    if(swat.vidas>0)
                    {


                        for(i=0; i< AKPENTE; i++)
                        {
                            if(!akbala[i].ativo)
                            {
                                if(swat.dir==1)
                                {
                                    akbala[i].dir = 1;
                                }
                            }

                            if(!akbala[i].ativo)
                            {
                                if(swat.dir==0)
                                {
                                    akbala[i].dir = 0;
                                }
                            }

                            if((akbala[i].ativo) && (akbala[i].dir == 0))
                            {

                                akbala[i].x += akbala[i].v;

                                if(akbala[i].x > largura)
                                    akbala[i].ativo = false;
                            }

                            if((akbala[i].ativo) && (akbala[i].dir == 1))
                            {

                                akbala[i].x -= akbala[i].v;

                                if(akbala[i].x < 0)
                                    akbala[i].ativo = false;
                            }

                            if(akbala[i].ativo)
                            {
                                for(z=0; z<ZOMBIES1; z++)
                                {
                                    if(zombie1[z].vivo)
                                    {
                                        if(akbala[i].x < (zombie1[z].x + zombie1[z].larg_x) && akbala[i].x > (zombie1[z].x - zombie1[z].larg_x) &&
                                                akbala[i].y < (zombie1[z].y + zombie1[z].alt_y) && akbala[i].y > (zombie1[z].y - zombie1[z].alt_y))
                                        {

                                            zombie1[z].vidas -= swat.dano;
                                            akbala[i].ativo=false;




                                            al_stop_sample_instance(zombie2);
                                            al_play_sample_instance(zombie2);



                                            if(zombie1[z].vidas<=0)
                                            {
                                                swat.pontos += 10;

                                                zombie1[z].vivo=false;
                                            }
                                        }



                                    }

                                }

                            }


                        }

                        for(z=0; z<ZOMBIES1; z++)
                        {
                            if(!zombie1[z].vivo)
                            {
                                if(swat.pontos>=0)
                                {


                                    if(rand() % 400 == 0)
                                    {
                                        zombie1[z].vivo=true;
                                        zombie1[z].x = largura;
                                        zombie1[z].y = 270 + rand() % (altura - 600);
                                    }
                                }

                                if(swat.pontos>=200)
                                {

                                    if(rand() % 700 == 0)
                                    {
                                        zombie1[z].vivo=true;
                                        zombie1[z].x = 0;
                                        zombie1[z].y = 270 + rand() % (altura - 600);
                                        zombie1[z].dano =20;
                                    }

                                    if(rand() % 350 == 0)
                                    {
                                        zombie1[z].vivo=true;
                                        zombie1[z].x = largura;
                                        zombie1[z].y = 270 + rand() % (altura - 600);
                                        zombie1[z].dano =20;
                                    }
                                }

                                if(swat.pontos>=600)
                                {
                                    if(rand() % 600 == 0)
                                    {
                                        zombie1[z].vivo=true;
                                        zombie1[z].x = 0;
                                        zombie1[z].y = 270 + rand() % (altura - 600);
                                        zombie1[z].dano =20;
                                    }


                                    if(rand() % 300 == 0)
                                    {
                                        zombie1[z].vivo=true;
                                        zombie1[z].x = largura;
                                        zombie1[z].y = 270 + rand() % (altura - 600);
                                        zombie1[z].dano = 30;
                                    }
                                }
                                if(swat.pontos>=1000)
                                {
                                    if(rand() % 550 == 0)
                                    {
                                        zombie1[z].vivo=true;
                                        zombie1[z].x = 0;
                                        zombie1[z].y = 270 + rand() % (altura - 600);
                                        zombie1[z].dano =20;
                                    }


                                    if(rand() % 200 == 0)
                                    {
                                        zombie1[z].vivo=true;
                                        zombie1[z].x = largura;
                                        zombie1[z].y = 270 + rand() % (altura - 600);
                                        zombie1[z].dano = 40;
                                    }
                                }
                                if(swat.pontos>=2000)
                                {

                                    if(rand() % 400 == 0)
                                    {
                                        zombie1[z].vivo=true;
                                        zombie1[z].x = 0;
                                        zombie1[z].y = 270 + rand() % (altura - 600);
                                        zombie1[z].dano =20;
                                    }
                                    if(rand() % 150 == 0)
                                    {
                                        zombie1[z].vivo=true;
                                        zombie1[z].x = largura;
                                        zombie1[z].y = 270 + rand() % (altura - 600);
                                        zombie1[z].dano = 50;
                                    }
                                }






                            }



                        }
                        for(z=0; z<ZOMBIES1; ++z)
                        {
                            if(zombie1[z].vivo)
                            {

                                if (zombie1[z].x<swat.x +10)
                                {
                                    zombie1[z].dir = 0;
                                    zombie1[z].x += zombie1[z].v;

                                }
                                else
                                {
                                    zombie1[z].dir = 1;
                                    zombie1[z].x -= zombie1[z].v;
                                }
                                if (zombie1[z].y<swat.y + 10)
                                {

                                    zombie1[z].y += zombie1[z].v;

                                }
                                else
                                {

                                    zombie1[z].y -= zombie1[z].v;
                                }

                            }


                            if(zombie1[z].vivo)
                            {
                                if((swat.x + swat.larg_x) > (zombie1[z].x - zombie1[z].larg_x)&&(swat.x - swat.larg_x) < (zombie1[z].x + zombie1[z].larg_x) &&
                                        (swat.y + swat.alt_y) > (zombie1[z].y - zombie1[z].alt_y)&&(swat.y - swat.alt_y) < (zombie1[z].y + zombie1[z].alt_y))
                                {


                                    if(swat.invul>=60)
                                    {

                                        swat.vidas -= zombie1[z].dano;
                                        swat.invul=0;
                                        if(swat.vidas -=zombie1[z].dano)
                                        {

                                            al_stop_sample_instance(dor1);
                                            al_play_sample_instance(dor1);
                                        }

                                    }




                                }

                            }

                        }

                        if(swat.vidas>0)
                        {


                            for(i=0; i<AKPENTE; i++)
                            {

                                if(akbala[i].ativo)
                                {
                                    al_draw_filled_rectangle(akbala[i].x, akbala[i].y, akbala[i].x + 3,akbala[i].y +2, al_map_rgb(255, 255, 0));

                                }
                            }
                            for(z=0; z<ZOMBIES1; z++)
                            {
                                if(zombie1[z].vivo)
                                {
                                    if(zombie1[z].dir==1)
                                    {
                                        al_draw_bitmap_region(zombie_esquerda,32*zcur,0,32,28,zombie1[z].x,zombie1[z].y,0);
                                    }

                                    if(zombie1[z].dir==0)
                                    {
                                        al_draw_bitmap_region(zombie_direita,32*zcur,0,32,28,zombie1[z].x,zombie1[z].y,0);
                                    }
                                }



                            }







                            if(swat.disp==1)
                            {
                                if(swat.dir == 0)
                                {
                                    al_draw_bitmap_region(zombie_direita_tiro,32*swat.cur,0,30,32,swat.x,swat.y,0);
                                }
                                if(swat.dir == 1)
                                {
                                    al_draw_bitmap_region(zombie_esquerda_tiro,32*swat.cur,0,30,32,swat.x,swat.y,0);
                                }

                            }



                            if(swat.disp == 0)
                            {


                                if(swat.dir==0)
                                {
                                    al_draw_bitmap_region(Akplayer,32*swat.cur,0,30,32,swat.x,swat.y,0);

                                }
                                if(swat.dir==1)
                                {
                                    al_draw_bitmap_region(Akplayer_esquerda,32*swat.cur,0,30,32,swat.x,swat.y,0);
                                }

                            }


                        }
                        for(i=0; i<AKPENTE; i++)
                        {


                            if(akbala[i].ativo<=AKPENTE)
                            {
                                recarregando = true;
                                al_draw_textf(fonte2, al_map_rgb(100,100,100), largura - 700, 10, 0, "Recarregando...");

                            }
                            if(akbala[i].ativo)
                            {
                                recarregando = false;
                                al_draw_textf(fonte2, al_map_rgb(255,0,0), largura - 700, 10, 0, "Recarregando...");

                            }
                        }
                        if(swat.pontos >= 200 && swat.pontos <=300)
                        {
                            al_draw_textf(fonte2, al_map_rgb(255,0,50), 180,300, 0, "Nova onda de zumbis!");
                        }
                        if(swat.pontos >= 600 && swat.pontos<=700)
                        {
                            al_draw_textf(fonte2, al_map_rgb(255,0,70), 180,300, 0, "Nova onda de zumbis!");
                        }
                        if(swat.pontos >= 1000 && swat.pontos<=1100)
                        {
                            al_draw_textf(fonte2, al_map_rgb(180,0,100), 180,300, 0, "Nova onda de zumbis!");
                        }
                        if(swat.pontos >= 2000 && swat.pontos<=2100)
                        {
                            al_draw_textf(fonte2, al_map_rgb(180,0,120), 180,300, 0, "Nova onda de zumbis!");
                        }



                        al_draw_textf(fonte2, al_map_rgb(0,0,166), largura - 170, 10, 0, "Vidas:%i ", swat.vidas);

                        al_draw_textf(fonte2, al_map_rgb(255,255,0), largura - 700, 30, 0, "Score: %i", swat.pontos);





                    }

                }


                if(fases == YOU_LOSE)
                {

                    al_play_sample_instance(fim1);



                    if(keys[ESCAPE])
                    {
                        acaba=true;
                    }
                    al_stop_sample_instance(somapocalipse1);

                    for(z=0; z<ZOMBIES1; z++)
                    {
                        zombie1[z].vivo=false;
                    }

                    if(keys[SPACE])
                    {

                        swat.vidas=100;
                        swat.x=400;
                        swat.y=200;
                        swat.pontos=0;
                        for(z=0; z<ZOMBIES1; z++)
                        {
                            zombie1[z].vivo=false;
                            if(!zombie1[z].vivo)
                            {
                                if(swat.pontos>=0)
                                {


                                    if(rand() % 400 == 0)
                                    {
                                        zombie1[z].vivo=true;
                                        zombie1[z].x = largura;
                                        zombie1[z].y = 270 + rand() % (altura - 600);
                                    }
                                }

                                if(swat.pontos>=200)
                                {


                                    if(rand() % 300 == 0)
                                    {
                                        zombie1[z].vivo=true;
                                        zombie1[z].x = largura;
                                        zombie1[z].y = 270 + rand() % (altura - 600);
                                        zombie1[z].dano =20;
                                    }
                                }

                                if(swat.pontos>=600)
                                {


                                    if(rand() % 200 == 0)
                                    {
                                        zombie1[z].vivo=true;
                                        zombie1[z].x = largura;
                                        zombie1[z].y = 270 + rand() % (altura - 600);
                                        zombie1[z].dano = 30;
                                    }
                                }
                                if(swat.pontos>=1000)
                                {


                                    if(rand() % 100 == 0)
                                    {
                                        zombie1[z].vivo=true;
                                        zombie1[z].x = largura;
                                        zombie1[z].y = 270 + rand() % (altura - 600);
                                        zombie1[z].dano = 40;
                                    }
                                }
                                if(swat.pontos>=2000)
                                {


                                    if(rand() % 80 == 0)
                                    {
                                        zombie1[z].vivo=true;
                                        zombie1[z].x = largura;
                                        zombie1[z].y = 270 + rand() % (altura - 600);
                                        zombie1[z].dano = 50;
                                    }
                                }
                            }
                        }

                        fases=APOCALIPSE;


                    }
                    al_draw_bitmap(overimg,0,0,0);
                    al_draw_textf(fonte2, al_map_rgb(255,255,0), largura/2 -100, 20, 0, "Seu Score:%i ", swat.pontos);
                }




            }

        }


        if(redraw && al_is_event_queue_empty(fila))
        {
            redraw = false;

            //al_draw_textf(fonte2, al_map_rgb(0,0,166), 400, 300, 0, "Vidas:%i ", zombie1[z].vidas);
            //al_draw_textf(fonte2, al_map_rgb(255,255,0), largura/2 - 100, 20, 0, "Seu Score:%i ", swat.pontos);
            al_flip_display();
            al_clear_to_color(al_map_rgb(0,0,0));
        }
    }
     al_destroy_sample_instance  (zombie2);
     al_destroy_sample_instance  (menusom1);
     al_destroy_sample_instance  (tiro1);
     al_destroy_sample_instance  (somapocalipse1);
     al_destroy_sample_instance  (dor1);
     al_destroy_sample_instance  (fim1);

    al_destroy_sample           (zombie);
    al_destroy_sample           (menusom);
    al_destroy_sample           (tiro);
    al_destroy_sample           (fim);
    al_destroy_sample           (dor);
    al_destroy_sample           (somapocalipse);




    al_destroy_bitmap(overimg);
    al_destroy_bitmap(zombie_direita_tiro);
    al_destroy_bitmap(zombie_esquerda_tiro);
    al_destroy_bitmap(zombie_esquerda);
    al_destroy_bitmap(zombie_direita);
    al_destroy_bitmap(becoimg);
    al_destroy_bitmap(tutorialimg);
    al_destroy_bitmap(Akplayer_esquerda);
    al_destroy_bitmap(menuimg);
    al_destroy_bitmap(Akplayer);

    al_destroy_event_queue(timersprite);
    al_destroy_event_queue(fila);
    al_destroy_timer(timer);
    al_destroy_display(display);





    return 0;





}

//y=320 e x=542
//y=467 e x=505


