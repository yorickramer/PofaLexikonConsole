#ifndef MAINFV_H
#define MAINFV_H
#include <stdbool.h>
#include <time.h>
#include <windows.h>


typedef struct AdatokLista{
    char nev[101];
    struct AdatokLista *kov;
    struct AdatokLista *elo;
}AdatokLista;

void follow(char *name);

void szemelyes(char *name);

void kereso(int *valaszto);

void idkereso(int start);

void linemodify(int tipus, char *name);

bool confirm(char *name);

AdatokLista* lista(char *name);

void sormodosit(AdatokLista *eleje, char *name);

void ismerosokism(char *name);

AdatokLista* ismerosok(char *name);

void nemismeroslista(char *nev, AdatokLista *felhasznalo, char *barat, AdatokLista **keresett);

void felszabadit(AdatokLista *eleje);

bool jelolt(AdatokLista *eleje);

bool baratjelolt(AdatokLista *eleje,char * barat);

#endif
