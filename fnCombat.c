#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>
#include <locale.h>

#include "fnUser.h"

///Funciones de Combate
///Creador de entidades
void createEntity(stEntity entity[], int pos,char nameE[],int heroMonsterE,int healthE,int healE, int damagMinE, int damagMaxE, int armorE, int hitE, int dodgeE, int stunE,int poisonE, int bleedE,stSkills skills[])
{
    //int userBoaE
    //entity[pos].userBoa=NULL;
    strcpy(entity[pos].name,nameE);
    entity[pos].heroMonster = heroMonsterE;
    entity[pos].hp = healthE;
    entity[pos].heal = healE;
    entity[pos].damageMin = damagMinE;
    entity[pos].damageMax = damagMaxE;
    entity[pos].armor = armorE;
    entity[pos].hit = hitE;
    entity[pos].dodge = dodgeE;
    entity[pos].poisonResist = poisonE;
    entity[pos].stunResist = stunE;
    entity[pos].bleedResist = bleedE;
    entity[pos].contStun=0;
    entity[pos].contPoison=0;
    entity[pos].contBleed=0;
    entity[pos].contArmor=0;
    entity[pos].buffArmor=0;
    entity[pos].debufBleed=0;
    entity[pos].debufPoison=0;
    entity[pos].skills[0]=skills[0];
    entity[pos].skills[1]=skills[1];
    entity[pos].skills[2]=skills[2];
    entity[pos].skills[3]=skills[3];
    entity[pos].skills[4]=skills[4];
    entity[pos].skills[5]=skills[5];
};
///Creador de dungeons
void createDungeon(stDungeon dungeonE[], int pos,char nameDungeonsE[],int lvlE,stEntity monster1E,stEntity monster2E,stEntity monster3E)
{
    strcpy(dungeonE[pos].type,nameDungeonsE);
    dungeonE[pos].lvl=lvlE;
    dungeonE[pos].enemyTeam[0]= monster1E;
    dungeonE[pos].enemyTeam[1]= monster2E;
    dungeonE[pos].enemyTeam[2]= monster3E;
}
///Creador de habilidades
void createSkills(stSkills entity[],int pos,char nameE[],int damageE,int healE,int armorE,char typeE,char objetiveE,char effectType1E,char effectType2E,int probE,int ally1E,int ally2E,int ally3E,int objetive1E,int objetive2E,int objetive3E)
{
    strcpy(entity[pos].name,nameE);
    entity[pos].damage=damageE;
    entity[pos].heal=healE;
    entity[pos].armor=armorE;
    entity[pos].type=typeE;
    entity[pos].type=typeE;
    entity[pos].objetive=objetiveE;
    entity[pos].effectType1=effectType1E;
    entity[pos].effectType2=effectType2E;
    entity[pos].prob=probE;
    entity[pos].ally1=ally1E;
    entity[pos].ally2=ally2E;
    entity[pos].ally3=ally3E;
    entity[pos].objetive1=objetive1E;
    entity[pos].objetive2=objetive2E;
    entity[pos].objetive3=objetive3E;
};
///Creador de Trinkets
void createTrinket(stTrinket trinkets[], int numE, char nameObjecE[], int buffoHPE, int buffoDamageE, int buffoArmorE,int buffoHitE,int buffoDodgeE,int buffoPoisonE, int buffoStunE, int buffoBleddE, int buffoHealE)
{
    strcpy(trinkets[numE].nameTrinket,nameObjecE);///Nombre
    trinkets[numE].buffDamage= buffoDamageE;
    trinkets[numE].buffHeal= buffoHealE;
    trinkets[numE].buffArmor= buffoArmorE;
    trinkets[numE].buffHP= buffoHPE;
    trinkets[numE].buffHit= buffoHitE;
    trinkets[numE].buffDodge= buffoDodgeE;
    trinkets[numE].buffStun= buffoStunE;
    trinkets[numE].buffPoison= buffoPoisonE;
    trinkets[numE].buffBledd= buffoBleddE;
};
///Mostrar dungeons:
/*void showList(int validos,stDungeon dungeons[])
{
    for(int i=0; i<validos; i++)
    {
        printf("-------------\n");
        printf("Nombre:..%s..\n",dungeons[i].type);
        printf("lvl:..%d..\n",dungeons[i].lvl);
        printf("Entidad1:..%s..\n",dungeons[i].enemyOne.name);
        printf("Entidad2:..%s..\n",dungeons[i].enemyTwo.name);
        printf("Entidad3:..%s..\n",dungeons[i].enemyThree.name);
        printf("-------------\n");
    }
}*/

