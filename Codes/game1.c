#include "dataholder.c"
#include "library.c"
#include "mics.c"
#include "graphic.c"

float midx, midy, tempd;
double gdd;

void levelloading1(){
    for(int n=0; n<100; n++){
        ships[n].exist=0;
    }
    for(int n=0; n<5000; n++){
        bullets[n].exist=0;
    }
    players.hp=10;
    players.sp=3;
    players.x=950;
    players.y=480;
    players.vy=5;
    players.prog=0;
    level=1;
    mainmenu.state=16;
}

void repos(){
    for(int n=0; n<100; n++){
        if(ships[n].exist==1 && ships[n].hp>0){
            ships[n].y+=ships[n].vy+players.vy-5;
            shipid=ships[n].id;
            for(int d=0; d<shipsto[shipid].nos; d++){
                turretid=ships[n].turrets[d].id;

                //Debugging
                midx=ships[n].x+shipsto[shipid].w/2;
                midy=ships[n].y+shipsto[shipid].h/2;

                dx=shipsto[shipid].spec[d].x-(shipsto[shipid].w/2);
                dy=shipsto[shipid].spec[d].y-(shipsto[shipid].h/2);

                if(dx!=0 && dy!=0){gdd=atan(dy/dx);}
                else{
                    if(dx==0){
                        if(dy>0){gdd=0;}
                        if(dy<0){gdd=pi;}
                    }
                    if(dy==0){
                        if(dx>0){gdd=pi/2;}
                        if(dx<0){gdd=pi*3/2;}
                    }
                }

                tempd=sqrt(dx*dx+dy*dy);

                ships[n].turrets[d].x=midx+tempd*sin(-(ships[n].degree/180*pi)+gdd)-turretsto[turretid].w/2;
                ships[n].turrets[d].y=midy+tempd*cos(-(ships[n].degree/180*pi)+gdd)-turretsto[turretid].h/2;

                //printf("[Ship%d Turret%d dx:%.4f dy:%.4f gdd:%.4f]\n", n, d, dx, dy, gdd);
                //Debugging


                dx=ships[n].turrets[d].x+turretsto[turretid].w/2-(players.x+playersto.w/2);
                dy=ships[n].turrets[d].y+turretsto[turretid].h/2-(players.y+playersto.h/2);

                ftemp=dy/dx;
                ships[n].turrets[d].degree=atan(ftemp)*180/pi-90;
                if(dx<0){ships[n].turrets[d].degree+=180;}
            }
        }
    }
    for(int n=0; n<5000; n++){
        if(bullets[n].exist==1){
            bullets[n].x+=bullets[n].vx;
            bullets[n].y+=bullets[n].vy+players.vy-5;
        }
    }

    if(key[82]&&players.vy<=10){players.vy++;} //Up
    if(key[81]&&players.vy>=0){players.vy--;} //Down
    if(key[80]&&players.vx>=-5){players.vx--;} //Left
    if(key[79]&&players.vx<=5){players.vx++;} //Right

    if(!key[79] &&!key[80]){
        if(players.vx>0){players.vx-=0.5;}
        if(players.vx<0){players.vx+=0.5;}
    }

    if(!key[81] &&!key[82]){
        if(players.vy>5){players.vy-=0.5;}
        if(players.vy<5){players.vy+=0.5;}
    }

    players.x+=players.vx;
    players.y-=players.vy-5;
    if(players.y>480){players.y--;}
    if(players.y<480){players.y++;}
    if(players.y-480<=1 && players.y-480>=-1){players.y=480;}


    if(players.y>580){players.y=580;}
    if(players.y<100){players.y=100;}

    if(players.x>1900-playersto.w){players.x=1900-playersto.w;}
    if(players.x<0){players.x=0;}

    if(players.vx==0){motion=0;}
    if(players.vx<0){motion=1;}
    if(players.vx>0){motion=2;}

    players.prog+=players.vy;

    bkgd1+=players.vy-2;
    bkgd2+=players.vy-2;
    if(bkgd1>1000){bkgd1-=8000;}
    if(bkgd2>1000){bkgd2-=8000;}
    printf("[1:%.2f] [2:%.2f]", bkgd1, bkgd2);
}

