
///-----------------------------------------------------Prototipado-----------------------------------------------------///


///------------------------------------Estructuras--------------------------------------///
///Trikets
typedef struct
{
    char nameTrinket[30];
    int buffDamage;
    int buffHeal;
    int buffArmor;
    int buffHP;
    int buffHit;
    int buffDodge;
    int buffStun;
    int buffPoison;
    int buffBledd;
} stTrinket;
///Usuarios:
typedef struct
{
    char name[30];
    char surname[30];
    int idUser;
    char userName[30];
    char password[20];
    int gold;           //dinero
    int type;          //adim | user
    int active;
    int dificult;      //1=normal 2=hard 3=bloodMoon
    int dungeonlvl;
    char dungeonType[15];
    int records;
    int posHeros[4];
    int availableHeros[15];
    int validsAvailableHeros;
    //stEntity heroes[15];
    stTrinket trinkets[30];
    //other heros...
} stUser;
///Habilidades
typedef struct
{
    char entity[21];
    char name[26];
    int damage;
    int heal;
    int armor;
    char type;
    char objetive;
    char effectType1;
    char effectType2;
    int prob;
    int ally1;
    int ally2;
    int ally3;
    int objetive1;
    int objetive2;
    int objetive3;
} stSkills;
///Entidades:
typedef struct
{
    //int userBoa;
    char name[21];
    int heroMonster;//Hero=1 Monster=0
    int hp;
    int heal;
    int damageMin;
    int damageMax;
    int armor;
    int hit;
    int dodge;
    int poisonResist; // percentage
    int stunResist;
    int bleedResist;
    int contStun;
    int contBleed;
    int contPoison;
    int contArmor;
    int buffArmor;
    int debufBleed;
    int debufPoison;
    stSkills skills[6];
    stTrinket tOne;
    stTrinket tTwo;
} stEntity;
///Dungeons:
typedef struct
{
    char type[11];
    int lvl;
    stEntity enemyTeam[4];
} stDungeon;
///-------------------------------------Funciones---------------------------------------///

///---------------------------------------fnUser----------------------------------------///
///Datos Predeterminados:
///Usuarios predeterminados:
void addUsers(int valids,stUser users[],char nameFile[]);
///Agregar un usuario:
void addUser(char nameE[],char userNameE[],char passWordE[],char nameFileUser[],char nameFileTrinket[]);
int validateUserName(char userName[],char nameFile[]);
///Mostrar usuarios:
void searchListUsers(char nameFile[]);
///Encriptar contraseñas
void mostrarMatriz(int filas, int colum,char matris[filas][colum]);
void encryptPassword(char passWord[]);
///Encriptar contraseñas
void decryptPassword(char passWord[]);
///store heros
void storeHeros(int listHero[]);
///Lista de heroes de usuario
int availableHerosList(stEntity listAvailable[], stEntity listHero[],stUser userOn[]);
///--------------------------------------fnCombat---------------------------------------///
///Creador de entidades:
void createEntity(stEntity entity[], int pos,char nameE[],int heroMonsterE,int healthE,int healE, int damagMinE, int damagMaxE, int armorE, int hitE, int dodgeE, int stunE,int poisonE, int bleedE,stSkills skills[]);
///Creador de Dungeons:
void createDungeon(stDungeon dungeonE[], int pos,char nameDungeonsE[],int lvlE,stEntity monster1E,stEntity monster2E,stEntity monster3E);
///Dungeons predeterminados
void addDungeonsFile(int validos,stDungeon dungeons[],char nameFileListDungeos[]);
///Mostrar dungeons:
void showList(int validos,stDungeon dungeons[]);
void searchListDungeons(stDungeon dungeonList[],char nameFile[]);
///Archivo de Heros
void showListHeros(int valids,stEntity heros[]);
int searchListHero(stEntity heros[],char nameFile[]);
void addHeroFile(int valids,stEntity ent[],char nameFile[]);
///Creador de Trinkets:
void createTrinket(stTrinket trinkets[], int numE, char nameObjecE[],int buffoHPE, int buffoDamageE,int buffoHitE,int buffoDodgeE,int buffoPoisonE, int buffoStunE, int buffoBleddE, int buffoHealE, int buffoArmorE);
///Mostrar Trinkets
void infoTrinkets(stTrinket trinkets[], int cant);
///CARGAR DUNGEON:
void dungeon(stUser userOn[],stDungeon dungeonOn[],char nameFill[]);
///Seleccionar dungeon:
void selectDungeon(stUser userOn[], char nameDungeon[], int lvlDungeon);
///SELECCION DE HEROES:
int choiseTreeHero(int valids,stEntity ent[]);
int validateSelectHero();
///Funciones de ataques:
int attackHero(stEntity entity);// emisor[return damage p]
int attackMonster(stEntity entity);// emisor[return damage p]
int proceduralDamage(int damage,stEntity objective,char type);// damage - receptor - skill type