void infoTrinkets(stTrinket trinkets[], int cant)
{
    int i=0;
    while(i<cant)
    {
        printf("\n---------------------");
        printf("\n name:--------%s", trinkets[i].nameTrinket);
        printf("\n Damage:------%d", trinkets[i].buffDamage);
        printf("\n Armor:-------%d", trinkets[i].buffArmor);
        printf("\n Hit:---------%d", trinkets[i].buffHit);
        printf("\n Dodge:-------%d", trinkets[i].buffDodge);
        printf("\n Poison:------%d", trinkets[i].buffPoison);
        printf("\n Stun:--------%d", trinkets[i].buffStun);
        printf("\n Bleed:-------%d", trinkets[i].buffBledd);
        printf("\n---------------------");
        i++;
    }
};
///Buscar dungeon
void searchListDungeons(stDungeon dungeonList[],char nameFile[])
{
    FILE * fileOpen=NULL;
    int i=0;
    fileOpen = fopen(nameFile, "rb");
    if(fileOpen!=NULL)
    {
        while(!feof(fileOpen))
        {
            fread(&dungeonList[i],sizeof(stDungeon),1,fileOpen);
            if(!feof(fileOpen))
            {
                i++;
            }
        }
        fclose(fileOpen);
    }
    else
    {
        printf("Data error. The file could not be opened.\n");
    }
    //showList(i,dungeons);
    //return i;
}

///Dungeons predeterminados
void addDungeonsFile(int validos,stDungeon dungeons[],char nameFileListDungeos[])
{
    int i=0;
    FILE *fil= fopen(nameFileListDungeos,"wb");
    if(fil!=NULL)
    {
        while(i<validos)
        {
            fwrite(&dungeons[i],sizeof(stDungeon),1,fil);
            i++;
        }
        fclose(fil);
    }
    else
    {
        printf("Data error. The file could not be opened.\n");
    }
};
///Cargar los heroes a un archivo:
void showListHero(int valids,stEntity hero[])
{
    for(int i=0; i<valids; i++)
    {
        printf("-------------\n");
        printf("Nombre:..%s.. Pos: ..%d..\n",hero[i].name, i);
        printf("-------------\n");
    }
}
void addHeroFile(int valids,stEntity ent[],char nameFile[])
{
    FILE *filOpen = fopen(nameFile,"wb");
    if(filOpen!=NULL)
    {
        for(int i=0; i<valids; i++)
        {
            fwrite(&ent[i],sizeof(stEntity),1,filOpen);
        }
        fclose(filOpen);
    }
    else
    {
        printf("Data error. The file could not be opened.\n");
    }
}


///CARGAR DUNGEON:
void dungeon(stUser userOn[],stDungeon dungeonOn[],char nameFill[])
{
    FILE * fileOpen = NULL;
    stDungeon aux;
    int flag=0;
    int i=0;
    fileOpen= fopen(nameFill,"rb");
    if(fileOpen!=NULL)
    {
        while(!feof(fileOpen) && flag==0)
        {
            fread(&aux,sizeof(stDungeon),1,fileOpen);
            if( strcmp(aux.type,userOn[0].dungeonType)==0 && aux.lvl==userOn[0].dungeonlvl )
            {
                dungeonOn[0]=aux;
                flag=1;
            }
            i++;
        }
        fclose(fileOpen);
    }
    else
    {
        printf("Data error. The file could not be opened.\n");
    }
}

///Cargar los heroes a un archivo:
void showListHeros(int valids,stEntity heros[])
{
    for(int i=0; i<valids; i++)
    {
        printf("-------------\n");
        printf("Nombre:..%s.. Pos: ..%d..\n",heros[i].name, i);
        printf("-------------\n");
    }
}
int searchListHero(stEntity heros[],char nameFile[])
{
    int i=0;
    FILE *fil = fopen(nameFile, "rb");
    if(fil!=NULL)
    {
        while(!feof(fil))
        {
            fread(&heros[i],sizeof(stEntity),1,fil);
            if(!feof(fil))
            {
                i++;
            }
        }
        fclose(fil);
    }
    else
    {
        printf("Data error. The file could not be opened.\n");
    }
    //printf("i= ..%d..", i);
    //showListHeros(i,heros);
    return(i);
}

