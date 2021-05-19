#include "loginfv.h"
#include "mainfv.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
//#include "debugmalloc.h"

/*ellenorzi reguisztralasnal hogy foglalt e a nev mar, visszateresi erteke igaz hamis -lehet lokalis */
 bool check(char *name){

        char nev[100+1];
    FILE *f = fopen("reg.txt", "r");
    if (f == NULL) {
        perror("Nem sikerült menteni a filet");
        return false;
    }
    while (fscanf(f, " %[^\n]",nev) == 1) {
        sscanf(nev, "%s", nev);
        if (strcmp(nev,name)==0){
            fclose(f);
            return false;
        }
    }

    fclose(f);
    return true;
}


/*regisztracios fv- ez hivja meg a check fvt, nem lehet lokalis fv*/
bool registrate(void){

    char name[101];
    char password[101];

    printf("REGISZTRACIO\n");
    printf("ird be a profilnevet\n");
    scanf("%s",name);
    printf("ird be a jelszot\n");
    scanf("%s",password);
    system("cls");
    if(check(name)==false){
        //printf("Ez a felhasznalonev mar foglalt!\n");
        return false;
    }

    FILE *f = fopen("reg.txt", "a");
    if (f == NULL) {
        perror("Nem sikerült megnyitni a filet");
        return false;
    }
    fprintf(f, "%s\t%s\t~\t\n", name,password);
    fclose(f);

    FILE *f2 = fopen("adatok.txt", "a");
    if (f == NULL) {
        perror("Nem sikerült megnyitni a filet");
        return false;
    }
    fprintf(f2, "%s\t-\t-\t-\t~\t\n", name);
    fclose(f2);
return true;
}


/*belepes fv - ha belepett igazat visszateresi erteke true, nem lehet static fv*/
bool login(char *id){
    char name[100+1];
    char password[100+1];
    char nev[100+1];
    char jelszo[100+1];
    char sor[200+1];
    system("cls");
    printf("BELEPES\n\n");
    printf("ird be a profilnevet\n");
    scanf("%s",name);
    printf("ird be a jelszot\n");
    scanf("%s",password);
    system("cls");

    FILE *f = fopen("reg.txt", "r");
    if (f == NULL) {
        perror("Nem sikerült megnyitni a filet");
        return false;
    }
    while (fscanf(f, " %[^\n]",sor) == 1)
        {
        sscanf(sor, "%s\t%s", nev,jelszo);
        if (strcmp(nev,name)==0&&strcmp(jelszo,password)==0)
        {
            fclose(f);
            strcpy(id, name);
            return true;
        }
    }
    fclose(f);
    return(false);
}

