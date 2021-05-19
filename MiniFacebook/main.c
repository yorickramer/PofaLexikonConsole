#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "loginfv.h"
#include "mainfv.h"
#include "messenger.h"
#include <time.h>
#include <windows.h>
//#include "debugmalloc.h"



int main(){

    int start;
    int valaszto = 0;

    char id[101];


    bool exit = false;

    //bool logged_in = false;


while(exit!=true){


    switch(valaszto){

      case  0:  //regisztracios oldal starting page
            printf("FACEBOOK\n\n");
            printf("BELEPES : 0 - REGISZTRACIO : 1\n");
            scanf("%d",&start);
            switch(start){
                case 0:
                    valaszto=2;
                    break;
                case 1:
                    valaszto=1;
                    break;
                default:
                    valaszto=0;
                    system("cls");
                    break;
            }
            break;

        case 1: //regisztracios page

            if (registrate()){
                system("cls");
                printf("sikeres regisztracio\n");
                valaszto=2;
            }
            else{
                printf("felhasznalo mar foglalt\n");
                valaszto=0;
            }

            break;



        case 2: //bejelentkezõ rész

            if(login(id)==true){
                printf("sikeres belepes\n");
                //logged_in=true;
                //printf("%s",id);
                valaszto=3;
            }
            else{
                printf("sikertelen belepes\n");
                valaszto=0;
            }

            break;

        case 3: //main menu
            start=0;
            system("cls");
            printf("kijelentkezes : 0 \nszemelyes adatok : 1 \nkereses : 2\nismerosnek jeloles : 3\nismerosok ismerosei: 4 \njelolesek : 5\nuzenetek : 6\nprogram bezarasa : 7\n");
            printf("\nValaszt :");
            scanf("%d",&start);
            switch(start){
                case 0:
                    valaszto=0;
                    system("cls");
                    //logged_in=false;
                    break;
                case 1:
                    valaszto=4;
                    break;
                case 2:
                    valaszto=6; //kereses
                    break;
                case 3:
                    valaszto=7;
                    break;
                case 4:
                    valaszto=8;
                    break;
                case 5:
                    valaszto=9;
                    break;
                case 6:
                    valaszto=10;
                    break;
                case 7:
                    exit=true;
                    break;
                default:
                    break;
            }
            break;



        case 4: //szemelyes adatok megjelenitese
            szemelyes(id);
            printf("\nvissza:0\n\nSzemelyes adatok modositasa : 1\n");
            scanf("%d",&start);
            switch(start){
            case 0:
                valaszto=3;
                break;
            case 1:
                valaszto=5;
                break;
            default:
                break;
            }

            break;


        case 5: //szemelyes adatok modositasa menu
            system("cls");
            printf("Mit szeretnel modositani? \nKor : 1 \nLakhely : 2 \nNem :3\n\nvissza: 0 - ");
            scanf("%d",&start);
            if (start==0)
                valaszto=4;
            else{
                linemodify(start,id);
                printf("Adatok modositava\n");
                valaszto=4;
            }
            break;

        case 6: //kereses algoritmusa

            printf("Mi alapjan szeretnel keresni? nev : 1 kor: 2 lakhely : 3 Nem : 4\n\n-- vissza : 0\n");
            scanf("%d",&start);
            if (start==0)
                valaszto=3;
            else if (start<=4)
                idkereso(start);
            break;

        case 7: //ismeros bekovetese

            //system("cls");
            follow(id);
            printf("vissza : 0 -  Uj ember keresese : 1\nValaszt: ");
            scanf("%d",&start);
            if (start==0)
                valaszto=3;
            else if (start==1){
                system("cls");
                valaszto=7;
            }
            break;

        case 8: //ismerosok ismerosei
            //bool siker = false;
            ismerosokism(id);
            printf("\nvissza : 1\n");
            scanf("%d",&start);
            if(start==1)
                valaszto=3;
            break;

        case 9: /*confirm freiendship*/
            if(confirm(id)){
                printf("Menu : 1 \nMas visszaigazolasa : 2\n\nValaszt : ");
                scanf("%d",&start);
            }
            else{
                printf("Menu : 1\n");
                scanf("%d",&start);
            }

            if (start==1)
                valaszto=3;
            else
                valaszto=9;
            break;


        case 10: //uzenetek
            system("cls");
            messenger(id);
            printf("menu : 1 , uzenetek : 2\n");
            scanf("%d",&start);
            if (start==1)
                valaszto=3;
            else
                valaszto=10;

            break;
        }


}
    system("cls");
    printf("kilepve...");
///*ismerosnek jeloles, ismerosok ismerosei felajanlas -- uzenetek kuldese, *///
return 0;
}

