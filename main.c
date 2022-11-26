#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>
#include <locale.h>

#include "fnUser.h"
#include "gotoxy.h"


int main()
{
    srand(time(NULL));
    //setlocale(LC_ALL,"Spanish");
    int dificultMode=1;
    int flagUser=0;
    srand(time(NULL));

    ///Entidades Heroes
    //stEntity *heros = malloc(sizeof(stEntity)*15);

    ///Trinkets
    stTrinket trinkets[80];

    ///user
    char userName[30];
    char passWord[20];

    char newName[30];
    char newSurName[30];
    char newUserName[30];
    char newPassWord[20];

    ///Entidades standard
    stEntity hero[20];
    stEntity monster[40];

    ///Skills Heroes:
    stSkills skillsCruzader[6];
    stSkills skillsBandolero[6];
    stSkills skillsVestal[6];
    stSkills skillsDoctorDeLaPlaga[6];
    stSkills skillsDiabla[6];
    stSkills skillsRompeEscudos[6];
    stSkills skillsLeproso[6];
    stSkills skillsBufon[6];
    stSkills skillsCazaRecompensas[6];
    stSkills skillsFlagelante[6];
    stSkills skillsFusilera[6];
    stSkills skillsHeraldo[6];
    stSkills skillsMaestroDeCanes[6];
    stSkills skillsOcultista[6];


    ///Skills Monsters:
    ///Las Ruinas:
    stSkills skillsSoldadoEsqueleto[2];
    stSkills skillsCortesanoEsqueleto[2];
    stSkills skillsArbalesteroEsqueleto[2];
    stSkills skillsDefensorEsqueleto[2];
    stSkills skillsLanceroEsqueleto[2];
    stSkills skillsCapitanEsqueleto[2];
    stSkills skillsPortadorEsqueleto[2];
    stSkills skillsNigromante[2];
    stSkills skillsProfeta[2];
    ///Catacumbas:
    stSkills skillsJavaliTriturador[2];
    stSkills skillsCerdoDegollador[1];
    stSkills skillsCerdoMiserable[1];
    stSkills skillsTamborPorcino[2];
    stSkills skillsCerdoLancero[2];
    stSkills skillsCerdotauro[2];
    stSkills skillsPrincipeCerdo[2];
    stSkills skillsWilbur[2];
    ///Cala:
    stSkills skillsPiraniaArponera[1];
    stSkills skillsPiraniaChaman[2];
    stSkills skillsGuardianOctopodo[2];
    stSkills skillsCaracolMarino[1];
    stSkills skillsMedusa[1];
    stSkills skillsSumergido[1];
    stSkills skillsTrituradorTenazario[2];
    stSkills skillsSirena[2];
    stSkills skillsTripulacionAhogada[2];
    stSkills skillsContramaestre[1];
    ///Patio:
    stSkills skillsSirviente[2];
    stSkills skillsDon[2];
    stSkills skillsCortesana[2];
    stSkills skillsSuplicante[1];
    stSkills skillsMosquito[1];
    stSkills skillsPortero[2];
    stSkills skillsCaballero[2];
    stSkills skillsBaron[2];
    stSkills skillsCondesa[2];

    ///Dungeons:
    stDungeon dungeons[15];

    stUser users[30];
    char nameFileListUsers[30];
    char nameFileListDungeos[30];
    char nameFileListHero[30];
    char nameFileListTrinkets[30];
    int danioHero,danioMonster,danioResibido;
    int validsHeros;
    int valueUser=0;

    strcpy(nameFileListTrinkets,"Trinkets list.dat");
    strcpy(nameFileListUsers,"User list.dat");
    strcpy(nameFileListDungeos,"Dungeon list.dat");
    strcpy(nameFileListHero,"Hero list.dat");

    char nameFile[20];
    /////////////////////////////////////////////////////////////////////////

    ///Trinkets:
    char nameTrinkets[80][21]={
        "Accuracy Stone",
        "Bleed Charm",
        "Bleed Stone",
        "Blight Charm",
        "Blight Stone",
        "Critical Stone",
        "Debuff Charm",
        "Debuff Stone",
        "Disease Charm",
        "Health Stone",
        "Stun Stone",
        "Archer's Ring",
        "Bloodied Fetish",
        "Slippery Boots",///"Book of Intuition"
        "Caution Cloak",
        "Damage Stone",
        "Dazzling Charm",
        "Deteriorating Bracer",
        "Reckless Charm"
        /*"Slippery Boots",
        "Snake Oil",
        "speed Stone",
        "Survival Guide",
        "Warrior's Bracer",
        "Warrior's Cap",
        "Bleed Amulet",
        "Blight Amulet",
        "Blood Charm",
        "Bloodthirst Ring",
        "Book of Constitution",
        "Book of Holiness",
        "Book of Rage",
        "Book of Relaxation",
        "Camouflage Cloak",
        "Calming Crystal",
        "Chirurgeon's Charm",
        "Dark Bracer",
        "Debuff Amulet",
        "Heavy Boots",
        "Life Crystal",
        "Move Amulet",
        "Seer Stone",
        "Shimmering Cloak",
        "Solar Bracer",
        "Steady Bracer",
        "Stun Amulet",
        "Surgical Gloves",
        "Swift Cloak",
        "Tenacity Ring",
        "Worrystone",
        "Beast Slayer's Ring",
        "Berserk Charm",
        "Brawler's Gloves",
        "Dark Crown",
        "Eldritch Slayer",
        "Fasting Seal",
        "Feather Crystal",
        "Man Slayer's Ring",
        "Moon Cloak",
        "Moon Ring",
        "Quick Draw Charm",
        "Recovery Charm",
        "Sniper's Ring",
        "Solar Crown",
        "Sun Ring",
        "Sun CloakbuffAttack",
        "Unholy Slayer's Ring",
        "Book of Sanity",
        "Cleansing Crystal",
        "Ethereal Crucifix",
        "Focus Ring",
        "Fortifying Garlic",
        "Hero's Ring",
        "Legendary Bracer",
        "Martyr's Seal",
        "Sun Cloak"
        */
    };
    createTrinket(trinkets,0 , nameTrinkets[0] ,10,0,10 ,10,0 ,0 ,0 ,0,0); ///Accuracy Stone
    createTrinket(trinkets,1 , nameTrinkets[1] ,5 ,0,0  ,0 ,10,0 ,10,0,0); ///Bleed Charm
    createTrinket(trinkets,2 , nameTrinkets[2] ,10,1,0  ,0 ,0 ,0 ,10,0,0); ///Bleed Stone
    createTrinket(trinkets,3 , nameTrinkets[3] ,5 ,0,10 ,0 ,10,0 ,0 ,0,0); ///Blight Charm
    createTrinket(trinkets,4 , nameTrinkets[4] ,10,1,0  ,0 ,10,0 ,0 ,0,0); ///Blight Stone
    createTrinket(trinkets,5 , nameTrinkets[5] ,5 ,1,0  ,0 ,0 ,0 ,0 ,0,2); ///Critical Stone
    createTrinket(trinkets,6 , nameTrinkets[6] ,0 ,2,10 ,0 ,0 ,0 ,0 ,0,1); ///buff Charm
    createTrinket(trinkets,7 , nameTrinkets[7] ,5 ,0,0  ,0 ,0 ,0 ,20,2,0); ///buff Stone
    createTrinket(trinkets,8 , nameTrinkets[8] ,5 ,0,0  ,0 ,0 ,0 ,20,0,1); ///Disease Charm
    createTrinket(trinkets,9 , nameTrinkets[9] ,10,0,5  ,0 ,0 ,0 ,0 ,2,0); ///Health Stone
    createTrinket(trinkets,10, nameTrinkets[10],10,5,0  ,0 ,0 ,20,0 ,0,0); ///Stun Stone
    createTrinket(trinkets,11, nameTrinkets[11],0 ,3,20 ,5 ,0 ,0 ,0 ,0,0); ///Archer's Ring
    createTrinket(trinkets,12, nameTrinkets[12],2 ,0,0  ,0 ,0 ,0 ,20,3,0); ///Bloodied Fetish
    createTrinket(trinkets,13, nameTrinkets[13],0 ,0,0  ,30,0 ,10,0 ,0,2); ///Book of Intuition
    createTrinket(trinkets,14, nameTrinkets[14],1 ,0,0  ,20,0 ,0 ,0 ,0,3); ///Caution Cloak
    createTrinket(trinkets,15, nameTrinkets[15],10,2,30 ,0 ,0 ,0 ,0 ,0,0); ///Damage Stone
    createTrinket(trinkets,16, nameTrinkets[16],5 ,0,20 ,20,0 ,0 ,0 ,0,0); ///Dazzling Charm
    createTrinket(trinkets,17, nameTrinkets[17],-5,4,-10,0 ,0 ,0 ,0 ,0,0); ///Deteriorating Bracer
    createTrinket(trinkets,18, nameTrinkets[18],5 ,2,10 ,0 ,0 ,0 ,0 ,0,0); ///Reckless Charm
    /*
    createTrinket(trinkets,19, nameTrinkets[19],0,0,2,0,3,0,1,0,0); ///Slippery Boots
    createTrinket(trinkets,20, nameTrinkets[20],-6,0,0,0,0,2,2,2,4); ///Snake Oil
    createTrinket(trinkets,21, nameTrinkets[21],0,2,0,2,2,0,0,0,0); ///Speed Stone
    createTrinket(trinkets,22, nameTrinkets[22],0,0,2,2,2,2,2,2,0); ///Survival Guide
    createTrinket(trinkets,23, nameTrinkets[23],10,0,2,0,0,0,0,0,0); ///Warrior's Bracer
    createTrinket(trinkets,24, nameTrinkets[24],15,0,3,0,0,0,0,0,0); ///Warrior's Cap
    createTrinket(trinkets,25, nameTrinkets[25],10,0,0,0,0,0,0,3,3); ///Bleed Amulet
    createTrinket(trinkets,26, nameTrinkets[26],0,0,0,0,3,3,3,0,0); ///Blight Amulet
    createTrinket(trinkets,27, nameTrinkets[27],0,0,0,2,2,0,3,3,0); ///Blood Charm
    createTrinket(trinkets,28, nameTrinkets[28],-10,3,-3,3,3,0,3,3,0); ///Bloodthirst Ring
    createTrinket(trinkets,29, nameTrinkets[29],15,0,0,0,0,0,0,0,0); ///Book of Constitution
    createTrinket(trinkets,30, nameTrinkets[30],0,0,0,0,0,0,0,0,5); ///Book of Holiness
    */
    /*
    createTrinket(trinkets,i, nameTrinkets[i],0,0,0,0,0,0,0,0); ///Book of Rage
    createTrinket(trinkets,i, nameTrinkets[i],0,0,0,0,0,0,0,0); ///Book of Relaxation
    createTrinket(trinkets,i, nameTrinkets[i],0,0,0,0,0,0,0,0); ///Camouflage Cloak
    createTrinket(trinkets,i, nameTrinkets[i],0,0,0,0,0,0,0,0); ///Calming Crystal
    createTrinket(trinkets,i, nameTrinkets[i],0,0,0,0,0,0,0,0);  ///Chirurgeon's Charm
    createTrinket(trinkets,i, nameTrinkets[i],0,0,0,0,0,0,0,0); ///Dark Bracer
    createTrinket(trinkets,i, nameTrinkets[i],0,0,0,0,0,0,0,0);  ///Debuff Amulet
    createTrinket(trinkets,i, nameTrinkets[i],0,0,0,0,0,0,0,0); ///Heavy Boots
    createTrinket(trinkets,i, nameTrinkets[i],0,0,0,0,0,0,0,0);  ///Life Crystal
    createTrinket(trinkets,i, nameTrinkets[i],0,0,0,0,0,0,0,0); ///Move Amulet
    createTrinket(trinkets,i, nameTrinkets[i],0,0,0,0,0,0,0,0); ///Seer Stone
    createTrinket(trinkets,i, nameTrinkets[i],0,0,0,0,0,0,0,0); ///Shimmering Cloak
    createTrinket(trinkets,i, nameTrinkets[i],0,0,0,0,0,0,0,0); ///Solar Bracer
    createTrinket(trinkets,i, nameTrinkets[i],0,0,0,0,0,0,0,0); ///Steady Bracer
    createTrinket(trinkets,i, nameTrinkets[i],0,0,0,0,0,0,0,0);  ///Stun Amulet
    createTrinket(trinkets,i, nameTrinkets[i],0,0,0,0,0,0,0,0); ///Surgical Gloves
    createTrinket(trinkets,i, nameTrinkets[i],0,0,0,0,0,0,0,0); ///Swift Cloak
    createTrinket(trinkets,i, nameTrinkets[i],0,0,0,0,0,0,0,0); ///Tenacity Ring
    createTrinket(trinkets,i, nameTrinkets[i],0,0,0,0,0,0,0,0); ///Worrystone
    createTrinket(trinkets,i, nameTrinkets[i],0,0,0,0,0,0,0,0); ///Beast Slayer's Ring
    createTrinket(trinkets,i, nameTrinkets[i],0,0,0,0,0,0,0,0); ///Berserk Charm
    createTrinket(trinkets,i, nameTrinkets[i],0,0,0,0,0,0,0,0);  ///Brawler's Gloves
    createTrinket(trinkets,i, nameTrinkets[i],0,0,0,0,0,0,0,0);  ///Dark Crown
    createTrinket(trinkets,i, nameTrinkets[i],0,0,0,0,0,0,0,0); ///Eldritch Slayer's Ring
    createTrinket(trinkets,i, nameTrinkets[i],0,0,0,0,0,0,0,0);  ///Fasting Seal
    createTrinket(trinkets,i, nameTrinkets[i],0,0,0,0,0,0,0,0);  ///Feather Crystal
    createTrinket(trinkets,i, nameTrinkets[i],0,0,0,0,0,0,0,0);  ///Man Slayer's Ring
    createTrinket(trinkets,i, nameTrinkets[i],0,0,0,0,0,0,0,0); ///Moon Cloak
    createTrinket(trinkets,i, nameTrinkets[i],0,0,0,0,0,0,0,0);  ///Moon Ring
    createTrinket(trinkets,i, nameTrinkets[i],0,0,0,0,0,0,0,0); ///Quick Draw Charm
    createTrinket(trinkets,i, nameTrinkets[i],0,0,0,0,0,0,0,0);  ///Recovery Charm
    createTrinket(trinkets,i, nameTrinkets[i],0,0,0,0,0,0,0,0);  ///Sniper's Ring
    createTrinket(trinkets,i, nameTrinkets[i],0,0,0,0,0,0,0,0); ///Solar Crown
    createTrinket(trinkets,i, nameTrinkets[i],0,0,0,0,0,0,0,0); ///Sun Cloak
    createTrinket(trinkets,i, nameTrinkets[i],0,0,0,0,0,0,0,0);  ///Sun Ring
    createTrinket(trinkets,i, nameTrinkets[i],0,0,0,0,0,0,0,0); ///Unholy Slayer's Ring
    createTrinket(trinkets,i, nameTrinkets[i],0,0,0,0,0,0,0,0);  ///Book of Sanity
    createTrinket(trinkets,i, nameTrinkets[i],0,0,0,0,0,0,0,0);  ///Cleansing Crystal
    createTrinket(trinkets,i, nameTrinkets[i],0,0,0,0,0,0,0,0);  ///Ethereal Crucifix
    createTrinket(trinkets,i, nameTrinkets[i],0,0,0,0,0,0,0,0);  ///Focus Ring
    createTrinket(trinkets,i, nameTrinkets[i],0,0,0,0,0,0,0,0);  ///Fortifying Garlic
    createTrinket(trinkets,i, nameTrinkets[i],0,0,0,0,0,0,0,0);  ///Hero's Ring
    createTrinket(trinkets,i, nameTrinkets[i],0,0,0,0,0,0,0,0);  ///Legendary Bracer
    createTrinket(trinkets,i, nameTrinkets[i],0,0,0,0,0,0,0,0);  ///Martyr's Seal
    */

   ///Nombre Habilidades Heroes:
    ///Cruzado
    char nameSkillsCruzader[6][26]={
        "          Herir          ",
        "          Carga          ",
        "      Baluarte de Fe     ",
        "   Curacion de Batalla   ",
        "     Permanecer Firme    ",
        "      Inquebrantable     "
    };

    ///Bandolero
    char nameSkillsBandolero[6][26]={
        "       Abrir Venas       ",
        "     Tiro de Pistolas    ",
        "   Disparo a Quemarropa  ",
        "    Rafaga de Metralla   ",
        "         Sutileza        ",
        "      Limpiar Armas      "
    };
    ///Vestal
    char nameSkillsVestal[6][26]={
        "      Divina Gracia      ",
        "    Divina Proteccion    ",
        "         Confesar        ",
        "       Luz Cegadora      ",
        "    Cantico Espiritual   ",
        "          Rezar          "
    };
    ///DOctor de la Plaga
    char nameSkillsDoctorDeLaPlaga[6][26]={
        "     Granada de Plaga    ",
        "        Incision         ",
        "   Medicina de Batalla   ",
        "           Rayo          ",
        "       Sanguijuelas      ",
        "      Automedicacion     "
    };
    ///Diabla
    char nameSkillsDiabla[6][26]={
        "         Devastar        ",
        "      Abrirse Camino     ",
        "     Grito Barbarico     ",
        "      Impetu Salvaje     ",
        "    Trance de Batalla    ",
        "          Juerga         "
    };
    ///Rompe Escudos
    char nameSkillsRompeEscudos[6][26]={
        "         Perforar        ",
        "         Empalar         ",
        "        Exposicion       ",
        "  Siseo de la Serpiente  ",
        "    Ojos de Serpiente    ",
        "     Tormeta de Arena    "
    };
    ///Leproso
    char nameSkillsLeproso[6][26]={
        "          Cortar         ",
        "          Purga          ",
        "         Venganza        ",
        "        Solemnidad       ",
        "      Cambiar Vendaje    ",
        "        Cuarentena       "
    };
    ///Bufon
    char nameSkillsBufon[6][26]={
        "          Segar          ",
        "       Grand Finale      ",
        "           Solo          ",
        "          Balada         ",
        "          Burla          ",
        " Cada Rosa Tiene Espinas "
    };
    ///Caza Recompensas
    char nameSkillsCazaRecompensas[6][26]={
        "     Recolectar Botin    ",
        "         Acercar         ",
        "    Bomba Destellante    ",
        "    Marcado para Morir   ",
        "        Patrullar        ",
        "  Asi se hacen las cosas "
    };
    ///Flagelante
    char nameSkillsFlagelante[6][26]={
        "         Castigar        ",
        "        Desangrar        ",
        "         Redimir         ",
        "          Sufrir         ",
        "      Ira del Latigo     ",
        "     Beso del Latigo     "
    };
    ///Fusilera
    char nameSkillsFusilera[6][26]={
        "     Disparo Preciso     ",
        "   Disparo de Perdigon   ",
        "     Granada de Humo     ",
        "     Pistola de Mano     ",
        "     Limpiar Mosquete    ",
        "      Tiro al Plato      "
    };
    ///Heraldo
    char nameSkillsHeraldo[6][26]={
        "         Triturar        ",
        "         Muralla         ",
        "       Pulverizar        ",
        "         Defensor        ",
        "         Reforzar        ",
        "         Bendajes        "
    };
    ///Maestro de Canes
    char nameSkillsMaestroDeCanes[6][26]={
        "         Aporrear        ",
        "       Por la Presa      ",
        "   Aullido de la Manada  ",
        "         Silvido         ",
        "       Mejor Amigo       ",
        "    Perro Terapeutico    "
    };
    ///Ocultista
    char nameSkillsOcultista[6][26]={
        "     Daga Ceremonial     ",
        " Maleficion de Devilidad ",
        "     Manos del Abismo    ",
        "      Reconstruccion     ",
        "      Fuerza Oscura      ",
        "      Ritual Oscuro      "
    };

    ///Nombre Habilidades Monstruos:
    ///Las Ruinas:
    ///Soldado Esqueleto:
    char nameSkillsSoldadoEsqueleto[2][26]={
        "           Tajo          ",
        "    Golpe a la cabeza    "
    };
    ///Cortesano Esqueleto:
    char nameSkillsCortesanoEsqueleto[2][26]={
        "      Copa Tentadora     ",
        "        Cuchillada       "
    };
    ///Arbalestero Esqueleto:
    char nameSkillsArbalesteroEsqueleto[2][26]={
        "          Disparo        ",
        "         Bayoneta        "
    };
    ///Defensor Esqueleto:
    char nameSkillsDefensorEsqueleto[2][26]={
        "      Hoja de Hacha      ",
        "       Peso Muerto       "
    };
    ///Lancero Esqueleto:
    char nameSkillsLanceroEsqueleto[2][26]={
        "         Empalar         ",
        "       Lanzamiento       "
    };
    ///Capitan Esqueleto:
    char nameSkillsCapitanEsqueleto[2][26]={
        "     Golpe Aplastante    ",
        "       Libra Molida      "
    };
    ///Portador Esqueleto:
    char nameSkillsPortadorEsqueleto[2][26]={
        "     Oleada Malvada      ",
        "       Icono Impio       "
    };
    ///Nigromante:
    char nameSkillsNigromante[2][26]={
        "          Corte          ",
        "   Los Muertos Aranian   "
    };
    ///Profeta:
    char nameSkillsProfeta[2][26]={
        "          Alarido        ",
        "         Escombros       "
    };
    ///Catacumbas
    ///Javali Triturador:
    char nameSkillsJavaliTriturador[2][26]={
        "    Corte de Carnicero   ",
        "      Bola y Cadena      "
    };
    ///Cerdo Degollador
    char nameSkillsCerdoDegollador[1][26]={
        "          Gancho         "
    };
    ///Cerdo Miserable
    char nameSkillsCerdoMiserable[1][26]={
        "          Vomito         "
    };
    ///Tambor Porcino
    char nameSkillsTamborPorcino[2][26]={
        "   Tambor de Fatalidad   ",
        "    Tambor de Guerra     "
    };
    ///Cerdo Lancero
    char nameSkillsCerdoLancero[2][26]={
        "       Lanza Pesada      ",
        "      Lanza Afilada      "
    };
    ///Cerdotauro
    char nameSkillsCerdotauro[2][26]={
        "      Lanza de Cerdo     ",
        "     Fiebre de Javali    "
    };
    ///Principe Cerdo
    char nameSkillsPrincipeCerdo[2][26]={
        "  Destruccion Enfurecida ",
        "     Agitado Salvaje     "
    };
    ///Wilbur
    char nameSkillsWilbur[2][26]={
        "         Chillido        ",
        "      Terminar Este!     "
    };
    ///Cala
    ///Pirania Arponera
    char nameSkillsPiraniaArponera[1][26]={
        "     Taja Hacia el Mar   "
    };
    ///Prirania Chaman
    char nameSkillsPiraniaChaman[2][26]={
        "  Llamado de lo profundo ",
        "       Brisa Marina      "
    };
    ///Guardian Octopodo
    char nameSkillsGuardianOctopodo[2][26]={
        "        Cercenar         ",
        "   Barrera de Percebes   "
    };
    ///Caracol Marino
    char nameSkillsCaracolMarino[1][26]={
        "        Salmuera         "
    };
    ///Medusa
    char nameSkillsMedusa[1][26]={
        "    Choque Electrico     "
    };
    ///Sumergido
    char nameSkillsSumergido[1][26]={
        "         Agarre          "
    };
    ///Triturador Tenazario
    char nameSkillsTrituradorTenazario[2][26]={
        "         Pinza           ",
        "    Golpe de Mareas      "
    };
    ///Sirena
    char nameSkillsSirena[2][26]={
        "    Cancion de Deseo     ",
        "      Marea Alta         "
    };
    ///Tripulacion Ahogada
    char nameSkillsTripulacionAhogada[2][26]={
        "         Motin           ",
        "  Beber con los Muertos  "
    };
    ///Contramaestre
    char nameSkillsContramaestre[1][26]={
        "         Ancla!          "
    };
    ///Patio
    ///Sirviente
    char nameSkillsSirviente[2][26]={
        "     Desea Beber?        ",
        "  Servidumbre Infalible  "
    };
    ///Don
    char nameSkillsDon[2][26]={
        "          Sed            ",
        "         Duelo           "
    };
    ///Cortesana
    char nameSkillsCortesana[2][26]={
        "        Susurros         ",
        "    Cuida tus Modales    "
    };
    ///Suplicante
    char nameSkillsSuplicante[1][26]={
        "      Predigestion       "
    };
    ///Mosquito
    char nameSkillsMosquito[1][26]={
        "       Picadura          "
    };
    ///Portero
    char nameSkillsPortero[2][26]={
        "       Bienvenido!       ",
        "        Mordedura        "
    };
    ///Caballero
    char nameSkillsCaballero[2][26]={
        "   Exposicion Enrredad   ",
        "   Pincho Subterraneo    "
    };
    ///Baron
    char nameSkillsBaron[2][26]={
        "        Latigaso         ",
        "    Deleito al Publico   "
    };
    ///Condesa
    char nameSkillsCondesa[2][26]={
        "    Muevete con Migo     ",
        "        Desonrra         "
    };
    ///Habilidades Cruzado:
    createSkills(skillsCruzader,0,nameSkillsCruzader[0],3,0,0,'a','s','n','n',0,0,1,1,1,1,0);
    createSkills(skillsCruzader,1,nameSkillsCruzader[1],4,0,0,'a','s','m','3',0,0,1,1,1,0,0);
    createSkills(skillsCruzader,2,nameSkillsCruzader[2],0,0,2,'s','s','a','n',0,0,1,1,1,0,0);
    createSkills(skillsCruzader,3,nameSkillsCruzader[3],0,2,0,'s','s','h','n',0,0,1,1,1,0,0);
    createSkills(skillsCruzader,4,nameSkillsCruzader[4],0,0,1,'s','m','a','n',0,0,1,1,1,0,0);
    createSkills(skillsCruzader,5,nameSkillsCruzader[5],0,0,1,'s','s','a','n',0,0,1,1,1,0,0);
    ///Habilidades Bandolero:
    createSkills(skillsBandolero,0,nameSkillsBandolero[0],3,0,0,'a','s','b','n',0, 0,1,1,1,0,0);
    createSkills(skillsBandolero,1,nameSkillsBandolero[1],2,0,0,'a','s','n','n',0, 1,1,1,1,1,1);
    createSkills(skillsBandolero,2,nameSkillsBandolero[2],3,0,0,'a','s','n','n',0,0,1,1,1,1,0);
    createSkills(skillsBandolero,3,nameSkillsBandolero[3],2,0,0,'a','m','n','n',0, 1,1,1,1,1,1);
    createSkills(skillsBandolero,4,nameSkillsBandolero[4],0,0,1,'s','s','a','n',0, 1,1,1,0,0,0);
    createSkills(skillsBandolero,5,nameSkillsBandolero[5],0,0,1,'s','s','a','n',0, 1,1,1,0,0,0);
    ///Habilidades Vestal:
    createSkills(skillsVestal,0,nameSkillsVestal[0],0,2,0,'s','m','n','n',0,1,1,1,0,0,0);
    createSkills(skillsVestal,1,nameSkillsVestal[1],1,4,0,'s','s','n','h',0,1,1,1,0,0,0);
    createSkills(skillsVestal,2,nameSkillsVestal[2],2,0,0,'a','s','n','n',0,1,1,1,1,1,1);
    createSkills(skillsVestal,3,nameSkillsVestal[3],2,0,0,'a','s','s','n',0,0,0,0,1,1,1);
    createSkills(skillsVestal,4,nameSkillsVestal[4],0,1,1,'s','m','h','a',0,1,1,1,0,0,0);
    createSkills(skillsVestal,5,nameSkillsVestal[5],0,1,1,'s','s','h','a',0,1,1,1,0,0,0);
    ///Habilidades Doctor de la Plaga:
    createSkills(skillsDoctorDeLaPlaga,0,nameSkillsDoctorDeLaPlaga[0],2,0,0,'a','m','p','n',0,1,1,0,1,1,1);
    createSkills(skillsDoctorDeLaPlaga,1,nameSkillsDoctorDeLaPlaga[1],2,0,0,'a','s','b','n',0,0,1,1,1,1,0);
    createSkills(skillsDoctorDeLaPlaga,2,nameSkillsDoctorDeLaPlaga[2],0,2,0,'s','s','h','b',0,1,1,1,0,0,0);
    createSkills(skillsDoctorDeLaPlaga,3,nameSkillsDoctorDeLaPlaga[3],0,0,2,'s','s','a','n',0,1,1,1,0,0,0);
    createSkills(skillsDoctorDeLaPlaga,4,nameSkillsDoctorDeLaPlaga[4],0,2,0,'s','s','h','p',0,1,1,1,0,0,0);
    createSkills(skillsDoctorDeLaPlaga,5,nameSkillsDoctorDeLaPlaga[5],0,3,0,'s','s','h','n',0,1,1,1,0,0,0);
    ///Habilidades Diabla:
    createSkills(skillsDiabla,0,nameSkillsDiabla[0],3,0,0,'a','s','n','n',0,0,1,1,1,1,0);
    createSkills(skillsDiabla,1,nameSkillsDiabla[1],2,0,0,'a','m','n','n',0,0,1,1,1,1,1);
    createSkills(skillsDiabla,2,nameSkillsDiabla[2],2,0,0,'a','s','n','n',0,0,1,1,1,1,0);
    createSkills(skillsDiabla,3,nameSkillsDiabla[3],0,1,1,'s','s','h','a',0,1,1,1,0,0,0);
    createSkills(skillsDiabla,4,nameSkillsDiabla[4],0,0,2,'s','s','a','n',0,1,1,1,0,0,0);
    createSkills(skillsDiabla,5,nameSkillsDiabla[5],0,2,0,'s','s','h','n',0,1,1,1,0,0,0);
    ///Habilidades Rompe Escudos:
    createSkills(skillsRompeEscudos,0,nameSkillsRompeEscudos[0],3,0,0,'a','s','m','3' ,0,1,1,1,1,1,1);
    createSkills(skillsRompeEscudos,1,nameSkillsRompeEscudos[1],2,0,0,'a','m','p','n' ,0,0,1,1,1,1,0);
    createSkills(skillsRompeEscudos,2,nameSkillsRompeEscudos[2],0,0,0,'a','s','m','-1',0,0,1,1,1,1,1);
    createSkills(skillsRompeEscudos,3,nameSkillsRompeEscudos[3],0,0,2,'s','s','a','n' ,0,1,1,1,0,0,0);
    createSkills(skillsRompeEscudos,4,nameSkillsRompeEscudos[4],0,0,2,'s','s','a','n' ,0,1,1,1,0,0,0);
    createSkills(skillsRompeEscudos,5,nameSkillsRompeEscudos[5],0,0,1,'s','m','a','n' ,0,1,1,1,0,0,0);
    ///Habilidades Leproso:
    createSkills(skillsLeproso,0,nameSkillsLeproso[0],3,0,0,'a','s','n','n' ,0,0,1,1,1,1,0);
    createSkills(skillsLeproso,1,nameSkillsLeproso[1],2,0,0,'a','s','n','n' ,0,1,1,1,1,1,0);
    createSkills(skillsLeproso,2,nameSkillsLeproso[2],0,0,2,'s','s','a','n' ,0,1,1,1,0,0,0);
    createSkills(skillsLeproso,3,nameSkillsLeproso[3],0,2,0,'s','s','h','n' ,0,1,1,1,0,0,0);
    createSkills(skillsLeproso,4,nameSkillsLeproso[4],0,2,0,'s','s','h','b' ,0,1,1,1,0,0,0);
    createSkills(skillsLeproso,5,nameSkillsLeproso[5],0,1,0,'s','m','h','n' ,0,1,1,1,0,0,0);
    ///Habilidades Bufon:
    createSkills(skillsBufon,0,nameSkillsBufon[0],2,0,0,'a','s','b','n' ,0,0,1,1,1,1,0);
    createSkills(skillsBufon,1,nameSkillsBufon[1],3,0,0,'a','s','n','n' ,0,0,1,1,1,1,1);
    createSkills(skillsBufon,2,nameSkillsBufon[2],2,0,0,'a','m','n','n' ,0,1,1,1,0,0,0);
    createSkills(skillsBufon,3,nameSkillsBufon[3],0,2,1,'s','s','h','a' ,0,1,1,1,0,0,0);
    createSkills(skillsBufon,4,nameSkillsBufon[4],0,3,0,'a','s','h','n' ,0,1,1,1,0,0,0);
    createSkills(skillsBufon,5,nameSkillsBufon[5],0,1,1,'s','s','h','a' ,0,1,1,1,0,0,0);
    ///Habilidades Flagelante:
    createSkills(skillsFlagelante,0,nameSkillsFlagelante[0],2,0,0,'a','s','b','n',0,0,1,1,1,1,0);
    createSkills(skillsFlagelante,1,nameSkillsFlagelante[1],2,0,0,'a','s','n','n',0,0,1,1,1,1,0);
    createSkills(skillsFlagelante,2,nameSkillsFlagelante[2],0,0,2,'s','s','a','b',0,1,1,1,0,0,0);
    createSkills(skillsFlagelante,3,nameSkillsFlagelante[3],1,0,0,'a','m','n','n',0,0,1,1,1,1,1);
    createSkills(skillsFlagelante,4,nameSkillsFlagelante[4],0,0,2,'s','s','a','b',0,1,1,1,0,0,0);
    createSkills(skillsFlagelante,5,nameSkillsFlagelante[5],0,4,0,'s','s','h','n',0,1,1,1,0,0,0);
    ///Habilidades Fusilera:
    createSkills(skillsFusilera,0,nameSkillsFusilera[0],3,0,0,'a','s','n' ,'n',0,1,1,1,1,1,1);
    createSkills(skillsFusilera,1,nameSkillsFusilera[1],2,0,0,'a','m','n' ,'n',0,1,1,1,1,1,0);
    createSkills(skillsFusilera,2,nameSkillsFusilera[2],1,0,0,'a','s','s' ,'n',0,1,1,0,1,1,1);
    createSkills(skillsFusilera,3,nameSkillsFusilera[3],0,0,2,'s','s','s' ,'n',0,1,1,1,0,0,0);
    createSkills(skillsFusilera,4,nameSkillsFusilera[4],0,0,2,'s','s','s' ,'n',0,1,1,0,0,0,0);
    createSkills(skillsFusilera,5,nameSkillsFusilera[5],0,0,1,'s','m','m' ,'n',0,1,1,1,0,0,0);
    ///Habilidades Heraldo:
    createSkills(skillsHeraldo,0,nameSkillsHeraldo[0],3,0,0,'a','s','n','n',0,0,1,1,1,1,0);
    createSkills(skillsHeraldo,1,nameSkillsHeraldo[1],1,0,0,'a','s','s','n',0,0,1,1,1,1,0);
    createSkills(skillsHeraldo,2,nameSkillsHeraldo[2],2,0,0,'a','m','n','n',0,0,1,1,1,1,0);
    createSkills(skillsHeraldo,3,nameSkillsHeraldo[3],0,0,2,'s','s','a','n',0,1,1,1,0,0,0);
    createSkills(skillsHeraldo,4,nameSkillsHeraldo[4],0,0,1,'s','m','a','n',0,1,1,1,0,0,0);
    createSkills(skillsHeraldo,5,nameSkillsHeraldo[5],0,2,0,'s','s','h','n',0,1,1,1,0,0,0);
    ///Habilidades Maestro de Canes:
    createSkills(skillsMaestroDeCanes,0,nameSkillsMaestroDeCanes[0],1,0,0,'a','s','s','n',0,0,1,1,1,1,0);
    createSkills(skillsMaestroDeCanes,1,nameSkillsMaestroDeCanes[1],3,0,0,'a','s','n','n',0,0,1,1,1,1,1);
    createSkills(skillsMaestroDeCanes,2,nameSkillsMaestroDeCanes[2],0,2,0,'s','m','h','n',0,1,1,1,0,0,0);
    createSkills(skillsMaestroDeCanes,3,nameSkillsMaestroDeCanes[3],2,0,0,'a','m','n','n',0,0,1,1,1,1,1);
    createSkills(skillsMaestroDeCanes,4,nameSkillsMaestroDeCanes[4],0,2,1,'s','s','h','n',0,1,1,1,0,0,0);
    createSkills(skillsMaestroDeCanes,5,nameSkillsMaestroDeCanes[5],0,2,1,'s','s','h','n',0,1,1,1,0,0,0);
    ///Habilidades Ocultista:
    createSkills(skillsOcultista,0,nameSkillsOcultista[0],3,0,0,'a','s','b','n',0,1,1,1,1,1,0);
    createSkills(skillsOcultista,1,nameSkillsOcultista[1],1,0,0,'a','m','s','n',0,1,1,1,0,1,1);
    createSkills(skillsOcultista,2,nameSkillsOcultista[2],2,0,0,'a','m','n','n',0,1,1,1,1,1,1);
    createSkills(skillsOcultista,3,nameSkillsOcultista[3],0,2,0,'s','s','h','b',0,1,1,1,0,0,0);
    createSkills(skillsOcultista,4,nameSkillsOcultista[4],0,0,1,'s','m','a','n',0,1,1,1,0,0,0);
    createSkills(skillsOcultista,5,nameSkillsOcultista[5],0,0,2,'s','s','a','n',0,1,1,1,0,0,0);



    ///Habilidades Monstruos:
    ///Las Ruinas
    ///Habilidades Soldado Esqueleto:
    createSkills(skillsSoldadoEsqueleto,0,nameSkillsSoldadoEsqueleto[0],3,0,0,'a','s','n','n',80,0,1,1,1,1,0);
    createSkills(skillsSoldadoEsqueleto,1,nameSkillsSoldadoEsqueleto[1],0,0,0,'a','s','s','n',20,0,1,1,1,1,0);
    ///Habilidades Cortesano Esqueleto:
    createSkills(skillsCortesanoEsqueleto,0,nameSkillsSoldadoEsqueleto[0],2,0,0,'a','s','p','n',80,1,1,0,0,1,1);
    createSkills(skillsCortesanoEsqueleto,1,nameSkillsSoldadoEsqueleto[1],2,0,0,'a','s','n','n',20,0,1,1,1,1,0);
    ///Habilidades Arbalestero Esqueleto:
    createSkills(skillsArbalesteroEsqueleto,0,nameSkillsSoldadoEsqueleto[0],2,0,0,'a','s','n','n',80,1,1,0,0,1,1);
    createSkills(skillsArbalesteroEsqueleto,1,nameSkillsSoldadoEsqueleto[1],2,0,0,'a','s','n','n',20,0,1,1,1,1,0);
    ///Habilidades Defensor Esqueleto:
    createSkills(skillsDefensorEsqueleto,0,nameSkillsDefensorEsqueleto[0],3,0,0,'a','s','n','n',80,0,1,1,1,1,0);
    createSkills(skillsDefensorEsqueleto,1,nameSkillsDefensorEsqueleto[1],0,0,0,'a','s','s','n',20,0,1,1,1,1,0);
    ///Habilidades Lancero Esqueleto:
    createSkills(skillsLanceroEsqueleto,0,nameSkillsLanceroEsqueleto[0],3,0,0,'a','s','n','n',80,0,1,0,1,1,0);
    createSkills(skillsLanceroEsqueleto,1,nameSkillsLanceroEsqueleto[1],2,0,0,'a','s','n','n',20,1,1,1,0,1,1);
    ///Habilidades Capitan Esqueleto:
    createSkills(skillsCapitanEsqueleto,0,nameSkillsCapitanEsqueleto[0],3,0,0,'a','s','n','n',80,0,1,1,1,1,0);
    createSkills(skillsCapitanEsqueleto,1,nameSkillsCapitanEsqueleto[1],1,0,0,'a','s','s','n',20,0,1,1,1,1,0);
    ///Habilidades Portador Esqueleto:
    createSkills(skillsPortadorEsqueleto,0,nameSkillsPortadorEsqueleto[0],2,0,0,'a','s','n','n',80,1,1,1,0,1,1);
    createSkills(skillsPortadorEsqueleto,1,nameSkillsPortadorEsqueleto[1],0,0,2,'s','s','a','n',20,1,1,1,1,1,0);
    ///Habilidades Nigromante
    createSkills(skillsNigromante,0,nameSkillsNigromante[0],4,0,0,'a','s','b','n',70,0,1,1,1,1,1);
    createSkills(skillsNigromante,1,nameSkillsNigromante[1],3,0,0,'a','m','b','n',30,1,1,1,1,1,1);
    ///Habilidades Profeta
    createSkills(skillsProfeta,0,nameSkillsProfeta[0],4,0,0,'a','s','n','n',80,1,1,1,1,1,1);
    createSkills(skillsProfeta,1,nameSkillsProfeta[1],3,0,0,'a','m','n','n',20,1,1,1,1,1,1);
    ///Catacumbas:
    ///Habilidades Javali Triturador:
    createSkills(skillsJavaliTriturador,0,nameSkillsJavaliTriturador[0],3,0,0,'a','s','p','n',80,0,1,1,1,1,0);
    createSkills(skillsJavaliTriturador,1,nameSkillsJavaliTriturador[1],2,0,0,'a','s','s','n',20,0,1,1,1,1,1);
    ///Habilidades Cerdo Degollador:
    createSkills(skillsCerdoDegollador,0,nameSkillsCerdoDegollador[0],3,0,0,'a','s','b','n',50,0,1,1,1,1,0);
    createSkills(skillsCerdoDegollador,1,nameSkillsCerdoDegollador[0],3,0,0,'a','s','b','n',50,0,1,1,1,1,0);
    ///Habilidades Cerdo Miserable:
    createSkills(skillsCerdoMiserable,0,nameSkillsCerdoMiserable[0],2,0,0,'a','s','p','n',50,1,1,1,1,1,1);
    createSkills(skillsCerdoMiserable,0,nameSkillsCerdoMiserable[0],2,0,0,'a','s','p','n',50,1,1,1,1,1,1);
    ///Habilidades Tambor Porcino:
    createSkills(skillsTamborPorcino,0,nameSkillsTamborPorcino[0],2,0,0,'a','m','n','n',70,1,1,1,1,1,1);
    createSkills(skillsTamborPorcino,1,nameSkillsTamborPorcino[1],0,0,2,'s','m','a','n',30,0,0,0,1,1,1);
    ///Habilidades Cerdo Lancero:
    createSkills(skillsCerdoLancero,0,nameSkillsCerdoLancero[0],2,0,0,'a','s','s','n',80,1,1,1,1,1,1);
    createSkills(skillsCerdoLancero,1,nameSkillsCerdoLancero[1],3,0,0,'a','s','n','n',20,1,1,1,1,1,1);
    ///Habilidades Cerdotauro:
    createSkills(skillsCerdotauro,0,nameSkillsCerdotauro[0],4,0,0,'a','s','n','n',80,1,1,1,1,1,0);
    createSkills(skillsCerdotauro,1,nameSkillsCerdotauro[1],2,0,0,'a','s','s','n',20,1,1,1,1,1,0);
    ///Habilidades Principe Cerdo:
    createSkills(skillsPrincipeCerdo,0,nameSkillsPrincipeCerdo[0],4,0,0,'a','s','n','n',60,0,1,1,1,1,1);
    createSkills(skillsPrincipeCerdo,1,nameSkillsPrincipeCerdo[1],3,0,0,'s','s','p','b',40,1,1,1,1,1,1);
    ///Habilidades Wilbur:
    createSkills(skillsWilbur,0,nameSkillsWilbur[0],3,0,0,'a','s','n','n',60,0,1,1,1,1,1);
    createSkills(skillsWilbur,1,nameSkillsWilbur[1],2,0,0,'a','s','p','b',40,0,1,1,1,1,1);
    ///Cala:
    ///Habilidades Pirania Arponera:
    createSkills(skillsPiraniaArponera,0,nameSkillsPiraniaArponera[0],2,0,0,'a','s','n','n',100,0,1,1,1,1,0);
    ///Habilidades Pirania Chaman:
    createSkills(skillsPiraniaChaman,0,nameSkillsPiraniaChaman[0],2,0,0,'a','m','n','n',70,1,1,1,1,1,1);
    createSkills(skillsPiraniaChaman,1,nameSkillsPiraniaChaman[1],0,3,0,'s','m','h','n',30,0,0,0,1,1,1);
    ///Habilidades Guardian Poctopodo:
    createSkills(skillsGuardianOctopodo,0,nameSkillsGuardianOctopodo[0],3,0,0,'a','s','n','n',80,0,1,1,1,1,0);
    createSkills(skillsGuardianOctopodo,1,nameSkillsGuardianOctopodo[1],0,0,2,'s','m','p','n',20,0,0,0,1,1,1);
    ///Habilidades Caracol Marino:
    createSkills(skillsCaracolMarino,0,nameSkillsCaracolMarino[0],3,0,0,'a','s','n','n',100,0,1,1,1,1,0);
    ///Habilidades Medusa:
    createSkills(skillsMedusa,0,nameSkillsMedusa[0],3,0,0,'a','s','n','n',50,0,1,1,1,1,0);
    createSkills(skillsMedusa,1,nameSkillsMedusa[0],3,0,0,'a','s','n','n',50,0,1,1,1,1,0);
    ///Habilidades Sumergido:
    createSkills(skillsSumergido,0,nameSkillsSumergido[0],3,0,0,'a','s','n','n',50,1,1,1,1,1,0);
    createSkills(skillsSumergido,1,nameSkillsSumergido[0],3,0,0,'a','s','n','n',50,1,1,1,1,1,0);
    ///Habilidades Triturador Tenazario:
    createSkills(skillsTrituradorTenazario,0,nameSkillsTrituradorTenazario[0],2,0,0,'a','s','b','n',30,0,1,1,1,1,0);
    createSkills(skillsTrituradorTenazario,1,nameSkillsTrituradorTenazario[1],3,0,0,'s','s','n','n',70,0,1,1,1,1,0);
    ///Habilidades Sirena:
    createSkills(skillsSirena,0,nameSkillsSirena[0],4,0,0,'a','s','n','n',70,1,1,1,1,1,1);
    createSkills(skillsSirena,1,nameSkillsSirena[1],0,4,0,'s','m','h','n',30,0,0,0,1,1,1);
    ///Habilidades Tripulacion Ahogado:
    createSkills(skillsTripulacionAhogada,0,nameSkillsTripulacionAhogada[0],4,0,0,'a','m','n','n',70,1,1,1,1,1,1);
    createSkills(skillsTripulacionAhogada,1,nameSkillsTripulacionAhogada[1],0,4,2,'s','m','h','n',30,0,0,0,1,1,1);
    ///Habilidades Contramaestre:
    createSkills(skillsContramaestre,0,nameSkillsContramaestre[0],5,0,0,'a','s','b','n',50,0,1,1,1,1,0);
    createSkills(skillsContramaestre,1,nameSkillsContramaestre[0],5,0,0,'a','s','b','n',50,0,1,1,1,1,0);
    ///Patio:
    ///Habilidades Sirviente:
    createSkills(skillsSirviente,0,nameSkillsSirviente[0],3,0,0,'a','s','p','n',70,1,1,1,1,1,0);
    createSkills(skillsSirviente,1,nameSkillsSirviente[1],0,0,2,'s','m','a','n',30,0,0,0,1,1,1);
    ///Habilidades Don:
    createSkills(skillsDon,0,nameSkillsDon[0],2,0,0,'a','s','b','n',60,0,1,1,1,1,1);
    createSkills(skillsDon,1,nameSkillsDon[1],3,0,0,'a','s','n','n',40,1,1,1,1,1,1);
    ///Habilidades Cortesana:
    createSkills(skillsCortesana,0,nameSkillsCortesana[0],2,0,0,'a','m','n','n',70,1,1,1,1,1,1);
    createSkills(skillsCortesana,1,nameSkillsCortesana[1],3,0,0,'a','s','s','n',30,0,1,1,1,1,1);
    ///Habilidades Suplicante:
    createSkills(skillsSuplicante,0,nameSkillsSuplicante[0],3,0,0,'a','s','b','n',50,1,1,1,1,1,1);
    createSkills(skillsSuplicante,1,nameSkillsSuplicante[0],3,0,0,'a','s','b','n',50,1,1,1,1,1,1);
    ///Habilidades Mosquito:
    createSkills(skillsMosquito,0,nameSkillsMosquito[0],3,0,0,'a','s','b','n',50,1,1,1,1,1,1);
    createSkills(skillsMosquito,1,nameSkillsMosquito[0],3,0,0,'a','s','b','n',50,1,1,1,1,1,1);
    ///Habilidades Portero:
    createSkills(skillsPortero,0,nameSkillsPortero[0],2,0,0,'a','s','n','n',60,1,1,1,1,1,1);
    createSkills(skillsPortero,1,nameSkillsPortero[1],3,0,0,'a','m','b','n',40,0,1,1,1,1,1);
    ///Habilidades Caballero:
    createSkills(skillsCaballero,0,nameSkillsCaballero[0],3,0,0,'a','s','b','n',70,0,1,1,1,1,0);
    createSkills(skillsCaballero,1,nameSkillsCaballero[1],2,0,0,'a','m','b','n',30,1,1,1,1,1,1);
    ///Habilidades Baron:
    createSkills(skillsBaron,0,nameSkillsBaron[0],4,0,0,'a','s','b','n',70,1,1,1,1,1,1);
    createSkills(skillsBaron,1,nameSkillsBaron[1],0,2,3,'s','m','h','a',30,0,0,0,1,1,1);
    ///Habilidades Condesa:
    createSkills(skillsCondesa,0,nameSkillsCondesa[0],4,0,0,'a','s','n','n',70,1,1,1,1,1,1);
    createSkills(skillsCondesa,1,nameSkillsCondesa[1],3,0,0,'a','m','n','n',30,1,1,1,1,1,1);


    ///Heroes
    char nameHero[20][21]={
        {"Cruzado"},
        {"Vestal"},
        {"Bandolero"},
        {"Doctor de la Plaga"},
        {"Diabla"},
        {"Rompe Escudos"},
        {"Leproso"},
        {"Bufon"},
        {"Flagelante"},
        {"Fusilera"},
        {"Heraldo"},
        {"Maestro de Canes"},
        {"Ocultista"}
    };

    ///Monstruos
    char nameMonsters[40][21]={///Las Ruinas:
        {"Soldado Esqueleto"},
        {"Cortesano Esqueleto"},
        {"Arbalesto Esqueleto"},
        {"Defensor Esqueleto"},
        {"Lancero Esqueleto"},
        {"Capitan Esqueleto"},
        {"Portador Esqueleto"},
        {"Nigromante"},
        {"Profeta"},///Catacumbas
        {"Jabali Triturador"},
        {"Cerdo Degollador"},
        {"Cerdo Miserable"},
        {"Tambor Porcino"},
        {"Cerdo Lancero"},
        {"Cerdotauro"},
        {"Principe Cerdo"},
        {"Wilbur"},///Cala
        {"Pirania Arponero"},
        {"Pirania Chaman"},
        {"Guardian Octopodo"},
        {"Caracol Marino"},
        {"Medusa"},
        {"Sumergido"},
        {"Triturador Tenazario"},
        {"Sirena"},
        {"Tripulacion Ahogada"},
        {"Contramaestre"},///Patio
        {"Sirviente"},
        {"Noble"},
        {"Cortesana"},
        {"Suplicante"},
        {"Mosquito"},
        {"Portero"},
        {"Caballero"},
        {"Baron"},
        {"Condesa"}
    };

    ///heros:
    ///   name, hero/monster,  hp, heal, damageMin, damageMax, armor, hit, dodge, stunRes, poisoRes, bleedRes, stSkills.
    createEntity(hero,0, nameHero[0] ,1,32,1,3,6,2,80,20,30,20,30,skillsCruzader); ///Cruzado
    createEntity(hero,1, nameHero[1] ,1,30,2,3,6,1,70,15,30,10,30,skillsVestal); ///Vestal
    createEntity(hero,2, nameHero[2] ,1,31,0,4,6,0,90,20,20,30,20,skillsBandolero); ///Bandolero
    createEntity(hero,3, nameHero[3] ,1,31,1,3,1,0,80,15,10,40,20,skillsDoctorDeLaPlaga); ///Doctor de la plaga
    createEntity(hero,4, nameHero[4] ,1,32,1,5,8,0,85,10,30,20,20,skillsDiabla); ///Diabla
    createEntity(hero,5, nameHero[5] ,1,33,1,3,6,0,90,12,20,40,10,skillsRompeEscudos); ///Rompe escudos
    createEntity(hero,6, nameHero[6] ,1,33,2,4,6,2,80,15,20,30,20,skillsLeproso); ///Leproso
    createEntity(hero,7, nameHero[7] ,1,30,0,4,6,0,75,20,10,30,20,skillsBufon); ///Bufon
    createEntity(hero,8, nameHero[8] ,1,31,1,3,1,0,80,00,20,10,40,skillsFlagelante); ///Flagelante
    createEntity(hero,9, nameHero[9] ,1,31,0,6,1,0,90,22,30,20,20,skillsFusilera); ///Fusilera
    createEntity(hero,10,nameHero[10],1,34,0,3,6,2,70,17,40,20,30,skillsHeraldo); ///Heraldo
    createEntity(hero,11,nameHero[11],1,31,0,4,6,0,90,20,20,30,20,skillsMaestroDeCanes); ///Maestro de canes
    createEntity(hero,12,nameHero[12],1,30,2,4,6,0,80,15,20,30,20,skillsOcultista); ///Ocultista

    ///Enemigos:
    ///Ruinas:
    ///   name, hero/monster,  hp, heal, damageMin, damageMax, armor, hit, dodge, stunRes, poisoRes,bleedRes, stDung.
    createEntity(monster,0,nameMonsters[0],0,10,0,3, 6,1,80,15,25,10,100,skillsSoldadoEsqueleto); ///Soldado esqueleto
    createEntity(monster,1,nameMonsters[1],0,10,0,3, 5,0,82,17,10,10,100,skillsCortesanoEsqueleto); ///Cortersano esqueleto
    createEntity(monster,2,nameMonsters[2],0,12,0,3, 7,1,90,18,10,10,100,skillsArbalesteroEsqueleto); ///Arbalestero esqueleto
    createEntity(monster,3,nameMonsters[3],0,11,0,3, 5,2,85,15,25,10,100,skillsDefensorEsqueleto); ///Defensor esqueleto
    createEntity(monster,4,nameMonsters[4],0,12,0,3, 5,1,90,20,30,20,100,skillsLanceroEsqueleto); ///Lancero esqueleto
    createEntity(monster,5,nameMonsters[5],0,18,0,4, 6,2,70,10,40,20,100,skillsCapitanEsqueleto); ///Capitan esqueleto
    createEntity(monster,6,nameMonsters[6],0,17,0,2, 4,1,85,20,40,20,100,skillsPortadorEsqueleto); ///Portador esqueleto
    createEntity(monster,7,nameMonsters[7],0,105,0,4, 8,1,85,27,75,20,20,skillsNigromante); ///Nigromante
    createEntity(monster,8,nameMonsters[8],0,105,0,6,12,0,75,30,100,0,0,skillsProfeta); ///Profeta
    ///Catacumbas:
    createEntity(monster, 9,nameMonsters[9] ,0,12,0,3,7,1,85,15,25,60,20,skillsJavaliTriturador); ///Javali triturador
    createEntity(monster,10,nameMonsters[10],0,8,0,3,7,1,90,17,10,40,40,skillsCerdoDegollador); ///cerdo degollador
    createEntity(monster,11,nameMonsters[11],0,12,0,4,0,0,80,5,10,40,10,skillsCerdoMiserable); ///Cerdo miserable
    createEntity(monster,12,nameMonsters[12],0,15,0,2,4,0,85,19,10,40,20,skillsTamborPorcino); ///Tambor porcino
    createEntity(monster,13,nameMonsters[13],0,12,0,4,8,1,85,17,30,40,20,skillsCerdoLancero); ///Cerdo lancero
    createEntity(monster,14,nameMonsters[14],0,19,0,4,9,2,90,10,30,50,30,skillsCerdotauro); ///Cerdotauro
    createEntity(monster,15,nameMonsters[15],0,132,0,5,9,2,90,20,100,0,0,skillsPrincipeCerdo); ///Principe cerdo
    createEntity(monster,16,nameMonsters[16],0,17,0,1,2,0,95,30,50,0,0,skillsWilbur); ///Wilbur
    ///Cala:
    createEntity(monster,17,nameMonsters[17],0,12,0,5,7,1,85,15,10,10,50,skillsPiraniaArponera); ///Pirania arponera
    createEntity(monster,18,nameMonsters[18],0,12,0,4,5,0,90,18,10,10,50,skillsPiraniaChaman); ///Pirania chaman
    createEntity(monster,19,nameMonsters[19],0,14,0,3,5,1,89,12,25,10,60,skillsGuardianOctopodo); ///Guardina octopodo
    createEntity(monster,20,nameMonsters[20],0,9,0,2,4,0,80,5,50,20,40,skillsCaracolMarino); ///Caracol marino
    createEntity(monster,21,nameMonsters[21],0,12,0,2,4,0,89,10,70,30,70,skillsMedusa); ///Medusa
    createEntity(monster,22,nameMonsters[22],0,14,0,5,9,0,90,11,50,10,30,skillsSumergido); ///Sumergido
    createEntity(monster,23,nameMonsters[23],0,20,0,4,9,2,75,19,60,30,60,skillsTrituradorTenazario); ///Triturador tenazario
    createEntity(monster,24,nameMonsters[24],0,119,0,5,8,2,90,30,50,40,60,skillsSirena); ///Sirena
    createEntity(monster,25,nameMonsters[25],0,100,0,4,9,1,90,20,50,20,60,skillsTripulacionAhogada); ///Tripulacion ahogada
    createEntity(monster,26,nameMonsters[26],0,14,0,3,6,2,85,30,25,20,60,skillsContramaestre); ///Contramaestre
    ///Patio
    createEntity(monster,27,nameMonsters[27],0,10,0,2,4,0,85,15,40,40,15,skillsSirviente); ///Sirviente
    createEntity(monster,28,nameMonsters[28],0,13,0,2,4,1,90,17,40,40,20,skillsDon); ///Don
    createEntity(monster,29,nameMonsters[29],0,13,0,3,4,0,85,18,45,40,20,skillsCortesana); ///Cortesana
    createEntity(monster,30,nameMonsters[30],0,12,0,3,5,0,89,10,50,50,15,skillsSuplicante); ///Suplicante
    createEntity(monster,31,nameMonsters[31],0,14,0,1,3,0,80,5,15,80,15,skillsMosquito); ///Mosquito
    createEntity(monster,32,nameMonsters[32],0,12,0,3,5,1,90,12,50,60,25,skillsPortero); ///Portero
    createEntity(monster,33,nameMonsters[33],0,19,0,5,7,2,90,10,20,50,20,skillsCaballero); ///Caballero
    createEntity(monster,34,nameMonsters[34],0,100,0,3,7,2,90,30,60,75,55,skillsBaron); ///Baron
    createEntity(monster,35,nameMonsters[35],0,120,0,4,9,2,100,30,70,70,60,skillsCondesa); ///Condesa

    ///Nombre Dungeons:
    char nameDungeons[4][11]={
        "Las Ruinas",
        "Catacumbas",
        "La Cala",
        "El Patio"
    };
    ///Las Ruinas
    createDungeon(dungeons,0,nameDungeons[0],1,monster[0],monster[2],monster[1]);
    createDungeon(dungeons,1,nameDungeons[0],2,monster[3],monster[4],monster[1]);
    createDungeon(dungeons,2,nameDungeons[0],3,monster[0],monster[0],monster[7]);
    createDungeon(dungeons,3,nameDungeons[0],3,monster[5],monster[6],monster[8]);
    ///Catacumbas
    createDungeon(dungeons,4,nameDungeons[1],1,monster[ 9],monster[10],monster[11]);
    createDungeon(dungeons,5,nameDungeons[1],2,monster[12],monster[13],monster[14]);
    createDungeon(dungeons,6,nameDungeons[1],3,monster[14],monster[16],monster[15]);
    ///Cala
    createDungeon(dungeons,7,nameDungeons[2],1,monster[17],monster[18],monster[19]);
    createDungeon(dungeons,8,nameDungeons[2],2,monster[20],monster[21],monster[22]);
    createDungeon(dungeons,9,nameDungeons[2],3,monster[21],monster[23],monster[24]);
    createDungeon(dungeons,10,nameDungeons[2],3,monster[22],monster[25],monster[26]);
    ///Patio
    createDungeon(dungeons,11,nameDungeons[3],1,monster[27],monster[28],monster[29]);
    createDungeon(dungeons,12,nameDungeons[3],2,monster[30],monster[31],monster[32]);
    createDungeon(dungeons,13,nameDungeons[3],3,monster[33],monster[33],monster[34]);
    createDungeon(dungeons,14,nameDungeons[3],3,monster[33],monster[33],monster[35]);


    ///Guardar en archivo dungeons
    addDungeonsFile(15,dungeons,nameFileListDungeos);
    //searchListDungeons(nameFileListDungeos);

    ///Guardar heroes en archivo
    addHeroFile(13,hero,nameFileListHero);
    //searchListHero(hero,nameFileListHero);


    ///Agregar usuarios:
    ///Damian
    users[0].idUser = 1001;
    strcpy(users[0].name,"Damian");
    strcpy(users[0].surname,"Barrionuebo");
    strcpy(users[0].userName,"kuld");
    strcpy(users[0].password,"123");
    users[0].gold=1000;
    users[0].type=1;
    users[0].active=1;
    users[0].dificult=3;
    users[0].dungeonlvl=1;
    strcpy(users[0].dungeonType,nameDungeons[0]);
    users[0].records=1000;
    users[0].posHeros[0]=0;
    users[0].posHeros[1]=1;
    users[0].posHeros[2]=2;
    users[0].availableHeros[0]=0;
    users[0].availableHeros[1]=1;
    users[0].availableHeros[2]=2;
    users[0].availableHeros[3]=3;
    users[0].availableHeros[4]=4;
    users[0].validsAvailableHeros=5;
    users[0].trinkets[0]=trinkets[0];
    users[0].trinkets[1]=trinkets[1];
    users[0].trinkets[2]=trinkets[2];
    users[0].trinkets[3]=trinkets[3];
    ///Javier
    users[1].idUser = 1002;
    strcpy(users[1].name,"Javier");
    strcpy(users[1].surname,"Barrionuebo");
    strcpy(users[1].userName,"yamvein");
    strcpy(users[1].password,"123");
    users[1].gold=0;
    users[1].type=1;
    users[1].active=1;
    users[1].dificult=2;
    users[1].dungeonlvl=2;
    strcpy(users[1].dungeonType,nameDungeons[0]);
    users[1].records=6000;
    users[1].posHeros[0]=0;
    users[1].posHeros[1]=1;
    users[1].posHeros[2]=2;
    users[1].availableHeros[0]=0;
    users[1].availableHeros[1]=1;
    users[1].availableHeros[2]=2;
    users[1].validsAvailableHeros=3;
    users[1].trinkets[0]=trinkets[0];
    users[1].trinkets[1]=trinkets[1];
    users[1].trinkets[2]=trinkets[2];
    users[1].trinkets[3]=trinkets[3];
    ///Sebastian
    users[2].idUser = 1003;
    strcpy(users[2].name,"Sebastian");
    strcpy(users[2].surname,"Barrionuebo");
    strcpy(users[2].userName,"sanderx");
    strcpy(users[2].password,"123");
    users[2].gold=5000;
    users[2].type=1;
    users[2].active=1;
    users[2].dificult=1;
    users[2].dungeonlvl=1;
    strcpy(users[2].dungeonType,nameDungeons[1]);
    users[2].records=2000;
    users[2].posHeros[0]=0;
    users[2].posHeros[1]=1;
    users[2].posHeros[2]=2;
    users[2].availableHeros[0]=0;
    users[2].availableHeros[1]=1;
    users[2].availableHeros[2]=2;
    users[2].validsAvailableHeros=3;
    users[2].trinkets[0]=trinkets[0];
    users[2].trinkets[1]=trinkets[1];
    users[2].trinkets[2]=trinkets[2];
    users[2].trinkets[3]=trinkets[3];
    ///Gustavo Sonvico
    users[3].idUser = 1004;
    strcpy(users[3].name,"Gustavo");
    strcpy(users[3].surname,"Sonvico");
    strcpy(users[3].userName,"Pedorro");
    strcpy(users[3].password,"123");
    users[3].gold=0;
    users[3].type=1;
    users[3].active=1;
    users[3].dificult=1;
    users[3].dungeonlvl=1;
    strcpy(users[3].dungeonType,nameDungeons[2]);
    users[3].records=8000;
    users[3].posHeros[0]=0;
    users[3].posHeros[1]=1;
    users[3].posHeros[2]=2;
    users[3].availableHeros[0]=0;
    users[3].availableHeros[1]=1;
    users[3].availableHeros[2]=2;
    users[3].validsAvailableHeros=3;
    users[3].trinkets[0]=trinkets[0];
    users[3].trinkets[1]=trinkets[1];
    users[3].trinkets[2]=trinkets[2];
    users[3].trinkets[3]=trinkets[3];
    ///Daniel
    users[4].idUser = 1005;
    strcpy(users[4].name,"Daniel");
    strcpy(users[4].surname,"Ginto");
    strcpy(users[4].userName,"yokasta");
    strcpy(users[4].password,"123");
    users[4].gold=0;
    users[4].type=0;
    users[4].active=1;
    users[4].dificult=1;
    users[4].dungeonlvl=1;
    strcpy(users[4].dungeonType,nameDungeons[3]);
    users[4].records=7000;
    users[4].posHeros[0]=0;
    users[4].posHeros[1]=1;
    users[4].posHeros[2]=2;
    users[4].availableHeros[0]=0;
    users[4].availableHeros[1]=1;
    users[4].availableHeros[2]=2;
    users[4].validsAvailableHeros=3;
    users[4].trinkets[0]=trinkets[0];
    users[4].trinkets[1]=trinkets[1];
    users[4].trinkets[2]=trinkets[2];
    users[4].trinkets[3]=trinkets[3];

    /*
    printf("Guarde sus datos:\n");
    printf("Ingrese su nombre:\n");
    fflush(stdin);
    gets(newName);
    printf("Ingrese su apellido:\n");
    fflush(stdin);
    gets(newSurName);
    printf("Ingrese su nombre de usuario:\n");
    fflush(stdin);
    gets(newUserName);
    printf("Ingrese su contrasenia:\n");
    fflush(stdin);
    gets(newPassWord);
    */

    addUsers(5,users,nameFileListUsers);
    //addUser(newName,newSurName,newUserName,newPassWord,nameFileListUsers);
    //searchListUsers(nameFileListUsers);




    ///Ej: Hero
    //danioHero=atackHero(hero[0]);
    //printf("Cruzado ataque: ..%d..\n",danioHero);
    ///Ej: Monster
    //danioMonster=atackMonster(3,monster[0]);
    //printf("Cruzado ataque: ..%d..\n",danioMonster);
    ///Ej: Hero => Monster
    //danioResibido=proceduralDamage(danioHero,monster[0],'b');
    ///Accion:
    //action(hero[0],monster[0],skillsCruzader[0],1);

    /*
    ///Usuario on:

    printf("Ingrese su nombre de usuario:\n");
    fflush(stdin);
    gets(userName);
    printf("Ingrese su contraseña:\n");
    fflush(stdin);
    gets(passWord);
    valueUser = whoAreYou(userName,passWord,userOn,nameFileListUsers);
    if(valueUser==1){
        printf("Bienvenido.\n");
    }else{
        printf("Nombre de usuario o contraseña invalida.\n");
    }
    */

    ///Cargar Dungeon:
    //dungeon(userOn,&dungeonOn,nameFileListDungeos);
    //enemyOne=dungeonOn.enemyOne;
    //enemyTwo=dungeonOn.enemyTwo;
    //enemyThree=dungeonOn.enemyThree;
    ///Seleccionar Heroes:
    //validsHeros=searchListHero(heros,nameFileListHero);
    //heroOne=heros[selectHero(validsHeros,heros)];
    //heroTwo=heros[selectHero(validsHeros,heros)];
    //heroThree=heros[selectHero(validsHeros,heros)];
    ///Seleccionar Abalorios
    //Funcion abalorios

    /*
    ///-(entity array, name, health, damage, hit, dodge, armor, poison res, stun res, bleed res)-
    stEntity hero[10];
    stEntity enemy[40];
    ///heros
    createEntity(hero, 0,{'W','a','r','r','i','o','r'},15, 5, 80, 20, 6, 10, 40, 60);
    createEntity(hero, 1,{'C','l','e','r','i','c'},15, 5, 80, 30, 3, 10, 10, 30);
    createEntity(hero, 2,{'M','a','g','e'},15, 9, 80, 30, 1, 0, 0, 0);
    ///enemys
    createEntity(enemy, 0,{'S','k','e','l','e','t','o','n',' ','W','a','r','r','i','o','r'},15, 5, 80, 30, 4, 10, 40, 60);
    createEntity(enemy, 1,{'W','a','r','r','i','o','r',' ','A','r','c','h','e','r'},15, 5, 80, 30, 3, 10, 40, 60);
    int gameOn=0;
    */

    ///inicio de programa
    gameOn(nameFileListUsers,nameFileListDungeos,nameFileListHero, nameFileListTrinkets);

    return 0;
}
