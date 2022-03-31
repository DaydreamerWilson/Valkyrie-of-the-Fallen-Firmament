#include "dataholder.c"
#include "library.c"
#include "mics.c"

#ifndef graphic
#define graphic

SDL_Rect imgrect;
SDL_Rect cutrect;

double bkgd1=0;
double bkgd2=-4000;
double disx;

float dx, dy, tempd, degree;
double gdd;

void RectSet(int x, int y, int h, int w){
    imgrect.x=x; imgrect.y=y; imgrect.h=h; imgrect.w=w;
}

void CutSet(int x, int y, int h, int w){
    cutrect.x=x; cutrect.y=y; cutrect.h=h; cutrect.w=w;
}

void DrawRect(int x, int y, int h, int w, int r, int g, int b, int a){
    RectSet(x, y, h, w);
    SDL_SetRenderDrawColor(render1, r, g, b, a);
    SDL_RenderFillRect(render1, &imgrect);
    SDL_SetRenderDrawColor(render1, 0, 0, 0, 255);
}

void DrawTexts(int x, int y, int h, int w, int itext[100], int limit){
    int x1, y1;
    for(counter=0; counter<limit; counter++){
        x1=itext[counter]%10*20;
        y1=itext[counter]/10*20;
        CutSet(x1, y1, 20, 20);
        RectSet(x, y, h, w);
        SDL_RenderCopy(render1, charsprite, &cutrect, &imgrect);
        x+=w;
    }
}

void TextsToSDL(int x, int y, int h, int w, char* ctext){
    printf("[%s]", ctext);
    int limit=strlen(ctext);
    int itext[100];
    for(counter=0; counter<limit; counter++){
        if(ctext[counter]>='1' && ctext[counter]<='9'){itext[counter]=ctext[counter]-19;}
        if(ctext[counter]=='0'){itext[counter]=39;}
        if(ctext[counter]>='a' && ctext[counter]<='z'){itext[counter]=ctext[counter]-93;}
        if(ctext[counter]==' '){itext[counter]=0;}
        if(ctext[counter]=='*'){itext[counter]=1;}
        if(ctext[counter]=='?'){itext[counter]=2;}
        if(ctext[counter]=='!'){itext[counter]=3;}
    }
    DrawTexts(x, y, h, w, itext, limit);
}


void IntToChar(int x, int y, int h, int w, int no){
    //printf("[Begin inttochar");
    char temp[16];
    sprintf(temp, "%d", no);
    //printf("[%s]", temp);
    char *passes=temp;
    //printf("[%s]]", passes);
    TextsToSDL(x, y, h, w, passes);
}

