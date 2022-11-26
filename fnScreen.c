#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>
#include <locale.h>
#include <windows.h>
#include <winuser.h>
#include <locale.h>

#include "fnUser.h"
#include "gotoxy.h"

#define RESET_COLOR    "\x1b[0m"
#define BLACK_T        "\x1b[30m"
#define BLACK_F        "\x1b[40m"
#define RED_T     "\x1b[31m"
#define RED_F     "\x1b[41m"
#define GREEN_T        "\x1b[32m"
#define GREEN_F        "\x1b[42m"
#define YELLOW_T "\x1b[33m"
#define YELLOW_F  "\x1b[43m"
#define BLUE_T     "\x1b[34m"
#define BLUE_F      "\x1b[44m"
#define MAGENTA_T  "\x1b[35m"
#define MAGENTA_F  "\x1b[45m"
#define CYAN_T     "\x1b[36m"
#define CYAN_F     "\x1b[46m"
#define WHITE_T   "\x1b[37m"
#define WHITE_F   "\x1b[47m"

///Funciones de pantalla
void gameOn(char routUser[], char routDungeon[], char routHeros[],char routTrinkets[])
{
    srand(time(NULL));

    int dificultMode=1;
    //setlocale(LC_ALL, "spanish");
    ///entidades activas
    stEntity heroList[16];
    stEntity heroTeam[3];
    stEntity heroAvailable[3];
    stUser userOn[2];
    stDungeon dungeonOn[1];//enemyOne
    int store[4];
    int selectedHero[5]= {9,9,9,0}; //(0 || 1 || 2)==heroPos  /  3==counterHero

    int round=1;
    int positions[4]; //0=heros - 1=enemys - 2=skills

    int cursorOn=0;       //flag del 1 bucle
    int x;
    int y;
    int control=0;        //flag del 2 bucle
    int counter=0;       //Contador y modificador de movimiento XY
    //int escape=0;         //flag de escape
    int result=0;

    int interval=0;       //Posiciones a mover cursor en XY
    int minInterval=0;    //minima posicion de XY
    int maxInterval=0;    //maxima posicion de XY
    int lateralMove=0;    //flag de movimientos laterales
    int verticalMove=0;    //flag de movimientos en todas direcciones
    //int botton=0;
    char axis='x';        //x - y

    //char lastMenu[15];
    char menuStage[15];
    //int lastOption=0;

    char userID[30];
    char password[30];
    char userName[30];
    char userNum[30];
    char newPassword[30];
    char confirmPassword[30];
    int flagLogin=0;
    int flagDown=0;
    //int flagAdmin=0;
    int flagControl=0;
    int logInBlockCounter=0;
    int logInBlockControl=0;
    int userFound = 0;
    int flagFind = 0;                //buscar usuario (admin)
    int flagNewUser=0;

    //int i=0;
    strcpy(menuStage, "startMenu");

    while(cursorOn==0)
    {
        ///RESET DE FLAGS
        //strcpy(lastMenu, menuStage);
        //lastOption = counter;
        lateralMove=0;
        verticalMove=0;
        minInterval=0;
        logInBlockCounter=0;
        logInBlockControl=0;
        control = 0;
        //positions[1]=4;

        if(strcmpi(menuStage, "startMenu")!=0)
        {
            system("cls");
        };
        ///actualizar heroes disponibles
        int valids=availableHerosList(heroAvailable,heroList,userOn);

        ///set de pantalla seleccionada
        setOptionMenu(menuStage,counter,userOn,dungeonOn,heroTeam,positions, dificultMode, &round, &cursorOn, routUser, routHeros, routDungeon, flagLogin, flagDown, &userFound, heroList, &result,
                      store, heroAvailable,selectedHero);

        ///set option x y
        if ((strcmpi(menuStage, "logIn") == 0) || (strcmpi(menuStage, "startMenu") == 0))
        {
            x = 46;
            y = 9;
            interval=4;
            maxInterval=12;
            verticalMove=1;
        }
        else if (strcmpi(menuStage, "newUser") == 0)
        {
            x = 46;  //new user
            y = 10;
            interval=4;
            maxInterval=12;
            verticalMove=1;
            flagNewUser=1;

        }
        else if (strcmpi(menuStage, "loginValidate") == 0)
        {
            if(flagNewUser==1) ///Agregar nuevo usuario
            {
                if(validateUserName(userID,routUser)==0)
                {
                    addUser(userName,userID,password,routUser,routTrinkets);
                    flagLogin=1;
                }
            }
            if(whoAreYou(userID,password,userOn,routUser)==1)
            {
                flagLogin=1;
                dungeon(userOn,dungeonOn,routDungeon);
                searchListHero(heroList,routHeros);//validos
                storeHeros(store);                           //array de posiciones de heroes aleatorios
                heroTeam[0]=heroList[userOn[0].posHeros[0]];
                heroTeam[1]=heroList[userOn[0].posHeros[1]];
                heroTeam[2]=heroList[userOn[0].posHeros[2]];
                if(validateUser(userOn[0].active)==0)
                {
                    flagDown=1;
                }
            }
            else
            {
                flagLogin=0;
            }
            control=1;
            flagControl=1;
            counter=10;
            logInBlockCounter=1;
            logInBlockControl=1;
            if(flagNewUser==1)
            {
                strcpy(menuStage,"newUser");
            }
            else
            {
                strcpy(menuStage,"logIn");
            }
            flagNewUser=0;
        }
        else if (strcmpi(menuStage, "index") == 0)
        {
            x = 43;
            y = 8;
            interval=2;
            maxInterval=12;
            verticalMove=1;
            control = 0;
        }
        else if (strcmpi(menuStage, "setDifficult") == 0)//DIFICULTAD
        {
            x = 26;
            y = 16;
            interval=17;
            maxInterval=34;
            lateralMove=1;
            verticalMove=1;
        }
        else if (strcmpi(menuStage, "continue") == 0) {} //-------aldope = "CONTINUAR" inicia combate
        else if (strcmpi(menuStage, "findUser") == 0)
        {
            x = 28;
            y = 14;
            lateralMove = 1;
            interval = 37;
            maxInterval = 37;
        }
        else if (strcmpi(menuStage, "invalidUser") == 0)
        {
            x = 50;
            y = 15;
        }
        else if (strcmpi(menuStage, "resultsMenu") == 0)
        {
            x = 49;
            y = 18;
        }
        else if (strcmpi(menuStage, "exitCombat") == 0)
        {
            x = 40;
            y = 16;
            lateralMove = 1;
            interval = 17;
            maxInterval = 17;
        }
        else if (strcmpi(menuStage, "succesfullSetDown") == 0)
        {
            x = 50;
            y = 15;
        }
        else if (strcmpi(menuStage, "activeUser") == 0)
        {
            control = 0;
            x = 36;
            y = 14;
            lateralMove=1;
            interval=28;
            maxInterval=28;
        }
        else if (strcmpi(menuStage, "screenMap") == 0)
        {
            x = 77;
            y = 7;
            interval=5;
            maxInterval=15;
            verticalMove=1;
        }
        else if (strcmpi(menuStage, "selectTrinket") == 0)
        {
            x = 84;
            y = 5;
            verticalMove=1;
            interval=2;
            maxInterval=18;
        }
        else if (strcmpi(menuStage, "selectTeam") == 0)
        {
            if(selectedHero[3]==3)
            {
                x = 87;
                y = 25;
                counter = 98;
                verticalMove=0;
            }
            else
            {
                x = 7;
                y = 5;
                verticalMove=1;
                interval=3;
                maxInterval=interval*userOn[0].validsAvailableHeros;
            }
        }
        else if (strcmpi(menuStage, "userPerfil") == 0)
        {
            x = 34;
            y = 21;
            if(userOn[0].type==1)
            {
                if(userFound==0)
                {
                    lateralMove=1;
                    interval=16;
                    maxInterval=16;
                }
                else
                {
                    x = 68;
                    y = 21;
                }
            }
            else
            {
                lateralMove=1;
                interval=32;
                maxInterval=32;
            }
        }
        else if (strcmpi(menuStage, "buy") == 0)
        {
            x = 50;
            y = 15;
        }
        else if (strcmpi(menuStage, "enoughMoney") == 0)
        {
            x = 50;
            y = 15;
        }
        else if (strcmpi(menuStage, "tierList") == 0)
        {
            x=84;
            y=26;
        }
        else if (strcmpi(menuStage, "store") == 0)
        {
            x = 85;
            y = 12;
            verticalMove=1;
            interval=6;
            maxInterval=12;
        }
        else if (strcmpi(menuStage, "resultsMenu") == 0)
        {
            x = 26;
            y = 12;
            interval=9;
            maxInterval=9;
        }
        else if (strcmpi(menuStage, "changePass") == 0)
        {
            x = 43;
            y = 12;
            interval=4;
            verticalMove=1;
        }
        else if (strcmpi(menuStage, "setDown") == 0)
        {
            x = 46;
            y = 13;
        }
        else if (strcmpi(menuStage, "error") == 0)
        {
            x = 50;
            y = 17;
        }
        else if (strcmpi(menuStage, "combat") == 0)
        {
            maxInterval=50;
            lateralMove=1;
            verticalMove=1;
            if(counter<=16 || counter==15 || counter==17 || counter==34)
            {
                x = 33;
                y = 20;
                interval=8;
                if (counter==15 || counter==17 || counter==34)
                {
                    counter=0;
                }
            }
            else
            {
                x=36;
                y=15;
                interval=13;
            }
        }
        else {};
        gotoxy(x,y);

        ///RESET DE FLAGS
        if(strcmpi(menuStage, "combat") != 0 && logInBlockCounter !=1)
        {
            if(strcmpi(menuStage, "selectTeam") == 0)
            {
                if(counter!=98)
                {
                    counter=0;
                    axis='s';
                }
                axis='s';
                //printf("%d",selectedHero[3]);
                //system("pause");
            }
            else
            {
                counter=0;
                axis='s';
            }
        }
        else if (logInBlockControl!=1) //flag de logeo
        {
            control = 0;
        }

        while(control == 0)         ///bucle del puntero
        {
            ///enter
            if(GetAsyncKeyState(0x0D))
            {
                control = 1;
                Sleep(200);
            }
            ///escape
            else if(GetAsyncKeyState(0x1B))
            {
                if((strcmpi(menuStage, "combat") != 0) || (strcmpi(menuStage, "index") != 0))
                {
                    control = 1;
                    counter = 99;
                    Sleep(200);
                }
            }
            if(control == 0)
            {
                if((GetAsyncKeyState(0x26) && counter>minInterval && verticalMove==1) || (GetAsyncKeyState(0x26) && verticalMove==1 && (strcmpi(menuStage, "combat") == 0)))
                {
                    /// flecha arriba
                    if(strcmpi(menuStage, "combat") == 0)
                    {
                        x=48;
                        y=4;
                        interval=0;
                        counter=15;
                        axis='s';
                    }
                    else if(strcmpi(menuStage, "selectTeam") == 0)
                    {
                        if(counter==maxInterval)
                        {
                            x = 7;
                            y = 5;
                            counter-=interval;
                        }
                        else
                        {
                            counter-=interval;
                        }
                        axis='y';
                    }
                    else
                    {
                        counter-=interval;
                    };
                    Sleep(200);
                    //axis='y';
                }
                else if(GetAsyncKeyState(0x28) && counter<maxInterval && verticalMove==1)
                {
                    /// flecha abajo
                    if(strcmpi(menuStage, "combat") == 0)
                    {
                        if(counter==15)
                        {
                            x = 33;
                            y = 20;
                            counter+=interval;
                            interval=8;
                            counter=0;
                            //axis='y';
                        }
                    }
                    else if(strcmpi(menuStage, "selectTrinket") == 0)
                    {
                        if(counter==18)
                        {
                            x = 85;
                            counter+=interval;
                        }
                        else
                        {
                            counter+=interval;
                        }
                        axis='y';
                    }
                    else if(strcmpi(menuStage, "selectTeam") == 0)
                    {
                        if(counter==maxInterval-interval)
                        {
                            x = 87;
                            y = 10;
                            counter+=interval;
                            //counter+=interval;
                            //axis='y';
                        }
                        else
                        {
                            counter+=interval;
                            axis='y';
                        }
                    }
                    else
                    {
                        counter+=interval;
                        axis='y';
                    };
                    Sleep(200);
                    //axis='y';
                }
                else if(GetAsyncKeyState(0x25)&& counter>minInterval && lateralMove==1)
                {
                    /// flecha izquierda
                    if(strcmpi(menuStage, "combat") == 0)  //condicion de pantalla de combate para bajar hasta las habilidades
                    {
                        if(counter==24) // bajar hasta las habilidades
                        {
                            x = 33;
                            y = 20;
                            interval=8;
                            counter-=interval;
                            axis='x';
                        }
                        else if(counter>24)
                        {
                            counter-=interval;
                            interval=13;
                            axis='x';
                        }
                        else if(counter<24 && counter!=15)
                        {
                            counter-=interval;
                            axis='x';
                        }
                    }
                    else
                    {
                        counter-=interval;
                        axis='x';
                    }
                    Sleep(200);
                    //axis='x';
                }
                else if(GetAsyncKeyState(0x27) && counter<maxInterval && lateralMove==1)
                {
                    /// flecha derecha
                    if(strcmpi(menuStage, "combat") == 0)  //condicion de pantalla de combate para subir hasta los enemigos
                    {
                        if(counter>=16)
                        {
                            x=36;
                            y=15;
                            counter+=interval;
                            interval=13;
                            axis='x';
                        }
                        else if(counter<16 && counter!=15)
                        {
                            counter+=interval;
                            axis='x';
                        }
                    }
                    else
                    {
                        counter+=interval;
                        axis='x';
                    }
                    Sleep(200);
                    //axis='x';
                }// teclado a-z y 0-9
                else if((GetAsyncKeyState(0x41)||GetAsyncKeyState(0x42)||GetAsyncKeyState(0x43)||GetAsyncKeyState(0x44)||GetAsyncKeyState(0x45)||
                         GetAsyncKeyState(0x46)||GetAsyncKeyState(0x47)||GetAsyncKeyState(0x48)||GetAsyncKeyState(0x49)||GetAsyncKeyState(0x50)||
                         GetAsyncKeyState(0x51)||GetAsyncKeyState(0x52)||GetAsyncKeyState(0x53)||GetAsyncKeyState(0x54)||GetAsyncKeyState(0x55)||
                         GetAsyncKeyState(0x56)||GetAsyncKeyState(0x57)||GetAsyncKeyState(0x58)||GetAsyncKeyState(0x59)||GetAsyncKeyState(0x5A)||
                         GetAsyncKeyState(0x30)||GetAsyncKeyState(0x31)||GetAsyncKeyState(0x32)||GetAsyncKeyState(0x33)||GetAsyncKeyState(0x34)||
                         GetAsyncKeyState(0x35)||GetAsyncKeyState(0x36)||GetAsyncKeyState(0x37)||GetAsyncKeyState(0x38)||GetAsyncKeyState(0x39))&&
                        (strcmpi(menuStage, "logIn")||strcmpi(menuStage, "newUser")||strcmpi(menuStage, "findUser")||(strcmpi(menuStage, "userPerfil"))||
                         (strcmpi(menuStage, "changePass"))||(strcmpi(menuStage, "setDown"))))
                {
                    if((counter==0 && strcmpi(menuStage, "logIn")==0) || (counter==4 && strcmpi(menuStage, "newUser")==0)) //id
                    {
                        fflush(stdin);
                        gets(userID);
                        if(GetAsyncKeyState(0x0D)) //enter
                        {
                            Sleep(200);
                            counter+=interval;
                            axis='y';
                        }
                    }
                    else if(counter==0 && strcmpi(menuStage, "findUser")==0) //id
                    {
                        gets(userNum);
                        Sleep(200);
                        if(GetAsyncKeyState(0x0D)) //enter
                        {
                            Sleep(200);
                            flagFind=1;
                        }
                        if(flagFind==1)
                        {
                            if(findUserForId(atoi(userNum),userOn,routUser) != 1)
                            {
                                counter = 9;
                            }
                            else
                            {
                                counter = 0;
                                userFound = 1;
                            }
                            control=1;
                        }
                    }
                    else if((counter==0 && strcmpi(menuStage, "newUser")==0) || (counter==37 && strcmpi(menuStage, "findUser")==0)) //user name
                    {
                        fflush(stdin);
                        gets(userName);
                        Sleep(200);
                        if(GetAsyncKeyState(0x0D)) //enter
                        {
                            Sleep(200);
                            if(strcmpi(menuStage, "findUser")!=0)
                            {
                                counter+=interval;
                                axis='y';
                            }
                            flagFind=1;
                        }
                        if(strcmpi(menuStage, "findUser")==0 && flagFind==1)
                        {
                            if(findUserForUserName(userName,userOn,routUser) != 1)
                            {
                                counter = 9;
                            }
                            else
                            {
                                counter = 0;
                                userFound = 1;
                            }
                            control=1;
                        }
                    }
                    else if((counter==4 && strcmpi(menuStage, "logIn")==0) || (counter==8 && strcmpi(menuStage, "newUser")==0) || (counter==0 && strcmpi(menuStage, "changePass")==0)) //user password
                    {
                        fflush(stdin);
                        gets(password);
                        if(GetAsyncKeyState(0x0D)) //enter
                        {
                            Sleep(200);
                            counter+=interval;
                            axis='y';
                        }
                    }
                    else if(counter==4 && strcmpi(menuStage, "changePass")==0) //new user password
                    {
                        fflush(stdin);
                        gets(newPassword);
                        if(strcmp(password, userOn[0].password) != 0)
                        {
                            counter = 9;
                        }
                        else
                        {
                            changePass(newPassword,userOn);
                            updateUser(userOn, routUser);
                        }
                    }
                    else if(strcmpi(menuStage, "setDown")==0) //user password confirm
                    {
                        fflush(stdin);
                        gets(confirmPassword);
                        if(strcmp(confirmPassword, userOn[0].password) != 0)
                        {
                            counter = 9;
                            changeState(userOn, 0, routUser);
                        }
                        else
                        {
                            counter = 0;
                        }
                    }
                    flagFind=0;
                }
                if(axis=='x')
                {
                    gotoxy(x+counter,y);
                }
                else if(axis=='y')
                {
                    gotoxy(x,y+counter);
                }
                else
                {
                    gotoxy(x,y);
                }
                //printf("%d",counter);
                //printf("%d",selectedHero[0]);
                //printf("%d",selectedHero[1]);
                //printf("%d",selectedHero[2]);
                //printf("%d",selectedHero[3]);
                //printf("%d",interval);
                //printf("%d",control);
                //printf("%s",menuStage);
            }
            else {};
        };
    };
};

