// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================

//Bibliotecas utilizadas
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//Estrutura para cadastramento dos territórios
typedef struct {
    char nome[30];
    char cor [10];
    int tropas;
} Territorio;

//Protótipos das Funções
void mapaMundo(Territorio *territorios, int totalTerritorios, char *missaoJogador);
int jogarDado();
void limparBufferEntrada();
void atacar(Territorio *territorios, int totalTerritorios, Territorio* atacante, Territorio* defensor, char *missaoJogador);
void liberarMemoria(Territorio* territorios, char *missaoJogador);
void qtdeTerritorios (Territorio *territorios, int *quantidadeTerritorios);
void exibirMenu();
void alocarMemoria (Territorio **territorios, int quantidadeTerritorios);
void cadastrarTerritorios (Territorio *territorios, int *totalTerritorios, int quantidadeTerritorios);
void atribuirMissão (char *destino, const char *missoes[], int totalMissoes);
int verificarMissao(const char *missao, Territorio *territorios, int tamanho);

//Função principal MAIN
int main () {   

    //Declaração das variáveis locais
    int menu, quantidadeTerritorios;
    Territorio *territorios;
    int totalTerritorios = 0;

    //Vetor de missões
    const char *missoes[] = {"Conquistar 2 territórios", "Permanecer com pelo menos 3 tropas", "Eliminar todas as tropas de pelo menos 1 território",
                            "Manter pelo menos 1 território com 5 ou mais tropas", "Não ser dominado"};

    int totalMissoes = sizeof(missoes) / sizeof(missoes[0]); //Calcula o tamanho do vetor
    char *missaoJogador = malloc (100 * sizeof(char));; //Aloca dinamicamente a memória para as missões 

    //Uso do srand para inicializar o gerador de números aleatórios
    srand(time(NULL));

    //Mensagem de boas vindas do jogo
    printf("===== BEM-VINDOS AO JOGO WAR =====\n\n");

    //Loop do menu inicial
    do {

        exibirMenu();
        scanf("%d", &menu);
        limparBufferEntrada();

        //Encerra o jogo se for selecionada a opção 2 do menu
        if (menu == 2) {
            printf("Saindo do jogo, até a próxima!\n");
            return 0;
            break;
            
        } else if (menu == 1) {

            //Permanece no cadastramento da quantidade de territórios se o usuário não informar pelo menos 2 territórios
            do{
                qtdeTerritorios(territorios, &quantidadeTerritorios);

            } while (quantidadeTerritorios <= 1); 

            alocarMemoria(&territorios, quantidadeTerritorios); //Alocação da memória para os territórios

            cadastrarTerritorios(territorios, &totalTerritorios, quantidadeTerritorios);

        } else {
            printf("\nOpção inválida! Pressione 'ENTER' para voltar ao menu principal!\n");
            getchar();
        }

    } while (menu > 2 || menu < 0);

    //Atribuição da missão
    atribuirMissão(missaoJogador, missoes, totalMissoes);

    //Chamada da função atacar
    atacar(territorios, totalTerritorios, territorios, territorios, missaoJogador);

    //Liberação da memória alocada dinamicamente
    liberarMemoria(territorios, missaoJogador);

    return 0;
}


//IMPLEMENTAÇÃO DAS FUNÇÕES

//Função para exibir o menu inicial
void exibirMenu () {
    //Menu inicial do jogo
    printf("O que você deseja fazer?\n");
    printf("1 - Iniciar o jogo\n");
    printf("2 - Sair do jogo\n\n");
    printf("Escolha uma opção: ");
}

//Função para exibir o mapa do mundo
void mapaMundo(Territorio *territorios, int totalTerritorios, char *missaoJogador) {
    printf("\n=============== MAPA DO MUNDO ================\n");

    for (int i=0; i<totalTerritorios; i++) {
        printf("%d - %s (Exército %s, Tropas: %d) \n", i+1, territorios[i].nome, territorios[i].cor, territorios[i].tropas);
    }
    printf("==============================================\n\n");
    printf("Missão: %s\n\n", missaoJogador);
}

//Função para jogar os dados
int jogarDado() {
    return (rand() % 6) + 1;
}

//Função para limpar o buffer de entrada após o "scanf"
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

//Função para sortear e atribuir a missão
void atribuirMissão (char *destino, const char *missoes[], int totalMissoes){
    
    int indice = rand() % totalMissoes;

    strcpy(destino, missoes[indice]);
}