void fire(){
    for(int n=0; n<100; n++){
        if(ships[n].exist==1 && ships[n].hp>0){
            shipid=ships[n].id;
            for(int d=0; d<shipsto[shipid].nos; d++){
                //printf("{%d}", ships[n].turrets[d].t);
                if(ships[n].turrets[d].t==0){
                    turretid=ships[n].turrets[d].id;
                    for(int i=0; i<turretsto[turretid].nos; i++){

                        dx=turretsto[turretid].spec[i].x-turretsto[turretid].w/2;
                        dy=turretsto[turretid].spec[i].y-turretsto[turretid].h/2;

                        if(dx!=0 && dy!=0){gdd=atan(dy/dx);}
                        else{
                            if(dx==0){
                                if(dy>0){gdd=0;}
                                if(dy<0){gdd=pi;}
                        }
                            if(dy==0){
                                if(dx>0){gdd=pi/2;}
                                if(dx<0){gdd=pi*3/2;}
                            }
                        }

                        tempd=sqrt(dx*dx+dy*dy);

                        dx=tempd*sin(-(ships[n].turrets[d].degree/180*pi)+gdd);
                        dy=tempd*cos(-(ships[n].turrets[d].degree/180*pi)+gdd);

                        //printf("[dx:%.4f dy:%.4f gdd:%.4f]\n", dx, dy, gdd);

                        dx+=ships[n].turrets[d].x+turretsto[turretid].w/2;
                        dy+=ships[n].turrets[d].y+turretsto[turretid].h/2;

                        //printf("[dx:%.4f dy:%.4f gdd:%.4f]", dx, dy, gdd);

                        createbullet(turretsto[turretid].spec[i].name, dx, dy, ships[n].turrets[d].v, ships[n].turrets[d].degree);
                    }
                    ships[n].turrets[d].t=turretsto[turretid].level;
                    //printf("[Firing Succeed]");
                }
                else{ships[n].turrets[d].t--;}
            }
        }
    }
}

int becheck(check, min, max){
    if(min>max){int temp=min; min=max; max=temp;}
    if(check>=min && check<=max){return 1;}else{return 0;}
}

int checkcollide(x1, y1, x2, y2, h1, w1, h2, w2){
    if(becheck(x1, x2, x2+w2-1)){return 1;}
    if(becheck(x1+h1-1, x2, x2+w2-1)){return 1;}
    if(becheck(y1, y2, y2+h2-1)){return 1;}
    if(becheck(y1+h1-1, y2, y2+h2-1)){return 1;}
    return 0;
}

void shipgenerate(int level){
    shiptimer=200;
    if(level==11){
        shiptimer=50;
    }

    //printf("[Checkpoint 1]");

    int m, x, y;
    int n = rand()%2+3;
    m = 1900/n;

    //printf("[Checkpoint 2]");
    if(level==11){
        n = rand()%4+6;
        m = 1900/n;
    }

    for(counter=0; counter<n; counter++){
        x=(counter*m)+(rand()%m);
        y=rand()%100-2000;
        createship(x, y, level);
    }
}

void gamecheck(){
    objectcount=0;
    for(int n=0; n<5000; n++){
        if(bullets[n].exist){
            objectcount++;
            if(!checkcontact(bullets[n].x, bullets[n].y, players.x-800, players.y-1000, 2000, 1600)){
                bullets[n].exist=0;
            }
        }
    }
    printf("<Bullets: %d>", objectcount);
    objectcount=0;
    for(int n=0; n<100; n++){
        if(ships[n].exist){
            objectcount++;
            if(ships[n].y>players.y+500){
                ships[n].exist=0;
            }
        }
    }
    printf("<Ships: %d>", objectcount);
    if(players.timer==0){
        for(int n=0; n<5000; n++){
            if(bullets[n].exist){
                bulletid=bullets[n].id;
                if(checkcontact(players.x+playersto.w/2, players.y+playersto.h/2, bullets[n].x, bullets[n].y, projectsto[bulletid].h, projectsto[bulletid].w)){
                    players.hp--;
                    players.timer=60;
                    bullets[n].exist=0;
                    //printf("!!!!!HIT!!!!!");
                }
            }
        }
    }
    else{players.timer--;}
    if(players.prog>level*10000){level++;}
    //level=11;
    if(level>10){
        level=11;
    }
}

void level1runner1(){
    if(players.hp>0){
        if(shiptimer>0){shiptimer--;}
        else{shipgenerate(level);}
        repos();
        fire();
        gamecheck();
    }
    else{players.hp--;}
    gamerender();
    if(players.hp<-120){mainmenu.state=50;}
}
