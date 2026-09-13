#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*Pedro Lucas Romeiro dos Santos  
RA 10781302*/

#define MAX_AMOSTRAS 100

/* Prototipos - funcoes de calculo nao usam scanf/printf, exceto exibirRelatorio */

/* Preenche as matrizes com 50 registros aleatorios; retorna o total de amostras. */
int inicializarDadosAleatorios(float velocidades[][2],
                                float sensoresFrontais[][3],
                                float sensoresLaterais[][2]);

/* Grava os valores (ja lidos na main) na proxima linha livre. */
void inserirAmostra(float velocidades[][2],
                     float sensoresFrontais[][3],
                     float sensoresLaterais[][2],
                     int indice,
                     float velAtual, float velFrente,
                     float radar, float lidar, float camera,
                     float faixaEsq, float faixaDir);


void calcularFusaoSensores(float sensoresFrontais[][3],
                            float processamento[][2],
                            int numAmostras);


void calcularDistanciaSegura(float velocidades[][2],
                              float processamento[][2],
                              int numAmostras,
                              float atrito,
                              float tempoReacao);


void analisarRiscoFrontal(float velocidades[][2],
                           float processamento[][2],
                           int status[][3],
                           int numAmostras);

void analisarFaixaDinamica(float velocidades[][2],
                            float sensoresLaterais[][2],
                            int status[][3],
                            int numAmostras);


void exibirRelatorio(float velocidades[][2],
                      float sensoresFrontais[][3],
                      float sensoresLaterais[][2],
                      float processamento[][2],
                      int status[][3],
                      int numAmostras);

