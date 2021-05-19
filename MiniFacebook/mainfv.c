#include "mainfv.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <windows.h>

/*felszabadítja az átadott láncolt listát*/
void felszabadit(AdatokLista *eleje){
    AdatokLista *iter = eleje;
    while(iter!=NULL){
        AdatokLista *kov=iter->kov;
        free(iter);
        iter=kov;
    }
}

//lancolt listat csinal az adatokbol
AdatokLista* lista(char *name){

    AdatokLista *eleje=NULL;
    AdatokLista *mozgo;
    AdatokLista *uj;
    FILE *f = fopen("adatok.txt", "rt");
    if (f == NULL) {
        perror("Nem sikerült megnyitni a filet");
        return NULL;
    }

    uj = (AdatokLista*) malloc(sizeof(AdatokLista));

    while (fscanf(f, " %[^\t]", uj->nev)== 1){
    eleje = uj;
    uj->kov = NULL;

        while (strcmp(uj->nev,"~")!=0){
            uj = (AdatokLista*) malloc(sizeof(AdatokLista));
            fscanf(f, " %[^\t]", uj->nev);
            mozgo = eleje;
            while (mozgo->kov != NULL)
                mozgo = mozgo->kov;
            mozgo->kov = uj;
            uj->elo=mozgo;
            uj->kov = NULL;
        }

        /**ha keresett felhasznaló sora, akkor a fv visszaadja a listara mutato pointert**/
        if (strcmp(eleje->nev,name)==0){
            fclose(f);
            return eleje;
        }
        /**ezt majd fel kell szabadítani!!!**/

        /**ha nem : akkor felszabadítja a listat**/
        else{
            felszabadit(eleje);
        }

        uj = (AdatokLista*) malloc(sizeof(AdatokLista));
    }

    fclose(f);
    return NULL;
}


/*megjeleneiti a szemelyes adatokat*/
void szemelyes(char *name){
    system("cls");
    int tipus = 1;
    AdatokLista *eleje;
    AdatokLista *mozgo;
    eleje=lista(name); /**megkapja a listat -> fel kell szabadítani !!!**/

    for (mozgo = eleje; mozgo != NULL; mozgo = mozgo->kov) {
            switch (tipus){
            case 1:
                printf("NEV: ");
                tipus=tipus+1;
                break;
            case 2:
                printf("ELETKOR: ");
                tipus=tipus+1;
                break;
            case 3:
                printf("LAKOHELY: ");
                tipus=tipus+1;
                break;
            case 4:
                printf("NEM: ");
                tipus=tipus+1;
                break;
            case 5:
                printf("\nISMEROSOK: ");
                tipus=tipus+1;
                break;

            default:
                break;
            }
                if (strcmp(mozgo->nev,"~")!=0&&strcmp(mozgo->kov->nev,"*")!=0&&strcmp(mozgo->nev,"*")!=0){
                    if (tipus>5&&strcmp(mozgo->kov->nev,"~")!=0)
                        printf("%s, ", mozgo->nev);
                    else if (strcmp(mozgo->kov->nev,"~")==0) /**ha az utolso nev kovetkezik, akkor nem ir "," -t**/
                        printf("%s", mozgo->nev);
                    else
                        printf("%s\n", mozgo->nev);
                }
    }
    felszabadit(eleje); /**felszabadítja a listát**/
    printf("\n");
    return;
}

/****/
//adatok modositasa;
void linemodify(int tipus,char *name){
    int nem;
    AdatokLista *eleje = lista(name); /**megkapja a listat -> fel kell szabadítani !!!**/

    switch(tipus){
    case 1: //kor
        printf("Ird be az uj korodat\n");
        scanf("%s",eleje->kov->nev);
        break;
    case 2: //varos
        printf("Ird be az uj varosodat\n");
        scanf("%s",eleje->kov->kov->nev);
        break;
    case 3: //nem
        printf("ferfi: 1 no : 2\n");
        scanf("%d",&nem);
        if (nem==1)
            strcpy(eleje->kov->kov->kov->nev,"ferfi\0");
        else
            strcpy(eleje->kov->kov->kov->nev,"no\0");
        break;
    }
    sormodosit(eleje,name);
    felszabadit(eleje); /**miutan visszatert a sormodosit fv bol, fel lehet szabadítani a listat**/

}

