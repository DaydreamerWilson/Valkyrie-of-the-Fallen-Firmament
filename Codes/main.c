
#include "dataholder.c"
#include "library.c"
#include "mics.c"
#include "graphic.c"
#include "game1.c"

#define TRUE 1
#define FALSE 0

#define player 0
#define friendly 1
#define enemy 2

/*
    State Menu:
111 Exit
0 Front
1 Login
2 Register
3 Menu
4 Register Success
5 Register Failed
6 Login Success
7 Login Failed
8 Login Process
9 Register Process
12 Admin
13 Game Menu
14
15 Level loading1
16 Game 1
17 Level loading2
18 Game 2
19 Level loading3
20 Game 3
50 Lost
51 Save Result
52
61 Leaderboard Setup
62 Leaderboard
65 Leaderboard Previous
66 Leaderboard Next
70 Setting Setup
71 Setting
74 Setting Next
75 Setting Previous

    Level of access:
0 Admin
1 User

*/

void buttonclick(){
    mousetimer=30;
    if(mainmenu.state<=14 || mainmenu.state>=50){
        for(counter=0; counter<nobutt; counter++){
            if(mainmenu.buttons[counter].page==mainmenu.state){
                if(checkcontact(mx, my, mainmenu.buttons[counter].x, mainmenu.buttons[counter].y,
                                mainmenu.buttons[counter].h, mainmenu.buttons[counter].w))
                   {
                       if(mainmenu.buttons>=0){
                            mainmenu.state=mainmenu.buttons[counter].action;
                            counter=nobutt;
                            printf("\nState changed to %d ", mainmenu.state);
                        }
                   }
            }
        }
    }
}

int mousein(){
    SDL_PollEvent(&keyevent);
    if(keyevent.type==SDL_MOUSEBUTTONDOWN){
        printf("Detected Click"); SDL_GetMouseState(&mx, &my); return 1;
    }
    else{return 0;}
}

void keyboardin(){
    SDL_PollEvent(&keyevent);
    if(keyevent.type==SDL_QUIT){mainmenu.state=111;}
    receinput=SDL_GetKeyboardState(NULL);
    for(counter=0; counter<512; counter++){
        if(receinput[counter])
            {key[counter]=TRUE; printf("[%d]", counter);}
        else
            {key[counter]=FALSE;}
    }
    for(counter=89; counter<99; counter++){
        if(key[counter]==TRUE){key[counter-59]=TRUE; key[counter]=FALSE;}
    }
}

void saveresult(){
    saveaccounts();
    mainmenu.state=3;
}

void result(){
    if(accounts[currentaccount].highscore<(int)players.prog){
        accounts[currentaccount].highscore=(int)players.prog;
    }
    resultrend();
}

void initiate(){
    SDL_Init(SDL_INIT_EVERYTHING);
    window1=SDL_CreateWindow("Valkyrie of the Fallen Firmament", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenw, screenh, 0);
    //SDL_SetWindowFullscreen(window1, SDL_WINDOW_FULLSCREEN);
    render1=SDL_CreateRenderer(window1, -1, 0);
    spriteloader();
    loadstart();
    loadgame();
    loadlevel();
    loadaccounts();
    srand(time(0));
    mainmenu.state=0;
}

void fronter(){
    fronterrend();
}

void loginY(){
    printf("Current Account [%d]", currentaccount);
    messagerrender("login success");
}

void loginN(){
    messagerrender("username or password incorrect");
}

void registY(){
    printf("Current Account [%d]", currentaccount);
    messagerrender("register success");
}

void registN(){
    messagerrender("please enter another username");
}