int setOptionMenu(char menu[],int selected,stUser userOn[],stDungeon dungeonOn[], stEntity heroTeam[],int positions[],int dificultMode, int *round, int *cursorOn,
                  char routUser[],char routHeros[], char routDungeon[],int flagLogin,int flagDown,int *userFound, stEntity heroList[],int *result,int  store[], stEntity heroAvailable[],int selectedHero[])
{
    int l=30,c=100;
    char screen[31][101];
    int heroPos = positions[0];
    int enemyPos = positions[1];
    int skillPos = positions[2];
    int userPos=0;

    if (strcmpi(menu, "startMenu") == 0)
    {
        findScreen(l, c,screen, "logIn");
        strcpy(menu,"logIn");
    }
    else if (strcmpi(menu, "activeUser") == 0)
    {
        switch(selected)
        {
        case 0:
            findScreen(l, c,screen, "index");
            strcpy(menu,"index");
            break;
        default:
            findScreen(l, c,screen, "logIn");
            strcpy(menu,"logIn");
            break;
        }
    }
    else if (strcmpi(menu, "invalidUser") == 0)
    {
        findScreen(l, c,screen, "logIn");
        strcpy(menu,"logIn");
    }
    else if (strcmpi(menu, "logIn") == 0)
    {
        switch(selected)
        {
        case 8:
            findScreen(l, c,screen, "login");
            strcpy(menu,"loginValidate");
            break;
        case 10:
            if(flagLogin==1)
            {
                if(flagDown==1)
                {
                    findScreen(l, c,screen, "activeUser");
                    strcpy(menu,"activeUser");
                }
                else
                {
                    findScreen(l, c,screen, "index");
                    strcpy(menu,"index");
                }
            }
            else
            {
                //flagLogin==0
                findScreen(l, c,screen, "invalidUser");
                strcpy(menu,"invalidUser");
            };
            break;
        case 12:
            findScreen(l, c,screen, "newUser");   //nuevo usuario
            strcpy(menu,"newUser");
            break;
        default:
            findScreen(l, c,screen, "logIn");
            strcpy(menu,"logIn");
            break;
        };
    }
    else if (strcmpi(menu, "newUser") == 0)       // nuevo usuario
    {
        switch(selected)
        {
        case 12:
            findScreen(l, c,screen, "newUser");
            strcpy(menu,"loginValidate");
            break;
        case 10:
            if(flagLogin==1)
            {
                findScreen(l, c,screen, "index");
                strcpy(menu,"index");
            }
            else
            {
                findScreen(l, c,screen, "invalidUser");
                strcpy(menu,"invalidUser");
            };
            break;
        case 99:
            findScreen(l, c,screen, "logIn");     //ingresar
            strcpy(menu,"logIn");
            break;
        default:
            break;
        };
    }
    else if (strcmpi(menu, "index") == 0)
    {
        switch(selected)
        {
        case 0:
            findScreen(l, c,screen, "combat");      //continuar/******************************************************************
            strcpy(menu,"combat");
            break;
        case 2:
            findScreen(l, c,screen, "selectTeam");   //nueva partida
            strcpy(menu,"selectTeam");
            break;
        case 4:
            findScreen(l, c,screen, "store");       //tienda
            strcpy(menu,"store");
            break;
        case 6:
            findScreen(l, c,screen, "userPerfil");  //opciones
            strcpy(menu,"userPerfil");
            break;
        case 8:
            findScreen(l, c,screen, "tierList");    //tier list
            strcpy(menu,"tierList");
            break;
        case 10:
            findScreen(l, c,screen, "logIn");       //cambiar user
            strcpy(menu,"logIn");
            break;
        case 12:
            *cursorOn=1;                            //escape (salir del programa)
            break;
        };
    }
    else if (strcmpi(menu, "selectTeam") == 0) ///seleccionar grupo
    {
        //int valids=userOn[0].validsAvailableHeros*3;
        switch(selected)
        {
        case 0:
            if(selectedHero[3]>=0)
            {
                if((selectedHero[0]!=0) && (selectedHero[1]!=0) && (selectedHero[2]!=0))
                {
                    selectedHero[selectedHero[3]]=0;  //setear pos
                    selectedHero[3]++;
                    //system("pause");
                }
                //else if(selectedHero[3]>0)
                else if(selectedHero[3]>0 && ((selectedHero[0]!=0) || (selectedHero[1]!=0) || (selectedHero[2]!=0)))
                {
                    selectedHero[0]=9;  //restar pos
                    selectedHero[3]--;
                }
            }
            break;
        case 3:
            if(selectedHero[3]>=0)
            {
                if((selectedHero[0]!=1) && (selectedHero[1]!=1) && (selectedHero[2]!=1))
                {
                    selectedHero[selectedHero[3]]=1;  //setear pos
                    selectedHero[3]++;
                }
                else if(selectedHero[3]>0 && ((selectedHero[0]!=1) || (selectedHero[1]!=1) || (selectedHero[2]!=1)))
                {
                    selectedHero[selectedHero[3]-1]=9;  //restar pos
                    selectedHero[3]--;
                }
            }
            break;
        case 6://---------------------------//
            if(selectedHero[3]>=0)
            {
                if((selectedHero[0]!=2) && (selectedHero[1]!=2) && (selectedHero[2]!=2))
                {
                    selectedHero[selectedHero[3]]=2;  //setear pos
                    selectedHero[3]++;
                    //system("pause");
                }
                //else if(selectedHero[3]>0)
                else if(selectedHero[3]>0 && ((selectedHero[0]!=2) || (selectedHero[1]!=2) || (selectedHero[2]!=2)))
                {
                    selectedHero[selectedHero[3]-1]=9;  //restar pos
                    selectedHero[3]--;
                    //system("pause");
                }
            }
            break;
        case 9://---------------------------//
            if(selectedHero[3]>=0)
            {
                if((selectedHero[0]!=3) && (selectedHero[1]!=3) && (selectedHero[2]!=3))
                {
                    selectedHero[selectedHero[3]]=3;  //setear pos
                    selectedHero[3]++;
                    //system("pause");
                }
                //else if(selectedHero[3]>0)
                else if(selectedHero[3]>0 && ((selectedHero[0]!=3) || (selectedHero[1]!=3) || (selectedHero[2]!=3)))
                {
                    selectedHero[selectedHero[3]-1]=9;  //restar pos
                    selectedHero[3]--;
                    //system("pause");
                }
            }
            break;
        /*case 16://---------------------------//
            selectedHero[selectedHero[4]]=4;
            selectedHero[4]++;
            break;
        case 20://---------------------------//
            selectedHero[selectedHero[4]]=5;
            selectedHero[4]++;
            break;
        case 24://---------------------------//
            selectedHero[selectedHero[4]]=6;
            selectedHero[4]++;
            break;
        case 28://---------------------------//
            selectedHero[selectedHero[4]]=7;
            selectedHero[4]++;
            break;
        case 32://---------------------------//
            selectedHero[selectedHero[4]]=8;
            selectedHero[4]++;
            break;
        case 36://---------------------------//
            selectedHero[selectedHero[4]]=9;
            selectedHero[4]++;
            break;
        case 40://---------------------------//
            selectedHero[selectedHero[4]]=10;
            selectedHero[4]++;
            break;
        case 44://---------------------------//
            selectedHero[selectedHero[4]]=11;
            selectedHero[4]++;
            break;
        case 48://---------------------------//
            selectedHero[selectedHero[4]]=12;
            selectedHero[4]++;
            break;*/
        case 98:
            findScreen(l, c,screen, "screenMap");
            strcpy(menu,"screenMap");
            break;
        case 99:
            findScreen(l, c,screen, "index");      //Escape (index)
            strcpy(menu,"index");
            break;
        };
        if(selected!=99 && selected!=98)
        {
            findScreen(l, c,screen, "selectTeam"); //Actualizar screen
            strcpy(menu,"selectTeam");
        }
    }
    /*else if (strcmpi(menu, "selectTrinket") == 0) ///equipar trinkets
    {
        switch(selected)
        {
        case 0:
            break;
        case 17:
            break;
        case 34:
            break;
        case 99:
            findScreen(l, c,screen, "index");      //index
            strcpy(menu,"index");
            break;
        };
        findScreen(l,c,screen,"combat");       //nueva partida
        strcpy(menu,"combat");
    }*/
    else if (strcmpi(menu, "setDifficult") == 0) ///nueva partida (seting dificult)
    {
        switch(selected)
        {
        case 0:
            userOn[0].dificult=1;
            break;
        case 17:
            userOn[0].dificult=2;
            break;
        case 34:
            userOn[0].dificult=3;
            break;
        case 99:
            findScreen(l, c,screen, "index");   //escape
            strcpy(menu,"index");
            break;
        };

        userOn[0].dungeonlvl=1;                                             //Reset de nivel
        dungeon(userOn,dungeonOn,routDungeon);                              //reset de dungeon
        saveTeam(selectedHero[0],selectedHero[1],selectedHero[2], userOn, routUser);    // nuevo grupo
        findScreen(l,c,screen,"combat");
        strcpy(menu,"combat");
    }
    else if (strcmpi(menu, "continue") == 0)  ///escape de combate
    {
        switch(selected)
        {
        case 0:
            findScreen(l, c,screen, "combat"); //aceptar
            strcpy(menu,"combat");
            break;
        default:
            findScreen(l, c,screen, "screenMap"); //salir
            strcpy(menu,"screenMap");
            break;
        };
    }
    else if (strcmpi(menu, "store") == 0) //new game (seting dificult)
    {
        switch(selected)
        {
        case 0:
            if(userOn[0].gold>=4000)
            {
                userOn[0].gold=userOn[0].gold-4000;
                int valids = userOn[0].validsAvailableHeros;
                userOn[0].availableHeros[valids]=store[0];
                userOn[0].validsAvailableHeros++;
                updateUser(userOn, routUser);
                findScreen(l, c,screen, "buy");      //index
                strcpy(menu,"buy");
            }
            else
            {
                findScreen(l, c,screen, "enoughMoney");      //index
                strcpy(menu,"enoughMoney");
            }
            break;
        case 6:
            if(userOn[0].gold>=4000)
            {
                userOn[0].gold=userOn[0].gold-4000;
                int valids = userOn[0].validsAvailableHeros;
                userOn[0].availableHeros[valids]=store[1];
                userOn[0].validsAvailableHeros++;
                updateUser(userOn, routUser);
                findScreen(l, c,screen, "buy");      //index
                strcpy(menu,"buy");
            }
            else
            {
                findScreen(l, c,screen, "enoughMoney");      //index
                strcpy(menu,"enoughMoney");
            }
            break;
        case 12:
            if(userOn[0].gold>=4000)
            {
                userOn[0].gold=userOn[0].gold-4000;
                int valids = userOn[0].validsAvailableHeros;
                userOn[0].availableHeros[valids]=store[2];
                userOn[0].validsAvailableHeros++;
                findScreen(l, c,screen, "buy");      //index
                strcpy(menu,"buy");
            }
            else
            {
                findScreen(l, c,screen, "enoughMoney");      //index
                strcpy(menu,"enoughMoney");
            }
            break;
        case 99:
            findScreen(l, c,screen, "index");      //index
            strcpy(menu,"index");
            break;
        };
    }
    else if (strcmpi(menu, "buy") == 0) //new game (seting dificult)
    {
        switch(selected)
        {
        case 0:
            findScreen(l, c,screen, "index");      //index
            strcpy(menu,"index");
            break;
        case 99:
            findScreen(l, c,screen, "index");      //index
            strcpy(menu,"index");
            break;
        };
    }
    else if (strcmpi(menu, "enoughMoney") == 0) //new game (seting dificult)
    {
        switch(selected)
        {
        case 0:
            findScreen(l, c,screen, "index");      //index
            strcpy(menu,"index");
            break;
        case 99:
            findScreen(l, c,screen, "index");      //index
            strcpy(menu,"index");
            break;
        };
    }
    else if (strcmpi(menu, "screenMap") == 0)
    {
        findScreen(l, c,screen, "setDifficult");
        strcpy(menu,"setDifficult");
        switch(selected)
        {
        case 0:
            strcpy(userOn[0].dungeonType,"Las Ruinas");    //ruinas
            break;
        case 5:
            strcpy(userOn[0].dungeonType,"Catacumbas");    //catacumba
            break;
        case 10:
            strcpy(userOn[0].dungeonType,"Cala");          //cala
            break;
        case 15:
            strcpy(userOn[0].dungeonType,"Patio");         //patio
            break;
        case 99:
            findScreen(l, c,screen, "index");
            strcpy(menu,"index");
            break;
        default:
            break;
        };
    }
    else if (strcmpi(menu, "findUser") == 0)
    {
        switch(selected)
        {
        case 0:
            findScreen(l, c,screen, "userPerfil");
            strcpy(menu,"userPerfil");
            break;
        case 37:
            findScreen(l, c,screen, "userPerfil");
            strcpy(menu,"userPerfil");
            break;
        case 9:
            findScreen(l, c,screen, "error");
            strcpy(menu,"error");
            break;
        default:
            break;
        };
    }
    else if (strcmpi(menu, "tierList") == 0)
    {
        findScreen(l, c,screen, "index");
        strcpy(menu,"index");
    }
    else if (strcmpi(menu, "changePass") == 0)
    {
        switch(selected)
        {
        case 4:
            findScreen(l, c,screen, "userPerfil");
            strcpy(menu,"userPerfil");
            break;
        case 9:
            findScreen(l, c,screen, "error");
            strcpy(menu,"error");
        };
    }
    else if (strcmpi(menu, "error") == 0)
    {
        findScreen(l, c,screen, "userPerfil");
        strcpy(menu,"userPerfil");
    }
    else if (strcmpi(menu, "resultsMenu") == 0)   ///RESULTADOS DE COMBATE
    {
        if(userOn[0].dungeonlvl==3)
        {
            userOn[0].dungeonlvl=1;
            findScreen(l, c,screen, "screenMap");
            strcpy(menu,"screenMap");
        }
        else
        {
            userOn[0].dungeonlvl++;
            findScreen(l, c,screen, "combat");
            strcpy(menu,"combat");
        }

        dungeon(userOn,dungeonOn,routDungeon);
        updateUser(userOn, routUser);
    }
    else if (strcmpi(menu, "succesfullSetDown") == 0)
    {
        if(userOn[0].type==0)
        {
            findScreen(l, c,screen, "logIn");
            strcpy(menu,"logIn");
        }
        else
        {
            findScreen(l, c,screen, "userPerfil");
            strcpy(menu,"userPerfil");
        }
        if(*userFound==0)
        {
            changeState(userOn,0,routUser);
        }
        else
        {
            changeState(userOn,1,routUser);
        }
        *userFound=0;
    }
    else if (strcmpi(menu, "setDown") == 0)
    {
        switch(selected)
        {
        case 0:
            findScreen(l, c,screen, "logIn");
            strcpy(menu,"logIn");
            break;
        case 9:
            findScreen(l, c,screen, "error");
            strcpy(menu,"error");
        };
    }
    else if (strcmpi(menu, "exitCombat") == 0)
    {
        switch(selected)
        {
        case 9:
            findScreen(l, c,screen, "index");
            strcpy(menu,"index");
            break;
        case 0:
            findScreen(l, c,screen, "index");
            strcpy(menu,"index");
        };
    }
    else if (strcmpi(menu, "userPerfil") == 0)
    {

        switch(selected)
        {
        case 0:
            if(*userFound==1)
            {
                findScreen(l, c,screen, "succesfullSetDown");  ///Baja de admin
                strcpy(menu,"succesfullSetDown");
            }
            else
            {
                findScreen(l, c,screen, "changePass");  ///Cambiar PassWord
                strcpy(menu,"changePass");
            }
            break;
        case 16:
            findScreen(l, c,screen, "findUser");  ///buscar usuario
            strcpy(menu,"findUser");
            break;
        case 32:
            if(userOn[0].type==1)
            {
                findScreen(l, c,screen, "succesfullSetDown");  ///Baja de admin
                strcpy(menu,"succesfullSetDown");
            }
            else
            {
                findScreen(l, c,screen, "setDown");  ///Solicitar baja de usuario
                strcpy(menu,"setDown");
            }
            break;
        case 99:
            findScreen(l, c,screen, "index");
            strcpy(menu,"index");
            *userFound=0;
            break;
        };
    }
    else if (strcmpi(menu, "confirm") == 0)
    {
        switch(selected)
        {
        case 0:
            findScreen(l, c,screen, "combat");
            strcpy(menu,"combat");
            break;
        default:
            findScreen(l, c,screen, "index");
            strcpy(menu,"index");
            break;
        };
    }
    else if (strcmpi(menu, "combat") == 0)
    {
        switch(selected)
        {
        case 0: //skill 1
            skillPos=0;
            break;
        case 8: //skill 3
            skillPos=1;
            break;
        case 16: //skill 3
            skillPos=2;
            break;
        case 24: //enemigo 1
            enemyPos=0;
            break;
        case 37: //enemigo 2
            enemyPos=1;
            break;
        case 50: //enemigo 3
            enemyPos=2;
            break;
        case 15: //ejecutar accion
            ///funcion de accion
            action(heroPos,heroTeam,enemyPos,dungeonOn[0].enemyTeam,skillPos, dificultMode);

            ///Comprobar estado de combate
            if(stillAliveTeam(heroTeam, dungeonOn)==0)
            {
                heroPos = passTurn(heroTeam,heroPos+1, dificultMode); //pasar turno de heroe

                if(heroPos==0)
                {
                    *round++;
                    for(int i=0; i<3; i++)
                    {
                        if(stillAliveTeam(heroTeam, dungeonOn)==0) //Continuar batalla
                        {
                            if(dungeonOn[0].enemyTeam[i].hp>0)
                            {
                                enemyPos=i;
                                int posHero;
                                do
                                {
                                    posHero=rand()%3;
                                }
                                while(heroTeam[posHero].hp<=0);

                                int skill = rand()%101;

                                if(skill < dungeonOn[0].enemyTeam[i].skills[0].prob)
                                {
                                    action(i,dungeonOn[0].enemyTeam, posHero,heroTeam,0,dificultMode);
                                }
                                else
                                {
                                    action(i,dungeonOn[0].enemyTeam, posHero,heroTeam,1,dificultMode);
                                };
                                Sleep(1200);
                                passTurn(dungeonOn[0].enemyTeam,i+1, dificultMode);
                            }
                            system("cls");
                        }
                        if(stillAliveTeam(heroTeam, dungeonOn)==0)
                        {
                            findScreen(l, c,screen, "combat");
                            strcpy(menu,"combat");
                        }
                        else if(stillAliveTeam(heroTeam, dungeonOn)==1) //VICTORIA
                        {
                            findScreen(l, c,screen, "resultsMenu");
                            strcpy(menu, "resultsMenu");
                            *result=1;
                        }
                        else if(stillAliveTeam(heroTeam, dungeonOn)==2) //DERROTA
                        {
                            findScreen(l, c,screen, "resultsMenu");
                            strcpy(menu, "resultsMenu");
                            *result=2;
                        }
                        showScreen(l, c, screen, userOn, dungeonOn, menu, heroTeam,heroPos,enemyPos,skillPos,userPos, routUser, heroList, *round, routDungeon, *userFound, store, heroAvailable,selectedHero);
                    };
                    system("cls");
                    enemyPos=0;
                    heroPos=0;
                    heroPos = passTurn(heroTeam,heroPos, dificultMode); //pasar turno de heroe
                }
            }
            if(*result==0)
            {
                findScreen(l, c,screen, "combat");
                strcpy(menu,"combat");
            }
            if(stillAliveTeam(heroTeam, dungeonOn)==0)
            {
                findScreen(l, c,screen, "combat");
                strcpy(menu,"combat");
            }
            else if(stillAliveTeam(heroTeam, dungeonOn)==1) //VICTORIA
            {
                findScreen(l, c,screen, "resultsMenu");
                strcpy(menu, "resultsMenu");
                *result=1;
            }
            else if(stillAliveTeam(heroTeam, dungeonOn)==2) //DERROTA
            {
                findScreen(l, c,screen, "resultsMenu");
                strcpy(menu, "resultsMenu");
                *result=2;
            }
            break;
        case 99:
            findScreen(l, c,screen, "exitCombat");
            strcpy(menu,"exitCombat");
            break;
        };
        if(*result==0 && selected!=99)
        {
            findScreen(l, c,screen, "combat");
            strcpy(menu,"combat");
        }
    }
    if(*userFound==1)
    {
        userPos=1;
    }

    showScreen(l, c, screen, userOn, dungeonOn, menu, heroTeam,heroPos,enemyPos,skillPos,userPos,routUser, heroList, *round, routDungeon, *userFound,store, heroAvailable, selectedHero);

    positions[0] = heroPos;
    positions[1] = enemyPos;
    positions[2] = skillPos;
    return heroPos;
};
int intleng(int num)
{
    int i=1, interval=10, flag=0;
    while(i<10&&flag==0)
    {
        if(num >= interval)
        {
            interval *= 10;
            i++;
        }
        else
        {
            flag=1;
        };
    };
    return i;
}
void printInt(int num,char color[])
{
    if(num<0)
    {
        num=0;
    }
    if(strcmpi(color,"RED")==0)
    {
        printf(":" RED_T "%d" RESET_COLOR, num);
    }
    else if(strcmpi(color,"BLUE")==0)
    {
        printf(":" BLUE_T "%d" RESET_COLOR, num);
    }
    else if(strcmpi(color,"YELLOW")==0)
    {
        printf(":" YELLOW_T "%d" RESET_COLOR, num);
    }
    else if(strcmpi(color,"GREEN")==0)
    {
        printf(":" GREEN_T "%d" RESET_COLOR, num);
    }
    else if(strcmpi(color,"CYAN")==0)
    {
        printf(":" CYAN_T "%d" RESET_COLOR, num);
    }
    else if(strcmpi(color,"MAGENTA")==0)
    {
        printf(":" MAGENTA_T "%d" RESET_COLOR, num);
    }
    else
    {
        printf(":%d",num);
    }
    int space=0, i=0;
    if(intleng(num)==1)
    {
        space=3;
    }
    else if(intleng(num)==2)
    {
        space=2;
    }
    else if(intleng(num)==3)
    {
        space=1;
    }
    else
    {
        space=0;
    }
    for(i=0; i<space; i++)
    {
        printf(" ");
    }
}
void showContEntity(stEntity entity)
{
    printf(" ");
    if(entity.heroMonster==1)
    {
        ///contStun
        if(entity.contStun > 0)
        {
            printf(YELLOW_T"%d",entity.contStun);
        }
        else
        {
            printf(" ");
        }
        ///contPoison
        if(entity.contPoison > 0)
        {
            printf(GREEN_T"%d",entity.contPoison);
        }
        else
        {
            printf(" ");
        }
        ///contBleed
        if(entity.contBleed > 0)
        {
            printf(RED_T"%d",entity.contBleed);
        }
        else
        {
            printf(" ");
        }
        ///contArmor
        if(entity.contArmor > 0)
        {
            printf(BLUE_T"%d",entity.contArmor);
        }
        else
        {
            printf(" ");
        }
    }
    else
    {
        ///contArmor
        if(entity.contArmor > 0)
        {
            printf(BLUE_T"%d",entity.contArmor);
        }
        else
        {
            printf(" ");
        }
        ///contBleed
        if(entity.contBleed > 0)
        {
            printf(RED_T"%d",entity.contBleed);
        }
        else
        {
            printf(" ");
        }
        ///contPoison
        if(entity.contPoison > 0)
        {
            printf(GREEN_T"%d",entity.contPoison);
        }
        else
        {
            printf(" ");
        }
        ///contStun
        if(entity.contStun > 0)
        {
            printf(YELLOW_T"%d",entity.contStun);
        }
        else
        {
            printf(" ");
        }
    }
    printf(RESET_COLOR);
};

