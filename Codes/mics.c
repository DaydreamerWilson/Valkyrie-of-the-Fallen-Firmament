#include "library.c"

#ifndef mics
#define mics

const int desiredfps = 60;

int current_t, frameps;
int runtime=0;
int needtime=0;
int delay=0;

time_t timex, timey, timez;

// 0 player
// 1 ship
// 2 turret
// 3 bullet

void createship(int x, int y, int level){
    int noid=0;
    int select;
    int ture;
    for(int n=0; n<100; n++){
        if(ships[n].exist==0){noid=n; break;}
    }

    //printf("[Checkpoint A]");

    int checker=FALSE;
    while(!checker){
        select=rand()%gamefile.shipno;
        if(shipsto[select].level<=level){ships[noid].id=select; checker=TRUE;}
    }

    //printf("[Checkpoint B]");

    ships[noid].exist=1;
    ships[noid].hp=shipsto[select].hp;
    ships[noid].eof=0;
    ships[noid].degree=180;

    //printf("[Checkpoint C]");

    for(int n=0; n<shipsto[select].nos; n++){
        ships[noid].turrets[n].exist=TRUE;
        for(int m=0; m<gamefile.turretno; m++){
            if(strcmp(turretsto[m].name, shipsto[select].spec[n].name)==0){ture=m;}
        }
        ships[noid].turrets[n].v=turretsto[ture].hp;
        ships[noid].turrets[n].id=ture;
        ships[noid].turrets[n].eof=1;
        ships[noid].turrets[n].t=turretsto[ture].level;
    }

    //printf("[Checkpoint D]");

    ships[noid].x=x;
    ships[noid].y=y;
    ships[noid].vy=rand()%3+5;

    if(ships[noid].x+shipsto[ships[noid].id].w>1900){
        ships[noid].x-=1900-ships[noid].x+shipsto[ships[noid].id].w;
    }
}

void createbullet(char name[100], int x, int y, int v, double degree){
    int noid=0;
    int selection=0;
    for(int n=0; n<5000; n++){
        if(bullets[n].exist==0){noid=n; break;}
    }
    for(int n=0; n<projectileno; n++){
        if(strcmp(name, projectsto[n].name)==0){selection=n; break;}
    }
    bullets[noid].exist=1;
    bullets[noid].id=selection;
    bullets[noid].eof=0;
    bullets[noid].x=x-projectsto[selection].w/2;
    bullets[noid].y=y-projectsto[selection].h/2;
    bullets[noid].degree=degree;
    bullets[noid].vx=v*sin(degree/180*pi);
    bullets[noid].vy=-v*cos(degree/180*pi);
    //printf("[Bullet Creating Succeed]");
}

void destroyships(int id){

}

int checkcontact(int x, int y, int x1, int y1, int h, int w){
    if(x>=x1 && x<=x1+w && y>=y1 && y<=y1+h){
        return 1;
    }
    else{return 0;}
}

int checkrange(int x, int x1, int x2){
    if(x>=x1 && x<=x2){return 1;}
    else{return 0;}
}

void frame(){
    runtime++;

    time(&timex);
    current_t = timex-timey;
    printf("%d ",timex-timey);

    if(timex>timez){
        time(&timez);
        frameps=runtime;
        runtime=0;
        if(frameps!=desiredfps){
            needtime=(1000/frameps)-delay;
            delay=(1000/desiredfps)-needtime;
        }
    }

    printf("Changing delay\n");
    if(delay<0){delay=0;}

    SDL_Delay(delay);

    printf("%d ", frameps);
    printf("%f ", delay);
}

#endif