void loginer(){
    if(mousein()==1){
        if(checkcontact(mx, my, 80, 300, 60, 640)){selection=1;}
        else{
            if(checkcontact(mx, my, 80, 400, 60, 640)){selection=2;}
            else{selection=0;}
        }
    }

    if(keytimer>0){keytimer--;}
    else{
    if(selection==1){
        for(counter=4; counter<40; counter++){
            if(key[counter]==TRUE){
                username[currentname]=counter;
                currentname++;
                keytimer=10;
            }
        }
        if(key[43]==TRUE){
            selection=2;
            printf(" {Selection=2} ");
            keytimer=10;
        }
        if(key[42]==TRUE){
            currentname--;
            username[currentname]=0;
            keytimer=10;
        }
    }
    else{
    if(selection==2){
        for(counter=4; counter<40; counter++){
            if(key[counter]==TRUE){
                password[currentpassword]=counter;
                currentpassword++;
                keytimer=10;
            }
        }
        if(key[43]==TRUE){
            selection=1;
            printf(" {Selection=1} ");
            keytimer=10;
        }
        if(key[42]==TRUE){
            currentpassword--;
            password[currentpassword]=0;
            keytimer=10;
        }
    }}
    }

    if(currentname<0){currentname=0;}
    if(currentpassword<0){currentpassword=0;}

    printf("Select[%d]", selection);

    loginerrend();
    if(key[41]==TRUE){mainmenu.state=0;}
    if(key[40]==TRUE){
        mainmenu.state=8;
    }
}

void regist(){
    if(mousein()==1){
        if(checkcontact(mx, my, 80, 300, 60, 640)){selection=1;}
        else{
            if(checkcontact(mx, my, 80, 400, 60, 640)){selection=2;}
            else{selection=0;}
        }
    }

    if(keytimer>0){keytimer--;}
    else{
    if(selection==1){
        for(counter=4; counter<40; counter++){
            if(key[counter]==TRUE){
                username[currentname]=counter;
                currentname++;
                keytimer=10;
            }
        }
        if(key[43]==TRUE){
            selection=2;
            printf(" {Selection=2} ");
            keytimer=10;
        }
        if(key[42]==TRUE){
            currentname--;
            username[currentname]=0;
            keytimer=10;
        }
    }
    else{
    if(selection==2){
        for(counter=4; counter<40; counter++){
            if(key[counter]==TRUE){
                password[currentpassword]=counter;
                currentpassword++;
                keytimer=10;
            }
        }
        if(key[43]==TRUE){
            selection=1;
            printf(" {Selection=1} ");
            keytimer=10;
        }
        if(key[42]==TRUE){
            currentpassword--;
            password[currentpassword]=0;
            keytimer=10;
        }
    }}
    }

    if(currentname<0){currentname=0;}
    if(currentpassword<0){currentpassword=0;}

    printf("Select[%d]", selection);

    registrend();
    if(key[41]==TRUE){mainmenu.state=0;}
    if(key[40]==TRUE){
        mainmenu.state=9;
    }
}

void loginpro(){
   checker=FALSE;
   currentaccount=accountnum+2;
        for(counter=0; counter<accountnum; counter++){
            printf("[%d Username{%s} {%s}]", counter, accounts[counter].user, username);
            if(memcmp(accounts[counter].user, username, 100)==0){currentaccount=counter; break;}
        }

        if(memcmp(accounts[currentaccount].pass, password, 100)==0){checker=TRUE;}
        printf("[%d Password{%s} {%s}]", counter, accounts[currentaccount].pass, password);

        if(username[0]==0){checker=FALSE;}
        if(password[0]==0){checker=FALSE;}
        if(checker==TRUE){mainmenu.state=6;}
        else{mainmenu.state=7;}
}

void registpro(){
    checker=TRUE;
        for(counter=0; counter<accountnum; counter++){
            if(memcmp(accounts[counter].user, username, 100)==0){checker=FALSE;}
        }

        if(username[0]==0){checker=FALSE;}
        if(checker==TRUE){mainmenu.state=4; registaccounts();}
        else{mainmenu.state=5;}
}

void menuer(){


    menuerrend();
}

