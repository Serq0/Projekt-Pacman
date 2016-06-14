/*
animacja pacmana
zdobywanie punktow + kropeczki
*/


#include <cstdlib>
#include <ctime>
#include <allegro.h>
#include <iomanip>
#include <cmath>
#include <math.h>

int mapa_x=760;
int mapa_y=550;
double player_speed=6;
int ghost_speed=3;
//int ludek_x = mapa_x/2;
//int ludek_y = mapa_y/2;
int zycie=3;
int punkty=0;
int levels=1;

int licznik=0; //timer pac-move
double dzwiek=0;
bool dzwieki=true;
int anim=0;
bool immune=false;
int immunetime=0;
bool ludek=false;


volatile long speed = 0;            //timery
void increment_speed()
{
    speed++;
}
END_OF_FUNCTION( increment_speed );     //timery
LOCK_VARIABLE( speed );
LOCK_FUNCTION( increment_speed );




void reset(int *punkty, int *zycie, double *player_speed)
{
    *punkty=0;
    *zycie=3;
    *player_speed=6;
}


int range(double x1,double x2,double y1,double y2)
{
    x1=x1+20;
    x2=x2+20;
    y1=y1+20;
    y2=y2+20;
    return ceil(sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1)));
}

int punkt(int w)
{
    return w+10;
}

struct swiece
{
    int x;
    int y;
};

struct player
{
    int x;
    int y;
    int old_x;
    int old_y;
};

struct blok
{
    int x;
    int y;
};

struct ghost
{
    int x;
    int y;
    int old_x;
    int old_y;
};

struct pktgold
{
    int x;
    int y;
    int licznik;
};