///SELECCION DE HEROES:
int validateSelectHero(int posHero)
{
    int flag=0;
    posHero=posHero-1;
    if(posHero>=0 && posHero<15)
    {
        flag=1;
    }
    else
    {
        //printf("Heroe invalido. Elija denuevo.\n");
    }
    return(flag);
}

///Ataque de Hero daño base
int attackHero(stEntity entity) // emisor [return damage p]
{
    int damage=0;
    int hitProb=rand()%101;
    damage = entity.damageMin+(rand()%entity.damageMax);
    if(hitProb>entity.hit)
    {
        damage=0;
    }
    return(damage);
}
///Ataque de Monster daño base
int attackMonster(stEntity entity) // emisor [return damage p]
{
    int damage=0;
    int hitProb=rand()%101;
    damage = (rand()%entity.damageMax);
    if(damage>=0 && damage<=3)
    {
        damage=damage+3;
    }
    if(hitProb>entity.hit)
    {
        damage=0;
    }
    return(damage);
}
///Danio recibido
int proceduralDamage(int damage, stEntity objective,char type) // danio - receptor - skill type
{
    int prob=rand()%101;
    int damageFinal=damage;
    if(prob>objective.dodge)
    {
        damageFinal=damage-objective.armor;
        if(type=='b')
        {
            damageFinal=((damageFinal*(100-objective.bleedResist))/100);
        }
        if(type=='p')
        {
            damageFinal=((damageFinal*(100-objective.poisonResist))/100);
        }
    }
    return(damageFinal);
}
void action(int entPos,stEntity ent[],int objPos,stEntity obj[],int skillPos,int dificult)
{
    //printf("\n%s",obj[0].name);
    //printf("\n%s",ent[0].name);
    //system("pause");
    char ope=ent[entPos].skills[skillPos].type;
    int damage=0;
    int heal=0;
    int result=0;
    switch(ope)
    {
    case 'a':
        if(ent[entPos].heroMonster==1)
        {
            damage = damage + attackHero(ent[entPos]);  ///Damage==0 fallo(hit)    Damage!=0 golpe objetivo
        }
        else
        {
            damage = damage + attackMonster(ent[entPos]);  ///Damage==0 fallo(hit)    Damage!=0 golpe objetivo
        }
        if(damage!=0)
        {
            damage = damage + ent[entPos].skills[skillPos].damage;    /// Suma daño de la habilidad
            damage = proceduralDamage(damage, obj[objPos], ent[entPos].skills[skillPos].effectType1);   ///Reduccion de daño por armadura, prob de dodgear y probavilidades de resisti tipo de daño  --  damage==0(dodge o resist)
            if(damage!=0)
            {
                ///Funcion golpear
                if(ent[entPos].skills[skillPos].effectType1=='s')
                {
                    ///Funcion stunea al objetivo
                    obj[objPos].contStun=3;
                }
                if(ent[entPos].skills[skillPos].effectType1=='p')
                {
                    ///Funcion deja debuf de envenenado
                    obj[objPos].contPoison=3;
                }
                if(ent[entPos].skills[skillPos].effectType1=='b')
                {
                    ///Funcion deja debuf de sangrado
                    obj[objPos].contBleed=3;
                }
            };
            if(ent[entPos].heroMonster==0)    ///Monster
            {
                damage *= dificult;
            }
            result = damage*(-1);
        }
        break;

    case 's':
        if(ent[entPos].skills[skillPos].effectType1=='h')
        {
            heal = ent[entPos].heal + ent[entPos].skills[skillPos].heal;    ///Funcion curar
            if(ent[entPos].skills[skillPos].effectType2=='p')
            {
                obj[objPos].contPoison=0;  ///Funcion curar poison
            }
            if(ent[entPos].skills[skillPos].effectType2=='b')
            {
                obj[objPos].contBleed=0;  ///Funcion curar bleed
            }
            if(ent[entPos].skills[skillPos].effectType2=='a')
            {
                obj[objPos].contArmor=3;   ///Funcion sumar armor
            }
            result=heal;
        }
        if(ent[entPos].skills[skillPos].effectType1=='a')
        {
            obj[objPos].contArmor=3;
        }
        break;

    default:
        printf("ERROR!");
    };
    obj[objPos].hp += result;
}

