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
    int i;

    //  - - preenchendo os dados dos territórios - - 
    printf("\nCadastro de Territórios:\n\n");

    // - - O laço será executado a cada 5 vezes, 1 para cada território. 
    for ( i = 0; i < 5; i++)

    {
        printf("Território %d:\n", i + 1);

        printf("Digite o nome do território: ");
        fgets(territorios[i].nome, NUM_TERRITORIOS, stdin); // lendo o nome do território
        scanf("%s", territorios[i].nome); // lendo o nome do território
    }
        
    
}