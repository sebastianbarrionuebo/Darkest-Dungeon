#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>
#include <locale.h>

#include "fnUser.h"


///Funciones de usuario
///Mostrar matriz para encriptacion de passwords
void mostrarMatriz(int filas, int colum,char matris[filas][colum]){
    for(int i=0;i<filas; i++){
        for(int j=0; j<colum; j++){
            printf("|%c|", matris[i][j]);
        }
        printf("\n");
    }
};
///Encriptar contraseñas
void encryptPassword(char passWord[]){
    char encrypt[2][2];
    char matrxPass[2][4];
    char encryptPass[2][4];
    ///Matriz de encriptacion
    printf("Matris de encript:\n");
    encrypt[0][0]=1;
    encrypt[0][1]=2;
    encrypt[1][0]=2;
    encrypt[1][1]=3;
    mostrarMatriz(2,2,encrypt);
    ///Contraseña pasada a matriz
    printf("Matris de pass:\n");
    matrxPass[0][0]=passWord[0];
    matrxPass[1][0]=passWord[1];
    matrxPass[0][1]=passWord[2];
    matrxPass[1][1]=passWord[3];
    matrxPass[0][2]=passWord[4];
    matrxPass[1][2]=passWord[5];
    matrxPass[0][3]=passWord[6];
    matrxPass[1][3]=passWord[7];
    mostrarMatriz(2,4,matrxPass);

    for(int i=0; i<2; i++){
        for(int k=0; k<4; k++){
            encryptPass[i][k] = 0;
        }
    }
    for(int i=0; i<2; i++){
        for(int j=0; j<2; j++){
            for(int k=0; k<4; k++){
                encryptPass[i][k] = encryptPass[i][k] + (encrypt[i][j] * matrxPass[j][k]);
            }
        }
    }
    printf("Matris encriptada:\n");
    mostrarMatriz(2,4,encryptPass);


    passWord[0]=encryptPass[0][0];
    passWord[1]=encryptPass[1][0];
    passWord[2]=encryptPass[0][1];
    passWord[3]=encryptPass[1][1];
    passWord[4]=encryptPass[0][2];
    passWord[5]=encryptPass[1][2];
    passWord[6]=encryptPass[0][3];
    passWord[7]=encryptPass[1][3];

    decryptPassword(passWord);
    printf("Desencriptar:\n");
    printf("\n");
}
///Encriptar contraseñas
void decryptPassword(char passWord[]){
    char decrypt[2][2];
    char matrxPass[2][4];
    char decryptPass[2][4];
    ///Matriz de desencriptacion
    printf("Matris de encript:\n");
    decrypt[0][0]=-3;
    decrypt[0][1]=2;
    decrypt[1][0]=2;
    decrypt[1][1]=-1;
    mostrarMatriz(2,2,decrypt);
    ///Contraseña encriptada pasada a matriz
    printf("Matris de pass:\n");
    matrxPass[0][0]=passWord[0];
    matrxPass[1][0]=passWord[1];
    matrxPass[0][1]=passWord[2];
    matrxPass[1][1]=passWord[3];
    matrxPass[0][2]=passWord[4];
    matrxPass[1][2]=passWord[5];
    matrxPass[0][3]=passWord[6];
    matrxPass[1][3]=passWord[7];
    mostrarMatriz(2,4,matrxPass);

    for(int i=0; i<2; i++){
        for(int k=0; k<4; k++){
            decryptPass[i][k] = 0;
        }
    }
    for(int i=0; i<2; i++){
        for(int j=0; j<2; j++){
            for(int k=0; k<4; k++){
                decryptPass[i][k] = decryptPass[i][k] + (decrypt[i][j] * matrxPass[j][k]);
            }
        }
    }

    printf("Matris desencriptada:\n");
    mostrarMatriz(2,4,decryptPass);
}
///Usuarios predeterminados:
void addUsers(int valids,stUser users[],char nameFile[]){
    FILE *fileOpen = fopen(nameFile, "wb");
    if(fileOpen!=NULL){
        for(int i=0; i<valids; i++){
            fwrite(&users[i],sizeof(stUser),1,fileOpen);
        }
        fclose(fileOpen);
    }else{
        printf("Data error. The file could not be opened.\n");
    }
}
///Agregar un usuario:
int validateUserName(char userName[],char nameFile[]){
    int flag=0;
    stUser aux;
    FILE *fileOpen = NULL;
    fileOpen = fopen(nameFile,"rb");
    if(fileOpen!=NULL){
        while(!feof(fileOpen) && flag==0){
            fread(&aux,sizeof(stUser),1,fileOpen);
            if(strcmp(aux.userName,userName)==0){
                flag=1;
            }
        }
        fclose(fileOpen);
    }else{
        printf("ERROR de datos. No se pudo abrir el archivo.\n");
    }
    return(flag);
}
///Agregar un usuario:
void addUser(char nameE[],char userNameE[],char passWordE[],char nameFileUser[],char nameFileTrinket[]){
    FILE *fileOpenUsers = NULL;
    FILE *fileOpenTrinkets = NULL;
    stUser newUser;
    stUser auxUser;
    stTrinket auxTrinket[5];

    fileOpenUsers = fopen(nameFileUser, "rb");
    if(fileOpenUsers!=NULL){
        fseek(fileOpenUsers,0,SEEK_END);
        fseek(fileOpenUsers,sizeof(stUser)*(-1),SEEK_CUR);
        fread(&auxUser,sizeof(stUser),1,fileOpenUsers);
        fclose(fileOpenUsers);
    }else{
        printf("Data error. The file could not be opened.\n");
    }

    fileOpenTrinkets = fopen(nameFileTrinket, "rb");
    if(fileOpenTrinkets!=NULL){
        for(int i=0; i<4; i++){
            fread(&auxTrinket[i],sizeof(stTrinket),1,fileOpenTrinkets);
        }
        fclose(fileOpenTrinkets);
    }else{
        printf("Data error. The file could not be opened.\n");
    }

    fileOpenUsers = fopen(nameFileUser, "ab");
    if(fileOpenUsers!=NULL){
        strcpy(newUser.name,nameE);
        strcpy(newUser.userName,userNameE);
        strcpy(newUser.password,passWordE);
        newUser.dificult=1;
        newUser.idUser=(auxUser.idUser+1);
        newUser.gold=0;
        newUser.type=0;
        newUser.active=1;
        newUser.dificult=1;
        newUser.dungeonlvl=1;
        strcpy(newUser.dungeonType,"Las Ruinas");
        newUser.records=0;
        newUser.posHeros[0]=0;
        newUser.posHeros[1]=1;
        newUser.posHeros[2]=2;
        newUser.availableHeros[0]=0;
        newUser.availableHeros[1]=1;
        newUser.availableHeros[2]=2;
        newUser.validsAvailableHeros=3;
        newUser.trinkets[0]=auxTrinket[0];
        newUser.trinkets[1]=auxTrinket[1];
        newUser.trinkets[2]=auxTrinket[2];
        newUser.trinkets[3]=auxTrinket[3];
        fwrite(&newUser,sizeof(stUser),1,fileOpenUsers);
        fclose(fileOpenUsers);
    }else{
        printf("Data error. The file could not be opened.\n");
    }
}