void leaderfilter(){
    //SDL_Delay(5000);
    printf("\nFilter Started\n");
    for(counter3=0; counter3<accountnum; counter3++){
        rankers[counter3].filter=FALSE;
        if(currentinput==0){rankers[counter3].filter=TRUE;}
        else{
            for(counter1=0; counter1<100; counter1++){
                checker=TRUE;
                if(accounts[rankers[counter3].id].user[counter1]==input[0]){
                    for(counter2=0; counter2<currentinput; counter2++){
                        if(accounts[rankers[counter3].id].user[counter1+counter2]!=input[counter2]){
                            checker=FALSE;
                        }
                        printf("[%d %d %d %d]", currentinput, counter3, counter1, counter2);
                    }
                }
                else{checker=FALSE;}
                if(accounts[rankers[counter3].id].user[counter1]==0){counter1=100; checker=FALSE;}
                if(checker==TRUE){rankers[counter3].filter=TRUE;}
            }
        }
    }

    counter2=0;
    for(counter1=0; counter1<accountnum; counter1++){
        if(rankers[counter1].filter==TRUE){
            filter[counter2]=rankers[counter1].id;
            counter2++;
        }
    }
    currentfilter=counter2;
    printf("\nCurrent Filter : %d", currentfilter);
    mainmenu.maxpage=(currentfilter/10);
    printf("\nFilter Completed\n");
}

void leader(){

    if(keytimer>0){keytimer--;}
    else{
        for(counter=4; counter<40; counter++){
            if(key[counter]==TRUE){
                input[currentinput]=counter;
                currentinput++;
                keytimer=10;
                leaderfilter();
                mainmenu.page=0;
            }
        }
        if(key[42]==TRUE){
            currentinput--;
            if(currentinput<0){currentinput=0;}
            input[currentinput]=0;
            keytimer=10;
            leaderfilter();
            mainmenu.page=0;
        }
    }

    leaderrend();
}

void leadernext(){
    mainmenu.page++;
    if(mainmenu.page>mainmenu.maxpage){mainmenu.page=mainmenu.maxpage;}
    mainmenu.state=62;
}

void leaderback(){
    mainmenu.page--;
    if(mainmenu.page<0){mainmenu.page=0;}
    mainmenu.state=62;
}

void settingnext(){
    mainmenu.page++;
    if(mainmenu.page>mainmenu.maxpage){mainmenu.page=mainmenu.maxpage;}
    mainmenu.state=73;
}

void settingback(){
    mainmenu.page--;
    if(mainmenu.page<0){mainmenu.page=0;}
    mainmenu.state=73;
}

void leaderset(){

    currentinput=0;

    for(counter=0; counter<accountnum; counter++){
        rankers[counter].id=counter;
        rankers[counter].score=accounts[counter].highscore;
    }

    for(int x=0; x<accountnum; x++){
        for(counter=0; counter<accountnum; counter++){
            if(rankers[counter].score<rankers[counter+1].score){
                tempranker=rankers[counter];
                rankers[counter]=rankers[counter+1];
                rankers[counter+1]=tempranker;
            }
        }
    }
    for(counter=0; counter<accountnum; counter++){
        printf("[(%d) %d %d]", counter, rankers[counter].id, rankers[counter].score);
        accounts[rankers[counter].id].temprank=counter;
    }

    for(counter=0; counter<accountnum; counter++){
        rankers[counter].filter=TRUE;
        filter[counter]=rankers[counter].id;
    }

    mainmenu.maxpage=(accountnum/10);

    currentfilter=accountnum;

    printf("\nCurrent Filter : %d", currentfilter);

    mainmenu.state=62;
}

void gamemenu(){
    gamemenurender();
}

void admin(){
    if(accounts[currentaccount].levelofaccess==0){
        mainmenu.state=71;
    }
    else{
        messagerrender("you dont have the permission");
    }
}

void setting(){

    settingrend();
}

void settingset(){
    leaderset();
    currentinput=0;
    mainmenu.state=73;
}

void settinglist(){

    if(keytimer>0){keytimer--;}
    else{
        for(counter=4; counter<40; counter++){
            if(key[counter]==TRUE){
                input[currentinput]=counter;
                currentinput++;
                keytimer=10;
                leaderfilter();
                mainmenu.page=0;
            }
        }
        if(key[42]==TRUE){
            currentinput--;
            if(currentinput<0){currentinput=0;}
            input[currentinput]=0;
            keytimer=10;
            leaderfilter();
            mainmenu.page=0;
        }
    }

    //leaderrend();

    settinglistrend();

    if(mousetimer==30 && mx>=110 && mx<=520 && my>=140 && my<=540){
        for(counter=0; counter<10; counter++){
            if(checkrange(my, counter*40+140, counter*40+180)){break;}
        }

        selectaccount=counter+mainmenu.page*10;

        if(selectaccount<currentfilter){
            selectaccount=filter[selectaccount];
            mainmenu.state=75;
        }
    }

}

