// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//Criação da estrutura para cadastramento dos territórios
typedef struct {
    char nome[30];
    char cor [10];
    int tropas;
} Territorio;

//Declaração das variáveis globais
Territorio *territorios;
int totalTerritorios = 0;

//Função para jogar os dados
int jogarDado() {
    return (rand() % 6) + 1;
}

//Função para exibir o mapa do mundo
void mapaMundo() {
    printf("\n===============================\n");
    printf("      MAPA DO MUNDO ATUAL\n");
    printf("===============================\n\n");

    for (int i=0; i<totalTerritorios; i++) {
        printf("%d - %s (Exército %s, Tropas: %d) \n", i+1, territorios[i].nome, territorios[i].cor, territorios[i].tropas);
    }
}

//Função para o ataque entre os territórios
void atacar(Territorio* atacante, Territorio* defensor){
    int ataque, defesa ;
    int podeAtacar = 0;

    //Loop de ataque
    do{
        printf("\n--- FASE DE ATAQUE ---\n\n");
        printf("Escolha o territorio atacante (1 a %d ou 0 para sair): ", totalTerritorios);
        scanf("%d", &ataque);
        limparBufferEntrada();
            if (ataque == 0) { //Caso o jogador escolha 0, sai do loop de ataque e encerra o jogo
                break;
            } else {
                printf("Escolha o território defensor (1 a %d): ", totalTerritorios);
                scanf("%d", &defesa);
                limparBufferEntrada();
                
                // Verificação das entradas de ataque e defesa
                if (ataque < 1 || ataque > totalTerritorios || defesa < 1 || defesa > totalTerritorios) {
                    printf("Opção inválida! Tente novamente.\n");
                } else if (ataque == defesa) {
                    printf("O território atacante e defensor não podem ser o mesmo! Tente novamente.\n");
                } else if (atacante[ataque - 1].tropas < 2) {
                    printf("O território atacante %s não possui tropas suficientes para atacar! Tente novamente.\n", atacante[ataque - 1].nome);
                } else {

                    //Resultado da batalha e rolagem dos dados
                    printf("\n--- RESULTADO DA BATALHA ---\n");
                    int dadoAtacante = jogarDado();
                    printf("\nO território Atacante %s rolou o dado e tirou: %d", atacante[ataque - 1].nome, dadoAtacante);
                    int dadoDefensor = jogarDado();
                    printf("\nO território Defensor %s rolou o dado e tirou: %d", defensor[defesa - 1].nome, dadoDefensor);

                    //Comparação dos dados e atualização das tropas
                    if (dadoAtacante > dadoDefensor) {
                        defensor[defesa - 1].tropas -= 1;
                        printf("\nATACANTE VENCEU! O território %s perdeu 1 tropa!\n", defensor[defesa - 1].nome);
                    } else if (dadoAtacante == dadoDefensor) {
                        atacante[ataque - 1].tropas -= 1;
                        printf("\nEMPATE! O território %s perdeu 1 tropa!\n", atacante[ataque - 1].nome);
                    } else {
                        atacante[ataque - 1].tropas -= 1;
                        printf("\nDEFENSOR VENCEU! O território %s perdeu 1 tropa!\n", atacante[ataque - 1].nome);
                    }

                    //Verificação se o território defensor foi conquistado
                    if (defensor[defesa - 1].tropas <= 0) {
                        printf("\nCONQUISTA! O território %s foi conquistado pelo exército %s!\n", defensor[defesa - 1].nome, atacante[ataque - 1].cor);
                        defensor[defesa - 1].tropas = 1; // O território conquistado começa com 1 tropa
                        atacante[ataque - 1].tropas -= 1; // O atacante perde 1 tropa ao conquistar
                        strcpy(defensor[defesa - 1].cor, atacante[ataque - 1].cor); // Transferência de cor do território
                    }
                }   

                printf("\nPressione ENTER para continuar...");
                getchar();

                mapaMundo();
            }
            
            //Verificação se algum território tem tropas suficientes para continuar atacando
            podeAtacar = 0;
            for (int i = 0; i < totalTerritorios; i++) {
                    if (territorios[i].tropas >= 2) {
                        podeAtacar = 1;
                        break;
                    }
                }

            if (!podeAtacar) {
                printf("Nenhum território possui tropas suficientes para atacar!\n");
                break;
            }

    } while (ataque != 0);
}

//Função para limpar o buffer de entrada após o "scanf"
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

//Função para liberar a memória alocada
void liberarMemoria(Territorio* mapa) {
    free(mapa);
}

int main () {

    //Declaração das variáveis locais
    int menu, quantidadeTerritorios;

    //Uso do srand para inicializar o gerador de números aleatórios
    srand(time(NULL));


    //Mensagem de boas vindas do jogo
    printf("===== BEM-VINDOS AO JOGO WAR =====\n\n");

    //Loop do menu inicial
    do {
        //Menu inicial do jogo
        printf("O que você deseja fazer?\n");
        printf("1 - Iniciar o jogo\n");
        printf("2 - Sair do jogo\n\n");
        printf("Escolha uma opção: ");
        scanf("%d", &menu);
        limparBufferEntrada();
        if (menu == 2) {
            printf("\nLiberando memória e encerrando o jogo, até a próxima...\n");
            return 0;
        } else if (menu >2 || menu <1) {
            printf("\nOpção inválida! Tente novamente!\n\n");
        } else {

                do{
                    //Cadastramento da quantidade de territórios
                    printf("\nInforme quantos territórios deseja cadastrar: ");
                    scanf("%d", &quantidadeTerritorios);
                    limparBufferEntrada();
                    
                    //Validação da quantidade mínima de territórios
                    if (quantidadeTerritorios <= 1) {
                        printf("\nVocê deve cadastrar no mínimo 2 territórios! Tente novamente.\n");
                    }

                } while (quantidadeTerritorios <= 1);

            //Uso do malloc para alocação dinâmica da struct territorio
            territorios = (Territorio *) malloc (quantidadeTerritorios * sizeof(Territorio));

            //Verificação se a alocação de memória foi bem sucedida
            if (territorios == NULL) {
                printf("Falha na alocação da memória!\n");
                return 1;
            }

            //Cadastramento dos territórios (nome, cor e numero de tropas)
            printf("\nVamos iniciar o cadastramento dos territórios do jogo.\n\n");

            for (int i=0; i<quantidadeTerritorios; i++) {
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
        }
    } while (menu > 2 || menu < 1); //Permanece no menu inicial se a opção for inválida

    printf("Tropas cadastradas com sucesso!\n");
    printf("_______________________________\n\n");

    //Chamada da função mapaMundo
    mapaMundo();

    //Chamada da função atacar
    atacar(territorios, territorios);

    //Liberação da memória alocada dinamicamente
    liberarMemoria(territorios);

    //Mensagem de encerramento do jogo
    printf("Liberando memória e encerrando o jogo, até a próxima...\n\n");

    return 0;
}