void showScreen(int line, int column, char screen[line][column],stUser userOn[],stDungeon dungeonOn[], char menu[], stEntity heroTeam[],int heroPos, int enemyPos,
                int skillPos, int userPos, char routUser[], stEntity heroList[], int round, char routDungeon[], int userFound, int  store[], stEntity heroAvailable[],int selectedHero[])
{
    int l=0,c=0,i=0, flag=0;
    while(l<line)
    {
        flag=0;
        for(c=0; c<column && flag==0; c++)
        {
            if(screen[l][c]=='B')  ///------------------------------GRAFICACION DE INTERFACE
            {
                int f=c;
                f++;
                printf(YELLOW_T);
                if(screen[l][f]=='9')
                {
                    while(screen[l][f]=='9')
                    {
                        printf("%c",205);
                        c++;
                        f++;
                    }
                    for(i=0; i<4; i++)
                    {
                        printf("%c",205);
                    };
                    //c-=1;c++;
                }
                else if(screen[l][f]=='8')
                {
                    printf("%c",186);
                    c++;
                }
                else if(screen[l][f]=='B')
                {
                    printf("           %c" RESET_COLOR "||",186);
                    flag=1;
                    c++;
                }
                else if(screen[l][f]=='7')
                {
                    printf("%c",201);
                    c++;
                }
                else if(screen[l][f]=='6')
                {
                    printf("%c",187);
                    c++;
                }
                else if(screen[l][f]=='5')
                {
                    printf("%c",200);
                    c++;
                }
                else if(screen[l][f]=='4')
                {
                    printf("%c",188);
                    c++;
                }
                else if(screen[l][f]=='3')
                {
                    printf("%c",203);
                    c++;
                }
                else if(screen[l][f]=='2')
                {
                    printf("%c",202);
                    c++;
                }
                else if(screen[l][f]=='1')
                {
                    printf("%c",184);
                    c++;
                }
                else
                {
                    printf(RESET_COLOR"%c",screen[l][c]);
                }
                //c++;
                printf(RESET_COLOR);
            }
            else if(screen[l][c]=='S')  ///------------Interface SKILL-1
            {
                int f=c;
                f++;
                if(skillPos==0)
                {
                    printf(YELLOW_T);
                }
                else
                {
                    printf(WHITE_T);
                }
                if(screen[l][f]=='9')
                {
                    while(screen[l][f]=='9')
                    {
                        printf("%c",205);
                        c++;
                        f++;
                    }
                    for(i=0; i<4; i++)
                    {
                        printf("%c",205);
                    };
                    //c-=1;c++;
                }
                else if(screen[l][f]=='8')
                {
                    printf("%c",186);
                    c++;
                }
                else if(screen[l][f]=='7')
                {
                    printf("%c",201);
                    c++;
                }
                else if(screen[l][f]=='6')
                {
                    printf("%c",187);
                    c++;
                }
                else if(screen[l][f]=='5')
                {
                    printf("%c",200);
                    c++;
                }
                else if(screen[l][f]=='4')
                {
                    printf("%c",188);
                    c++;
                }
                else
                {
                    printf(RESET_COLOR"%c",screen[l][c]);
                }
                //c++;
                printf(RESET_COLOR);
            }
            else if(screen[l][c]=='K')  ///------------Interface SKILL-2
            {
                int f=c;
                f++;
                if(skillPos==1)
                {
                    printf(YELLOW_T);
                }
                else
                {
                    printf(WHITE_T);
                }
                if(screen[l][f]=='9')
                {
                    while(screen[l][f]=='9')
                    {
                        printf("%c",205);
                        c++;
                        f++;
                    }
                    for(i=0; i<4; i++)
                    {
                        printf("%c",205);
                    };
                }
                else if(screen[l][f]=='8')
                {
                    printf("%c",186);
                    c++;
                }
                else if(screen[l][f]=='7')
                {
                    printf("%c",201);
                    c++;
                }
                else if(screen[l][f]=='6')
                {
                    printf("%c",187);
                    c++;
                }
                else if(screen[l][f]=='5')
                {
                    printf("%c",200);
                    c++;
                }
                else if(screen[l][f]=='4')
                {
                    printf("%c",188);
                    c++;
                }
                else
                {
                    printf(RESET_COLOR"%c",screen[l][c]);
                }
                //c++;
                printf(RESET_COLOR);
            }
            else if(screen[l][c]=='L')  ///------------Interface SKILL-3
            {
                int f=c;
                f++;
                if(skillPos==2)
                {
                    printf(YELLOW_T);
                }
                else
                {
                    printf(WHITE_T);
                }
                if(screen[l][f]=='9')
                {
                    c++;
                    while(screen[l][f]=='9')
                    {
                        printf("%c",205);
                        c++;
                        f++;
                    }
                    for(i=0; i<4; i++)
                    {
                        printf("%c",205);
                    };
                    c-=1;
                }
                else if(screen[l][f]=='8')
                {
                    printf("%c",186);
                    c++;
                }
                else if(screen[l][f]=='7')
                {
                    printf("%c",201);
                    c++;
                }
                else if(screen[l][f]=='6')
                {
                    printf("%c",187);
                    c++;
                }
                else if(screen[l][f]=='5')
                {
                    printf("%c",200);
                    c++;
                }
                else if(screen[l][f]=='4')
                {
                    printf("%c",188);
                    c++;
                }
                else
                {
                    printf("%c",screen[l][c]);
                }
                printf(RESET_COLOR);
            }
            else if(screen[l][c]=='Z')  ///-----------------------------SELECCION DE OBJETIVO
            {
                int f=c;
                f++;
                //c+=strlen("|-----|");
                c+=2;
                if(screen[l][f]=='1') ///enemy 1
                {
                    if(enemyPos==0)
                    {
                        printf(RED_T);
                        printf("%c%c%c%c%c%c%c",204,205,205,205,205,205,185);
                        //printf(RESET_COLOR);
                        c+=4;
                    }
                    else
                    {
                        printf("   ");
                    }
                }
                else if(screen[l][f]=='2') ///enemy 2
                {
                    if(enemyPos==1)
                    {
                        printf(RED_T);
                        printf("%c%c%c%c%c%c%c",204,205,205,205,205,205,185);
                        //printf(RESET_COLOR);
                        c+=4;
                    }
                    else
                    {
                        printf("   ");
                    }
                }
                else if(screen[l][f]=='3') ///enemy 3
                {
                    if(enemyPos==2)
                    {
                        printf(RED_T);
                        printf("%c%c%c%c%c%c%c",204,205,205,205,205,205,185);
                        //printf(RESET_COLOR);
                        c+=4;
                    }
                    else
                    {
                        printf("   ");
                    }
                }
                else if(screen[l][f]=='4') ///hero 1
                {
                    if(heroPos==0)
                    {
                        printf(CYAN_T);
                        printf("%c%c%c%c%c%c%c",204,205,205,205,205,205,185);
                        //printf(RESET_COLOR);
                        c+=4;
                    }
                    else
                    {
                        printf("   ");
                    }
                }
                else if(screen[l][f]=='5') ///hero 2
                {
                    if(heroPos==1)
                    {
                        printf(CYAN_T);
                        printf("%c%c%c%c%c%c%c",204,205,205,205,205,205,185);
                        //printf(RESET_COLOR);
                        c+=4;
                    }
                    else
                    {
                        printf("   ");
                    }
                }
                else if(screen[l][f]=='6') ///hero 3
                {
                    if(heroPos==2)
                    {
                        printf(CYAN_T);
                        printf("%c%c%c%c%c%c%c",204,205,205,205,205,205,185);
                        //printf(RESET_COLOR);
                        c+=4;
                    }
                    else
                    {
                        printf("   ");
                    }
                }
                printf(RESET_COLOR);
            }
            else if (screen[l][c]=='U')
            {
                int f=c;
                f++;
                if(screen[l][f]=='i')
                {
                    if(userOn[0].type==1)
                    {
                        f++;
                        if(userFound==0)
                        {
                            if(screen[l][f]=='1')
                            {
                                printf(".------------.");
                                c+=strlen("------------.");
                            }
                            else if(screen[l][f]=='2')
                            {
                                printf("|Buscar  User|");
                                c+=strlen("------------.");
                            }
                            else if(screen[l][f]=='3')
                            {
                                printf(".------------.");
                                c+=strlen("------------.");
                            }
                            else if(screen[l][f]=='7')
                            {
                                printf(".------------.");
                                c+=strlen("------------.");
                            }
                            else if(screen[l][f]=='8')
                            {
                                printf("|Cambiar pass|");
                                c+=strlen("------------.");
                            }
                            else if(screen[l][f]=='9')
                            {
                                printf(".------------.");
                                c+=strlen("------------.");
                            }
                            {
                                printf("   ");
                                c+=2;
                            }
                        }
                        else
                        {
                            if(screen[l][f]=='4')
                            {
                                printf(".------------.");
                                c+=strlen("------------.");
                            }
                            else if(screen[l][f]=='5')
                            {
                                printf("|  Alta/baja |");
                                c+=strlen("------------.");
                            }
                            else if(screen[l][f]=='6')
                            {
                                printf(".------------.");
                                c+=strlen("------------.");
                            }
                            else
                            {
                                printf("   ");
                                c+=2;
                            }
                        }
                    }
                    if(userOn[0].type==0)
                    {
                        f++;
                        if(screen[l][f]=='4')
                        {
                            printf(".------------.");
                            c+=strlen("------------.");
                        }
                        else if(screen[l][f]=='5')
                        {
                            printf("|  Dar baja  |");
                            c+=strlen("------------.");
                        }
                        else if(screen[l][f]=='6')
                        {
                            printf(".------------.");
                            c+=strlen("------------.");
                        }
                        else if(screen[l][f]=='7')
                        {
                            printf(".------------.");
                            c+=strlen("------------.");
                        }
                        else if(screen[l][f]=='8')
                        {
                            printf("|Cambiar pass|");
                            c+=strlen("------------.");
                        }
                        else if(screen[l][f]=='9')
                        {
                            printf(".------------.");
                            c+=strlen("------------.");
                        }
                        else
                        {
                            printf("   ");
                            c+=2;
                        }
                    }
                }
                else
                {
                    printf("%c",screen[l][c]);
                }
            }
            else if(screen[l][c]=='T')///----------------------------------SELECCION DE GRUPO
            {
                char selectTeam[3][100]=                 ///array de heroe dinamico
                {
                    {"|||   .--------------------------------------------------------------------------------------.   |||"},
                    {"|||   | n                  |  h |  d |  e   |   a     |  g     |   s     |   p    |   b      |   |||"},
                    {"|||   .--------------------------------------------------------------------------------------.   |||"},
                };
                int f=c+1;
                if(screen[l][f]=='1')
                {
                    int r=0, i=0;
                    while(i<userOn[0].validsAvailableHeros)
                    {
                        while(r<3)
                        {
                            for(int q=0; q<column; q++)
                            {
                                if((i==selectedHero[0]) || (i==selectedHero[1]) || (i==selectedHero[2]))
                                {
                                    printf(YELLOW_T);
                                }
                                if(selectTeam[r][q]=='n')
                                {
                                    printf("%s",heroAvailable[i].name);
                                    q+=strlen(heroAvailable[i].name)-1;
                                }
                                else if(selectTeam[r][q]=='h')
                                {
                                    printInt(heroAvailable[i].hp,"GREEN");
                                    q+=4;
                                }
                                else if(selectTeam[r][q]=='d')
                                {
                                    printInt(heroAvailable[i].damageMax,"RED");
                                    q+=4;
                                }
                                else if(selectTeam[r][q]=='e')
                                {
                                    printInt(heroAvailable[i].heal,"GREEN");
                                    q+=4;
                                }
                                else if(selectTeam[r][q]=='a')
                                {
                                    printInt(heroAvailable[i].armor,"BLUE");
                                    q+=4;
                                }
                                else if(selectTeam[r][q]=='g')
                                {
                                    printInt(heroAvailable[i].dodge,"CYAN");
                                    q+=4;
                                }
                                else if(selectTeam[r][q]=='s')
                                {
                                    printInt(heroAvailable[i].stunResist,"YELLOW");
                                    q+=4;
                                }
                                else if(selectTeam[r][q]=='p')
                                {
                                    printInt(heroAvailable[i].poisonResist,"GREEN");
                                    q+=4;
                                }
                                else if(selectTeam[r][q]=='b')
                                {
                                    printInt(heroAvailable[i].bleedResist,"RED");
                                    q+=4;
                                }
                                else
                                {
                                    printf("%c",selectTeam[r][q]);
                                }
                                printf(RESET_COLOR);
                            }
                            if(r<2)
                            {
                                printf("\n");//salto de linea de array
                            }
                            r++;
                        }
                        if(i<userOn[0].validsAvailableHeros-1)
                        {
                            printf("\n");//salto de linea entre arrays
                        }
                        r++;
                        r=0;
                        i++;
                        if(i<7)//Si los validos del user son mayores a 7, deja de restar columnas a partir del heroe 7
                        {
                            l+=3;
                        }
                    }
                    flag=1;
                    /*while((screen[l][f]=='1')||(screen[l][f]=='2')||(screen[l][f]=='3')||(screen[l][f]=='4')||(screen[l][f]=='5')||(screen[l][f]=='6'))
                    {
                        if(screen[l][f]=='1')
                        {
                            printf("%c",201);
                        }
                        else if(screen[l][f]=='2')
                        {
                            printf("%c",205);
                        }
                        else if(screen[l][f]=='3')
                        {
                            printf("%c",187);
                        }
                        else if(screen[l][f]=='4')
                        {
                            printf("%c",200);
                        }
                        else if(screen[l][f]=='5')
                        {
                            printf("%c",188);
                        }
                        else if(screen[l][f]=='6')
                        {
                            printf("%c",186);
                        }
                        f++;
                        c++;
                    }*/
                }
                else
                {
                    printf("%c", screen[l][c]);
                }
            }
            else if(screen[l][c]=='R')///----------------------------------RONDA
            {
                int f=c+1;
                if(screen[l][f]=='d')
                {
                    c+=3;
                    printInt(round,"NONE");
                }
                else
                {
                    printf("%c", screen[l][c]);
                }
            }
            else if(screen[l][c]==':') ///---------------------------------ESTADISTICAS DE ENTIDADES
            {
                int f=c+1;
                if(screen[l][f]=='h') ///----------------Heroe
                {
                    f++;
                    c+=4;
                    if(screen[l][f]=='h')/// hp - hl - ht
                    {
                        f++;
                        if(screen[l][f]=='p')
                        {
                            printInt(heroTeam[heroPos].hp,"RED");
                        }
                        else if(screen[l][f]=='l')
                        {
                            printInt(heroTeam[heroPos].heal,"GREEN"); ///heal
                        }
                        else if(screen[l][f]=='t')///hit
                        {
                            printInt(heroTeam[heroPos].hit, "NONE");
                        }
                        else if(screen[l][f]=='1')
                        {
                            printInt(heroTeam[0].hp, "GREEN");
                        }
                        else if(screen[l][f]=='2')
                        {
                            printInt(heroTeam[1].hp, "GREEN");
                        }
                        else if(screen[l][f]=='3')
                        {
                            printInt(heroTeam[2].hp, "GREEN");
                        }
                    }
                    else if(screen[l][f]=='n')
                    {
                        f++;
                        if(screen[l][f]=='m')
                        {
                            printf(CYAN_T"%s "RESET_COLOR,heroTeam[heroPos].name);
                            //printf("%s ",heroTeam[heroPos].name); ///name
                            c+=strlen(heroTeam[heroPos].name)-4;
                        }
                        else if(screen[l][f]=='1')
                        {
                            printf(CYAN_T"%s "RESET_COLOR,heroTeam[0].name);
                            //printf("%s ",heroTeam[0].name); ///name
                            c+=strlen(heroTeam[0].name)-4;
                        }
                        else if(screen[l][f]=='2')
                        {
                            printf(CYAN_T"%s "RESET_COLOR,heroTeam[1].name);
                            //printf("%s ",heroTeam[1].name); ///name
                            c+=strlen(heroTeam[1].name)-4;
                        }
                        else if(screen[l][f]=='3')
                        {
                            printf(CYAN_T"%s "RESET_COLOR,heroTeam[2].name);
                            //printf("%s ",heroTeam[2].name); ///name
                            c+=strlen(heroTeam[2].name)-4;
                        }
                    }
                    else if(screen[l][f]=='a')
                    {
                        printInt(heroTeam[heroPos].armor, "BLUE");///armor
                    }
                    else if(screen[l][f]=='d')
                    {
                        printInt(heroTeam[heroPos].dodge, "NONE"); ///dodge
                    }
                    else if(screen[l][f]=='p')
                    {
                        printInt(heroTeam[heroPos].poisonResist,"GREEN"); ///poisonResist
                    }
                    else if(screen[l][f]=='b')
                    {
                        printInt(heroTeam[heroPos].bleedResist, "RED"); ///bleedResist
                    }
                    else if(screen[l][f]=='s')
                    {
                        printInt(heroTeam[heroPos].stunResist, "YELLOW"); ///stunResist
                    }
                    else if(screen[l][f]=='c')
                    {
                        f++;
                        if(screen[l][f]=='3')
                        {
                            showContEntity(heroTeam[2]);
                        }
                        else if(screen[l][f]=='2')
                        {
                            showContEntity(heroTeam[1]);
                        }
                        else if(screen[l][f]=='1')
                        {
                            showContEntity(heroTeam[0]);
                        }
                    }
                }
                else if(screen[l][f]=='m') ///----------------------------------Monstruo
                {
                    f++;
                    //printf("%d",enemyPos);
                    //system("pause");
                    c+=4;
                    if(screen[l][f]=='h')
                    {
                        f++;
                        if(screen[l][f]=='p')
                        {
                            if(enemyPos<4)
                            {
                                printInt(dungeonOn[0].enemyTeam[enemyPos].hp, "RED"); ///hp
                            }
                            else
                            {
                                printInt(0, "NONE"); ///Sin seleccion
                            }
                        }
                        else if(screen[l][f]=='l')
                        {
                            if(enemyPos<4)
                            {

                                printInt(dungeonOn[0].enemyTeam[enemyPos].heal, "NONE"); ///heal
                            }
                            else

                            {
                                printInt(0, "NONE"); ///Sin seleccion
                            }
                        }
                        else if(screen[l][f]=='t')
                        {
                            if(enemyPos<4)
                            {

                                printInt(dungeonOn[0].enemyTeam[enemyPos].hit, "NONE"); ///hit

                            }
                            else

                            {
                                printInt(0, "NONE"); ///Sin seleccion
                            }
                        }
                    }
                    else if(screen[l][f]=='a')
                    {
                        if(enemyPos<4)
                        {
                            printInt(dungeonOn[0].enemyTeam[enemyPos].armor, "BLUE");///armorelse
                        }
                        else
                        {
                            printInt(0, "NONE"); ///Sin seleccion
                        }
                    }
                    else if(screen[l][f]=='p')
                    {
                        if(enemyPos<4)
                        {
                            printInt(dungeonOn[0].enemyTeam[enemyPos].poisonResist, "GREEN"); ///poisonResist
                        }
                        else
                        {
                            printInt(0, "NONE"); ///Sin seleccion
                        }
                    }
                    else if(screen[l][f]=='d')
                    {
                        if(enemyPos<4)
                        {
                            printInt(dungeonOn[0].enemyTeam[enemyPos].dodge, "NONE"); ///dodge
                        }
                        else
                        {
                            printInt(0, "NONE"); ///Sin seleccion
                        }
                    }
                    else if(screen[l][f]=='b')
                    {
                        if(enemyPos<4)
                        {
                            printInt(dungeonOn[0].enemyTeam[enemyPos].bleedResist, "RED"); ///bleedResist
                        }
                        else
                        {
                            printInt(0, "NONE");  ///Sin seleccion
                        }
                    }
                    else if(screen[l][f]=='s')
                    {
                        if(enemyPos<4)
                        {
                            printInt(dungeonOn[0].enemyTeam[enemyPos].stunResist, "YELLOW"); ///stunResist
                        }
                        else
                        {
                            printInt(0, "NONE"); ///Sin seleccion
                        }
                    }
                    else if(screen[l][f]=='n')
                    {
                        if(enemyPos<4)
                        {
                            printf("%s",dungeonOn[0].enemyTeam[enemyPos].name); ///name
                            c+=strlen(dungeonOn[0].enemyTeam[enemyPos].name)-5;
                        }
                        else
                        {
                            printf("      Monster"); ///name   ///Sin seleccion
                            c+=strlen("      Monster")-5;
                        }
                    }
                    else if(screen[l][f]=='m')
                    {
                        f++;
                        if(screen[l][f]=='1')                                ///vida de enemigos en combate
                        {
                            printInt(dungeonOn[0].enemyTeam[0].hp, "GREEN"); ///enemigo 1
                        }
                        else if(screen[l][f]=='2')
                        {
                            printInt(dungeonOn[0].enemyTeam[1].hp, "GREEN"); ///enemigo 2
                        }
                        else if(screen[l][f]=='3')
                        {
                            printInt(dungeonOn[0].enemyTeam[2].hp, "GREEN"); ///enemigo 3
                        }
                    }
                    else if(screen[l][f]=='c')
                    {
                        f++;
                        if(screen[l][f]=='1')                          ///debuf de enemigos
                        {
                            showContEntity(dungeonOn[0].enemyTeam[0]); ///enemigo 1
                        }
                        else if(screen[l][f]=='2')
                        {
                            showContEntity(dungeonOn[0].enemyTeam[1]); ///enemigo 2
                        }
                        else if(screen[l][f]=='3')
                        {
                            showContEntity(dungeonOn[0].enemyTeam[2]); ///enemigo 3
                        }
                    }

                }
                else if(screen[l][f]=='u') ///----------------------------------usuario
                {
                    f++;
                    c+=3;
                    if(screen[l][f]=='i')///idUser
                    {
                        f++;
                        if(screen[l][f]=='d')
                        {
                            printInt(userOn[userPos].idUser, "CYAN"); ///idUser
                        }
                    }
                    else if(screen[l][f]=='p')
                    {
                        printInt(userOn[userPos].records, "CYAN"); ///progress
                    }
                    else if(screen[l][f]=='s')
                    {
                        if (userOn[userPos].active==1)
                        {
                            printf(CYAN_T":Activo"RESET_COLOR);
                            //printf(":Activo");
                            c+=strlen(":Activo")-5;
                        }
                        else
                        {
                            printf(RED_T":Inactivo"RESET_COLOR);
                            //printf(":Inactivo");
                            c+=strlen(":Inactivo")-5;
                        }
                    }
                    else if(screen[l][f]=='d')
                    {
                        f++;
                        if(screen[l][f]=='f')
                        {
                            if(userOn[userPos].dificult==1)///dificultad
                            {
                                printf(GREEN_T":Normal"RESET_COLOR);
                                c+=strlen(":Normal")-5;
                            }
                            else if(userOn[userPos].dificult==2)
                            {
                                printf(YELLOW_T":Dificil"RESET_COLOR);
                                c+=strlen(":Dificil")-5;
                            }
                            else
                            {
                                printf(RED_T":Luna de sangre"RESET_COLOR);
                                c+=strlen(":Luna de sangre")-5;
                            }
                        }
                        else if(screen[l][f]=='t')
                        {
                            //printf(":%s",userOn[userPos].dungeonType); ///ultimo dungeon
                            printf(":");
                            printf(RED_T"%s"RESET_COLOR,userOn[userPos].dungeonType); ///ultimo dungeon
                            c+=strlen(userOn[userPos].dungeonType)-4;
                        }
                        else
                        {
                            printInt(userOn[userPos].dungeonlvl, "RED"); ///dungeonlvl
                        }
                    }
                    else if(screen[l][f]=='g')
                    {
                        f++;
                        if(screen[l][f]=='l')
                        {
                            c++;
                        }
                        printInt(userOn[userPos].gold, "YELLOW"); ///oro
                    }
                    else if(screen[l][f]=='n')
                    {
                        f++;
                        if(screen[l][f]=='m')
                        {
                            //printf(":%s",userOn[userPos].name); ///name
                            printf(BLUE_T"%s"RESET_COLOR,userOn[userPos].name); ///name
                            c+=strlen(userOn[userPos].name)-4;
                        }
                        else if(screen[l][f]=='n')
                        {
                            //printf(":%s",userOn[userPos].name); ///name
                            printf(BLUE_T"%s"RESET_COLOR,userOn[userPos].name); ///name
                            c+=strlen(userOn[userPos].name)-5;
                        }
                    }
                    else {};
                }
                else if(screen[l][f]=='d') ///----------------------------------DUNGEON
                {
                    stDungeon dungeons[15];
                    searchListDungeons(dungeons, routDungeon);;
                    f++;
                    if(screen[l][f]=='n') ///Tipo de dungeon
                    {
                        printf("%s",dungeonOn[0].type);
                        c+=strlen(dungeonOn[0].type)-1;
                    }
                    else if(screen[l][f]=='1')
                    {
                        f++;
                        if(screen[l][f]=='n')
                        {
                            printf("%s",dungeons[0].type);
                            c+=strlen(dungeons[0].type)-1;
                        }
                        else if(screen[l][f]=='m')
                        {
                            f++;
                            if(screen[l][f]=='1')
                            {
                                printf("%s",dungeons[0].enemyTeam[0].name);
                                c+=strlen(dungeons[0].enemyTeam[0].name)-1;
                            }
                            else if(screen[l][f]=='2')
                            {
                                printf("%s",dungeons[0].enemyTeam[1].name);
                                c+=strlen(dungeons[0].enemyTeam[1].name)-1;
                            }
                            else if(screen[l][f]=='3')
                            {
                                printf("%s",dungeons[0].enemyTeam[2].name);
                                c+=strlen(dungeons[0].enemyTeam[2].name)-1;
                            }
                        }
                    }
                    else if(screen[l][f]=='2')
                    {
                        f++;
                        if(screen[l][f]=='n')
                        {
                            printf("%s",dungeons[4].type);
                            c+=strlen(dungeons[4].type)-1;
                        }
                        else if(screen[l][f]=='m')
                        {
                            f++;
                            if(screen[l][f]=='1')
                            {
                                printf("%s",dungeons[4].enemyTeam[0].name);
                                c+=strlen(dungeons[4].enemyTeam[0].name)-1;
                            }
                            else if(screen[l][f]=='2')
                            {
                                printf("%s",dungeons[4].enemyTeam[1].name);
                                c+=strlen(dungeons[4].enemyTeam[1].name)-1;
                            }
                            else if(screen[l][f]=='3')
                            {
                                printf("%s",dungeons[4].enemyTeam[2].name);
                                c+=strlen(dungeons[4].enemyTeam[2].name)-1;
                            }
                        }
                    }
                    else if(screen[l][f]=='3')
                    {
                        f++;
                        if(screen[l][f]=='n')
                        {
                            printf("%s",dungeons[7].type);
                            c+=strlen(dungeons[7].type)-1;
                        }
                        else if(screen[l][f]=='m')
                        {
                            f++;
                            if(screen[l][f]=='1')
                            {
                                printf("%s",dungeons[7].enemyTeam[0].name);
                                c+=strlen(dungeons[7].enemyTeam[0].name)-1;
                            }
                            else if(screen[l][f]=='2')
                            {
                                printf("%s",dungeons[7].enemyTeam[1].name);
                                c+=strlen(dungeons[7].enemyTeam[1].name)-1;
                            }
                            else if(screen[l][f]=='3')
                            {
                                printf("%s",dungeons[7].enemyTeam[2].name);
                                c+=strlen(dungeons[7].enemyTeam[2].name)-1;
                            }
                        }
                    }
                    else if(screen[l][f]=='4')
                    {
                        f++;
                        if(screen[l][f]=='n')
                        {
                            printf("%s",dungeons[11].type);
                            c+=strlen(dungeons[11].type)-1;
                        }
                        else if(screen[l][f]=='m')
                        {
                            f++;
                            if(screen[l][f]=='1')
                            {
                                printf("%s",dungeons[11].enemyTeam[0].name);
                                c+=strlen(dungeons[11].enemyTeam[0].name)-1;
                            }
                            else if(screen[l][f]=='2')
                            {
                                printf("%s",dungeons[11].enemyTeam[1].name);
                                c+=strlen(dungeons[11].enemyTeam[1].name)-1;
                            }
                            else if(screen[l][f]=='3')
                            {
                                printf("%s",dungeons[11].enemyTeam[2].name);
                                c+=strlen(dungeons[11].enemyTeam[2].name)-1;
                            }
                        }
                    }
                }
                else if(screen[l][f]=='s') ///----------------------------------skill
                {
                    f++;
                    c+=4;
                    if(screen[l][f]=='n')
                    {
                        printf("%s",heroTeam[heroPos].skills[skillPos].name);  //name
                        c+=strlen(heroTeam[0].skills[skillPos].name)-5;
                    }
                    else if(screen[l][f]=='d')
                    {
                        printInt(heroTeam[heroPos].skills[skillPos].damage, "NONE"); //damage
                        //c+=3;
                    }
                    else if(screen[l][f]=='h')
                    {
                        printInt(heroTeam[heroPos].skills[skillPos].heal, "NONE"); //heal
                        //c+=3;
                    }
                    else if(screen[l][f]=='f')
                    {
                        f++;
                        if(screen[l][f]=='1')
                        {
                            if(heroTeam[heroPos].skills[skillPos].effectType1 == 'p')
                            {
                                printf(":veneno");
                                c+=strlen("veneno")-4;
                            }
                            else if(heroTeam[heroPos].skills[skillPos].effectType1 == 's')
                            {
                                printf(":aturdimiento");
                                c+=strlen("aturdimiento")-4;
                            }
                            else if(heroTeam[heroPos].skills[skillPos].effectType1 == 'b')
                            {
                                printf(":sangrado");
                                c+=strlen("sangrado")-4;
                            }
                            else
                            {
                                printf(":normal");
                                c+=strlen("normal")-4;
                            }
                        }
                        else
                        {
                            if(heroTeam[heroPos].skills[skillPos].effectType2 == 'p')
                            {
                                printf(":veneno");
                                c+=strlen("veneno")-4;
                            }
                            else if(heroTeam[heroPos].skills[skillPos].effectType2 == 's')
                            {
                                printf(":aturdimiento");
                                c+=strlen("aturdimiento")-4;
                            }
                            else if(heroTeam[heroPos].skills[skillPos].effectType2 == 'b')
                            {
                                printf(":sangrado");
                                c+=strlen("sangrado")-4;
                            }
                            else
                            {
                                printf(":normal");
                                c+=strlen("normal")-4;
                            }
                        }
                    }
                    else if(screen[l][f]=='p')
                    {
                        printf("%d-%d-%d",heroTeam[heroPos].skills[skillPos].ally1,heroTeam[heroPos].skills[skillPos].ally2,heroTeam[heroPos].skills[skillPos].ally3);
                        c+=1;
                    }
                    else if(screen[l][f]=='o')
                    {
                        printf(" <-> %d-%d-%d",heroTeam[heroPos].skills[skillPos].objetive1,heroTeam[heroPos].skills[skillPos].objetive2,heroTeam[heroPos].skills[skillPos].objetive3);
                        c+=4;
                    }
                }
                else if(screen[l][f]=='r')///----------------------------------RECORDS
                {
                    stUser records[5];
                    higherRecords(records,routUser);
                    f++;
                    c+=4;
                    if(screen[l][f]=='p')
                    {
                        f++;
                        if(screen[l][f]=='1')
                        {
                            printInt(records[0].records, "YELLOW");
                        }
                        else if(screen[l][f]=='2')
                        {
                            printInt(records[1].records, "YELLOW");
                        }
                        else if(screen[l][f]=='3')
                        {
                            printInt(records[2].records, "YELLOW");
                        }
                        else if(screen[l][f]=='4')
                        {
                            printInt(records[3].records, "YELLOW");
                        }
                    }
                    else if(screen[l][f]=='d')
                    {
                        f++;
                        if(screen[l][f]=='n')
                        {
                            f++;
                            if(screen[l][f]=='1')
                            {
                                printf(RED_T"%s"RESET_COLOR,records[0].dungeonType);
                                c+=strlen(records[0].dungeonType)-5;
                            }
                            else if(screen[l][f]=='2')
                            {
                                printf(RED_T"%s"RESET_COLOR,records[1].dungeonType);
                                c+=strlen(records[1].dungeonType)-5;
                            }
                            else if(screen[l][f]=='3')
                            {
                                printf(RED_T"%s"RESET_COLOR,records[2].dungeonType);
                                c+=strlen(records[2].dungeonType)-5;
                            }
                            else if(screen[l][f]=='4')
                            {
                                printf(RED_T"%s"RESET_COLOR,records[3].dungeonType);
                                c+=strlen(records[3].dungeonType)-5;
                            }
                        }
                        if(screen[l][f]=='l')
                        {
                            f++;
                            if(screen[l][f]=='1')
                            {
                                printInt(records[0].dungeonlvl, "RED");
                            }
                            else if(screen[l][f]=='2')
                            {
                                printInt(records[1].dungeonlvl, "RED");
                            }
                            else if(screen[l][f]=='3')
                            {
                                printInt(records[2].dungeonlvl, "RED");
                            }
                            else if(screen[l][f]=='4')
                            {
                                printInt(records[3].dungeonlvl, "RED");
                            }
                        }
                    }
                    else if(screen[l][f]=='h')/// nombre de Heroe
                    {
                        f++;
                        if(screen[l][f]=='1')
                        {
                            printf(CYAN_T"%s"RESET_COLOR,heroList[records[0].posHeros[0]].name); ///top 1 hero 1
                            c+=strlen(heroList[records[0].posHeros[0]].name)-5;
                        }
                        else if(screen[l][f]=='2')
                        {
                            printf(CYAN_T"%s"RESET_COLOR,heroList[records[0].posHeros[1]].name); ///top 1 hero 2
                            c+=strlen(heroList[records[0].posHeros[1]].name)-5;
                        }
                        else if(screen[l][f]=='3')
                        {
                            printf(CYAN_T"%s"RESET_COLOR,heroList[records[0].posHeros[2]].name); ///top 1 hero 3
                            c+=strlen(heroList[records[0].posHeros[2]].name)-5;
                        }
                        else if(screen[l][f]=='4')
                        {
                            printf(CYAN_T"%s"RESET_COLOR,heroList[records[1].posHeros[0]].name); ///top 2 hero 1
                            c+=strlen(heroList[records[1].posHeros[0]].name)-5;
                        }
                        else if(screen[l][f]=='5')
                        {
                            printf(CYAN_T"%s"RESET_COLOR,heroList[records[1].posHeros[1]].name); ///top 2 hero 2
                            c+=strlen(heroList[records[1].posHeros[1]].name)-5;
                        }
                        else if(screen[l][f]=='6')
                        {
                            printf(CYAN_T"%s"RESET_COLOR,heroList[records[1].posHeros[2]].name); ///top 2 hero 3
                            c+=strlen(heroList[records[1].posHeros[2]].name)-5;
                        }
                        else if(screen[l][f]=='7')
                        {
                            printf(CYAN_T"%s"RESET_COLOR,heroList[records[2].posHeros[0]].name); ///top 3 hero 1
                            c+=strlen(heroList[records[2].posHeros[0]].name)-5;
                        }
                        else if(screen[l][f]=='8')
                        {
                            printf(CYAN_T"%s"RESET_COLOR,heroList[records[2].posHeros[1]].name); ///top 3 hero 2
                            c+=strlen(heroList[records[2].posHeros[1]].name)-5;
                        }
                        else if(screen[l][f]=='9')
                        {
                            printf(CYAN_T"%s"RESET_COLOR,heroList[records[2].posHeros[2]].name); ///top 3 hero 3
                            c+=strlen(heroList[records[2].posHeros[2]].name)-5;
                        }
                        else if(screen[l][f]=='x')
                        {
                            printf(CYAN_T"%s"RESET_COLOR,heroList[records[3].posHeros[0]].name); ///top 4 hero 1
                            c+=strlen(heroList[records[3].posHeros[0]].name)-5;
                        }
                        else if(screen[l][f]=='y')
                        {
                            printf(CYAN_T"%s"RESET_COLOR,heroList[records[3].posHeros[1]].name); ///top 4 hero 2
                            c+=strlen(heroList[records[3].posHeros[1]].name)-5;
                        }
                        else if(screen[l][f]=='z')
                        {
                            printf(CYAN_T"%s"RESET_COLOR,heroList[records[3].posHeros[2]].name); ///top 4 hero 3
                            c+=strlen(heroList[records[3].posHeros[2]].name)-5;
                        }
                        else {};
                    }
                    else if(screen[l][f]=='n')/// nombre de usuarios
                    {
                        f++;
                        if(screen[l][f]=='1')
                        {
                            printf(BLUE_T"%s"RESET_COLOR,records[0].userName);
                            c+=strlen(records[0].userName)-5;
                        }
                        else if(screen[l][f]=='2')
                        {
                            printf(BLUE_T"%s"RESET_COLOR,records[1].userName);
                            c+=strlen(records[1].userName)-5;
                        }
                        else if(screen[l][f]=='3')
                        {
                            printf(BLUE_T"%s"RESET_COLOR,records[2].userName);
                            c+=strlen(records[2].userName)-5;
                        }
                        else if(screen[l][f]=='4')
                        {
                            printf(BLUE_T"%s"RESET_COLOR,records[3].userName);
                            c+=strlen(records[3].userName)-5;
                        }
                    }
                }
            }
            else if(screen[l][c]==';') /// STORE
            {
                int f=c;
                f++;
                c+=4;
                if(screen[l][f]=='h')
                {
                    f++;
                    if(screen[l][f]=='n')
                    {
                        f++;
                        if(screen[l][f]=='1')
                        {
                            printf(CYAN_T"%s"RESET_COLOR,heroList[store[0]].name);
                            c+=strlen(heroList[store[0]].name)-5;
                        }
                        else if(screen[l][f]=='2')
                        {
                            printf(CYAN_T"%s"RESET_COLOR,heroList[store[1]].name);
                            c+=strlen(heroList[store[1]].name)-5;
                        }
                        else if(screen[l][f]=='3')
                        {
                            printf(CYAN_T"%s"RESET_COLOR,heroList[store[2]].name);
                            c+=strlen(heroList[store[2]].name)-5;
                        }
                    }
                    else if(screen[l][f]=='p')
                    {
                        f++;
                        if(screen[l][f]=='1')
                        {
                            printInt(heroList[store[0]].hp, "GREEN");
                        }
                        else if(screen[l][f]=='2')
                        {
                            printInt(heroList[store[1]].hp, "GREEN");
                        }
                        else if(screen[l][f]=='3')
                        {
                            printInt(heroList[store[2]].hp, "GREEN");
                        }
                    }
                    else if(screen[l][f]=='a')
                    {
                        f++;
                        if(screen[l][f]=='1')
                        {
                            printInt(heroList[store[0]].armor, "BLUE");
                        }
                        else if(screen[l][f]=='2')
                        {
                            printInt(heroList[store[1]].armor, "BLUE");
                        }
                        else if(screen[l][f]=='3')
                        {
                            printInt(heroList[store[2]].armor, "BLUE");
                        }
                    }
                    else if(screen[l][f]=='h')
                    {
                        f++;
                        if(screen[l][f]=='1')
                        {
                            printInt(heroList[store[0]].heal, "GREEN");
                        }
                        else if(screen[l][f]=='2')
                        {
                            printInt(heroList[store[1]].heal, "GREEN");
                        }
                        else if(screen[l][f]=='3')
                        {
                            printInt(heroList[store[2]].heal, "GREEN");
                        }
                    }
                    else if(screen[l][f]=='i')
                    {
                        f++;
                        if(screen[l][f]=='1')
                        {
                            printInt(heroList[store[0]].hit, "NONE");
                        }
                        else if(screen[l][f]=='2')
                        {
                            printInt(heroList[store[0]].hit, "NONE");
                        }
                        else if(screen[l][f]=='3')
                        {
                            printInt(heroList[store[0]].hit, "NONE");
                        }
                    }
                }
                else if(screen[l][f]=='d')
                {
                    f++;
                    if(screen[l][f]=='m')
                    {
                        f++;
                        if(screen[l][f]=='1')
                        {
                            printInt(heroList[store[0]].damageMin, "RED");
                        }
                        else if(screen[l][f]=='2')
                        {
                            printInt(heroList[store[0]].damageMin, "RED");
                        }
                        else if(screen[l][f]=='3')
                        {
                            printInt(heroList[store[0]].damageMin, "RED");
                        }
                    }
                    else if(screen[l][f]=='g')
                    {
                        f++;
                        if(screen[l][f]=='1')
                        {
                            printInt(heroList[store[0]].dodge, "NONE");
                        }
                        else if(screen[l][f]=='2')
                        {
                            printInt(heroList[store[0]].dodge, "NONE");
                        }
                        else if(screen[l][f]=='3')
                        {
                            printInt(heroList[store[0]].dodge, "NONE");
                        }
                    }
                }
                else if(screen[l][f]=='s')
                {
                    f++;
                    if(screen[l][f]=='t')
                    {
                        f++;
                        if(screen[l][f]=='1')
                        {
                            printInt(heroList[store[0]].stunResist, "YELLOW");
                        }
                        else if(screen[l][f]=='2')
                        {
                            printInt(heroList[store[0]].stunResist, "YELLOW");
                        }
                        else if(screen[l][f]=='3')
                        {
                            printInt(heroList[store[0]].stunResist, "YELLOW");
                        }
                    }
                }
                else if(screen[l][f]=='p')
                {
                    f++;
                    if(screen[l][f]=='o')
                    {
                        f++;
                        if(screen[l][f]=='1')
                        {
                            printInt(heroList[store[0]].poisonResist, "GREEN");
                        }
                        else if(screen[l][f]=='2')
                        {
                            printInt(heroList[store[0]].poisonResist, "GREEN");
                        }
                        else if(screen[l][f]=='3')
                        {
                            printInt(heroList[store[0]].poisonResist, "GREEN");
                        }
                    }
                }
                else if(screen[l][f]=='b')
                {
                    f++;
                    if(screen[l][f]=='e')
                    {
                        f++;
                        if(screen[l][f]=='1')
                        {
                            printInt(heroList[store[0]].bleedResist, "RED");
                        }
                        else if(screen[l][f]=='2')
                        {
                            printInt(heroList[store[0]].bleedResist, "RED");
                        }
                        else if(screen[l][f]=='3')
                        {
                            printInt(heroList[store[0]].bleedResist, "RED");
                        }
                    }
                }
            }
            else
            {
                printf("%c", screen[l][c]);
            }
        };
        printf("\n");
        l++;
    };
};
void findScreen(int l, int c,char newScreen[l][c], char screenName[])
{
    ///screens

    char screenSelectTrinket[31][101]=
    {
        {"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"},
        {"|||                                                                                              |||"},
        {"|||   Admin :unm                                                                                 |||"},
        {"|||                        .---------------------------------------------------------.           |||"},
        {"|||                        | HP  |Dmg  |Sana  |Def  |Esq  |Res.Atur|Res.Ven|Res.Sang |           |||"},
        {"|||   .------------------------------------------------------------------------------.-------.   |||"},
        {"|||   | :hn0               |:hp0 |:hd0 |:hhe0 |:ha0 |:hd0 |  :hs0   | :hp0 | :hb0    |Equipar|   |||"},
        {"|||   .------------------------------------------------------------------------------.-------.   |||"},
        {"|||   | :hn1               |:hp1 |:hd1 |:hhe1 |:ha1 |:hd1 |  :hs1   | :hp1 | :hb1    |Equipar|   |||"},
        {"|||   .------------------------------------------------------------------------------.-------.   |||"},
        {"|||   | :hn4               |:hp2 |:hd2 |:hhe2 |:ha2 |:hd2 |  :hs2   | :hp2 | :hb2    |Equipar|   |||"},
        {"|||   .------------------------------------------------------------------------------.-------.   |||"},
        {"|||   | :hn6               |:hp3 |:hd3 |:hhe3 |:ha3 |:hd3 |  :hs3   | :hp3 | :hb3    |Equipar|   |||"},
        {"|||   .------------------------------------------------------------------------------.-------.   |||"},
        {"|||   | :hn8               |:hp4 |:hd4 |:hhe4 |:ha4 |:hd4 |  :hs4   | :hp4 | :hb4    |Equipar|   |||"},
        {"|||   .------------------------------------------------------------------------------.-------.   |||"},
        {"|||   | :hn9               |:hp5 |:hd5 |:hhe5 |:ha5 |:hd5 |  :hs5   |:hp5  | :hb5    |Equipar|   |||"},
        {"|||   .------------------------------------------------------------------------------.-------.   |||"},
        {"|||   | :hn9               |:hp6 |:hd6 |:hhe6 |:ha6 |:hd6 |  :hs6   |:hp6  | :hb6    |Equipar|   |||"},
        {"|||   .------------------------------------------------------------------------------.-------.   |||"},
        {"|||   | :hn9               |:hp7 |:hd7 |:hhe7 |:ha7 |:hd7 |  :hs7   |:hp7  | :hb7    |Equipar|   |||"},
        {"|||   .------------------------------------------------------------------------------.-------.   |||"},
        {"|||   | :hn9               |:hp8 |:hd8 |:hhe8 |:ha8 |:hd8 |  :hs8   |:hp8  | :hb8    |Equipar|   |||"},
        {"|||   .------------------------------------------------------------------------------.-------.   |||"},
        {"|||   | :hn9               |:hp9 |:hd9 |:hhe9 |:ha9 |:hd9 |  :hs9   |:hp9  | :hb9    |Equipar|   |||"},
        {"|||   .------------------------------------------------------------------------------.-------.   |||"},
        {"|||                                                                               .----------.   |||"},
        {"|||     Atras(esc)                                                                |Continuar |   |||"},
        {"|||                                                                               .----------.   |||"},
        {"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"}
    };

    /*char screenSelectTeam[31][101]=
    {
        {"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"},
        {"|||                                                                                              |||"},
        {"|||   Admin :unm           .-----------------------------------------------------------------.   |||"},
        {"|||                        | HP |Dmg | Sana |Armadura |Esquiva |Res.Atur |Res.Ven |Res.Sang  |   |||"},
        {"|||   .--------------------------------------------------------------------------------------.   |||"},
        {"|||   | :hn0               |:hp0|:hd0| :hhe0|  :ha0   | :hd0   |  :hs0   |  :hp0  |  :hb0    |   |||"},
        {"|||   .--------------------------------------------------------------------------------------.   |||"},
        {"|||   | :hn1               |:hp1|:hd1| :hhe1|  :ha1   | :hd1   |  :hs1   |  :hp1  |  :hb1    |   |||"},
        {"|||   .--------------------------------------------------------------------------------------.   |||"},
        {"|||   | :hn2               |:hp2|:hd2| :hhe2|  :ha2   | :hd2   |  :hs2   |  :hp2  |  :hb2    |   |||"},
        {"|||   .--------------------------------------------------------------------------------------.   |||"},
        {"|||   | :hn3               |:hp3|:hd3| :hhe3|  :ha3   | :hd3   |  :hs3   |  :hp3  |  :hb3    |   |||"},
        {"|||   .--------------------------------------------------------------------------------------.   |||"},
        {"|||   | :hn4               |:hp4|:hd4| :hhe4|  :ha4   | :hd4   |  :hs4   |  :hp4  |  :hb4    |   |||"},
        {"|||   .--------------------------------------------------------------------------------------.   |||"},
        {"|||   | :hn5               |:hp5|:hd5| :hhe5|  :ha5   | :hd5   |  :hs5   |  :hp5  |  :hb5    |   |||"},
        {"|||   .--------------------------------------------------------------------------------------.   |||"},
        {"|||   | :hn6               |:hp6|:hd6| :hhe6|  :ha6   | :hd6   |  :hs6   |  :hp6  |  :hb6    |   |||"},
        {"|||   .--------------------------------------------------------------------------------------.   |||"},
        {"|||   | :hn7               |:hp7|:hd7| :hhe7|  :ha7   | :hd7   |  :hs7   |  :hp7  |  :hb7    |   |||"},
        {"|||   .--------------------------------------------------------------------------------------.   |||"},
        {"|||   | :hn8               |:hp8|:hd8| :hhe8|  :ha8   | :hd8   |  :hs8   |  :hp8  |  :hb8    |   |||"},
        {"|||   .--------------------------------------------------------------------------------------.   |||"},
        {"|||   | :hn9               |:hp9|:hd9| :hhe9|  :ha9   | :hd9   |  :hs9   |  :hp9  |  :hb9    |   |||"},
        {"|||   .--------------------------------------------------------------------------------------.   |||"},
        {"|||                                                                               .----------.   |||"},
        {"|||                                                                               |Continuar |   |||"},
        {"|||     Atras(esc)                                                                .----------.   |||"},
        {"|||                                                                                              |||"},
        {"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"}
    };*/
    /*char screenSelectTeam[31][101]=
    {
        {"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"},
        {"|||                                                                                              |||"},
        {"|||   Admin :unm           .-----------------------------------------------------------------.   |||"},
        {"|||                        | HP |Dmg | Sana |Armadura |Esquiva |Res.Atur |Res.Ven |Res.Sang  |   |||"},
        {"|||    T122222222222222222222222222222222222222222222222222222222222222222222222222222222222223   |||"},
        {"|||    T6  hn0              | hp0| hd0| hhe0 |  ha0    |  hd0   |   hs0   |   hp0  |   hb0    T6  |||"},
        {"|||    T422222222222222222222222222222222222222222222222222222222222222222222222222222222222225   |||"},
        {"|||    T122222222222222222222222222222222222222222222222222222222222222222222222222222222222223   |||"},
        {"|||    T6  hn1              | hp1| hd1| hhe1 |  ha1    |  hd1   |   hs1   |   hp1  |   hb1    T6  |||"},
        {"|||    T422222222222222222222222222222222222222222222222222222222222222222222222222222222222225   |||"},
        {"|||    T122222222222222222222222222222222222222222222222222222222222222222222222222222222222223   |||"},
        {"|||    T6  hn9              | hp9| hd9| hhe9 |  ha9    |  hd0   |   hs2   |   hp2  |   hb2    T6  |||"},
        {"|||    T422222222222222222222222222222222222222222222222222222222222222222222222222222222222225   |||"},
        {"|||    T122222222222222222222222222222222222222222222222222222222222222222222222222222222222223   |||"},
        {"|||    T6  hn9              | hp9| hd9| hhe9 |  ha9    |  hd0   |   hs0   |   hp0  |   hb0    T6  |||"},
        {"|||    T422222222222222222222222222222222222222222222222222222222222222222222222222222222222225   |||"},
        {"|||    T122222222222222222222222222222222222222222222222222222222222222222222222222222222222223   |||"},
        {"|||    T6  hn9              | hp9| hd9| hhe9 |  ha9    |  hd0   |   hs0   |   hp0  |   hb0    T6  |||"},
        {"|||    T422222222222222222222222222222222222222222222222222222222222222222222222222222222222225   |||"},
        {"|||    T122222222222222222222222222222222222222222222222222222222222222222222222222222222222223   |||"},
        {"|||    T6  hn9              | hp9| hd9| hhe9 |  ha9    |  hd0   |   hs0   |   hp0  |   hb0    T6  |||"},
        {"|||    T422222222222222222222222222222222222222222222222222222222222222222222222222222222222225   |||"},
        {"|||    T122222222222222222222222222222222222222222222222222222222222222222222222222222222222223   |||"},
        {"|||    T6  hn9              | hp9| hd9| hhe9 |  ha9    |  hd0   |   hs0   |   hp0  |   hb0    T6  |||"},
        {"|||    T422222222222222222222222222222222222222222222222222222222222222222222222222222222222225   |||"},
        {"|||                                                                               .----------.   |||"},
        {"|||                                                                               |Continuar |   |||"},
        {"|||     Atras(esc)                                                                .----------.   |||"},
        {"|||                                                                                              |||"},
        {"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"}
    };*/
    char screenSelectTeam[31][101]=
    {
        {"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"},
        {"|||                                                                                              |||"},
        {"|||   User :unm            .-----------------------------------------------------------------.   |||"},
        {"|||                        | HP |Dmg | Sana |Armadura |Esquiva |Res.Atur |Res.Ven |Res.Sang  |   |||"},
        {"T1                                                                                               |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                               .----------.   |||"},
        {"|||                                                                               |Continuar |   |||"},
        {"|||     Atras(esc)                                                                .----------.   |||"},
        {"|||                                                                                              |||"},
        {"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"}
    };

    char screenLogIn[31][101]=
    {
        {"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                       Nombre se usuario                                      |||"},
        {"|||                                      .----------------.                                      |||"},
        {"|||                                      |    ........    |                                      |||"},
        {"|||                                      .----------------.                                      |||"},
        {"|||                                          Contrasena                                          |||"},
        {"|||                                      .----------------.                                      |||"},
        {"|||                                      |    ........    |                                      |||"},
        {"|||                                      .----------------.                                      |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                           Ingresar                                           |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                      .----------------.                                      |||"},
        {"|||                                      |  Nuevo usuario |                                      |||"},
        {"|||                                      .----------------.                                      |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"}
    };  //0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789
    //          1         2         3         4         5         6         7         8         9
    char screenNewUser[31][101]=
    {
        {"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                        Rellanar datos                                        |||"},
        {"|||                                                                                              |||"},
        {"|||                                            Nombre                                            |||"},
        {"|||                                      .----------------.                                      |||"},
        {"|||                                      |    .........   |                                      |||"},
        {"|||                                      .----------------.                                      |||"},
        {"|||                                              ID                                              |||"},
        {"|||                                      .----------------.                                      |||"},
        {"|||                                      |    .........   |                                      |||"},
        {"|||                                      .----------------.                                      |||"},
        {"|||                                          Contrasena                                          |||"},
        {"|||                                      .----------------.                                      |||"},
        {"|||                                      |    .........   |                                      |||"},
        {"|||                                      .----------------.                                      |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                           aceptar                                            |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||     Atras(esc)                                                                               |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"}
    };  //0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789
    //          1         2         3         4         5         6         7         8         9
    char screenFindUser[31][101]=
    {
        {"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"},
        {"|||                                                                                              |||"},
        {"|||   Admin :unm                                                                                 |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                    .-----------------.                  .-----------------.                  |||"},
        {"|||                    | Busqueda por ID |                  |Busqueda por user|                  |||"},
        {"|||                    .-----------------.                  .-----------------.                  |||"},
        {"|||                                                                                              |||"},
        {"|||                    .-----------------.                  .-----------------.                  |||"},
        {"|||                    |    ********     |                  |    ********     |                  |||"},
        {"|||                    .-----------------.                  .-----------------.                  |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||     Atras(esc)                                                                               |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"}
    };
    char screenSetDown[31][101]=
    {
        {"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                              .---------------------------------.                             |||"},
        {"|||                              |                                 |                             |||"},
        {"|||                              |      Dar de baja la cuenta      |                             |||"},
        {"|||                              |                                 |                             |||"},
        {"|||                              .---------------------------------.                             |||"},
        {"|||                                                                                              |||"},
        {"|||                                          Contrasenia                                         |||"},
        {"|||                                     .-------------------.                                    |||"},
        {"|||                                     |     ********      |                                    |||"},
        {"|||                                     .-------------------.                                    |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||     Atras(esc)                                                                               |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"}
    };
    char screenChangePass[31][101]=
    {
        {"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                              .---------------------------------.                             |||"},
        {"|||                              |                                 |                             |||"},
        {"|||                              |       Cambiar contrasenia       |                             |||"},
        {"|||                              |                                 |                             |||"},
        {"|||                              .---------------------------------.                             |||"},
        {"|||                                          Contrasenia                                         |||"},
        {"|||                                     .-------------------.                                    |||"},
        {"|||                                     |  **************   |                                    |||"},
        {"|||                                     .-------------------.                                    |||"},
        {"|||                                       Nueva contrasenia                                      |||"},
        {"|||                                     .-------------------.                                    |||"},
        {"|||                                     |  **************   |                                    |||"},
        {"|||                                     .-------------------.                                    |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||     Atras(esc)                                                                               |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"}
    };


    char screenIndex[31][101]=
    {
        {"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"},
        {"|||                                                                                              |||"},
        {"|||  Usuario :unm                                                                                |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                      .----------------.                                      |||"},
        {"|||                                      |   Continuar    |                                      |||"},
        {"|||                                      .----------------.                                      |||"},
        {"|||                                      |  Nueva partida |                                      |||"},
        {"|||                                      .----------------.                                      |||"},
        {"|||                                      |     Tienda     |                                      |||"},
        {"|||                                      .----------------.                                      |||"},
        {"|||                                      |    Opciones    |                                      |||"},
        {"|||                                      .----------------.                                      |||"},
        {"|||                                      |    Tier list   |                                      |||"},
        {"|||                                      .----------------.                                      |||"},
        {"|||                                      |  Cambiar user  |                                      |||"},
        {"|||                                      .----------------.                                      |||"},
        {"|||                                      |     Salida     |                                      |||"},
        {"|||                                      .----------------.                                      |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||     Atras(esc)                                                                               |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"}
    };
    char screenNewGame[31][101]=
    {
        {"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"},
        {"|||                                                                                              |||"},
        {"|||   Usuario :unm                                                                               |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                      .----------------.                                      |||"},
        {"|||                                      |   Dificultad   |                                      |||"},
        {"|||                                      .----------------.                                      |||"},
        {"|||                                                                                              |||"},
        {"|||                    .----------------..----------------..----------------.                    |||"},
        {"|||                    |     Normal     ||     Dificil    || Luna de sangre |                    |||"},
        {"|||                    .----------------..----------------..----------------.                    |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||     Atras(esc)                                                                               |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"}
    };

    char screenTierList[31][101]=
    {
        {"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"},
        {"|||                                                                                              |||"},
        {"|||  Usuario :unm                                                                                |||"},
        {"|||      .--------------..--------------------------..--------------------.---------------.      |||"},
        {"|||      |                     Heroes                   Ultimo dungeon         Records    |      |||"},
        {"|||      |     :rn1              :rh1                     :rdn1                :rp1       |      |||"},
        {"|||      |                       :rh2                     Nivel :rdl1                     |      |||"},
        {"|||      |                       :rh3                                                     |      |||"},
        {"|||      .--------------..--------------------------..--------------------.---------------.      |||"},
        {"|||      |                     Heroes                   Ultimo dungeon         Records    |      |||"},
        {"|||      |     :rn2              :rh4                     :rdn2                :rp2       |      |||"},
        {"|||      |                       :rh5                     Nivel :rdl2                     |      |||"},
        {"|||      |                       :rh6                                                     |      |||"},
        {"|||       .-------------..--------------------------..-------------------.---------------.       |||"},
        {"|||      |                     Heroes                   Ultimo dungeon         Records    |      |||"},
        {"|||      |     :rn3              :rh7                     :rdn3                :rp3       |      |||"},
        {"|||      |                       :rh8                     Nivel :rdl3                     |      |||"},
        {"|||      |                       :rh9                                                     |      |||"},
        {"|||      .--------------..--------------------------..--------------------.---------------.      |||"},
        {"|||      |                     Heroes                   Ultimo dungeon         Records    |      |||"},
        {"|||      |     :rn4              :rhy                     :rdn4                :rp4       |      |||"},
        {"|||      |                       :rhx                     Nivel :rdl1                     |      |||"},
        {"|||      |                       :rhz                                                     |      |||"},
        {"|||      .--------------..--------------------------..--------------------.---------------.      |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                           .-----------.      |||"},
        {"|||                                                                           |   Salir   |      |||"},
        {"|||     Atras(esc)                                                            .-----------.      |||"},
        {"|||                                                                                              |||"},
        {"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"}
    };
    char screenMap[31][101]=
    {
        {"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"},
        {"|||                                                                                              |||"},
        {"|||  Usuario :unm                                                                                |||"},
        {"|||                                            Mapas                                             |||"},
        {"|||       .-----------------------------------------------------------------------------.        |||"},
        {"|||       | Dungeon :d1n                                                 .----------.   |        |||"},
        {"|||       | enemy1  :d1m1                                                | Combate! |   |        |||"},
        {"|||       | enemy2  :d1m2                                                .----------.   |        |||"},
        {"|||       | enemy3  :d1m3                                                               |        |||"},
        {"|||       .-----------------------------------------------------------------------------.        |||"},
        {"|||       | Dungeon :d2n                                                 .----------.   |        |||"},
        {"|||       | enemy1  :d2m1                                                | Combate! |   |        |||"},
        {"|||       | enemy2  :d2m2                                                .----------.   |        |||"},
        {"|||       | enemy3  :d2m3                                                               |        |||"},
        {"|||       .-----------------------------------------------------------------------------.        |||"},
        {"|||       | Dungeon :d3n                                                 .----------.   |        |||"},
        {"|||       | enemy1  :d3m1                                                | Combate! |   |        |||"},
        {"|||       | enemy2  :d3m2                                                .----------.   |        |||"},
        {"|||       | enemy3  :d3m3                                                               |        |||"},
        {"|||       .-----------------------------------------------------------------------------.        |||"},
        {"|||       | Dungeon :d4n                                                 .----------.   |        |||"},
        {"|||       | enemy1  :d4m1                                                | Combate! |   |        |||"},
        {"|||       | enemy2  :d4m2                                                .----------.   |        |||"},
        {"|||       | enemy3  :d4m3                                                               |        |||"},
        {"|||       .-----------------------------------------------------------------------------.        |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||  Atras(esc)                                                                                  |||"},
        {"|||                                                                                              |||"},
        {"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"}
    };
    char screenResultsMenu[31][101]=
    {
        {"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"},
        {"|||                                                                                              |||"},
        {"|||  Usuario :unm                                                                                |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                    .----------------------------------------------------.                    |||"},
        {"|||                    ||                                                  ||                    |||"},
        {"|||                    ||              Dificultad:udf                     ||                    |||"},
        {"|||                    ||                                                  ||                    |||"},
        {"|||                    ||                     Ronda:Rd                    ||                    |||"},
        {"|||                    ||                                                  ||                    |||"},
        {"|||                    ||                  Mapa:udt                       ||                    |||"},
        {"|||                    ||                                                  ||                    |||"},
        {"|||                    ||                     lvl:udl                     ||                    |||"},
        {"|||                    ||                                                  ||                    |||"},
        {"|||                    ||                   .---------.                    ||                    |||"},
        {"|||                    ||                   | ACAPTAR |                    ||                    |||"},
        {"|||                    ||                   .---------.                    ||                    |||"},
        {"|||                    .----------------------------------------------------.                    |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||  Atras(esc)                                                                                  |||"},
        {"|||                                                                                              |||"},
        {"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"}
    };  //0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789
    //          1         2         3         4         5         6         7         8         9
    char screenConfirm[31][101]=
    {
        {"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"},
        {"|||                                                                                              |||"},
        {"|||  Usuario :unm                                                                                |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                         ..--------------------------------------..                           |||"},
        {"|||                         ||                                      ||                           |||"},
        {"|||                         ||       Estas seguro de salir del      ||                           |||"},
        {"|||                         ||                                      ||                           |||"},
        {"|||                         ||               combate?               ||                           |||"},
        {"|||                         ||                                      ||                           |||"},
        {"|||                         ||    .-----------.     .-----------.   ||                           |||"},
        {"|||                         ||    | CONTINUAR |     |   SALIR   |   ||                           |||"},
        {"|||                         ||    .-----------.     .-----------.   ||                           |||"},
        {"|||                         ||                                      ||                           |||"},
        {"|||                         ..--------------------------------------..                           |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||  Atras(esc)                                                                                  |||"},
        {"|||                                                                                              |||"},
        {"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"}
    };  //0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789
    //          1         2         3         4         5         6         7         8         9

    char screenUserPerfil[31][101]=
    {
        {"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"},
        {"|||                                                                                              |||"},
        {"|||  Usuario :unm                                                                                |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"||| .--------------------------------------------.    .----------------------------------------. |||"},
        {"||| | Nombre de use: |   :unn                    |    |               Dungeon                  | |||"},
        {"||| |                                            |    |                                        | |||"},
        {"||| |    Id Usuario: |   :uid                    |    |     Ultimo Dungeon:       :udt         | |||"},
        {"||| |                                            |    |        Ultimo lvl:        :udl         | |||"},
        {"||| |    Dificultad: |   :udf                    |    .----------------------------------------. |||"},
        {"||| |                                            |    .----------------------------------------. |||"},
        {"||| |      Progreso: |   :upg                    |    |                Grupo                   | |||"},
        {"||| |                                            |    |                                        | |||"},
        {"||| |           Oro: |   :ugl                    |    |           :hn1                         | |||"},
        {"||| |                                            |    |           :hn2                         | |||"},
        {"||| |        Estado: |   :usd                    |    |           :hn3                         | |||"},
        {"||| |                                            |    |                                        | |||"},
        {"||| .--------------------------------------------.    .----------------------------------------. |||"},
        {"|||                                                                                              |||"},
        {"|||                          Ui7             Ui1             Ui4                                 |||"},
        {"|||                          Ui8             Ui2             Ui5                                 |||"},
        {"|||                          Ui9             Ui3             Ui6                                 |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||  Atras(esc)                                                                                  |||"},
        {"|||                                                                                              |||"},
        {"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"}
    };

    char screenActiveUser[31][101]=
    {
        {"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                       .-----------------------------------------------.                      |||"},
        {"|||                       |     Usted esta dado de baja.¿Desea darse      |                      |||"},
        {"|||                       |         de alta nuevamente en el juego?       |                      |||"},
        {"|||                       .-----------------------------------------------.                      |||"},
        {"|||                                                                                              |||"},
        {"|||                       .-------------------.       .-------------------.                      |||"},
        {"|||                       |      Aceptar      |       |     Cancelar      |                      |||"},
        {"|||                       .-------------------.       .-------------------.                      |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||     Atras(esc)                                                                               |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"}
    };

    char screenInvalidUser[31][101]=
    {
        {"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                       .-----------------------------------------------.                      |||"},
        {"|||                       |               Usuario invalido                |                      |||"},
        {"|||                       |          intente ingresar nuevamente          |                      |||"},
        {"|||                       .-----------------------------------------------.                      |||"},
        {"|||                                                                                              |||"},
        {"|||                                    .---------------------.                                   |||"},
        {"|||                                    |       Aceptar       |                                   |||"},
        {"|||                                    .---------------------.                                   |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||     Atras(esc)                                                                               |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"}
    };
    char screenError[31][101]=
    {
        {"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                      .-----------------------------------------------.                       |||"},
        {"|||                      |         Que hace pibe?! La gileaste           |                       |||"},
        {"|||                      |              intenta otra vez!                |                       |||"},
        {"|||                      .-----------------------------------------------.                       |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                    .---------------------.                                   |||"},
        {"|||                                    |       Aceptar       |                                   |||"},
        {"|||                                    .---------------------.                                   |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||     Atras(esc)                                                                               |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"}
    };
    char screenSucefull[31][101]=
    {
        {"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                       .-----------------------------------------------.                      |||"},
        {"|||                       |                                               |                      |||"},
        {"|||                       |        Exito en cambiar la contrasenia        |                      |||"},
        {"|||                       |                                               |                      |||"},
        {"|||                       .-----------------------------------------------.                      |||"},
        {"|||                                                                                              |||"},
        {"|||                                     .-------------------.                                    |||"},
        {"|||                                     |      Aceptar      |                                    |||"},
        {"|||                                     .-------------------.                                    |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||     Atras(esc)                                                                               |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"}
    };
    char screenSucefullSetDown[31][101]=
    {
        {"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                       .-----------------------------------------------.                      |||"},
        {"|||                       |                                               |                      |||"},
        {"|||                       |              Usuario dado de baja             |                      |||"},
        {"|||                       |                                               |                      |||"},
        {"|||                       .-----------------------------------------------.                      |||"},
        {"|||                                                                                              |||"},
        {"|||                                     .-------------------.                                    |||"},
        {"|||                                     |      Aceptar      |                                    |||"},
        {"|||                                     .-------------------.                                    |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||     Atras(esc)                                                                               |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"}
    };
    char screenBuy[31][101]=
    {
        {"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                       .-----------------------------------------------.                      |||"},
        {"|||                       |                                               |                      |||"},
        {"|||                       |          Felicidades! por tu compra           |                      |||"},
        {"|||                       |                                               |                      |||"},
        {"|||                       .-----------------------------------------------.                      |||"},
        {"|||                                                                                              |||"},
        {"|||                                     .-------------------.                                    |||"},
        {"|||                                     |      Aceptar      |                                    |||"},
        {"|||                                     .-------------------.                                    |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||     Atras(esc)                                                                               |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"}
    };
    char screenEnoughMoney[31][101]=
    {
        {"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                       .-----------------------------------------------.                      |||"},
        {"|||                       |                                               |                      |||"},
        {"|||                       |         Pobre! No te alcanza el oro           |                      |||"},
        {"|||                       |                                               |                      |||"},
        {"|||                       .-----------------------------------------------.                      |||"},
        {"|||                                                                                              |||"},
        {"|||                                     .-------------------.                                    |||"},
        {"|||                                     |      Aceptar      |                                    |||"},
        {"|||                                     .-------------------.                                    |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"|||     Atras(esc)                                                                               |||"},
        {"|||                                                                                              |||"},
        {"|||                                                                                              |||"},
        {"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"}
    };
    char screenStore[31][101]=
    {
        {"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"},
        {"|||                                                                                              |||"},
        {"|||   Usuario :unm           Oro:ugl                                                             |||"},
        {"|||                                                                                              |||"},
        {"|||   .------------------------------------------------------------------------------------.     |||"},
        {"|||   |   Heroes                                                                           |     |||"},
        {"|||   |   Name             | Vida | Arm | Danio | Cura | Golp | Esq | Atur | Ven | Sang |  |     |||"},
        {"|||   .------------------------------------------------------------------------------------.     |||"},
        {"|||   .------------------------------------------------------------------------------------.     |||"},
        {"|||   |;hn1                |;hp1  |;ha1 |;dm1   |;hh1  |;hi1  |;dg1 |;st1  |;po1 |;be1  |  |     |||"},
        {"|||   .------------------------------------------------------------------------------------.     |||"},
        {"|||                                                                .--------.   .----------.     |||"},
        {"|||                                                                |  4000  |   | Comprar  |     |||"},
        {"|||                                                                .--------.   .----------.     |||"},
        {"|||   .------------------------------------------------------------------------------------.     |||"},
        {"|||   |;hn2                |;hp2  |;ha2 |;dm2   |;hh2  |;hi2  |;dg2 |;st2  |;po2 |;be2  |  |     |||"},
        {"|||   .------------------------------------------------------------------------------------.     |||"},
        {"|||                                                                .--------.   .----------.     |||"},
        {"|||                                                                |  4000  |   | Comprar  |     |||"},
        {"|||                                                                .--------.   .----------.     |||"},
        {"|||   .------------------------------------------------------------------------------------.     |||"},
        {"|||   |;hn3                |;hp3  |;ha3 |;dm3   |;hh3  |;hi3  |;dg3 |;st3  |;po3 |;be3  |  |     |||"},
        {"|||   .------------------------------------------------------------------------------------.     |||"},
        {"|||                                                                .--------.   .----------.     |||"},
        {"|||                                                                |  4000  |   | Comprar  |     |||"},
        {"|||                                                                .--------.   .----------.     |||"},
        {"|||                                                                                              |||"},
        {"|||     Atras(esc)                                                                               |||"},
        {"|||                                                                                              |||"},
        {"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"}
    };
    char screenCombat[31][101]=
    {
        {"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"},//0
        {"||                                                                                                ||"},//1
        {"|| Usuario :unm                                                                                   ||"},//2
        {"|| Dungeon :udt                            .---------.                                           ||"},//3
        {"|| Nivel :udl                              | Aceptar |                                           ||"},//4
        {"||                                          .---------.                                           ||"},//5
        {"||                                                                                                ||"},//6
        {"||                                                                                                ||"},//8
        {"||                                                                                                ||"},//7
        {"||          :hh3         :hh2         :hh1                :mm1         :mm2         :mm3          ||"},//13
        {"||       .-------.    .-------.    .-------.           .-------.    .-------.    .-------.        ||"},//10
        {"||       | Heroe |    | Heroe |    | Heroe |           | Enemy |    | Enemy |    | Enemy |        ||"},//11
        {"||       |   3   |    |   2   |    |   1   |           |   1   |    |   2   |    |   3   |        ||"},//12
        {"||        -------      -------      -------             -------      -------      -------         ||"},//9
        {"||         :hc3         :hc2         :hc1                :mc1         :mc2         :mc3           ||"},//14
        {"||        Z6           Z5           Z4                  Z1           Z2           Z3              ||"},//15
        {"||B7B999999999999999999999B3B9999999999999999999999B3B9999999999999999999999999999999999999B6||"},     //16
        {"||B8 :hnm                    B8       Habilidades        B8          :mnm                BB8||"},      //17
        {"||B8                         B8 S7S9S6 K7K9K6 L7L9L6  B8                              BB8||"},         //18
        {"||B8 Vida:hhp                B8 S8  1  S8 K8  2  K8 L8  3  L8  B8  Vida:mhp                    BB8||"},//19
        {"||B8 Armadura:har            B8 S5S9S4 K5K9K4 L5L9L4  B8  Armadura:mar                BB8||"},         //20
        {"||B8 Esquiva:hdg             B8:snm                      B8  Esquiva:mdg                 BB8||"},      //21
        {"||B8 Prob. de golpe:hht      B8                          B8  Prob. de golpe:mht          BB8||"},      //22
        {"||B8                         B8 Dano:sdm                 B8                              BB8||"},      //23
        {"||B8 Resistencias            B8 Heal:shl                 B8  Resistencias                BB8||"},      //24
        {"||B8 aturdimiento:hst        B8 Efecto:sf1               B8  aturdimiento:mst            BB8||"},      //25
        {"||B8 veneno:hps              B8 Efecto:sf2               B8  veneno:mps                  BB8||"},      //26
        {"||B8 sangrado:hbl            B8                          B8  sangrado:mbl                BB8||"},      //27
        {"||B5B999999999999999999999B2B9999999999999999999999B2B9999999999999999999999999999999999999B4||"},     //28
        {"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"} //29
    };  //0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789
    //          1         2         3         4         5         6         7         8         9

    int i;
    for(i=0; i<l; i++)
    {
        if (strcmpi(screenName, "logIn") == 0)
        {
            strcpy(newScreen[i],screenLogIn[i]);
        }
        else if (strcmpi(screenName, "newUser") == 0)
        {
            strcpy(newScreen[i],screenNewUser[i]);
        }
        else if (strcmpi(screenName, "index") == 0)
        {
            strcpy(newScreen[i],screenIndex[i]);
        }
        else if (strcmpi(screenName, "exitCombat") == 0)
        {
            strcpy(newScreen[i],screenConfirm[i]);
        }
        else if (strcmpi(screenName, "continue") == 0)
        {
            strcpy(newScreen[i],screenCombat[i]);
        }
        else if (strcmpi(screenName, "results") == 0)
        {
            strcpy(newScreen[i],screenResultsMenu[i]);
        }
        else if (strcmpi(screenName, "userPerfil") == 0)
        {
            strcpy(newScreen[i],screenUserPerfil[i]);
        }
        else if (strcmpi(screenName, "screenMap") == 0)
        {
            strcpy(newScreen[i],screenMap[i]);
        }
        else if (strcmpi(screenName, "tierList") == 0)
        {
            strcpy(newScreen[i],screenTierList[i]);
        }
        else if (strcmpi(screenName, "combat") == 0)
        {
            strcpy(newScreen[i],screenCombat[i]);
        }
        else if (strcmpi(screenName, "store") == 0)
        {
            strcpy(newScreen[i],screenStore[i]);
        }
        else if (strcmpi(screenName, "findUser") == 0)
        {
            strcpy(newScreen[i],screenFindUser[i]);
        }
        else if (strcmpi(screenName, "setDifficult") == 0)
        {
            strcpy(newScreen[i],screenNewGame[i]);
        }
        else if (strcmpi(screenName, "selectTeam") == 0)
        {
            strcpy(newScreen[i],screenSelectTeam[i]);
        }
        else if (strcmpi(screenName, "selectTrinket") == 0)
        {
            strcpy(newScreen[i],screenSelectTrinket[i]);
        }
        else if (strcmpi(screenName, "invalidUser") == 0)
        {
            strcpy(newScreen[i],screenInvalidUser[i]);
        }
        else if (strcmpi(screenName, "activeUser") == 0)
        {
            strcpy(newScreen[i],screenActiveUser[i]);
        }
        else if (strcmpi(screenName, "sucefull") == 0)
        {
            strcpy(newScreen[i],screenSucefull[i]);
        }
        else if (strcmpi(screenName, "setDown") == 0)
        {
            strcpy(newScreen[i],screenSetDown[i]);
        }
        else if (strcmpi(screenName, "changePass") == 0)
        {
            strcpy(newScreen[i],screenChangePass[i]);
        }
        else if (strcmpi(screenName, "error") == 0)
        {
            strcpy(newScreen[i],screenError[i]);
        }
        else if (strcmpi(screenName, "resultsMenu") == 0)
        {
            strcpy(newScreen[i],screenResultsMenu[i]);
        }
        else if (strcmpi(screenName, "succesfullSetDown") == 0)
        {
            strcpy(newScreen[i],screenSucefullSetDown[i]);
        }
        else if (strcmpi(screenName, "enoughMoney") == 0)
        {
            strcpy(newScreen[i],screenEnoughMoney[i]);
        }
        else if (strcmpi(screenName, "buy") == 0)
        {
            strcpy(newScreen[i],screenBuy[i]);
        }
    };
};
