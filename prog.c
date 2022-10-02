#include<stdio.h>
#include<stdlib.h>
#include "header.h"

int main(int argc, char* args[]){
    char filename[51];
    FILE* fp;
    ugyfel* root=createElement("NEV","EMAIL","TELEFONSZAM","EGYENLEG","UTOLSO MUVELET","EVES KAMAT ( % )");
    char* prevDatum=malloc(sizeof(char)*12);
    fileInit(filename,&fp);
    getData(fp,&root,prevDatum);

    char* datum=malloc(sizeof(char)*12);
    datumInit(datum,prevDatum);
    
    callMenu(datum , filename,fp, root); 
    free(prevDatum);
    fclose(fp);
    fileWrite(root , filename, datum);
    free(datum);
    destroyList(&root);
    printf("Viszont latasra!\n");
    return 0;
}