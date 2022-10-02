//lancolt lista structja
typedef struct ugyfel{
    char* name;
    char* emailaddr;
    char* tel;
    char* funds;
    char* date;
    char* intr;
    struct ugyfel* next;
}ugyfel;

//called in func. file
//uj ugyfel hozzaadasa a lista vegere
void addUgyfel(ugyfel* start,char* nev,char* email,char* telefonszam,char* kezdoosz,char* lekotesdatum,char* kamat);
//return a megfelelo nevhez tartozo pointert
ugyfel* getUgyfelByNev(ugyfel* root, char* nev);
//return 1 ha szerepel a listan, kulonben 0
int isPresent(ugyfel*root, char* nev);

//jo=1,tartalmaz nem szamot=0,rossz honap=2,rossz nap=3,nem megfelelo datum az elozohoz kepest=4,hibas elvalaszto jel=-1;
int datumCheck(char* datum,char* prevDatum);
//return 1 ha szam, 0 ha nem
static inline int isNumber(char ch);
//return 1 ha jo, kulonben 0;
int isStringNumber(char* String);
//return 1 ha syokoev, kulonben 0
static inline int isLeapYear(int year);

//return a szam hatvanya (csak nem negativ egeszekre!)
double Pow(double num, int toPow);
//return a szam abszolut erteke
int abs(int num);

//a ugyfellista tartalmanak megjelenitese
void ugyfelekMenu(ugyfel* start);
//a sajat penzugyek menu tartalmanak megjelenitese
void sajatpenzugyekMenu(ugyfel* root,char* datum);
//az ujugyfel menu tartalmanak megjelenitese
void ujUgyfel(ugyfel* root,char* datum);
//az ugyfel torlese menu tartalmanak megjelenitese
void removeUgyfel(ugyfel* root);

//sajatpenzugyekMenu sub-menurendszer

//penzugyek menu megjelenitese
void penzugyekMenu(ugyfel* currentUgyfel,ugyfel* root,char* datum);
//penzugyek menun beluli kezpenz lekotes menu megjelenitese
void kplekotes(ugyfel* currentUgyfel,char* datum);
//penzugyek menun beluli utalas-szamlazas menu megjelenitese
void utalas(ugyfel* currentugyfel, ugyfel* root,char* datum);
//kamatjovairas n ev mulva kalkulalasa
void kamatCalc(ugyfel* kalkulalando);
//penzugyek menun beluli adatkezeles megjelenitese
void adatkezeles(ugyfel* currentUgyfel,ugyfel* root,char* datum);
//adatkezeles menun beluli azonosito modositas menu meghivasa
void azModositas(ugyfel* currentugyfel,ugyfel* root,char* datum);
//adatkezeles menun beluli telszam modositas menu meghivasa
void telModositas(ugyfel* currentugyfel, ugyfel* root,char* datum);
//adatkezeles menun beluli email modositas menu meghivasa
void emailModositas(ugyfel* currentugyfel,ugyfel* root,char* datum);

//return 1 ha jo, 0 ha tul rovid, -1 ha tartalmaz karaktert: Telefonszam ellenorzo az adat modositashoz
int telCheck(char* number);
//return 1 ha jo, 0 ha hibas: Email ellenorzo az adat modositashoz
int mailCheck(char* mail);

//egy string egessze alakitasa
int strToInt(char* String);
//egy string hosszanak megallapitasa
int strLength(char* String);
//return 1 ha megegyezik, kulonben 0: Ket string osszehasonlitasa
int stringEquals(char* String1, char* String2);
//egy string substringjenek meghivasa egy masik tombbe. Kell a kezdo index(ez bele szamit) es bezaro index(ez nem szamit bele)
void getSubString(char* subStringTo,char* String, int start, int end);
//egy string masolasa masik tombbe
void copyString(char* copyfrom,char* copyto);
//return char index, ha nincs -1;
int strCharIndex(char* String, char containedChar);

//called in main

//datum inicializalas
void datumInit(char* datum,char* datumInit);
//file inicializalas
int fileInit(char* filename,FILE** fp);
//adat olvasasa filebol
void getData(FILE* fp,ugyfel** root,char* prevDatum);
//fo menu meghivsa
void callMenu(char* datum, char* filename,FILE *fp, ugyfel* datalist);
//uj listaelem letrehozasa
ugyfel* createElement(char* nev,char* email,char* telefonszam,char* kezdoosz,char* lekotesdatum,char* kamat);
//a lista fileba irasa
void fileWrite(ugyfel* root,char* filename,char* datum);
#include "functions.c"