#include "library.c"

#ifndef dataholder
#define dataholder

SDL_Renderer *render1;
SDL_Window *window1;
SDL_Surface *surface;

int loadercount=0;
int counter=0;
int noitem, nobutt;

FILE *folder;
char tempho[100];
char buffer[100];

void reallocate(){

    loadercount=noitem-1;

    while(loadercount>=0){
        switch(store[loadercount].type){
            case 'C' : playersto=store[loadercount]; break;
            case 'S' : shipsto[shipno]=store[loadercount]; shipno++; break;
            case 'T' : turretsto[turretno]=store[loadercount]; turretno++; break;
            case 'P' : projectsto[projectileno]=store[loadercount]; projectileno++; break;
        }
        loadercount--;
    }
}

void spriteloader(){
    strcpy(tempho, "resources//image//");
    strcat(tempho, "charspritesheet.png");
    printf("|%s|\n", tempho);
    surface=IMG_Load(tempho);
    charsprite=SDL_CreateTextureFromSurface(render1, surface);
    SDL_FreeSurface(surface);
    if(charsprite==NULL){printf("\nTexture Loading Failed\n");}
    printf(" %s ", SDL_GetError());
}

void imageloader(){
    strcpy(tempho, "resources//image//");
    strcat(tempho, store[loadercount].link);
    printf("|%s|\n", tempho);
    surface=IMG_Load(tempho);
    store[loadercount].texture=SDL_CreateTextureFromSurface(render1, surface);
    SDL_FreeSurface(surface);
    if(store[loadercount].texture==NULL){printf("\nTexture Loading Failed\n");}
    printf(" %s ", SDL_GetError());
}

void levelimgloader(){
    strcpy(tempho, "resources//image//");
    strcat(tempho, maps[loadercount].link);
    printf("|%s|\n", tempho);
    surface=IMG_Load(tempho);
    maps[loadercount].texture=SDL_CreateTextureFromSurface(render1, surface);
    SDL_FreeSurface(surface);
    if(maps[loadercount].texture==NULL){printf("\nTexture Loading Failed\n");}
    printf(" %s ", SDL_GetError());
}

void loadbutton(){
    strcpy(tempho, "resources//image//");
    strcat(tempho, mainmenu.buttons[loadercount].link);
    printf("|%s|\n", tempho);
    surface=IMG_Load(tempho);
    mainmenu.buttons[loadercount].texture=SDL_CreateTextureFromSurface(render1, surface);
    SDL_FreeSurface(surface);
    if(mainmenu.buttons[loadercount].texture==NULL){printf("Texture Loading Failed\n");}
    printf(" %s ", SDL_GetError());
}

void loadplayer(){
    printf("Loading player |");
    strcpy(tempho, "resources//object//");
    strcat(tempho, store[loadercount].link);
    folder=fopen(tempho, "r");
    printf("File Opened |");
    fscanf(folder, "name: %s\n", &store[loadercount].name);
    fscanf(folder, "size: %d %d\n", &store[loadercount].h, &store[loadercount].w);
    fscanf(folder, "img: %s\n", &store[loadercount].link);
    fclose(folder);
    printf("Player Loaded\n");
    imageloader();
}

void loadship(){
    printf("Loading ship |");
    strcpy(tempho, "resources//object//");
    strcat(tempho, store[loadercount].link);
    folder=fopen(tempho, "r");
    printf("File Opened |");
    fscanf(folder, "name: %s\n", &store[loadercount].name);
    fscanf(folder, "size: %d %d\n", &store[loadercount].h, &store[loadercount].w);
    fscanf(folder, "img: %s\n", &store[loadercount].link);
    fscanf(folder, "level: %d\n", &store[loadercount].level);
    fscanf(folder, "health: %d\n", &store[loadercount].hp);
    fscanf(folder, "turretno: %d\n", &store[loadercount].nos);
    fgets(buffer, 100, folder);
    for(counter=0; counter<store[loadercount].nos; counter++){
        fscanf(folder, "%s %d %d\n", &store[loadercount].spec[counter].name, &store[loadercount].spec[counter].x, &store[loadercount].spec[counter].y);
    }
    fclose(folder);
    printf("Ship Loaded\n");
    imageloader();
}

void loadturret(){
    printf("Loading turret |");
    strcpy(tempho, "resources//object//");
    strcat(tempho, store[loadercount].link);
    folder=fopen(tempho, "r");
    printf("File Opened |");
    fscanf(folder, "name: %s\n", &store[loadercount].name);
    fscanf(folder, "size: %d %d\n", &store[loadercount].h, &store[loadercount].w);
    fscanf(folder, "img: %s\n", &store[loadercount].link);
    fscanf(folder, "velocity: %d\n", &store[loadercount].hp);
    fscanf(folder, "firerate: %d\n", &store[loadercount].level);
    fscanf(folder, "barrelno: %d\n", &store[loadercount].nos);
    fgets(buffer, 100, folder);
    for(counter=0; counter<store[loadercount].nos; counter++){
        fscanf(folder, "%s %d %d\n", &store[loadercount].spec[counter].name, &store[loadercount].spec[counter].x, &store[loadercount].spec[counter].y);
    }
    fclose(folder);
    printf("Turret Loaded\n");
    imageloader();
}

