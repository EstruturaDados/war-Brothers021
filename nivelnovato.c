#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO_NOME 30
#define TAMANHO_COR 10
#define NUM_TERRITORIOS 5

//  - - criando a estrutura de territótio usando struct - -
 typedef struct {
    char nome[TAMANHO_NOME]; // nome do território
    char cor[TAMANHO_COR]; // cor do território
    int tropas; // número de tropas do território 
} territorio;

// criando um buffer para limpar a entrada de dados.
    void limparBuffer() {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }

// * * * nova função que simula um ataque * * * 
// simula um combate entre dois territórios usando números aleatórios

    void atacar(territorio* atacante, territorio* defensor) {
        //Aqui vamos simular os dados de ataque
        int dadoAtacante = (rand() % 6) + 1; // dados de atacante 
        int dadoDefensor = (rand() % 6) + 1; // dados do defensor

        printf("\n - - Resultado da Batalha - -\n");
        printf("Dado do Atacante: %d\n", dadoAtacante);
        printf("Dado do defensor: %d\n", dadoDefensor);

        // Aqui verifica quem venceu!
        if (dadoAtacante > dadoDefensor)
        { // aqui o atacante venceu
            printf("%s Venceu a batalha!\n\n", atacante ->nome);

            // Calcula as tropas que foram transferidas
            int tropasTransferidas =  atacante->tropas /2;

            //Aqui atualiza as informações do defensor
            strcpy(defensor->cor, atacante->cor); // faz mudar a cor do territorio
            defensor->tropas = tropasTransferidas; //Aqui ele recebe as tropas

            // Vamos atualizar as informações do atacante 
            atacante->tropas = atacante->tropas - tropasTransferidas;

            printf("O território '%s' agora pertence a %s!\n", defensor->nome, atacante->cor);
            printf("tropas transferidas: %d\n\n", tropasTransferidas);

        } else if (dadoAtacante < dadoDefensor) {
            // O defensor venceu!
            printf(" %s Defendeu com sucesso!\n\n", defensor->nome);
            atacante->tropas--;
            printf("%s perdeu 1 tropa na batalha.\n",atacante->nome);
            printf("Tropas restantes do atacante: %d\n\n", atacante->tropas);
        } else {
            // Aqui vamos conferir o empate 
            printf(" Foi um Empate!\n\n");
            atacante->tropas--;
            printf("como foi empate, %s perde 1 tropa (perdeu a vez).\n", atacante->nome);
            printf("Tropas restantes do atacante: %d\n\n", atacante->tropas);
        }
        
    }
// - - função principal - - 

int main() {
    struct territorio territorio[NUM_TERRITORIOS];
    int i;

    //  - - preenchendo os dados dos territórios - - 
    printf("\n - - Cadastro de Territórios: - -\n\n");

    // - - O laço será executado a cada 5 vezes, 1 para cada território. 
    for ( i = 0; i < NUM_TERRITORIOS; i++)
    {
        printf("Território %d:\n", i + 1);

        printf("Digite o nome do território:\n");
        fgets(territorios[i].nome, sizeof territorios[i].nome, stdin);
        //remove o "\n" que o fgets guarda no final da string
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0';

        printf("Digite a cor do território:\n");
        fgets(territorios[i].cor, sizeof territorios[i].cor, stdin);
        //remove o "\n" que o fgets guarda no final da string

        printf("Digite o número de tropas:\n");

        if (scanf("%d", &territorios[i].tropas) != 1) {
            territorios[i].tropas = 0;
        }
        //limpa o \n que sobrou no buffer após o scanf
        limparBuffer();

        printf("\n");

    }
        // Aqui irei exibir os dados dos territórios cadastrados 
        
        printf("\n - - territórios cadastrados - - \n\n");
        for ( i = 0; i < NUM_TERRITORIOS; i++)
        {
            printf("Território %d:\n", i + 1);
            printf("Nome:  %s\n", territorios[i].nome);
            printf("Cor:  %s\n", territorios[i].cor);
            printf("Número de tropas: %d\n", territorios[i].tropas);
        }
        
        return 0;
    
} 