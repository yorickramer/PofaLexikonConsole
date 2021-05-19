#ifndef MESSENGER_H
#define MESSENGER_H
#include <stdbool.h>

typedef struct Uzenetlista{
    char text[10001];
    struct Uzenetlista *kov;
}Uzenetlista;

void uzenetfelszabadit(Uzenetlista *eleje);

void messenger(char *name);

void messkiir(char *name1,char *name2);

void sendmess(char *uzenet, char *name1, char *name2);

#endif