void loadprojectile(){
    printf("Loading projectile |");
    strcpy(tempho, "resources//object//");
    strcat(tempho, store[loadercount].link);
    folder=fopen(tempho, "r");
    printf("File Opened |");
    fscanf(folder, "name: %s\n", &store[loadercount].name);
    fscanf(folder, "size: %d %d\n", &store[loadercount].h, &store[loadercount].w);
    fscanf(folder, "img: %s\n", &store[loadercount].link);
    fclose(folder);
    printf("Projectile Loaded\n");
    imageloader();
}

void loadstart(){

    folder=fopen("resources//object//menu.txt", "r");
    while(!feof(folder)){
        fscanf(folder, "page: %d action: %d x: %d y: %d w: %d h: %d link: %s\n",
                                            &mainmenu.buttons[loadercount].page,
                                            &mainmenu.buttons[loadercount].action,
                                            &mainmenu.buttons[loadercount].x, &mainmenu.buttons[loadercount].y,
                                            &mainmenu.buttons[loadercount].w, &mainmenu.buttons[loadercount].h,
                                            &mainmenu.buttons[loadercount].link);
        loadercount++;
    }

    nobutt=loadercount+1;
    fclose(folder);
    loadercount--;

    while(loadercount>=0){
        loadbutton();
        loadercount--;
    }

    printf("Finished Loading Menu\n");
    loadercount=0;
}

void loadgame(){

    folder=fopen("resources//object//tololi.txt", "r");
    fscanf(folder, "%d %d %d\n", &gamefile.shipno, &gamefile.turretno, &gamefile.projectileno);
    printf("ship:%d turret:%d projectile:%d\n", gamefile.shipno, gamefile.turretno, gamefile.projectileno);

    while(!feof(folder)){
        fscanf(folder, "%c %s\n", &store[loadercount].type, &store[loadercount].link);
        printf("%d %c %s\n", loadercount, store[loadercount].type, &store[loadercount].link);
        loadercount++;
    }

    noitem=loadercount+1;
    fclose(folder);
    loadercount--;

    while(loadercount>=0){
        switch(store[loadercount].type){
            case 'C' : loadplayer(); break;
            case 'S' : loadship(); break;
            case 'T' : loadturret(); break;
            case 'P' : loadprojectile(); break;
        }
        loadercount--;
    }

    printf("Finished Loading Objects\n");
    reallocate();
    loadercount=0;
}

void loadlevel(){

    loadercount=0;
    folder=fopen("resources//object//level.txt", "r");

    while(!feof(folder)){
        fscanf(folder, "%s\n", &maps[loadercount].link);
        printf(" %s ", maps[loadercount].link);
        loadercount++;
    }

    fclose(folder);
    loadercount--;

    while(loadercount>=0){
        levelimgloader();
        loadercount--;
    }

    printf("Finished Loading Level\n");
    loadercount=0;
}

void loadaccounts(){

    loadercount=0;
    folder=fopen("resources//object//database.txt", "r");

    printf("Loading Accounts\n");

    while(!feof(folder)){
        fscanf(folder, "%d ", &accountnum);
        for(counter=0; counter<100; counter++){
            fscanf(folder, "%d %d ", &accounts[accountnum].user[counter], &accounts[accountnum].pass[counter]);
        }
        fscanf(folder, "%d %d \n", &accounts[accountnum].highscore, &accounts[accountnum].levelofaccess);
        printf("Accounts:[%d %d %d]\n", accountnum, accounts[accountnum].highscore, accounts[accountnum].levelofaccess);
        accountnum++;
    }

    printf("Finish Loading Accounts\n");

    fclose(folder);
}

void saveaccounts(){
    folder=fopen("resources//object//database.txt", "w");
    for(counter=0; counter<accountnum; counter++){
        fprintf(folder, "%d ", counter);
        for(int x=0; x<100; x++){
            fprintf(folder, "%d %d ", accounts[counter].user[x], accounts[counter].pass[x]);
        }
        fprintf(folder, "%d %d \n", accounts[counter].highscore, accounts[counter].levelofaccess);
    }

    fclose(folder);
}

void registaccounts(){
    memcpy(accounts[accountnum].user, username, 100);
    memcpy(accounts[accountnum].pass, password, 100);
    accounts[accountnum].highscore=0;
    accounts[accountnum].levelofaccess=1;
    currentaccount=accountnum;
    accountnum++;

    saveaccounts();
}

#endif
