#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO_NOME 30
#define TAMANHO_COR 10
#define MAX_MISSAO 100

// Estrutura de um território com nome, cor e tropas.
typedef struct {
    char nome[TAMANHO_NOME];
    char cor[TAMANHO_COR];
    int tropas;
} Territorio;

// Limpa o buffer de entrada após scanf.
void limparBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Exibe o mapa de territórios.
void exibirMapa(Territorio* mapa, int tamanho) {
    printf("\n--- MAPA ATUAL DE TERRITÓRIOS ---\n");
    for (int i = 0; i < tamanho; i++) {
        printf("Território %d:\n", i + 1);
        printf("  Nome: %s\n", mapa[i].nome);
        printf("  Cor: %s\n", mapa[i].cor);
        printf("  Tropas: %d\n\n", mapa[i].tropas);
    }
}

// Atribui uma missão aleatória a um jogador.
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int indice = rand() % totalMissoes;
    strcpy(destino, missoes[indice]);
}

// Exibe a missão do jogador.
void exibirMissao(const char* missao, const char* jogador) {
    printf("\nMissão do %s:\n", jogador);
    printf("  %s\n\n", missao);
}

// Verifica se a missão foi cumprida.
int verificarMissao(const char* missao, Territorio* mapa, int tamanho, const char* corJogador) {
    if (strstr(missao, "3 territórios seguidos") != NULL) {
        int contador = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, corJogador) == 0) {
                contador++;
                if (contador >= 3) {
                    return 1;
                }
            } else {
                contador = 0;
            }
        }
        return 0;
    }

    if (strstr(missao, "Eliminar todas as tropas da cor vermelha") != NULL) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "vermelha") == 0 && mapa[i].tropas > 0) {
                return 0;
            }
        }
        return 1;
    }

    if (strstr(missao, "Ter pelo menos 10 tropas em um território") != NULL) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, corJogador) == 0 && mapa[i].tropas >= 10) {
                return 1;
            }
        }
        return 0;
    }

    if (strstr(missao, "Controlar mais da metade dos territórios") != NULL) {
        int controle = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, corJogador) == 0) {
                controle++;
            }
        }
        return controle > tamanho / 2;
    }

    if (strstr(missao, "Ter um território com nome iniciado em A") != NULL) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, corJogador) == 0 &&
                (mapa[i].nome[0] == 'A' || mapa[i].nome[0] == 'a')) {
                return 1;
            }
        }
        return 0;
    }

    return 0;
}

// Simula um ataque entre dois territórios.
void atacar(Territorio* atacante, Territorio* defensor) {
    if (atacante->tropas <= 1) {
        printf("O território %s não tem tropas suficientes para atacar.\n", atacante->nome);
        return;
    }

    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("\n--- Resultado da Batalha ---\n");
    printf("Dado do atacante: %d\n", dadoAtacante);
    printf("Dado do defensor: %d\n", dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("%s venceu a batalha!\n", atacante->nome);
        int tropasTransferidas = atacante->tropas / 2;
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = tropasTransferidas;
        atacante->tropas -= tropasTransferidas;
        printf("O território '%s' agora pertence a %s.\n", defensor->nome, atacante->cor);
        printf("Tropas transferidas: %d\n", tropasTransferidas);
    } else if (dadoAtacante < dadoDefensor) {
        printf("%s defendeu com sucesso!\n", defensor->nome);
        atacante->tropas--;
        printf("%s perdeu 1 tropa na batalha.\n", atacante->nome);
    } else {
        printf("Empate! %s perde 1 tropa.\n", atacante->nome);
        atacante->tropas--;
    }

    printf("Tropas restantes do atacante %s: %d\n", atacante->nome, atacante->tropas);
    printf("Tropas do defensor %s: %d\n\n", defensor->nome, defensor->tropas);
}

