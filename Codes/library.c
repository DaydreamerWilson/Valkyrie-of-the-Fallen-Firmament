#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <math.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#ifndef library
#define library

#define pi 3.1415926

typedef struct{
    int id, hp, sp, timer;
    double vx, vy, x, y, degree, prog;
}playerobject;

typedef struct{
    int id, eof, exist, t, v;
    double x, y, degree;
}turret;

typedef struct{
    int id, eof, exist, hp;
    double vx, vy, x, y, degree;
    turret turrets[10];
}ship;

typedef struct{
    int id, eof, exist;
    double vx, vy, x, y, degree;
}bullet;

typedef struct{
    char name[100];
    int x, y;
}nodetail;

typedef struct{
    char name[10];
    int type, h, w, nos, level, hp;
    char link[100];
    SDL_Texture *texture;
    nodetail spec[10];
}storage;

typedef struct{
    int x, y, page, id, action, h, w;
    char link[100];
    SDL_Texture *texture;
}button;

typedef struct{
    button buttons[50];
    int page, state, maxpage;
}menu;

typedef struct{
    SDL_Texture *texture;
    char link[100];
}map;

typedef struct{
    int shipno, turretno, projectileno;
}game;

typedef struct{
    int user[100], pass[100], temprank, highscore, levelofaccess;
}account;

typedef struct{
    int id, score, filter;
}ranker;

const UINT8 *receinput;
const int screenh=680;
const int screenw=800;

SDL_Event keyevent;

int key[512];
int mx, my;
int level;
int motion;
int running=TRUE;
int objectcount=0;
int keytimer=0;
int mousetimer=0;
int shiptimer=50;
int checker=TRUE;

float ftemp;
int counter1, counter2, counter3;
int username[100], password[100], input[100], temps[100], filter[100];
int currentname=0;
int currentpassword=0;
int currentinput=0;
int currentfilter=0;
int selection=1;
int accountnum=0;
int currentaccount=0;
int selectaccount=0;
int shipid, turretid, bulletid;
int shipno=0;
int turretno=0;
int projectileno=0;

storage store[10];
storage playersto;
storage shipsto[10];
storage turretsto[10];
storage projectsto[10];
ship ships[100];
playerobject players;
bullet bullets[5000];
game gamefile;
menu mainmenu;
map maps[20];
account accounts[1000];
ranker rankers[1000];
ranker tempranker;
SDL_Texture *charsprite;


#endif
