#include <stdio.h>
#include <string.h>

#define NUM_TERRITORIOS 5 //crinando uma constante para o número de territórios

//  - - criando a estrutura de territótio usando struct - -
struct territorio {
    char nome[30]; // nome do território
    char cor[10]; // cor do território
    int tropas; // número de tropas do território 
};
// - - função para limpar o buffer de entrada - -
void limparbufferentrada()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
// - - função principal - - 

int main() {
    struct territorio territorios[NUM_TERRITORIOS];
    int totalterritorios = 0; 
    int opcao;
}