// Realiza o ataque do jogador atual.
void rodadaAtaque(Territorio* mapa, int tamanho, const char* corJogador) {
    int escolhaAtacante, escolhaDefensor;
    int ataqueValido = 0;

    printf("\n--- Turno do jogador %s ---\n", corJogador);
    exibirMapa(mapa, tamanho);

    while (!ataqueValido) {
        printf("Digite o índice do território atacante (1 a %d): ", tamanho);
        if (scanf("%d", &escolhaAtacante) != 1) {
            limparBuffer();
            printf("Entrada inválida! Tente novamente.\n");
            continue;
        }
        limparBuffer();

        if (escolhaAtacante < 1 || escolhaAtacante > tamanho) {
            printf("Índice inválido! Tente novamente.\n");
            continue;
        }
        escolhaAtacante--;

        if (strcmp(mapa[escolhaAtacante].cor, corJogador) != 0) {
            printf("Escolha um território que pertença ao jogador %s.\n", corJogador);
            continue;
        }

        if (mapa[escolhaAtacante].tropas <= 1) {
            printf("Território sem tropas suficientes para atacar.\n");
            continue;
        }

        printf("Digite o índice do território defensor (1 a %d): ", tamanho);
        if (scanf("%d", &escolhaDefensor) != 1) {
            limparBuffer();
            printf("Entrada inválida! Tente novamente.\n");
            continue;
        }
        limparBuffer();

        if (escolhaDefensor < 1 || escolhaDefensor > tamanho) {
            printf("Índice inválido! Tente novamente.\n");
            continue;
        }
        escolhaDefensor--;

        if (escolhaDefensor == escolhaAtacante) {
            printf("Atacante e defensor não podem ser o mesmo território.\n");
            continue;
        }

        if (strcmp(mapa[escolhaDefensor].cor, corJogador) == 0) {
            printf("Você não pode atacar um território da sua própria cor.\n");
            continue;
        }

        ataqueValido = 1;
        printf("\nAtacante: %s (%s, %d tropas)\n", mapa[escolhaAtacante].nome,
               mapa[escolhaAtacante].cor, mapa[escolhaAtacante].tropas);
        printf("Defensor: %s (%s, %d tropas)\n\n", mapa[escolhaDefensor].nome,
               mapa[escolhaDefensor].cor, mapa[escolhaDefensor].tropas);

        atacar(&mapa[escolhaAtacante], &mapa[escolhaDefensor]);
    }
}

// Libera memória alocada dinamicamente.
void liberarMemoria(Territorio* mapa, char* missao1, char* missao2) {
    if (mapa != NULL) {
        free(mapa);
    }
    if (missao1 != NULL) {
        free(missao1);
    }
    if (missao2 != NULL) {
        free(missao2);
    }
}