//egy adott sort modosit
void sormodosit(AdatokLista *eleje2, char *name){

    AdatokLista *eleje=NULL;
    AdatokLista *mozgo;
    AdatokLista *uj;

    FILE *f = fopen("adatok.txt", "rt");
    if (f == NULL) {
        perror("Nem sikerült megnyitni a filet");
        return;
    }
    FILE *f2 = fopen("seged.txt", "wt");
    if (f2 == NULL) {
        perror("Nem sikerült megnyitni a filet");
        return;
    }

    uj = (AdatokLista*) malloc(sizeof(AdatokLista));

    while (fscanf(f, " %[^\t]", uj->nev)== 1){
    eleje = uj;
    uj->kov = NULL;

        while (strcmp(uj->nev,"~")!=0){
            uj = (AdatokLista*) malloc(sizeof(AdatokLista));
            fscanf(f, " %[^\t]", uj->nev);
            mozgo = eleje;
            while (mozgo->kov != NULL)
                mozgo = mozgo->kov;
            mozgo->kov = uj;
            uj->kov = NULL;
        }

        AdatokLista *m;
        if (strcmp(eleje->nev,name)==0){
            for (m = eleje2; m != NULL; m = m->kov)
                fprintf(f2, "%s\t", m->nev);
        } /**ezt a listat a linemodify fv ben szabadítom fel**/

        else{
            for (m = eleje; m != NULL; m = m->kov)
                fprintf(f2, "%s\t", m->nev);
        }
        fprintf(f2, "\n");
        uj = (AdatokLista*) malloc(sizeof(AdatokLista));
    }
    /**felszabadítom az ujonnan letrehozott listat**/
    felszabadit(eleje);
    fclose(f);
    fclose(f2);
    remove("adatok.txt");
    rename("seged.txt", "adatok.txt");
}

/*keres az adatbazisban, majd felsorolja az informaciokat*/
void idkereso(int start){ //nev1 kor2 lakhely nem
    system("cls"); /**képernyő törlése**/
    char kereses[101];

    printf("Kereses:\n");
    scanf("%s",kereses);
    system("cls");

    printf("Kereses eredmenye:\n\n");

    AdatokLista *eleje=NULL;
    AdatokLista *mozgo;
    AdatokLista *uj;

    FILE *f = fopen("adatok.txt", "rt");
    if (f == NULL) {
        perror("Nem sikerült megnyitni a filet");
        return;
    }

    uj = (AdatokLista*) malloc(sizeof(AdatokLista));

    while (fscanf(f, " %[^\t]", uj->nev)== 1){
    eleje = uj;
    uj->kov = NULL;

        while (strcmp(uj->nev,"~")!=0){
            uj = (AdatokLista*) malloc(sizeof(AdatokLista));
            fscanf(f, " %[^\t]", uj->nev);
            mozgo = eleje;
            while (mozgo->kov != NULL)
                mozgo = mozgo->kov;
            mozgo->kov = uj;
            uj->kov = NULL;
        }


        switch(start){
            case 1:
                if (strcmp(eleje->nev,kereses)==0){
                    szemelyes(eleje->nev);
                    printf("\n\n");
                    felszabadit(eleje); /**felszabadítjuk a listat**/
                }
                else{
                    felszabadit(eleje); /**felszabadítjuk a listat**/
                    }
                break;

            case 2:
                if (strcmp(eleje->kov->nev,kereses)==0){
                    szemelyes(eleje->nev);
                    printf("\n\n");
                    felszabadit(eleje); /**felszabadítjuk a listat**/
                }
                else{
                    felszabadit(eleje); /**felszabadítjuk a listat**/
                    }
                break;

            case 3:
                if (strcmp(eleje->kov->kov->nev,kereses)==0){
                    szemelyes(eleje->nev);
                    printf("\n\n");
                    felszabadit(eleje); /**felszabadítjuk a listat**/
                }
                else{
                    felszabadit(eleje); /**felszabadítjuk a listat**/
                    }
                break;
            case 4:
                if (strcmp(eleje->kov->kov->kov->nev,kereses)==0){
                    szemelyes(eleje->nev);
                    printf("\n\n");
                    felszabadit(eleje); /**felszabadítjuk a listat**/

                }
                else{
                    felszabadit(eleje); /**felszabadítjuk a listat**/
                    }
                break;
            default:
                break;
        }


        uj = (AdatokLista*) malloc(sizeof(AdatokLista));
    }
    felszabadit(uj); //a vegen foglalt teruletet felszabadítja
    fclose(f);
}