///Victoria o derrota
int stillAliveTeam(stEntity heros[],stDungeon dungeonOn[])
{
    int alive;
    if(heros[0].hp<=0 && heros[1].hp<=0 && heros[2].hp<=0)
    {
        alive=2;
    }
    else if(dungeonOn[0].enemyTeam[0].hp<=0 && dungeonOn[0].enemyTeam[1].hp<=0 && dungeonOn[0].enemyTeam[2].hp<=0)
    {
        alive=1;
    }
    else
    {
        alive=0;
    };
    return alive;// 0== continue / 1==heroWin / 2==enemyWin
};
///Pasar turno
int passTurn(stEntity entity[],int entityPos, int dificultMode)
{
    int alive=0;
    while(alive==0)
    {
        if(entity[entityPos].hp>0 && entity[entityPos].contStun==0)
        {
            alive=1;
        }
        else
        {
            if(entityPos<2)
            {
                entityPos++;
            }
            else
            {
                entityPos=0;
                alive=1;
            };
            entity[entityPos].contBleed=0;
            entity[entityPos].contStun=0;
            entity[entityPos].contPoison=0;
            entity[entityPos].contArmor=0;
        };
        if (entity[entityPos].contStun>0)
        {
            entity[entityPos].contStun--;
        }
        else {};
        if (entity[entityPos].contBleed>0)
        {
            entity[entityPos].contBleed--;
            entity[entityPos].hp -= 2 + dificultMode;
        }
        else {};
        if (entity[entityPos].contPoison>0)
        {
            entity[entityPos].contPoison--;
            entity[entityPos].hp -= 2 + dificultMode;
        }
        else {};
        if (entity[entityPos].contArmor>0)
        {
            entity[entityPos].contArmor--;
            entity[entityPos].armor--;
            //if(entity[entityPos].armor==0){}
        }
    };
    if(entityPos==3)
    {
        entityPos=0;
    }
    return entityPos; //pos hero
};
///salvar heros en archi y heroTeam
void saveTeam(int pos1, int pos2, int pos3, stUser userOn[], char fileName[])
{
    userOn[0].posHeros[0]=pos1;
    userOn[0].posHeros[1]=pos2;
    userOn[0].posHeros[2]=pos3;
    stUser aux;
    int flag=0;
    int pos=-1;

    FILE * fileOpen = NULL;
    fileOpen = fopen(fileName, "r+b");
    if(fileOpen!=NULL)
    {
        while(!feof(fileOpen) && flag==0)
        {
            fread(&aux,sizeof(stUser),1,fileOpen);
            if(aux.idUser==userOn[0].idUser)
            {
                pos=ftell(fileOpen)-sizeof(stUser);
                fseek(fileOpen,pos,SEEK_SET);
                fwrite(&userOn[0], sizeof(stUser), 1, fileOpen);
                flag=1;
            }
        }
        fclose(fileOpen);
    }
    else
    {
        printf("ERROR!. No pudo leerse el archivo");
    }
}
///Cambiar dungeon
void selectDungeon(stUser userOn[], char nameDungeon[], int lvlDungeon)
{
    strcpy(userOn[0].dungeonType,nameDungeon);
    userOn[0].dungeonlvl=lvlDungeon;
}
///records
int positionMinor(int pos,int valids,stUser listUsers[])
{
    stUser Higher = listUsers[pos];
    int posHigher = pos;
    int j = pos + 1;
    while(j<valids)
    {
        if(Higher.records < listUsers[j].records)
        {
            Higher = listUsers[j];
            posHigher = j;
        }
        j++;
    }
    return(posHigher);
}

void organizeList(int valids,stUser listUsers[])
{
    stUser aux;
    int posHigher=0;
    int i=0;
    while(i<valids-1)
    {
        posHigher = positionMinor(i,valids,listUsers);
        aux = listUsers[posHigher];
        listUsers[posHigher] = listUsers[i];
        listUsers[i]=aux;
        i++;
    }
}