void profileset(){
    currentname=0;
    while(accounts[selectaccount].user[currentname]!=0){
        currentname++;
    }
    currentpassword=0;
    while(accounts[selectaccount].pass[currentpassword]!=0){
        currentpassword++;
    }

    memcpy(username, accounts[selectaccount].user, 100);
    memcpy(password, accounts[selectaccount].pass, 100);

    mainmenu.state=74;
}

void profile(){

    if(mousein()==1){
        if(checkcontact(mx, my, 80, 300, 60, 640)){selection=1;}
        else{
            if(checkcontact(mx, my, 80, 400, 60, 640)){selection=2;}
            else{selection=0;}
        }
    }

    if(keytimer>0){keytimer--;}
    else{
    if(selection==1){
        for(counter=4; counter<40; counter++){
            if(key[counter]==TRUE){
                username[currentname]=counter;
                currentname++;
                keytimer=10;
            }
        }
        if(key[43]==TRUE){
            selection=2;
            printf(" {Selection=2} ");
            keytimer=10;
        }
        if(key[42]==TRUE){
            currentname--;
            username[currentname]=0;
            keytimer=10;
        }
    }
    else{
    if(selection==2){
        for(counter=4; counter<40; counter++){
            if(key[counter]==TRUE){
                password[currentpassword]=counter;
                currentpassword++;
                keytimer=10;
            }
        }
        if(key[43]==TRUE){
            selection=1;
            printf(" {Selection=1} ");
            keytimer=10;
        }
        if(key[42]==TRUE){
            currentpassword--;
            password[currentpassword]=0;
            keytimer=10;
        }
    }}
    }

    if(currentname<0){currentname=0;}
    if(currentpassword<0){currentpassword=0;}

    profilerend();
}

void profilesave(){

    memcpy(accounts[selectaccount].user, username, 100);
    memcpy(accounts[selectaccount].pass, password, 100);

    saveaccounts();
    mainmenu.state=74;
}

void statecheck(){
    switch(mainmenu.state){
    case 111: SDL_Quit(); running=0; break;
    case 0: fronter(); break;
    case 1: loginer(); break;
    case 2: regist(); break;
    case 3: menuer(); break;
    case 4: registY(); break;
    case 5: registN(); break;
    case 6: loginY(); break;
    case 7: loginN(); break;
    case 8: loginpro(); break;
    case 9: registpro(); break;
    case 12: admin(); break;
    case 13: gamemenu(); break;
    case 15: levelloading1(); break;
    case 16: level1runner1(); break;
    case 50: result(); break;
    case 51: saveresult(); break;
    case 61: leaderset(); break;
    case 62: leader(); break;
    case 65: leaderback(); break;
    case 66: leadernext(); break;
    case 71: setting(); break;
    case 72: settingset(); break;
    case 73: settinglist(); break;
    case 74: profile(); break;
    case 75: profileset(); break;
    case 76: profilesave(); break;
    case 78: settingback(); break;
    case 79: settingnext(); break;
    }
}

int main(int argc, char* argv[]){
    HWND windowh = GetConsoleWindow();
    ShowWindow(windowh, SW_HIDE);

    srand(time(NULL));
    time(&timey);
    initiate();
    //getchar();
    mousetimer=15;
    while(running){
        if(mousetimer>0){mousetimer--;}
        else{if(mousein()==1){buttonclick();}}
        if(mainmenu.state<=14 || mainmenu.state>=50){SDL_ShowCursor(SDL_ENABLE);}else{SDL_ShowCursor(SDL_DISABLE);}
        keyboardin();
        //printf("Keyboard");
        statecheck();
        //printf("State");
        frame();
        //printf("frame");
        printf(" State:%d ", mainmenu.state);
        printf(" %s ", SDL_GetError());
    }
    if(!running){ShowWindow(windowh, SW_SHOW); SDL_Quit(); exit(0);}
}