void follow(char *name){
    int eldont;
    char nev[101];

    printf("ird be kit szeretnel ismerosnek jelolni\n");
    scanf("%s",nev);

    printf("\n\n");
    szemelyes(nev); /**kiírja a keresett szemely adatait**/

    AdatokLista *eleje = lista(nev); /**elejet fel kell szabadítani !!!**/
    AdatokLista *mozgo;
    bool talalt=false;
    for (mozgo = eleje; mozgo != NULL; mozgo = mozgo->kov){
        if (strcmp(mozgo->nev,name)==0){
            talalt=true;
            printf("\n%s mar az ismerosod\n\n",eleje->nev);
            felszabadit(eleje);
            return;
        }
    } /**ellenorzi az ismerettséget**/
    if (talalt==false){
        printf("nincs ilyen nevu felhasznalo\n");
        felszabadit(eleje);
        return;
    }


    printf("\nismerosnek szeretned jelolni igen : 1 - nem : 2 ?\n");
    scanf("%d",&eldont);

    if (eldont==1){

        mozgo = eleje;
        while (mozgo->kov != NULL)
            mozgo = mozgo->kov;
        strcpy(mozgo->nev,name);
        strcat(mozgo->nev,"\t*\t~");


     sormodosit(eleje,eleje->nev);
     felszabadit(eleje); /**lista felszabadítása**/
    }
}


bool confirm(char *name){

    char barat[101];
    AdatokLista *eleje = lista(name); /**Listat fel kell majd szabaditani**/
    AdatokLista *mozgo;
    int eldont;
    bool talalt;

    system("cls");
    printf("Ismerosok visszaigazolasa\n\n");
    talalt=jelolt(eleje); /**megnezi hogy van e ismerosnek jeloles, ha van kiirja**/

    if (talalt==false){
        system("cls");
        printf("nincsenek ismerosnek jeloleseid\n\n");
        return false;
    }

    printf("\nird be a nevet annak akit vissza szeretnel igazolni ismerosnek\n");
    scanf("%s",barat);
    talalt=baratjelolt(eleje,barat);

    if (talalt==false){
        system("cls");
        printf("ilyen nevu ember nem jelolt ismerosnek teged!\n");
        return false;
    }

    printf("\nbiztos vissza szeretned igazolni?\nigen : 1\nnem : 2\n\nValaszt : ");
    scanf("%d",&eldont);

    if(eldont==1){
        for (mozgo = eleje; mozgo != NULL; mozgo = mozgo->kov) {
            if (strcmp(mozgo->nev,"*")==0&&strcmp(mozgo->elo->nev,barat)==0){
                mozgo->elo->kov=mozgo->kov;
                free(mozgo);
            }
        }
    }

    sormodosit(eleje,name);
    system("cls");
    printf("Sikeresen visszaigazoltad\n");
    felszabadit(eleje);

    eleje=lista(barat); /**akit visszaigazoltunk, ismerosnek ad minket**/
    mozgo = eleje;
        while (mozgo->kov != NULL)
            mozgo = mozgo->kov;
        strcpy(mozgo->nev,name);
        strcat(mozgo->nev,"\t~");
     sormodosit(eleje,eleje->nev);

    felszabadit(eleje);
    return true;
} /**memoria felszabaditva - fv tobb reszre kell osztani**/


bool jelolt(AdatokLista *eleje){
    bool talalt = false;
    AdatokLista *mozgo;

    for (mozgo = eleje; mozgo != NULL; mozgo = mozgo->kov) {
        if (strcmp(mozgo->nev,"*")==0){
            printf("- %s\n",mozgo->elo->nev);
            talalt=true;
        }
    } /**megnezi hogy van e ismerosnek jeloles, ha van kiirja**/

    return talalt;
}