int main()
{

    allegro_init();
    install_keyboard();
    set_color_depth( 16 );
    set_gfx_mode( GFX_AUTODETECT, 800, 600, 0, 0 );

    install_timer();
    install_int_ex( increment_speed, BPS_TO_TIMER( 25 ) ); //operacji na sekunde

    install_sound( DIGI_AUTODETECT, MIDI_AUTODETECT, "" );
    set_volume( 255, 255 );

    srand( time( NULL ) );

    BITMAP * bufor = NULL;
    BITMAP * ludekdown1 = NULL;
    BITMAP * ludekdown2 = NULL;
    BITMAP * ludekright1 = NULL;
    BITMAP * ludekright2 = NULL;
    BITMAP * ludekup1 = NULL;
    BITMAP * ludekup2 = NULL;
    BITMAP * ludekleft1 = NULL;
    BITMAP * ludekleft2 = NULL;
    BITMAP * duszek = NULL;
    BITMAP * duszek2 = NULL;
    BITMAP * sciana = NULL;
    BITMAP * menupac = NULL;
    SAMPLE * pacman_beginning = NULL;
    SAMPLE * pacman_chomp = NULL;
    SAMPLE * pacman_death = NULL;
    BITMAP * poswiata = NULL;
    BITMAP * immuneimage = NULL;
    BITMAP * gold = NULL;
    ghost duch[4];
    pktgold golds[15];
    blok wall[66];
    swiece swieca[4];
    player gracz;
    bufor = create_bitmap( 800, 600 );
    int go[]={0,0,0,0};
    int actionx[]={0,0,0,0};
    int actiony[]={0,0,0,0};

    //######################################################################################
    swieca[0].x=mapa_x-15;
    swieca[0].y=mapa_y-15;
    swieca[1].x=15;
    swieca[1].y=15;
    swieca[2].x=mapa_x-15;
    swieca[2].y=15;
    swieca[3].x=15;
    swieca[3].y=mapa_y-15;

    wall[0].x=60;
    wall[0].y=60;
    wall[1].x=100;
    wall[1].y=60;
    wall[2].x=140;
    wall[2].y=60;
    wall[3].x=260;
    wall[3].y=60;
    wall[4].x=300;
    wall[4].y=60;
    wall[5].x=340;
    wall[5].y=60;
    wall[6].x=430;
    wall[6].y=60;
    wall[7].x=470;
    wall[7].y=60;
    wall[8].x=510;
    wall[8].y=60;
    wall[9].x=630;
    wall[9].y=60;
    wall[10].x=670;
    wall[10].y=60;
    wall[11].x=710;
    wall[11].y=60;
    wall[12].x=60;
    wall[12].y=150;
    wall[13].x=100;
    wall[13].y=150;
    wall[14].x=140;
    wall[14].y=150;
    wall[15].x=260;
    wall[15].y=150;
    wall[16].x=300;
    wall[16].y=150;
    wall[17].x=340;
    wall[17].y=150;
    wall[18].x=430;
    wall[18].y=150;
    wall[19].x=470;
    wall[19].y=150;
    wall[20].x=510;
    wall[20].y=150;
    wall[21].x=630;
    wall[21].y=150;
    wall[22].x=670;
    wall[22].y=150;
    wall[23].x=710;
    wall[23].y=150;
    wall[24].x=240; //rz 2
    wall[24].y=230;
    wall[25].x=280;
    wall[25].y=230;
    wall[26].x=320;
    wall[26].y=230;
    wall[27].x=240;
    wall[27].y=310;
    wall[28].x=280;
    wall[28].y=310;
    wall[29].x=320;
    wall[29].y=310;
    wall[30].x=440;
    wall[30].y=230;
    wall[31].x=480;
    wall[31].y=230;
    wall[32].x=520;
    wall[32].y=230;
    wall[33].x=440;
    wall[33].y=310;
    wall[34].x=480;
    wall[34].y=310;
    wall[35].x=520;
    wall[35].y=310;
    wall[36].x=60;
    wall[36].y=400;
    wall[37].x=100;
    wall[37].y=400;
    wall[38].x=140;
    wall[38].y=400;
    wall[39].x=260;
    wall[39].y=400;
    wall[40].x=300;
    wall[40].y=400;
    wall[41].x=340;
    wall[41].y=400;
    wall[42].x=430;
    wall[42].y=400;
    wall[43].x=470;
    wall[43].y=400;
    wall[44].x=510;
    wall[44].y=400;
    wall[45].x=630;
    wall[45].y=400;
    wall[46].x=670;
    wall[46].y=400;
    wall[47].x=710;
    wall[47].y=400;
    wall[48].x=60;
    wall[48].y=490;
    wall[49].x=100;
    wall[49].y=490;
    wall[50].x=140;
    wall[50].y=490;
    wall[51].x=260;
    wall[51].y=490;
    wall[52].x=300;
    wall[52].y=490;
    wall[53].x=340;
    wall[53].y=490;
    wall[54].x=430;
    wall[54].y=490;
    wall[55].x=470;
    wall[55].y=490;
    wall[56].x=510;
    wall[56].y=490;
    wall[57].x=630;
    wall[57].y=490;
    wall[58].x=670;
    wall[58].y=490;
    wall[59].x=710;
    wall[59].y=490;
    wall[60].x=100;
    wall[60].y=235;
    wall[61].x=100;
    wall[61].y=275;
    wall[62].x=100;
    wall[62].y=315;
    wall[63].x=660;
    wall[63].y=235;
    wall[64].x=660;
    wall[64].y=275;
    wall[65].x=660;
    wall[65].y=315;
 /*   wall[66].x=;
    wall[66].y=;
*/

//######################################################################################
    wybor:
    clear_to_color( screen, makecol( 0, 0, 0 ) );

    menupac = load_bmp( "menupac.bmp", default_palette );
    if( !menupac )
        {
        set_gfx_mode( GFX_TEXT, 0, 0, 0, 0 );
        allegro_message( "nie mogê za³adowaæ obrazka Ludek !" );
        allegro_exit();
        return 0;
    }

    blit( menupac, screen, 0, 0, 100, 0, menupac->w, menupac->h );

    //wyswietlanie menu
    textprintf( screen, font, 370, 50, makecol( 255, 255, 128 ), "PACMAN", 0 );
    textprintf( screen, font, 50, 400, makecol( 255, 255, 128 ), "Wcisnij F1 by rozpoczac", 0 );
    textprintf( screen, font, 50, 430, makecol( 255, 255, 128 ), "Wcisnij ESC by wyjsc", 0 );
    textprintf( screen, font, 50, 415, makecol( 255, 255, 128 ), "Wcisnij F4 by wylaczyc lub wlaczyc dzwieki", 0 );

    pacman_beginning = load_sample( "pacman_beginning.wav" );
    if( !pacman_beginning )
    {
        set_gfx_mode( GFX_TEXT, 0, 0, 0, 0 );
        allegro_message( "error pacman_beginning" );
        allegro_exit();
        return 0;
    }
        pacman_death = load_sample( "pacman_death.wav" );
    if( !pacman_death )
    {
        set_gfx_mode( GFX_TEXT, 0, 0, 0, 0 );
        allegro_message( "error pacman_death" );
        allegro_exit();
        return 0;
    }
        pacman_chomp = load_sample( "pacman_chomp.wav" );
    if( !pacman_chomp )
    {
        set_gfx_mode( GFX_TEXT, 0, 0, 0, 0 );
        allegro_message( "error pacman_chomp" );
        allegro_exit();
        return 0;
    }

    menuz:
    int q=readkey();
    switch(q)
    {
    case 12032:
        reset(&punkty, &zycie, &player_speed);
        levels=1;
        player_speed=player_speed-(0.2*levels);
        gracz.x=mapa_x/2;
        gracz.y=mapa_y/2;

        golds[0].licznik=15;

        duch[0].x=100;
        duch[0].y=100;
        duch[1].x=100;
        duch[1].y=mapa_y-100;
        duch[2].x=mapa_x-100;
        duch[2].y=100;
        duch[3].x=mapa_x-100;
        duch[3].y=mapa_y-100;

        for(int a=0;a<4;a++)
        {
            swieca[0].x=mapa_x-15;
            swieca[0].y=mapa_y-15;
            swieca[1].x=15;
            swieca[1].y=15;
            swieca[2].x=mapa_x-15;
            swieca[2].y=15;
            swieca[3].x=15;
            swieca[3].y=mapa_y-15;

            duch[a].old_x=duch[a].x;
            duch[a].old_y=duch[a].y;
            go[a]=0;
        }

        for(int a=0;a<15;a++)
        {
 //           re:
            golds[a].x=( rand() % 750 ) + 10;
            golds[a].y=( rand() % 540 ) + 10;
            for(int b=0;b<66;b++)
            {
                if(range(golds[a].x, wall[b].x, golds[a].y, wall[b].y)<40)
                   {
   //                  goto re;
                        a=a-1;
                   }
            }
            for(int ba=0;ba<a;ba++)
            {
                if(range(golds[a].x,golds[ba].x,golds[a].y,golds[ba].y)<120)
                {
                    a=a-1;
                }
            }
        }

        if(dzwieki==true)
        {
        play_sample( pacman_beginning, 255, 127, 1000, 0 );
        }
        break;
    case 15131:
        return 0;
    default:
        if( key[ KEY_F4 ] )
        {
            if(dzwieki==true)
            {
                dzwieki=false;
                goto menuz;
            }
        if(dzwieki==false)
            {
                dzwieki=true;
                play_sample( pacman_chomp, 255, 127, 1000, 0 );
                goto menuz;
            }
        }
        goto menuz;
    }

    destroy_bitmap( menupac );

    if( !bufor )
    {
        set_gfx_mode( GFX_TEXT, 0, 0, 0, 0 );
        allegro_message( "blad bufora" );
        allegro_exit();
        return 0;
    }
    sciana = load_bmp("sciana.bmp", default_palette);
    if (!sciana)
    {
        set_gfx_mode( GFX_TEXT, 0, 0, 0, 0 );
        allegro_message( "error sciana" );
        allegro_exit();
        return 0;
    }
    duszek = load_bmp("duszek.bmp", default_palette);
    if (!duszek)
    {
        set_gfx_mode( GFX_TEXT, 0, 0, 0, 0 );
        allegro_message( "error duszek" );
        allegro_exit();
        return 0;
    }
    duszek2 = load_bmp("duszek2.bmp", default_palette);
    if (!duszek2)
    {
        set_gfx_mode( GFX_TEXT, 0, 0, 0, 0 );
        allegro_message( "error duszek2" );
        allegro_exit();
        return 0;
    }
    ludekup1 = load_bmp( "ludekup1.bmp", default_palette );
    if( !ludekup1 )
    {
        set_gfx_mode( GFX_TEXT, 0, 0, 0, 0 );
        allegro_message( "error ludek" );
        allegro_exit();
        return 0;
    }
    ludekup2 = load_bmp( "ludekup2.bmp", default_palette );
    if( !ludekup2 )
    {
        set_gfx_mode( GFX_TEXT, 0, 0, 0, 0 );
        allegro_message( "error ludek" );
        allegro_exit();
        return 0;
    }
    ludekright1 = load_bmp( "ludekright1.bmp", default_palette );
    if( !ludekright1 )
    {
        set_gfx_mode( GFX_TEXT, 0, 0, 0, 0 );
        allegro_message( "error ludek" );
        allegro_exit();
        return 0;
    }
    ludekright2 = load_bmp( "ludekright2.bmp", default_palette );
    if( !ludekright2 )
    {
        set_gfx_mode( GFX_TEXT, 0, 0, 0, 0 );
        allegro_message( "error ludek" );
        allegro_exit();
        return 0;
    }
    ludekdown1 = load_bmp( "ludekdown1.bmp", default_palette );
    if( !ludekdown1 )
    {
        set_gfx_mode( GFX_TEXT, 0, 0, 0, 0 );
        allegro_message( "error ludek" );
        allegro_exit();
        return 0;
    }
    ludekdown2 = load_bmp( "ludekdown2.bmp", default_palette );
    if( !ludekdown2 )
    {
        set_gfx_mode( GFX_TEXT, 0, 0, 0, 0 );
        allegro_message( "error ludek" );
        allegro_exit();
        return 0;
    }
    ludekleft1 = load_bmp( "ludekleft1.bmp", default_palette );
    if( !ludekleft1 )
    {
        set_gfx_mode( GFX_TEXT, 0, 0, 0, 0 );
        allegro_message( "error ludek" );
        allegro_exit();
        return 0;
    }
    ludekleft2 = load_bmp( "ludekleft2.bmp", default_palette );
    if( !ludekleft2 )
    {
        set_gfx_mode( GFX_TEXT, 0, 0, 0, 0 );
        allegro_message( "error ludek" );
        allegro_exit();
        return 0;
    }
    poswiata = load_bmp( "poswiata.bmp", default_palette );
    if( !poswiata )
    {
        set_gfx_mode( GFX_TEXT, 0, 0, 0, 0 );
        allegro_message( "error poswiata" );
        allegro_exit();
        return 0;
    }
    immuneimage = load_bmp( "swieca.bmp", default_palette );
    if( !immuneimage )
    {
        set_gfx_mode( GFX_TEXT, 0, 0, 0, 0 );
        allegro_message( "error swieca" );
        allegro_exit();
        return 0;
    }
    gold = load_bmp( "gold.bmp", default_palette );
    if( !gold )
    {
        set_gfx_mode( GFX_TEXT, 0, 0, 0, 0 );
        allegro_message( "error gold" );
        allegro_exit();
        return 0;
    }




    rest(500);

    while( !key[ KEY_ESC ] ) //glowna petla gry
    {
        while( (speed > 0) )
    {
        //punkty=punkt(punkty); //testowe dodawanie punktow
        for(int a=0;a<4;a++) //obliczanie odleglosci gracza od duchow
        {
            if(range(gracz.x,swieca[a].x,gracz.y,swieca[a].y)<40)
            {
                immunetime=0;
                immune=true;
                swieca[a].x=1000;
                swieca[a].y=1000;
                player_speed=player_speed+1;
            }
            if(immune==true)
            {
                //nic nie rob
            }
            else
            if(range(duch[a].x,gracz.x,duch[a].y,gracz.y)<40)  //domyslnie 40
            {
                if(dzwieki)
                {
                    play_sample( pacman_death, 255, 127, 1000, 0 );
                }
                zycie--;
                gracz.x=mapa_x/2;
                gracz.y=mapa_y/2;
                duch[0].x=100;
                duch[0].y=100;
                duch[1].x=100;
                duch[1].y=mapa_y-100;
                duch[2].x=mapa_x-100;
                duch[2].y=100;
                duch[3].x=mapa_x-100;
                duch[3].y=mapa_y-100;
                rest(800);
            }
        }


        if(gracz.x <= 0)     //sprawdzanie czy gracz nie jest poza mapa
        {
            gracz.x=gracz.old_x;
        }
        if(gracz.y <= 0)
        {
            gracz.y=gracz.old_y;
        }
        if(gracz.x >=mapa_x)
        {
            gracz.x = gracz.old_x;
        }
        if(gracz.y >=mapa_y)
        {
            gracz.y = gracz.old_y;
        }

        for(int as=0;as<66;as++)
        {
            if(range(gracz.x,wall[as].x,gracz.y,wall[as].y)<35)
            {
                gracz.x=gracz.old_x;
                gracz.y=gracz.old_y;
            }
        }

        for(int as=0;as<15;as++)
        {
            if(range(gracz.x,golds[as].x,gracz.y,golds[as].y)<30)
            {
                punkty=punkt(punkty);
                golds[as].x=1000;
                golds[as].y=1000;
                golds[0].licznik=golds[0].licznik-1;
            }
        }
        if(golds[0].licznik<=0)
        {
            rest(800);

            levels++;
            player_speed=6-(0.2*levels);
            gracz.x=mapa_x/2;
            gracz.y=mapa_y/2;

            golds[0].licznik=15;

            duch[0].x=100;
            duch[0].y=100;
            duch[1].x=100;
            duch[1].y=mapa_y-100;
            duch[2].x=mapa_x-100;
            duch[2].y=100;
            duch[3].x=mapa_x-100;
            duch[3].y=mapa_y-100;

            for(int a=0;a<4;a++)
            {
                swieca[0].x=mapa_x-15;
                swieca[0].y=mapa_y-15;
                swieca[1].x=15;
                swieca[1].y=15;
                swieca[2].x=mapa_x-15;
                swieca[2].y=15;
                swieca[3].x=15;
                swieca[3].y=mapa_y-15;

                duch[a].old_x=duch[a].x;
                duch[a].old_y=duch[a].y;
                go[a]=0;
            }

            for(int a=0;a<15;a++)
            {

                golds[a].x=( rand() % 750 ) + 10;
                golds[a].y=( rand() % 540 ) + 10;
                for(int b=0;b<66;b++)
                {
                    if(range(golds[a].x, wall[b].x, golds[a].y, wall[b].y)<40)
                       {
                            a=a-1;
                       }
                }

                for(int ba=0;ba<a;ba++)
                {
                    if(range(golds[a].x,golds[ba].x,golds[a].y,golds[ba].y)<120)
                    {
                        a=a-1;
                    }
                }
            }
        }
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        dzwiek=gracz.x/2.98; // 760/255   x.mapa/prawy glosnik
        dzwiek=round(dzwiek);

        gracz.old_x=gracz.x;  //zapis pozycji gracza przed wykonywaniem ruchow
        gracz.old_y=gracz.y;


        if(gracz.x <= mapa_x && gracz.x >= 0 && gracz.y >= 0 && gracz.y <= mapa_y)  //poruszanie sie
        {
            if( key[ KEY_F3 ] ) goto wybor;

            if( key[ KEY_LEFT ] )
            {
                if(licznik%16==1)
                {
                    if(dzwieki)
                        play_sample( pacman_chomp, 155, dzwiek, 1000, 0 );
                }
                gracz.x=gracz.x-player_speed;
            }

            if( key[ KEY_RIGHT ] )
            {
                gracz.x=gracz.x+player_speed;
                if(licznik%16==1)
                {
                    if(dzwieki)
                        play_sample( pacman_chomp, 155, dzwiek, 1000, 0 );
                }
            }

            if( key[ KEY_UP ] )
            {
                gracz.y=gracz.y-player_speed;
                if(licznik%16==1)
                {
                    if(dzwieki)
                        play_sample( pacman_chomp, 155, dzwiek, 1000, 0 );
                }
            }

            if( key[ KEY_DOWN ] )
            {
                gracz.y=gracz.y+player_speed;
                if(licznik%16==1)
                {
                    if(dzwieki)
                        play_sample( pacman_chomp, 155, dzwiek, 1000, 0 );
                }
            }

            if( key[KEY_BACKSPACE]) //reset
            {

            }

        }

        clear_to_color( bufor, makecol( 100, 100, 100 ) );
    //  rest(10);



        for(int a=0;a<4;a++)  //poruszanie sie ducha
        {

            if((duch[a].x>0 && duch[a].x<mapa_x) and (duch[a].y>0 && duch[a].y<mapa_y) )
            {
                duch[a].x+=actionx[a];
                duch[a].y+=actiony[a];
                duch[a].x+=actionx[a];
                duch[a].y+=actiony[a];
            }

            if((duch[a].x <=0) or (duch[a].x >= mapa_x))
            {
                duch[a].x=duch[a].old_x;
                actionx[a]=0;
            }
            if((duch[a].y <=0) or (duch[a].y >= mapa_y))
            {
                duch[a].y=duch[a].old_y;
                actiony[a]=0;
            }

            for(int as=0;as<66;as++)
            {
                if(range(duch[a].x,wall[as].x,duch[a].y,wall[as].y)<35)
                {
                    duch[a].x=duch[a].old_x;
                    duch[a].y=duch[a].old_y;
                }
            }


            duch[a].old_x=duch[a].x;
            duch[a].old_y=duch[a].y;

                go[a]=( rand() % 5 ) + 1;
                switch(go[a])
                    {
                    case 1:
                        //duch[a].x+=ghost_speed;
                        actionx[a]=ghost_speed;
                        break;
                    case 2:
                        //duch[a].x-=ghost_speed;
                        actionx[a]=0-ghost_speed;
                        break;
                    case 3:
                        //duch[a].y+=ghost_speed;
                        actiony[a]=ghost_speed;
                        break;
                    case 4:
                        //duch[a].y-=ghost_speed;
                        actiony[a]=0-ghost_speed;
                        break;
                    case 5:
                        if(gracz.x<duch[a].x)
                        {
                            actionx[a]=0-ghost_speed;
                        }
                        else
                        {
                            actionx[a]=ghost_speed;
                        }
                        if(gracz.y<duch[a].y)
                        {
                            actiony[a]=0-ghost_speed;
                        }
                        else
                        {
                            actiony[a]=ghost_speed;
                        }
                    }

            if(anim<30)
            {
                masked_blit( duszek, bufor, 0, 0, duch[a].x, duch[a].y, duszek->w, duszek->h );
            }
            if(anim>=30)
            {
                masked_blit( duszek2, bufor, 0, 0, duch[a].x, duch[a].y, duszek->w, duszek->h );
            }
            if(anim>60)
            {
                anim=0;
            }


        }

        if(immune==true)
        {
            masked_blit( poswiata, bufor, 0, 0, gracz.x-6, gracz.y-7, poswiata->w, poswiata->h );
        }

        masked_blit( immuneimage, bufor, 0, 0, swieca[0].x, swieca[0].y, immuneimage->w, immuneimage->h);
        masked_blit( immuneimage, bufor, 0, 0, swieca[1].x, swieca[1].y, immuneimage->w, immuneimage->h);
        masked_blit( immuneimage, bufor, 0, 0, swieca[2].x, swieca[2].y, immuneimage->w, immuneimage->h);
        masked_blit( immuneimage, bufor, 0, 0, swieca[3].x, swieca[3].y, immuneimage->w, immuneimage->h);


        if(gracz.old_x<gracz.x) //animacja w prawo
        {

                if(ludek==true)
                {
                    masked_blit( ludekright1, bufor, 0, 0, gracz.x, gracz.y, ludekright1->w, ludekright1->h);
                }
                if(ludek==false)
                {
                    masked_blit( ludekright2, bufor, 0, 0, gracz.x, gracz.y, ludekright2->w, ludekright2->h);
                }
        }
        else if(gracz.old_x>gracz.x) //animacja w lewo
        {
            if(ludek==true)
                {
                    masked_blit( ludekleft1, bufor, 0, 0, gracz.x, gracz.y, ludekleft1->w, ludekleft1->h);
                }
                if(ludek==false)
                {
                    masked_blit( ludekleft2, bufor, 0, 0, gracz.x, gracz.y, ludekleft2->w, ludekleft2->h);
                }
        }
        else if(gracz.old_y>gracz.y) //animacja w gore
        {
            if(ludek==true)
                {
                    masked_blit( ludekup1, bufor, 0, 0, gracz.x, gracz.y, ludekup1->w, ludekup1->h);
                }
                if(ludek==false)
                {
                    masked_blit( ludekup2, bufor, 0, 0, gracz.x, gracz.y, ludekup2->w, ludekup2->h);
                }
        }
        else if(gracz.old_y<gracz.y)  //animacja w dol
        {
            if(ludek==true)
                {
                    masked_blit( ludekdown1, bufor, 0, 0, gracz.x, gracz.y, ludekdown1->w, ludekdown1->h);
                }
                if(ludek==false)
                {
                    masked_blit( ludekdown2, bufor, 0, 0, gracz.x, gracz.y, ludekdown2->w, ludekdown2->h);
                }
        }
        else if(gracz.old_y==gracz.y and gracz.old_x==gracz.x)
        {
            masked_blit( ludekright1, bufor, 0, 0, gracz.x, gracz.y, ludekright1->w, ludekright1->h);
        }


  //      masked_blit( ludekright1, bufor, 0, 0, gracz.x, gracz.y, ludekright1->w, ludekright1->h);

        for(int b=60; b<360;b=b+40)
        {
            if(b>160 and b<250)
            {
                b=b+40;
                continue;
            }
            masked_blit( sciana, bufor, 0, 0, b, 60, sciana->w, sciana->h);
            masked_blit( sciana, bufor, 0, 0, b+370, 60, sciana->w, sciana->h);
            masked_blit( sciana, bufor, 0, 0, b, 150, sciana->w, sciana->h);
            masked_blit( sciana, bufor, 0, 0, b+370, 150, sciana->w, sciana->h);

            masked_blit( sciana, bufor, 0, 0, b+180, mapa_y-240, sciana->w, sciana->h);
            masked_blit( sciana, bufor, 0, 0, b+180, mapa_y-320, sciana->w, sciana->h);


            masked_blit( sciana, bufor, 0, 0, b, mapa_y-150, sciana->w, sciana->h);
            masked_blit( sciana, bufor, 0, 0, b+370, mapa_y-150, sciana->w, sciana->h);
            masked_blit( sciana, bufor, 0, 0, b, mapa_y-60, sciana->w, sciana->h);
            masked_blit( sciana, bufor, 0, 0, b+370, mapa_y-60, sciana->w, sciana->h);


        }
        for(int b=140;b<260;b=b+40)
        {
            masked_blit( sciana, bufor, 0, 0, 100, b+95, sciana->w, sciana->h);
            masked_blit( sciana, bufor, 0, 0, mapa_x-100, b+95, sciana->w, sciana->h);
        }


        for(int ad=0;ad<15;ad++)
        {
            masked_blit( gold, bufor, 0, 0, golds[ad].x, golds[ad].y, gold->w, gold->h);
        }

        blit( bufor, screen, 0, 0, 0, 0, 800, 600 );

        textprintf( screen, font, 650, 20, makecol( 255, 255, 128 ), "Poziom : %d", levels );
        //textprintf( screen, font, 650, 35, makecol( 255, 255, 128 ), "Szybkosc : %d", 6-(0.2*levels) );
        textprintf( screen, font, 650, 35, makecol( 255, 255, 128 ), "Zycia : %d", zycie );
        textprintf( screen, font, 650, 50, makecol( 255, 255, 128 ), "Punkty : %d", punkty );
        if(zycie<=0)
        {
            textprintf( screen, font, 230 , mapa_y/2 , makecol( 255, 255, 128 ), "Koniec gry, wcisnij F3 by wejsc do menu.", -1 );
            player_speed=0;

        }

        if(immunetime>125)
        {
            immune=false;
            player_speed=6-(0.2*levels);
            if(zycie<=0)
            {
                player_speed=0;
            }
        }

        speed--;
        licznik++;
        anim++;
        immunetime++;

        if(licznik%8==1)
        {
            if(ludek==false)
            {
                ludek=true;
            }
            else
            {
                ludek=false;
            }
        }
    }
    }
    destroy_bitmap( sciana );
//    destroy_bitmap( ludek );
    destroy_bitmap( bufor );
    destroy_bitmap( duszek );
    allegro_exit();
    return 0;
}
END_OF_MAIN();