void gamerender(){
    printf("Started Rendering Game ");
    SDL_RenderClear(render1);

    if(players.x>1500){disx=players.x-1500+400;}
    else{
        if(players.x<400){disx=players.x;}
            else{disx=400;}
    }

    //background
    RectSet(disx-players.x, bkgd2, 4000, 1900);
    SDL_RenderCopy(render1, maps[3].texture, NULL, &imgrect);
    RectSet(disx-players.x, bkgd1, 4000, 1900);
    SDL_RenderCopy(render1, maps[3].texture, NULL, &imgrect);

    //ships
    for(int n=0; n<100; n++){
        if(ships[n].exist==1){
            shipid=ships[n].id;
            RectSet(ships[n].x-players.x+disx, ships[n].y, shipsto[shipid].h, shipsto[shipid].w);
            SDL_RenderCopyEx(render1, shipsto[shipid].texture, NULL, &imgrect, ships[n].degree, NULL, SDL_FLIP_NONE);
            for(int d=0; d<shipsto[shipid].nos; d++){
                turretid=ships[n].turrets[d].id;
                RectSet(ships[n].turrets[d].x-players.x+disx, ships[n].turrets[d].y, turretsto[turretid].h, turretsto[turretid].w);
                SDL_RenderCopyEx(render1, turretsto[turretid].texture, NULL, &imgrect, ships[n].turrets[d].degree, NULL, SDL_FLIP_NONE);
            }
        }
    }
    //turrets

    SDL_SetRenderDrawColor(render1, 255, 0, 0, 0);
    for(int n=0; n<100; n++){
        if(ships[n].exist==1){
            shipid=ships[n].id;
            dx=-(ships[n].x+shipsto[shipid].w/2)+(players.x+playersto.w/2);
            dy=(ships[n].y+shipsto[shipid].h/2)-(players.y+playersto.h/2);

            tempd=sqrt(dx*dx+dy*dy);

            if(tempd<5000){
                degree=atan(dy/dx)*180/pi-90;
                if(dx<0){degree+=180;}
                gdd=degree/180*pi;
                SDL_RenderDrawLine(render1, disx+playersto.w/2+20*sin(gdd), players.y+playersto.h/2+20*cos(gdd), disx+playersto.w/2+50*sin(gdd), players.y+playersto.h/2+50*cos(gdd));
            }
        }
    }
    //Marker

    RectSet(disx, players.y, playersto.h, playersto.w);
    CutSet(64*motion, 0, 64, 64);
    if(players.timer==0){
        SDL_RenderCopy(render1, playersto.texture, &cutrect, &imgrect);
    }
    else{if((players.timer%10)!=0){SDL_RenderCopy(render1, playersto.texture, &cutrect, &imgrect);}}
    //player

    for(int n=0; n<5000; n++){
        if(bullets[n].exist==1){
            bulletid=bullets[n].id;
            RectSet(bullets[n].x-players.x+disx, bullets[n].y, projectsto[bulletid].h, projectsto[bulletid].w);
            SDL_RenderCopyEx(render1, projectsto[bulletid].texture, NULL, &imgrect, bullets[n].degree, NULL, SDL_FLIP_NONE);
        }
    }
    //projectiles

    //UI
    RectSet(0, 0, 680, 800);
    SDL_RenderCopy(render1, maps[2].texture, NULL, &imgrect);
    if(players.hp>0){
        for(int n=0; n<players.hp; n++){
            RectSet(100+(n*30), 20, 20, 20);
            CutSet(0, 0, 64, 64);
            if(players.timer==0){
                SDL_RenderCopy(render1, playersto.texture, &cutrect, &imgrect);
            }
            else{if((players.timer%10)!=0){SDL_RenderCopy(render1, playersto.texture, &cutrect, &imgrect);}}
        }
    }

    if(level<=10){
        TextsToSDL(520, 60, 20, 20, "level");
        IntToChar(630, 50, 40, 40, level);
    }
    else{
        TextsToSDL(520,40, 60, 60, "hell");
    }

    IntToChar(50, 60, 20, 20, (int)players.prog/100*100);

    if(players.prog<1000){
        TextsToSDL(50, 70, 40, 20, "this is your hp bar");
        TextsToSDL(200, 200, 40, 20, "use your arrow key to move");
    }

    if(players.prog>1000 && players.prog<1500){
        TextsToSDL(200, 200, 40, 20, "good luck");
    }

    if(players.prog>1000000 && players.prog<1000500){
        TextsToSDL(200, 200, 40, 20, "warning warning warning");
    }

    SDL_RenderPresent(render1);
    printf("Finished Rendering Game ");
}

void fronterrend(){
    SDL_RenderClear(render1);
    //
    RectSet(60, 0, 680, 680);
    SDL_RenderCopy(render1, maps[0].texture, NULL, &imgrect);

    for(counter=0; counter<nobutt; counter++){
        if(mainmenu.buttons[counter].page==mainmenu.state)
        {
            RectSet(mainmenu.buttons[counter].x, mainmenu.buttons[counter].y,
                         mainmenu.buttons[counter].h, mainmenu.buttons[counter].w);
            SDL_RenderCopy(render1, mainmenu.buttons[counter].texture, NULL, &imgrect);
        }
    }
    //
    SDL_RenderPresent(render1);
}