int main(void) {
    srand(time(NULL));

    int quantidadeTerritorios;
    Territorio* territorios = NULL;
    char corJogador1[TAMANHO_COR];
    char corJogador2[TAMANHO_COR];

    char* missoes[] = {
        "Conquistar 3 territórios seguidos",
        "Eliminar todas as tropas da cor vermelha",
        "Ter pelo menos 10 tropas em um território",
        "Controlar mais da metade dos territórios",
        "Ter um território com nome iniciado em A"
    };
    int totalMissoes = sizeof(missoes) / sizeof(missoes[0]);

    char* missaoJogador1 = malloc(MAX_MISSAO);
    char* missaoJogador2 = malloc(MAX_MISSAO);
    if (missaoJogador1 == NULL || missaoJogador2 == NULL) {
        printf("Erro ao alocar memória para missões.\n");
        free(missaoJogador1);
        free(missaoJogador2);
        return 1;
    }

    printf("\n--- Sistema de Missões Estratégicas ---\n");
    printf("Digite a cor do jogador 1: ");
    fgets(corJogador1, sizeof(corJogador1), stdin);
    corJogador1[strcspn(corJogador1, "\n")] = '\0';

    printf("Digite a cor do jogador 2: ");
    fgets(corJogador2, sizeof(corJogador2), stdin);
    corJogador2[strcspn(corJogador2, "\n")] = '\0';

    while (strcmp(corJogador1, corJogador2) == 0) {
        printf("As cores dos jogadores devem ser diferentes. Digite outra cor para o jogador 2: ");
        fgets(corJogador2, sizeof(corJogador2), stdin);
        corJogador2[strcspn(corJogador2, "\n")] = '\0';
    }

    printf("Digite a quantidade de territórios que deseja criar: ");
    while (scanf("%d", &quantidadeTerritorios) != 1 || quantidadeTerritorios <= 0) {
        limparBuffer();
        printf("Entrada inválida! Por favor, digite um número inteiro positivo: ");
    }
    limparBuffer();

    territorios = malloc(quantidadeTerritorios * sizeof(Territorio));
    if (territorios == NULL) {
        printf("Erro ao alocar memória para territórios.\n");
        liberarMemoria(NULL, missaoJogador1, missaoJogador2);
        return 1;
    }

    printf("\n--- Cadastro de Territórios ---\n");
    for (int i = 0; i < quantidadeTerritorios; i++) {
        printf("Território %d:\n", i + 1);
        printf("Digite o nome do território: ");
        fgets(territorios[i].nome, sizeof(territorios[i].nome), stdin);
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0';

        do {
            printf("Digite a cor do território (%s ou %s): ", corJogador1, corJogador2);
            fgets(territorios[i].cor, sizeof(territorios[i].cor), stdin);
            territorios[i].cor[strcspn(territorios[i].cor, "\n")] = '\0';
            if (strcmp(territorios[i].cor, corJogador1) != 0 && strcmp(territorios[i].cor, corJogador2) != 0) {
                printf("Cor inválida. Use apenas a cor do jogador 1 ou do jogador 2.\n");
            }
        } while (strcmp(territorios[i].cor, corJogador1) != 0 && strcmp(territorios[i].cor, corJogador2) != 0);

        printf("Digite o número de tropas: ");
        while (scanf("%d", &territorios[i].tropas) != 1 || territorios[i].tropas < 0) {
            limparBuffer();
            printf("Entrada inválida! Digite um número inteiro.\n");
        }
        limparBuffer();
        printf("\n");
    }

    atribuirMissao(missaoJogador1, missoes, totalMissoes);
    atribuirMissao(missaoJogador2, missoes, totalMissoes);

    exibirMissao(missaoJogador1, "Jogador 1");
    exibirMissao(missaoJogador2, "Jogador 2");

    int opcao = 0;
    int turnoJogador = 1;
    int ganhou = 0;

    while (opcao != 3 && !ganhou) {
        printf("--- MENU PRINCIPAL ---\n");
        printf("1. Exibir mapa de territórios\n");
        printf("2. Realizar ataque (turno do jogador %d)\n", turnoJogador);
        printf("3. Sair\n");
        printf("Escolha uma opção: ");

        if (scanf("%d", &opcao) != 1) {
            limparBuffer();
            printf("Entrada inválida! Tente novamente.\n\n");
            continue;
        }
        limparBuffer();

        if (opcao == 1) {
            exibirMapa(territorios, quantidadeTerritorios);
        } else if (opcao == 2) {
            const char* corAtual = (turnoJogador == 1) ? corJogador1 : corJogador2;
            rodadaAtaque(territorios, quantidadeTerritorios, corAtual);

            const char* missaoAtual = (turnoJogador == 1) ? missaoJogador1 : missaoJogador2;
            if (verificarMissao(missaoAtual, territorios, quantidadeTerritorios, corAtual)) {
                printf("\nParabéns! O jogador %d cumpriu a missão e venceu o jogo!\n", turnoJogador);
                ganhou = 1;
            } else {
                turnoJogador = (turnoJogador == 1) ? 2 : 1;
            }
        } else if (opcao == 3) {
            printf("Saindo do jogo...\n");
        } else {
            printf("Opção inválida! Tente novamente.\n");
        }
    }

    liberarMemoria(territorios, missaoJogador1, missaoJogador2);
    printf("\nObrigado por jogar!\n");
    return 0;
}
