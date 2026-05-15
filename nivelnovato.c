#include <stdio.h>
#include <string.h>

#define NUM_TERRITORIOS 5 //crinando uma constante para o número de territórios

//  - - criando a estrutura de territótio usando struct - -
struct territorio {
    char nome[30]; // nome do território
    char cor[10]; // cor do território
    int tropas; // número de tropas do território 
};

// - - função principal - - 

int main() {
    struct territorio territorios[NUM_TERRITORIOS];
    int i;

    //  - - preenchendo os dados dos territórios - - 
    printf("\nCadastro de Territórios:\n\n");

    // - - O laço será executado a cada 5 vezes, 1 para cada território. 
    for ( i = 0; i < NUM_TERRITORIOS; i++)
    {
        printf("Território %d:\n", i + 1);

        printf("Digite o nome do território: ");
        fgets(territorios[i].nome, sizeof territorios[i].nome, stdin);
        remover_newline(territorios[i].nome);

        printf("Digite a cor do território: ");
        fgets(territorios[i].cor, sizeof territorios[i].cor, stdin);
        remover_newline(territorios[i].cor);

        printf("Digite o número de tropas:\n ");
        if (scanf("%d", &territorios[i].tropas) != 1) {
            territorios[i].tropas = 0;
        }

    }
        // Aqui irei exibir os dados dos territórios cadastrados 
        
        printf("\n - - territórios cadastrados - - \n\n");
        for ( i = 0; i < NUM_TERRITORIOS; i++)
        {
            printf("Território %d:\n", i + 1);
            printf("Nome: %s\n", territorios[i].nome);
            printf("Cor: %s\n", territorios[i].cor);
            printf("Número de tropas: %d\n\n", territorios[i].tropas);
        }
        
        return 0;
    
}