//Função para verificar o cumprimento da missão
int verificarMissao(const char *missao, Territorio *territorios, int tamanho){

    //Missão 1
    if (strcmp(missao, "Conquistar 2 territórios") == 0) {
        int conquistados = 0;
        for (int i=0; i<tamanho; i++) {
            if (strcmp(territorios[i].cor, territorios[0].cor) == 0 && territorios[i].tropas > 0) {
                conquistados++;
            }
        }
        if (conquistados >= 2) {
            return 1;
        }
    }

    //Missão 2
    else if (strcmp(missao, "Permanecer com pelo menos 3 tropas") == 0) {
        for (int i=0; i<tamanho; i++) {
            if (strcmp(territorios[i].cor, territorios[0].cor) == 0 && territorios[i].tropas >= 3) {
                return 1;
            }
        }
    }
    
    //Missao 3
    else if (strcmp(missao, "Eliminar todas as tropas de pelo menos 1 território") == 0) {
        for (int i=0; i<tamanho; i++) {
            if (strcmp(territorios[i].cor, territorios[0].cor) != 0 && territorios[i].tropas == 0) {
                return 1;
            }
        }
    }

    //Missao 4
    else if (strcmp(missao, "Manter pelo menos 1 território com 5 ou mais tropas") == 0) {
        for (int i=0; i<tamanho; i++) {
            if (strcmp(territorios[i].cor, territorios[0].cor) == 0 && territorios[i].tropas >= 5) {
                return 1;
            }
        }
    }

    //Missão 5
    else if (strcmp(missao, "Não ser dominado") == 0){
        for (int i=0; i<tamanho; i++) {
            if (strcmp(territorios[i].cor, territorios[0].cor) == 0 && territorios[i].tropas > 0) {
                return 1;
            }
        }
    }

    return 0;
}

//Função para o ataque entre os territórios
void atacar(Territorio *territorios, int totalTerritorios, Territorio* atacante, Territorio* defensor, char *missaoJogador) {
    
    int ataque, defesa;
    int podeAtacar = 0;
    int menuAtaque;

    //Loop de ataque
    do{

        mapaMundo(territorios, totalTerritorios, missaoJogador);
        
        printf("*** MENU DE ATAQUE ***\n\n");
        printf("O que você deseja fazer? \n");
        printf("1. Atacar\n");
        printf("2. Verificar missão\n");
        printf("0. Sair\n");
        printf("Digite a opção desejada: ");
        scanf("%d", &menuAtaque);
        limparBufferEntrada();

        switch (menuAtaque) {
       
            case 1:

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
                    printf("\nNenhum território possui tropas suficientes para atacar!\n");
                    break;
                }    
                break;
            
            case 2:

                if (verificarMissao(missaoJogador, territorios, totalTerritorios)) {
                    printf("\nParabéns! Missão cumprida!\n");
                    printf("Pressione ENTER para continuar...");
                    getchar();
                    break;
                } else {
                    printf("\nA missão ainda não foi cumprida! Continue tentando.\n");
                    printf("Pressione ENTER para continuar...");
                    getchar();
                    break;
                }
                break;

            case 0:
                break;

            default:
                printf("\nOpção inválida!\n");
                printf("Pressione ENTER para continuar...");
                getchar();
                break;
        }

    } while (ataque != 0 && menuAtaque != 0);
}

//Função para liberar a memória alocada
void liberarMemoria(Territorio* territorios, char *missaoJogador) {
    free(territorios);
    free(missaoJogador);
    printf("Liberando memória e encerrando o jogo, até a próxima...\n\n");
}

//Função para cadastrar a quantidade de territórios para o jogo
void qtdeTerritorios (Territorio *territorios, int *quantidadeTerritorios) {
    //Cadastramento da quantidade de territórios
    printf("\nInforme quantos territórios deseja cadastrar: ");
    scanf("%d", &*quantidadeTerritorios);
    limparBufferEntrada();
                    
    //Validação da quantidade mínima de territórios
    if (*quantidadeTerritorios <= 1) {
        printf("\nVocê deve cadastrar no mínimo 2 territórios! Tente novamente.\n");
    }
}

//Função para cadastrar nome dos territórios, cores e tropas
void cadastrarTerritorios (Territorio *territorios, int *totalTerritorios, int quantidadeTerritorios) {
    //Cadastramento dos territórios (nome, cor e numero de tropas)
    printf("\nVamos iniciar o cadastramento dos territórios do jogo.\n\n");

    for (int i=0; i<quantidadeTerritorios; i++) {
        printf("---- CADASTRANDO TERRITÓRIO %d ----\n", i+1);
        printf("Nome do território: ");
        fgets(territorios[*totalTerritorios].nome, 30, stdin);
        
        //Uso da função "strcspn" para remover o a quebra de linha do fgets
        territorios[*totalTerritorios].nome[strcspn(territorios[*totalTerritorios].nome, "\n")] = '\0';

        printf("Cor do Exército: ");
        fgets(territorios[*totalTerritorios].cor, 10, stdin);
        
        //Uso da função "strcspn" para remover o a quebra de linha do fgets
        territorios[*totalTerritorios].cor[strcspn(territorios[*totalTerritorios].cor, "\n")] = '\0';

        printf("Número de tropas: ");
        scanf ("%d", &territorios[*totalTerritorios].tropas);
        limparBufferEntrada();

        (*totalTerritorios)++;
        printf("\n");
    }

    printf("Tropas cadastradas com sucesso!\n");
    printf("_______________________________\n\n");
}

//Alocação de memória para os territórios
void alocarMemoria (Territorio **territorios, int quantidadeTerritorios) {
    //Uso do malloc para alocação dinâmica da struct territorio
    *territorios = (Territorio *) malloc (quantidadeTerritorios * sizeof(Territorio));

    //Verificação se a alocação de memória foi bem sucedida
    if (*territorios == NULL) {
        printf("Falha na alocação da memória!\n");
        exit (1);
    }
}