void loginerrend(){
    SDL_RenderClear(render1);
    //
    RectSet(60, 0, 680, 680);
    SDL_RenderCopy(render1, maps[0].texture, NULL, &imgrect);

    DrawRect(0, 180, 200, 800, 0, 255, 255, 0);
    DrawRect(80, 300, 60, 640, 255, 255, 255, 0);

    DrawRect(0, 380, 100, 800, 0, 255, 255, 0);
    DrawRect(80, 400, 60, 640, 255, 255, 255, 0);

    TextsToSDL(80, 220, 40, 20, "login");
    TextsToSDL(80, 280, 20, 10, "username");
    TextsToSDL(80, 380, 20, 10, "password");
    DrawTexts(80, 310, 40, 20, username, currentname);
    DrawTexts(80, 410, 40, 20, password, currentpassword);

    if(selection>0){DrawRect(55, 200+selection*100, 60, 20, 255, 0, 0, 0);}

    for(counter=0; counter<nobutt; counter++){
        if(mainmenu.buttons[counter].page==mainmenu.state)
        {
            RectSet(mainmenu.buttons[counter].x, mainmenu.buttons[counter].y,
                         mainmenu.buttons[counter].h, mainmenu.buttons[counter].w);
            SDL_RenderCopy(render1, mainmenu.buttons[counter].texture, NULL, &imgrect);
        }
    }
    //
    SDL_RenderPresent(render1);
}

void registrend(){
    SDL_RenderClear(render1);
    //
    RectSet(60, 0, 680, 680);
    SDL_RenderCopy(render1, maps[0].texture, NULL, &imgrect);

    DrawRect(0, 180, 200, 800, 50, 150, 255, 0);
    DrawRect(80, 300, 60, 640, 255, 255, 255, 0);

    DrawRect(0, 380, 100, 800, 50, 150, 255, 0);
    DrawRect(80, 400, 60, 640, 255, 255, 255, 0);

    TextsToSDL(80, 220, 40, 20, "register");
    TextsToSDL(80, 280, 20, 10, "username");
    TextsToSDL(80, 380, 20, 10, "password");
    DrawTexts(80, 310, 40, 20, username, currentname);
    DrawTexts(80, 410, 40, 20, password, currentpassword);

    if(selection>0){DrawRect(55, 200+selection*100, 60, 20, 255, 0, 0, 0);}

    for(counter=0; counter<nobutt; counter++){
        if(mainmenu.buttons[counter].page==mainmenu.state)
        {
            RectSet(mainmenu.buttons[counter].x, mainmenu.buttons[counter].y,
                         mainmenu.buttons[counter].h, mainmenu.buttons[counter].w);
            SDL_RenderCopy(render1, mainmenu.buttons[counter].texture, NULL, &imgrect);
        }
    }
    //
    SDL_RenderPresent(render1);
}

void menuerrend(){
    SDL_RenderClear(render1);
    //
    RectSet(60, 0, 680, 680);
    SDL_RenderCopy(render1, maps[1].texture, NULL, &imgrect);

    for(counter=0; counter<nobutt; counter++){
        if(mainmenu.buttons[counter].page==mainmenu.state)
        {
            RectSet(mainmenu.buttons[counter].x, mainmenu.buttons[counter].y,
                         mainmenu.buttons[counter].h, mainmenu.buttons[counter].w);
            SDL_RenderCopy(render1, mainmenu.buttons[counter].texture, NULL, &imgrect);
        }
    }
    //
    SDL_RenderPresent(render1);
}

void gamemenurender(){
    SDL_RenderClear(render1);
    //
    RectSet(60, 0, 680, 680);
    SDL_RenderCopy(render1, maps[1].texture, NULL, &imgrect);

    TextsToSDL(150, 135, 20, 20, "bullet hell");

    for(counter=0; counter<nobutt; counter++){
        if(mainmenu.buttons[counter].page==mainmenu.state)
        {
            RectSet(mainmenu.buttons[counter].x, mainmenu.buttons[counter].y,
                         mainmenu.buttons[counter].h, mainmenu.buttons[counter].w);
            SDL_RenderCopy(render1, mainmenu.buttons[counter].texture, NULL, &imgrect);
        }
    }
    //
    SDL_RenderPresent(render1);
}

