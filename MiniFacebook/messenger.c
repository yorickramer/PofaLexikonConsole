#include "messenger.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "mainfv.h"

void uzenetfelszabadit(Uzenetlista *eleje){
    Uzenetlista *iter = eleje;
    while(iter!=NULL){
        Uzenetlista *kov=iter->kov;
        free(iter);
        iter=kov;
    }
}

void messkiir(char *name1,char *name2){

    Uzenetlista *eleje;
    Uzenetlista *mozgo;
    Uzenetlista *uj;

    FILE *f = fopen("uzenet.txt", "rt");
    if (f == NULL) {
        perror("Nem sikerült megnyitni a filet");
        return;
    }

    uj = (Uzenetlista*) malloc(sizeof(Uzenetlista));

    while (fscanf(f, " %[^\t]", uj->text)== 1){
    eleje = uj;
    uj->kov = NULL;

        while (strcmp(uj->text,"~")!=0){
            uj = (Uzenetlista*) malloc(sizeof(Uzenetlista));
            fscanf(f, " %[^\t]", uj->text);
            mozgo = eleje;
            while (mozgo->kov != NULL)
                mozgo = mozgo->kov;
            mozgo->kov = uj;
            uj->kov = NULL;
        }


        if (strcmp(eleje->text,name1)==0&&strcmp(eleje->kov->text,name2)==0){
            printf("- %s\n",eleje->kov->kov->text);
        }

        else if (strcmp(eleje->text,name2)==0&&strcmp(eleje->kov->text,name1)==0){
            printf("+ %s\n",eleje->kov->kov->text);
        }

        uzenetfelszabadit(eleje);

        uj = (Uzenetlista*) malloc(sizeof(Uzenetlista));
    }

    uzenetfelszabadit(uj);
    fclose(f);
    return;
}

void sendmess(char *uzenet, char *name1, char *name2){

    FILE *f = fopen("uzenet.txt", "a");
    if (f == NULL) {
        perror("Nem sikerült megnyitni a filet");
        return;
    }

    fprintf(f,"%s\t%s\t%s\t~\t\n",name1,name2,uzenet);
    fclose(f);

}

void messenger(char *name){

    char barat[101];
    //char nev[101];
    int valaszt;
    char uzenet[10001];
    char c;

    AdatokLista *eleje;
    AdatokLista *mozgo;

    eleje= ismerosok(name);


    //system("cls");
    printf("uzenetek\n\n");
    printf("ismeroseid:\n");

    for (mozgo = eleje; mozgo != NULL; mozgo = mozgo->kov)
            printf("- %s\n",mozgo->nev);


    printf("\nkinek szeretnel uzenetet kuldeni?\n");
    scanf("%s",barat);
    system("cls");
    printf("beszelgetes vele: %s\n\n",barat);
    messkiir(name,barat);
    printf("\nuj uzenet irasa : 1 vissza : 2\n");
    scanf("%d",&valaszt);

    while(valaszt==1){

            printf("uzeneted '- & enter' a kuldes :  ");

            strcpy(uzenet,"");

            int i=0;
            scanf("%c",&c);

            while(c!='-'){
                uzenet[i]=c;
                scanf("%c",&c);

                i=i+1;
            }
            uzenet[i]=0;
            uzenet[0]=' ';

            sendmess(uzenet,name,barat);
            system("cls");

            printf("beszelgetes vele: %s\n\n",barat);
            messkiir(name,barat);
            printf("\nuj uzenet irasa :1 vissza :2\n");
            scanf("%d",&valaszt);
    }
}