///Mostrar usuarios: funcion de desarrollo
void searchListUsers(char nameFile[]){
    stUser aux[30];
    int valids=0;
    FILE * fileOpen = fopen(nameFile,"rb");
    if(fileOpen!=NULL){
        while(!feof(fileOpen)){
            fread(&aux[valids],sizeof(stUser),1,fileOpen);
            if(!feof(fileOpen)){
                valids++;
            }
        }
        fclose(fileOpen);
    }else{
        printf("Data error. The file could not be opened.\n");
    }
    printf("Lista de usuarios:\n");
    for(int i=0; i<valids; i++){
        printf("-------------\n");
        printf("Id usuario:..%d..\n",aux[i].idUser);
        printf("Nombre:..%s..\n",aux[i].name);
        printf("Username:..%s..\n",aux[i].userName);
        printf("Password:..%s..\n",aux[i].password);
        printf("Progreso:..%d..\n",aux[i].gold);
        printf("Type:..%c..\n",aux[i].type);
        printf("dificult:..%c..\n",aux[i].dificult);
        printf("Ultimo lvl dungeon:..%d..\n",aux[i].dungeonlvl);
        printf("Ultimo dungeon:..%s..\n",aux[i].dungeonType);
        //printf("Heroe 1:..%s..\n",aux[i].heroes[0].name);
        printf("Trinket 1:..%s..\n",aux[i].trinkets[0].nameTrinket);
        /*
        printf("Heroes:\n");
        printf("Cruzado:..%d..\n",aux[i].cruzader);
        printf("Vestal:..%d..\n",aux[i].vestal);
        printf("Bandido:..%d..\n",aux[i].bandit);
        printf("Doctor de la plaga:..%d..\n",aux[i].plagueDoctor);
        */
        printf("-------------\n");
    }
}
///validar usuario logeado
int whoAreYou(char userNameE[],char passWordE[],stUser userOn[],char findFile[]){
    int flag=0;
    stUser aux;

    FILE *fil = fopen(findFile,"rb");
    if(fil!=NULL){
        while(!feof(fil) && flag==0){
            if(fread(&aux,sizeof(stUser),1,fil)>0){
                if(strcmp(aux.userName,userNameE)==0){
                    if(strcmp(aux.password,passWordE)==0){
                        userOn[0]=aux;
                        flag=1;
                    }
                }
            }
        }
        fclose(fil);
    }else{
        printf("Data error. The file could not be opened.\n");
    }
    return(flag);
}
///Validar algun dato de users 0 o 1
int validateUser(int condition){
    int flag=0;
    if(condition == 1){
        flag=1;
    }
    return(flag);
}
///store trinkets
void storeTrinket(stTrinket listTrinket[],char nameFileTrinket[]){
    FILE *fileTrinket = NULL;
    int count=0;
    int position=0;

    stTrinket aux;

    fileTrinket = fopen(nameFileTrinket,"rb");
    if(fileTrinket!=NULL){
        while(count<3){
            position=rand()%30;
            fseek(fileTrinket,sizeof(stTrinket)*(position),SEEK_SET);
            fread(&aux,sizeof(stTrinket),1,fileTrinket);
            listTrinket[count]=aux;
        }
        fclose(fileTrinket);
    }else{
        printf("ERROR!");
    }
}
///Validacion de passWord
int validatePass(char pass[],stUser userOn[]){
    int flag=0;
    if(strcmp(userOn[0].password,pass)){
        flag=1;
    }
    return(flag);
};
///Cambiar passWord
void changePass(char newPass[],stUser userOn[]){
    strcpy(userOn[0].password,newPass);
};
///Actualizar usuario
void updateUser(stUser userOn[],char fileName[]){
    FILE * fileOpen = NULL;
    stUser aux;
    int flag=0;
    int pos=0;

    fileOpen = fopen(fileName,"r+b");
    if(fileOpen!=NULL){
        while(!feof(fileOpen) && flag==0){
            fread(&aux,sizeof(stUser),1,fileOpen);
            if(aux.idUser == userOn[0].idUser){
                pos=ftell(fileOpen)-sizeof(stUser);
                fseek(fileOpen,pos,SEEK_SET);
                fwrite(&userOn[0], sizeof(stUser), 1, fileOpen);
                flag=1;
            }
        }
        fclose(fileOpen);
    }else{
        printf("ERROR!");
    }
};
///Baja y Alta logica de un usuario
void changeState(stUser userOn[], int position,char fileName[]){
    if(userOn[position].active==0){
        userOn[position].active=1;
    }else{
        userOn[position].active=0;
    }

    FILE * fileOpen = NULL;
    stUser aux;
    int flag=0;
    int pos=0;

    fileOpen = fopen(fileName,"r+b");
    if(fileOpen!=NULL){
        while(!feof(fileOpen) && flag==0){
            fread(&aux,sizeof(stUser),1,fileOpen);
            if(aux.idUser == userOn[position].idUser){
                pos=ftell(fileOpen)-sizeof(stUser);
                fseek(fileOpen,pos,SEEK_SET);
                fwrite(&userOn[position], sizeof(stUser), 1, fileOpen);
                flag=1;
            }
        }
        fclose(fileOpen);
    }else{
        printf("ERROR!");
    }
};
///Buscar un usuario por su ID
int findUserForId(int idUser,stUser userOn[],char nameFile[]){
    stUser aux;
    int flag=0;
    FILE * fileOpen = NULL;

    fileOpen = fopen(nameFile, "rb");
    if(fileOpen!=NULL){
        while(!feof(fileOpen) && flag==0){
            fread(&aux, sizeof(stUser), 1, fileOpen);
            if(aux.idUser == idUser){
                userOn[1]=aux;
                flag=1;
            }
        }
        fclose(fileOpen);
    }else{
        printf("Error!\n");
    }
    return(flag);
}