void resultrend(){
    SDL_RenderClear(render1);
    //
    int temp, y, len;
    RectSet(60, 0, 680, 680);
    SDL_RenderCopy(render1, maps[1].texture, NULL, &imgrect);

    DrawRect(60+50, 30, 20, 580, 255, 150, 150, 0);
    TextsToSDL(60+50, 150, 20, 20, "you were defeated...");

    DrawTexts(60+50, 200, 40, 20, accounts[currentaccount].user, currentname);
    IntToChar(60+460, 200, 40, 20, players.prog);

    if(accounts[currentaccount].highscore==(int)players.prog){
        TextsToSDL(60+350,260, 40, 20, "new highscore!");
    }

    for(counter=0; counter<nobutt; counter++){
        if(mainmenu.buttons[counter].page==mainmenu.state)
        {
            RectSet(mainmenu.buttons[counter].x, mainmenu.buttons[counter].y,
                         mainmenu.buttons[counter].h, mainmenu.buttons[counter].w);
            SDL_RenderCopy(render1, mainmenu.buttons[counter].texture, NULL, &imgrect);
        }
    }

    SDL_RenderPresent(render1);
}

void settinglistrend(){
    SDL_RenderClear(render1);
    //
    int temp, y, len;

    DrawRect(60+50, 30, 20, 580, 255, 0, 0, 0);
    DrawRect(60+50, 50, 560, 580, 255, 255, 255, 0);
    DrawRect(380, 10, 60, 320, 220, 220, 220, 0);

    DrawTexts(380, 20, 40, 20, input, currentinput);

    TextsToSDL(60+50, 30, 20, 20, "admin setting");
    IntToChar(60+50, 90, 40, 20, 1+accounts[currentaccount].temprank);
    DrawTexts(60+100, 90, 40, 20, accounts[currentaccount].user, currentname);
    IntToChar(60+460, 90, 40, 20, accounts[currentaccount].highscore);

    DrawRect(60+50, 130, 10, 580, 255, 0, 0, 0);

    y=10;
    if(mainmenu.page==mainmenu.maxpage){
        y=currentfilter-mainmenu.maxpage*10;
    }

    printf("[filter=%d] [y=%d] [page=%d]", currentfilter, y, mainmenu.page);

    counter1=0;

    for(int x=0; x<y; x++){
        //if(rankers[x+mainmenu.page*10].filter==TRUE){
        //printf("[Drawing Rank %d]", x+mainmenu.page*10);
        temp=40*x;
        //printf("%s", accounts[rankers[x+mainmenu.page*10].id].user);
        len=strlen(accounts[filter[x+mainmenu.page*10]].user);
        IntToChar(60+50, 140+temp, 40, 20, 1+x+mainmenu.page*10);
        DrawTexts(60+100, 140+temp, 40, 20, accounts[filter[x+mainmenu.page*10]].user, 6);
        IntToChar(60+460, 140+temp, 40, 20, accounts[filter[x+mainmenu.page*10]].highscore);
        //}
    }

    for(counter=0; counter<nobutt; counter++){
        if(mainmenu.buttons[counter].page==mainmenu.state)
        {
            RectSet(mainmenu.buttons[counter].x, mainmenu.buttons[counter].y,
                         mainmenu.buttons[counter].h, mainmenu.buttons[counter].w);
            SDL_RenderCopy(render1, mainmenu.buttons[counter].texture, NULL, &imgrect);
        }
    }
    //
    SDL_RenderPresent(render1);
}