///Creador de habilidades:
void createSkills(stSkills entity[],int pos,char nameE[],int damageE,int healE,int armorE,char typeE,char objetiveE,char effectType1E,char effectType2E,int probE,int ally1E,int ally2E,int ally3E,int objetive1E,int objetive2E,int objetive3E);
///Funcion para desglosar las diferentes acciones
void action(int entPos,stEntity ent[],int objPos,stEntity obj[],int skillPos,int dificut);
///Validacion de usuario:
int whoAreYou(char userName[],char passWord[],stUser userOn[],char findFile[]);
///Buscar un usuario por ID
int findUserForId(int idUser,stUser userOn[],char nameFile[]);
///Buscar un usuario por userName
int findUserForUserName(char userNameE[],stUser userOn[],char nameFile[]);

///Validar si un vando ha caido
int ifFinalCombat(stEntity heros[],stEntity enemys[]);//if !stillAlive = who win

///--------------------------------------fnScreen---------------------------------------///
///Ejecucion del juego y puntero
void gameOn(char routUser[], char routDungeon[], char routHeros[],char routTrinkets[]);
///Seleccion de pantalla segun puntero
int setOptionMenu(char menu[],int selected,stUser userOn[],stDungeon dungeonOn[], stEntity heroTeam[],int positions[],int dificultMode, int *round, int *cursorOn,
                  char routUser[],char routDungeon[],char routHeros[],int flagLogin,int flagDown,int *userFound, stEntity heroList[],int *result, int store[],
                  stEntity heroAvailable[],int selectedHero[]);
///Buscar pantalla seleccionada
void findScreen(int l, int c,char newScreen[l][c], char screenName[]);
///Mostrar pantalla seleccionada
void showScreen(int line, int column, char screen[line][column],stUser userOn[],stDungeon dungeonOn[], char menu[], stEntity heroTeam[],int heroPos, int enemyPos,
                int skillPos, int userPos, char routUser[], stEntity heroList[], int round, char routDungeon[], int userFound, int store[], stEntity heroAvailable[],
                int selectedHero[]);
///Cantidad de caracteres de un num
int intleng(int num);
///Imprimir numero por cant de caracteres y seleccion de color
void printInt(int num,char color[]);
///Funcion aux de showscreen para entidades
void showContEntity(stEntity entity);
///Pasar turno de heroes y finalizar ronda
int passTurn(stEntity heros[],int heroPos, int dificultMode);
///Verificar si algun bando a muerto
int stillAliveTeam(stEntity heros[],stDungeon dungeonOn[]);
///
void saveTeam(int pos1, int pos2, int pos3, stUser userOn[], char fileName[]);
///
int validateUser(int condition);
///store fns
void storeTrinket(stTrinket listTrinket[],char nameFileTrinket[]);
///Validacion de passWord
int validatePass(char pass[],stUser userOn[]);
///Cambiar passWord
void changePass(char newPass[],stUser userOn[]);
///Actualizar usuario
void updateUser(stUser userOn[],char fileName[]);
///Baja y Alta logica de un usuario
void changeState(stUser userOn[], int position,char fileName[]);
///Funcion buscar un usuario por userName
int findUserForUserName(char userNameE[],stUser userOn[],char nameFile[]);
///Buscar un usuario por su ID
int findUserForId(int idUser,stUser userOn[],char nameFile[]);
///Records
int positionMinor(int pos,int valids,stUser listUsers[]);
void organizeList(int valids,stUser listUsers[]);
///Guardar en un array los 5 usuarios con records mas altos
void higherRecords(stUser listUsers[],char fileName[]);