///Funcion buscar un usuario por userName
int findUserForUserName(char userNameE[],stUser userOn[],char nameFile[]){
    stUser aux;
    int flag=0;
    FILE * fileOpen = NULL;

    fileOpen = fopen(nameFile, "rb");
    if(fileOpen!=NULL){
        while(!feof(fileOpen) && flag==0){
            fread(&aux, sizeof(stUser), 1, fileOpen);
            if(strcmp(aux.userName,userNameE)==0){
                userOn[1]=aux;
                flag=1;
            }
        }
        fclose(fileOpen);
    }else{
        printf("Error!\n");
    }
    return(flag);
}
///Guardar en un array los 5 usuarios con records mas altos.
void higherRecords(stUser listUsers[],char fileName[]){
    FILE * fileOpen=NULL;
    stUser aux[40];
    int i=0;
    fileOpen = fopen(fileName, "rb");
    if(fileOpen!=NULL){
        while(!feof(fileOpen)){
            fread(&aux[i],sizeof(stUser),1,fileOpen);
            if(!feof(fileOpen)){
                i++;
            }
        }
        fclose(fileOpen);
    }else{
        printf("Error");
    }
    organizeList(i,aux);
    for(int i=0;i<5;i++){
        listUsers[i]=aux[i];
    }
}
///store heros
void storeHeros(int listHero[]){
    FILE *fileHeros = NULL;
    int count=0;
    int flag=0;
    int position1=0;
    int position2=0;
    int position3=0;

    position1=rand()%13;
    while(flag==0){
        position2=rand()%13;
        if(position1==position2){
            position2=rand()%13;
        }else{
            position3=rand()%13;
            if(position3==position1 || position3==position2){
                position3=rand()%13;
            }else{
                flag=1;
            }
        }
    }
    listHero[0]=position1;
    listHero[1]=position2;
    listHero[2]=position3;
}
///Lista de heroes de usuario
int availableHerosList(stEntity listAvailable[], stEntity listHero[],stUser userOn[]){
    int i=0;
    for(i=0; i<userOn[0].validsAvailableHeros; i++){
        listAvailable[i]=listHero[userOn[0].availableHeros[i]];
    }
    return(i);
}