bool baratjelolt(AdatokLista *eleje, char *barat){
    AdatokLista *mozgo;
    bool talalt=false;
    for (mozgo = eleje; mozgo != NULL; mozgo = mozgo->kov) {
        if (strcmp(mozgo->nev,"*")==0){
            if(strcmp(mozgo->elo->nev,barat)==0)
                talalt=true;
        }
    } /**leellenorzi, hogy akit vissza szeretnel igazolni, az bejelolt e teged**/

    return talalt;
}


//ismerosok ismerosei itt kezdodnek
void ismerosokism(char *name){


    AdatokLista *eleje=ismerosok(name); /**fel kell majd szabaditani a listat!!!**/

    AdatokLista *mozgo;
    //printf("\nvisszatert\n");
    AdatokLista *keresett=NULL;

    if (eleje==NULL){
        printf("nincs ismerosod\n");
        return;
    }

    for (mozgo = eleje; mozgo != NULL; mozgo = mozgo->kov){
        nemismeroslista(name, eleje, mozgo->nev, &keresett);
        //printf("%s\n",mozgo->nev);
    }
    system("cls");
    printf("Ismeroseid ismerosei:\n");
    for (mozgo = keresett; mozgo!=NULL;mozgo=mozgo->kov)
        printf("- %s\n",mozgo->nev);

    felszabadit(keresett);
    felszabadit(eleje);
 /**keresett felszabaditasa - eleje felszabaditasa !!**/
 return ;
}

void nemismeroslista(char *nev, AdatokLista *felhasznalo, char *barat, AdatokLista **keresett){

    //printf("barat : %s\n",barat);

    AdatokLista *barateleje=ismerosok(barat);
    AdatokLista *mozgo, *mozgo2;
    AdatokLista *uj;

    bool talalt = false;

    for (mozgo=barateleje; mozgo!=NULL; mozgo=mozgo->kov){
        for (mozgo2=felhasznalo; mozgo2!=NULL; mozgo2=mozgo2->kov){
            if(strcmp(mozgo->nev,mozgo2->nev)==0)
                talalt=true;
        }
        if (strcmp(mozgo->nev, nev)==0)
            talalt=true;
        if (talalt==false){
            uj = (AdatokLista*) malloc(sizeof(AdatokLista));
            strcpy(uj->nev,mozgo->nev);
            uj->kov=*keresett;
            *keresett=uj;
        }
        talalt=false;
    }

    felszabadit(barateleje);
    /*for (mozgo=*keresett; mozgo!=NULL; mozgo=mozgo->kov)
        printf("///  %s\n",mozgo->nev);*/
    /**felszabadit a barateleje listat**/
}

AdatokLista* ismerosok(char *name){
    //printf("name : %s\n",name);
    AdatokLista *eleje=lista(name);/**megkapja az illeto informaciot lancolt listaban**/
    AdatokLista *mozgo;
    for (mozgo = eleje; mozgo != NULL; mozgo = mozgo->kov){
            //printf("%s:  %s\n",name, mozgo->nev);
    }
    /**a meg nem ismerosok kiszedese a listabol**/
    for (mozgo = eleje; mozgo != NULL; mozgo = mozgo->kov){
        if(strcmp(mozgo->nev,"*")==0){
            AdatokLista *seged = mozgo->elo->elo;
            //printf("seged : %s\n",seged->nev);
            AdatokLista *utan = mozgo->kov;
            //printf("kov: %s\n", utan->nev);
            free(mozgo->elo);
            free(mozgo);
            utan->elo=seged;
            seged->kov=utan;
            mozgo=seged;
        }
        //printf("*%s *: %s\n",name,mozgo->nev);
    }

    /**az elso 4 adat kiszedese a listabol**/
    for (int i=1;i<=4;i++){
        AdatokLista *kov=eleje->kov;
        free(eleje);
        eleje=kov;
    }
    if(eleje->kov==NULL){
        free(eleje);
        return NULL;
    }

    /**~ torlese a listabol (utolso lancszem)**/
    for (mozgo = eleje; mozgo->kov != NULL; mozgo = mozgo->kov);
    AdatokLista *seged = mozgo->elo;
    felszabadit(mozgo); /**felszabadítjuk a listat**/
    seged->kov=NULL;

    for (mozgo = eleje; mozgo != NULL; mozgo = mozgo->kov){
        //printf("::: %s\n",mozgo->nev);
    }

    return eleje;
}


