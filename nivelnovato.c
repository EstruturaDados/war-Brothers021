#include <stdio.h>
#include <stdlib.h>

#define NUM_TERRITORIOS 5 //crinando uma constante para o número de territórios

//  - - criando a estrutura de territótio usando struct - -
struct territorio {
    char nome[30]; // nome do território
    char cor[10]; // cor do território
    int tropas; // número de tropas do território 
};