/* MAIN - unica funcao autorizada a fazer scanf */
int main(void) {

    float velocidades[MAX_AMOSTRAS][2];
    float sensoresFrontais[MAX_AMOSTRAS][3];
    float sensoresLaterais[MAX_AMOSTRAS][2];
    float processamento[MAX_AMOSTRAS][2];
    int   status[MAX_AMOSTRAS][3];

    int numAmostras = 0;
    float atrito;
    int sensibilidade;
    float tempoReacao;
    int opcao;

    srand((unsigned int) time(NULL));

    printf("=== SAFEDRIVE - Simulador de Telemetria ADAS ===\n\n");

    printf("Digite o atrito da via (ex: 0.7): ");
    scanf("%f", &atrito);

    printf("Escolha a sensibilidade do ADAS (1-Esportivo, 2-Normal, 3-Seguro): ");
    scanf("%d", &sensibilidade);

    if (sensibilidade == 1)      tempoReacao = 1.0f;
    else if (sensibilidade == 2) tempoReacao = 1.5f;
    else                          tempoReacao = 2.0f;

    do {
        printf("\n===== MENU SAFEDRIVE =====\n");
        printf("1. Carregar dados iniciais\n");
        printf("2. Inserir nova amostra\n");
        printf("3. Processar e exibir relatorio de riscos\n");
        printf("4. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                numAmostras = inicializarDadosAleatorios(velocidades, sensoresFrontais, sensoresLaterais);
                printf("\nDados iniciais carregados (%d amostras aleatorias).\n", numAmostras);
                break;

            case 2:
                if (numAmostras >= MAX_AMOSTRAS) {
                    printf("\nLimite maximo de %d amostras atingido!\n", MAX_AMOSTRAS);
                } else {
                    float velAtual, velFrente, radar, lidar, camera, faixaEsq, faixaDir;

                    printf("\n--- Nova amostra (indice %d) ---\n", numAmostras);
                    printf("Velocidade atual (km/h): ");
                    scanf("%f", &velAtual);
                    printf("Velocidade do veiculo a frente (km/h): ");
                    scanf("%f", &velFrente);
                    printf("Leitura do radar (m): ");
                    scanf("%f", &radar);
                    printf("Leitura do lidar (m): ");
                    scanf("%f", &lidar);
                    printf("Leitura da camera (m): ");
                    scanf("%f", &camera);
                    printf("Distancia da faixa esquerda (m): ");
                    scanf("%f", &faixaEsq);
                    printf("Distancia da faixa direita (m): ");
                    scanf("%f", &faixaDir);

                    inserirAmostra(velocidades, sensoresFrontais, sensoresLaterais, numAmostras,
                                   velAtual, velFrente, radar, lidar, camera, faixaEsq, faixaDir);
                    numAmostras++;

                    printf("Amostra registrada com sucesso!\n");
                }
                break;

            case 3: {
                if (numAmostras == 0) {
                    printf("\nNenhuma amostra registrada ainda!\n");
                    break;
                }

                calcularFusaoSensores(sensoresFrontais, processamento, numAmostras);
                calcularDistanciaSegura(velocidades, processamento, numAmostras, atrito, tempoReacao);
                analisarRiscoFrontal(velocidades, processamento, status, numAmostras);
                analisarFaixaDinamica(velocidades, sensoresLaterais, status, numAmostras);

               

                exibirRelatorio(velocidades, sensoresFrontais, sensoresLaterais,
                                 processamento, status, numAmostras);

                break;
            }

            case 4:
                printf("Encerrando o simulador...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 4);

    return 0;
}

/* ---------- Implementacoes ---------- */

/* Gera um float aleatorio entre minValor e maxValor. */
float valorAleatorio(float minValor, float maxValor) {
    float fracao = (float) rand() / (float) RAND_MAX;
    return minValor + fracao * (maxValor - minValor);
}

/* Preenche as 50 primeiras linhas de cada matriz com os dados aleatorios. */
int inicializarDadosAleatorios(float velocidades[][2],
                                float sensoresFrontais[][3],
                                float sensoresLaterais[][2]) {

    int i;
    float distanciaBase;

    for (i = 0; i < 50; i++) {

        velocidades[i][0] = valorAleatorio(0.0f, 120.0f);
        velocidades[i][1] = valorAleatorio(0.0f, 120.0f);

        distanciaBase = valorAleatorio(5.0f, 100.0f);
        sensoresFrontais[i][0] = distanciaBase + valorAleatorio(-1.0f, 1.0f);
        sensoresFrontais[i][1] = distanciaBase + valorAleatorio(-1.0f, 1.0f);
        sensoresFrontais[i][2] = distanciaBase + valorAleatorio(-1.0f, 1.0f);

        sensoresLaterais[i][0] = valorAleatorio(0.2f, 1.0f);
        sensoresLaterais[i][1] = valorAleatorio(0.2f, 1.0f);
    }

    return 50;
}


void inserirAmostra(float velocidades[][2],
                     float sensoresFrontais[][3],
                     float sensoresLaterais[][2],
                     int indice,
                     float velAtual, float velFrente,
                     float radar, float lidar, float camera,
                     float faixaEsq, float faixaDir) {

    velocidades[indice][0] = velAtual;
    velocidades[indice][1] = velFrente;

    sensoresFrontais[indice][0] = radar;
    sensoresFrontais[indice][1] = lidar;
    sensoresFrontais[indice][2] = camera;

    sensoresLaterais[indice][0] = faixaEsq;
    sensoresLaterais[indice][1] = faixaDir;
}

/* Regra A */
void calcularFusaoSensores(float sensoresFrontais[][3],
                            float processamento[][2],
                            int numAmostras) {
    int i;
    float radar, lidar, camera, maior, menor, mediana;

    for (i = 0; i < numAmostras; i++) {
        radar  = sensoresFrontais[i][0];
        lidar  = sensoresFrontais[i][1];
        camera = sensoresFrontais[i][2];

        maior = radar;
        if (lidar  > maior) maior = lidar;
        if (camera > maior) maior = camera;

        menor = radar;
        if (lidar  < menor) menor = lidar;
        if (camera < menor) menor = camera;

        mediana = (radar + lidar + camera) - maior - menor;

        processamento[i][0] = mediana;
    }
}

/* Regra B */
void calcularDistanciaSegura(float velocidades[][2],
                              float processamento[][2],
                              int numAmostras,
                              float atrito,
                              float tempoReacao) {
    int i;
    float velKmh, velMs, distancia;

    for (i = 0; i < numAmostras; i++) {
        velKmh = velocidades[i][0];
        velMs  = velKmh / 3.6f;

        distancia = (velMs * tempoReacao) + (velMs * velMs) / (2.0f * atrito * 9.81f);

        processamento[i][1] = distancia;
    }
}

/* Regra C */
void analisarRiscoFrontal(float velocidades[][2],
                           float processamento[][2],
                           int status[][3],
                           int numAmostras) {
    int i;
    float velRelativa, validada, segura, metadeSegura;

    for (i = 0; i < numAmostras; i++) {
        velRelativa = velocidades[i][0] - velocidades[i][1];

        if (velRelativa <= 0.0f) {
            status[i][0] = 0;
        } else {
            validada = processamento[i][0];
            segura   = processamento[i][1];
            metadeSegura = segura * 0.5f;

            if (validada >= segura) {
                status[i][0] = 0;
            } else if (validada >= metadeSegura) {
                status[i][0] = 1;
            } else {
                status[i][0] = 2;
            }
        }
    }
}

/* Regra D  */
void analisarFaixaDinamica(float velocidades[][2],
                            float sensoresLaterais[][2],
                            int status[][3],
                            int numAmostras) {
    int i;
    float velAtual, margemBase, margemDinamica, zonaAtencao, limiteAtencao;
    float leituraEsq, leituraDir;

    margemBase  = 0.50f;
    zonaAtencao = 0.20f;

    for (i = 0; i < numAmostras; i++) {
        velAtual = velocidades[i][0];

        margemDinamica = margemBase;
        if (velAtual > 80.0f) {
            margemDinamica += (velAtual - 80.0f) * 0.01f;
        }

        limiteAtencao = margemDinamica + zonaAtencao;

        leituraEsq = sensoresLaterais[i][0];
        leituraDir = sensoresLaterais[i][1];

        /* Faixa esquerda */
        if (leituraEsq < margemDinamica) {
            status[i][1] = 2;
        } else if (leituraEsq < limiteAtencao) {
            status[i][1] = 1;
        } else {
            status[i][1] = 0;
        }

        /* Faixa direita */
        if (leituraDir < margemDinamica) {
            status[i][2] = 2;
        } else if (leituraDir < limiteAtencao) {
            status[i][2] = 1;
        } else {
            status[i][2] = 0;
        }
    }
}

/* Regra E  */
void exibirRelatorio(float velocidades[][2],
                      float sensoresFrontais[][3],
                      float sensoresLaterais[][2],
                      float processamento[][2],
                      int status[][3],
                      int numAmostras) {
    int i;
    const char *statusFrontalTexto;
    const char *statusEsqTexto;
    const char *statusDirTexto;

    printf("\n============================================================\n");
    printf("         RELATORIO SAFEDRIVE - ANALISE DE TELEMETRIA\n");
    printf("============================================================\n");

    for (i = 0; i < numAmostras; i++) {

        printf("\n\n------------------------------------------------------------\n");
        printf(" AMOSTRA %d\n", i);
        printf("------------------------------------------------------------\n\n");

        /* Dados de entrada */
        printf("  [ DADOS DE ENTRADA ]\n\n");
        printf("  %-24s %.2f km/h\n\n", "Velocidade atual:", velocidades[i][0]);
        printf("  %-24s %.2f km/h\n\n", "Veiculo a frente:", velocidades[i][1]);
        printf("  %-24s %.2f m\n\n",    "Radar:", sensoresFrontais[i][0]);
        printf("  %-24s %.2f m\n\n",    "Lidar:", sensoresFrontais[i][1]);
        printf("  %-24s %.2f m\n\n",    "Camera:", sensoresFrontais[i][2]);
        printf("  %-24s %.2f m\n\n",    "Faixa esquerda:", sensoresLaterais[i][0]);
        printf("  %-24s %.2f m\n\n",    "Faixa direita:", sensoresLaterais[i][1]);

        /* Dados processados */
        printf("  [ DADOS PROCESSADOS ]\n\n");
        printf("  %-24s %.2f m\n\n", "Distancia validada:", processamento[i][0]);
        printf("  %-24s %.2f m\n\n", "Distancia segura:", processamento[i][1]);

        if (status[i][0] == 0)      statusFrontalTexto = "SEGURO";
        else if (status[i][0] == 1) statusFrontalTexto = "ATENCAO";
        else                          statusFrontalTexto = "RISCO DE COLISAO (AEB ACIONADO)";

        if (status[i][1] == 0)      statusEsqTexto = "NORMAL";
        else if (status[i][1] == 1) statusEsqTexto = "ATENCAO";
        else                          statusEsqTexto = "PERIGO DE INVASAO";

        if (status[i][2] == 0)      statusDirTexto = "NORMAL";
        else if (status[i][2] == 1) statusDirTexto = "ATENCAO";
        else                          statusDirTexto = "PERIGO DE INVASAO";

        /* Traducao de status */
        printf("  [ STATUS ]\n\n");
        printf("  %-24s %s\n\n", "Status frontal:", statusFrontalTexto);
        printf("  %-24s %s\n\n", "Faixa esquerda:", statusEsqTexto);
        printf("  %-24s %s\n\n", "Faixa direita:", statusDirTexto);

        /* Decisao geral */
        if (status[i][0] == 2 || status[i][1] == 2 || status[i][2] == 2) {
            printf("  >>> STATUS GERAL: INTERVENCAO CRITICA EXIGIDA <<<\n");
        } else if (status[i][0] == 1 || status[i][1] == 1 || status[i][2] == 1) {
            printf("  >>> STATUS GERAL: ATENCAO <<<\n");
        } else {
            printf("  >>> STATUS GERAL: NORMAL <<<\n");
        }
    }

    printf("\n\n============================================================\n");
}
