// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================

#include <stdio.h>
#include <string.h>

// Criação da estrutura para cadastramento dos territórios
typedef struct {
    char nome[30];
    char cor [10];
    int tropas;
} Territorio;

//Função para limpar o buffer de entrada após o "scanf"
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main () {

    Territorio territorios[5];
    int totalTerritorios = 0;

    //Mensagem de boas vindas do jogo
    printf("===== BEM-VINDOS AO JOGO WAR =====\n\n");
    printf("Nesse primeiro momento vamos dar início ao cadastramento dos territórios do jogo.\n\n");

    //Cadastramento dos territórios (nome, cor e numero de tropas)
    for (int i=0; i<5; i++) {
        printf("---- CADASTRANDO TERRITÓRIO %d ----\n", i+1);
        printf("Nome do território: ");
        fgets(territorios[totalTerritorios].nome, 30, stdin);
        
        //Uso da função "strcspn" para remover o a quebra de linha do fgets
        territorios[totalTerritorios].nome[strcspn(territorios[totalTerritorios].nome, "\n")] = '\0';

        printf("Cor do Exército: ");
        fgets(territorios[totalTerritorios].cor, 10, stdin);
        
        //Uso da função "strcspn" para remover o a quebra de linha do fgets
        territorios[totalTerritorios].cor[strcspn(territorios[totalTerritorios].cor, "\n")] = '\0';

        printf("Número de tropas: ");
        scanf ("%d", &territorios[totalTerritorios].tropas);
        limparBufferEntrada();

        totalTerritorios++;
        printf("\n");
    }

    printf("Tropas cadastradas com sucesso!\n");
    printf("_______________________________\n\n");

    //Visualização das tropas cadastradas
    printf("\n===============================\n");
    printf("      MAPA DO MUNDO ATUAL\n");
    printf("===============================\n\n");

    for (int i=0; i<totalTerritorios; i++) {
        printf("TERRITÓRIO %d: \n", i+1);
        printf(" - Nome: %s\n", territorios[i].nome);
        printf(" - Cor do Exército: %s\n", territorios[i].cor);
        printf(" - Tropas: %d\n\n", territorios[i].tropas);

    }
    
    return 0;
}