void leaderrend(){
    SDL_RenderClear(render1);
    //
    int temp, y, len;
    RectSet(60, 0, 680, 680);
    SDL_RenderCopy(render1, maps[1].texture, NULL, &imgrect);

    DrawRect(60+50, 30, 20, 580, 255, 150, 150, 0);
    DrawRect(60+50, 50, 560, 580, 220, 220, 220, 0);
    DrawRect(380, 10, 60, 320, 255, 255, 255, 0);

    DrawTexts(380, 20, 40, 20, input, currentinput);

    TextsToSDL(60+50, 30, 20, 20, "leaderboard");
    IntToChar(60+50, 90, 40, 20, 1+accounts[currentaccount].temprank);
    DrawTexts(60+100, 90, 40, 20, accounts[currentaccount].user, currentname);
    IntToChar(60+460, 90, 40, 20, accounts[currentaccount].highscore);

    DrawRect(60+50, 130, 10, 580, 255, 255, 0, 0);

    y=10;
    if(mainmenu.page==mainmenu.maxpage){
        y=currentfilter-mainmenu.maxpage*10;
    }

    printf("[filter=%d] [y=%d] [page=%d]", currentfilter, y, mainmenu.page);

    counter1=0;

    for(int x=0; x<y; x++){
        //if(rankers[x+mainmenu.page*10].filter==TRUE){
        //printf("[Drawing Rank %d]", x+mainmenu.page*10);
        temp=40*x;
        //printf("%s", accounts[rankers[x+mainmenu.page*10].id].user);
        len=strlen(accounts[filter[x+mainmenu.page*10]].user);
        IntToChar(60+50, 140+temp, 40, 20, 1+x+mainmenu.page*10);
        DrawTexts(60+100, 140+temp, 40, 20, accounts[filter[x+mainmenu.page*10]].user, 6);
        IntToChar(60+460, 140+temp, 40, 20, accounts[filter[x+mainmenu.page*10]].highscore);
        //}
    }

    for(counter=0; counter<nobutt; counter++){
        if(mainmenu.buttons[counter].page==mainmenu.state)
        {
            RectSet(mainmenu.buttons[counter].x, mainmenu.buttons[counter].y,
                         mainmenu.buttons[counter].h, mainmenu.buttons[counter].w);
            SDL_RenderCopy(render1, mainmenu.buttons[counter].texture, NULL, &imgrect);
        }
    }
    //
    SDL_RenderPresent(render1);
}

void settingrend(){
    SDL_RenderClear(render1);
    //
    RectSet(60, 0, 680, 680);
    SDL_RenderCopy(render1, maps[1].texture, NULL, &imgrect);

    for(counter=0; counter<nobutt; counter++){
        if(mainmenu.buttons[counter].page==mainmenu.state)
        {
            RectSet(mainmenu.buttons[counter].x, mainmenu.buttons[counter].y,
                         mainmenu.buttons[counter].h, mainmenu.buttons[counter].w);
            SDL_RenderCopy(render1, mainmenu.buttons[counter].texture, NULL, &imgrect);
        }
    }
    //
    SDL_RenderPresent(render1);
}

void profilerend(){
    SDL_RenderClear(render1);
    //

    DrawRect(0, 0, 800, 800, 255, 150, 150, 0);
    DrawRect(80, 300, 60, 640, 255, 255, 255, 0);
    DrawRect(80, 400, 60, 640, 255, 255, 255, 0);

    TextsToSDL(80, 220, 40, 20, "account*");
    DrawTexts(300, 220, 40, 20, accounts[selectaccount].user, 100);
    TextsToSDL(80, 280, 20, 10, "username");
    TextsToSDL(80, 380, 20, 10, "password");
    DrawTexts(80, 310, 40, 20, username, currentname);
    DrawTexts(80, 410, 40, 20, password, currentpassword);

    if(selection>0){DrawRect(55, 200+selection*100, 60, 20, 255, 0, 0, 0);}

    for(counter=0; counter<nobutt; counter++){
        if(mainmenu.buttons[counter].page==mainmenu.state)
        {
            RectSet(mainmenu.buttons[counter].x, mainmenu.buttons[counter].y,
                         mainmenu.buttons[counter].h, mainmenu.buttons[counter].w);
            SDL_RenderCopy(render1, mainmenu.buttons[counter].texture, NULL, &imgrect);
        }
    }
    //
    SDL_RenderPresent(render1);
}

void messagerrender(char* ctext){
    SDL_RenderClear(render1);
    //
    RectSet(60, 0, 680, 680);
    SDL_RenderCopy(render1, maps[0].texture, NULL, &imgrect);

    DrawRect(200, 200, 200, 600, 50, 150, 255, 0);
    TextsToSDL(210, 210, 40, 20, ctext);

    for(counter=0; counter<nobutt; counter++){
        if(mainmenu.buttons[counter].page==mainmenu.state)
        {
            RectSet(mainmenu.buttons[counter].x, mainmenu.buttons[counter].y,
                         mainmenu.buttons[counter].h, mainmenu.buttons[counter].w);
            SDL_RenderCopy(render1, mainmenu.buttons[counter].texture, NULL, &imgrect);
        }
    }
    //
    SDL_RenderPresent(render1);
}

#endif // graphic
