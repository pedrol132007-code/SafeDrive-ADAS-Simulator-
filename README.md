# SafeDrive-ADAS-Simulator-
Simulador de telemetria ADAS desenvolvido em C, com fusão de sensores, análise de risco de colisão e monitoramento dinâmico de faixas.

# SafeDrive ADAS Simulator 🚗

Simulador de telemetria veicular desenvolvido em **C**, com foco em conceitos de sistemas **ADAS (Advanced Driver Assistance Systems)**.

O projeto simula dados provenientes de diferentes sensores do veículo e utiliza esses dados para realizar fusão de sensores, calcular uma distância segura de frenagem e identificar situações de risco frontal e de invasão de faixa.

---

## 📌 Sobre o projeto

O **SafeDrive** foi desenvolvido como um simulador de análise de telemetria para representar, de forma simplificada, algumas funcionalidades presentes em sistemas modernos de assistência ao motorista.

O programa trabalha com informações como:

* Velocidade atual do veículo;
* Velocidade do veículo à frente;
* Distâncias obtidas por radar, LiDAR e câmera;
* Distâncias em relação às faixas laterais;
* Atrito da pista;
* Tempo de reação configurado pelo nível de sensibilidade.

A partir desses dados, o sistema processa cada amostra e apresenta um relatório contendo os níveis de risco identificados.

---

## ⚙️ Funcionalidades

### 🔹 Fusão de sensores

O sistema recebe três leituras frontais:

* Radar
* LiDAR
* Câmera

Para obter uma distância validada, o programa utiliza a **mediana das três leituras**, reduzindo a influência de valores extremos.

### 🔹 Cálculo da distância segura

A distância segura é calculada considerando:

* velocidade atual do veículo;
* tempo de reação;
* atrito da via;
* aceleração da gravidade.

A velocidade é convertida de km/h para m/s antes do cálculo.

### 🔹 Análise de risco frontal

O programa compara a distância validada pelos sensores com a distância segura.

Os possíveis estados são:

* **SEGURO**
* **ATENÇÃO**
* **RISCO DE COLISÃO**

Em situações classificadas como risco de colisão, o relatório indica o acionamento do sistema **AEB (Automatic Emergency Braking)**.

### 🔹 Monitoramento dinâmico de faixa

O sistema monitora as distâncias do veículo em relação às faixas esquerda e direita.

A margem considerada segura varia de acordo com a velocidade do veículo, permitindo uma análise dinâmica.

Os estados possíveis são:

* **NORMAL**
* **ATENÇÃO**
* **PERIGO DE INVASÃO**

### 🔹 Geração de dados

O programa pode gerar automaticamente **50 amostras aleatórias** para simulação.

Também é possível inserir novas amostras manualmente pelo menu.

O sistema suporta até **100 amostras**.

---

## 🧠 Regras implementadas

O projeto é dividido em etapas de processamento:

| Regra   | Função                                      |
| ------- | ------------------------------------------- |
| Regra A | Fusão das leituras do radar, LiDAR e câmera |
| Regra B | Cálculo da distância segura                 |
| Regra C | Análise do risco frontal                    |
| Regra D | Análise dinâmica das faixas                 |
| Regra E | Geração do relatório final                  |

---

## 🛠️ Tecnologias utilizadas

* **C**
* `stdio.h`
* `stdlib.h`
* `time.h`

O projeto utiliza principalmente:

* funções;
* matrizes;
* estruturas de repetição;
* estruturas condicionais;
* geração de números aleatórios;
* modularização do código;
* processamento de dados.

---

## 📂 Estrutura do projeto

```text
SafeDrive-ADAS-Simulator/
│
├── src/
│   └── safedrive.c
│
├── README.md
├── .gitignore
└── LICENSE
```

---

## ▶️ Como executar

### 1. Clone o repositório

```bash
git clone https://github.com/SEU-USUARIO/SafeDrive-ADAS-Simulator.git
```

### 2. Entre na pasta

```bash
cd SafeDrive-ADAS-Simulator
```

### 3. Compile o programa

Utilizando GCC:

```bash
gcc src/safedrive.c -o safedrive
```

### 4. Execute

No Windows:

```bash
safedrive.exe
```

No Linux/macOS:

```bash
./safedrive
```

---

## 🖥️ Funcionamento

Ao iniciar, o programa solicita:

```text
=== SAFEDRIVE - Simulador de Telemetria ADAS ===

Digite o atrito da via:
Escolha a sensibilidade do ADAS:
```

A sensibilidade define o tempo de reação utilizado pelo sistema:

| Sensibilidade | Tempo de reação |
| ------------- | --------------: |
| Esportivo     |           1,0 s |
| Normal        |           1,5 s |
| Seguro        |           2,0 s |

Depois disso, o usuário pode acessar o menu principal:

```text
===== MENU SAFEDRIVE =====

1. Carregar dados iniciais
2. Inserir nova amostra
3. Processar e exibir relatorio de riscos
4. Sair
```

---

## 📊 Relatório

Para cada amostra processada, o sistema apresenta:

### Dados de entrada

* Velocidade atual;
* Velocidade do veículo à frente;
* Radar;
* LiDAR;
* Câmera;
* Faixa esquerda;
* Faixa direita.

### Dados processados

* Distância validada;
* Distância segura.

### Status

* Status frontal;
* Status da faixa esquerda;
* Status da faixa direita;
* Status geral da situação.

O programa classifica o status geral como:

```text
STATUS GERAL: NORMAL
STATUS GERAL: ATENÇÃO
STATUS GERAL: INTERVENÇÃO CRÍTICA EXIGIDA
```

---

## 🎯 Objetivos acadêmicos

Este projeto foi desenvolvido para praticar conceitos fundamentais de programação em **C**, principalmente:

* declaração e manipulação de matrizes;
* criação e utilização de funções;
* passagem de parâmetros;
* estruturas condicionais;
* estruturas de repetição;
* modularização;
* processamento de dados;
* simulação de situações reais através de programação.

---

## 🚀 Possíveis melhorias

Algumas evoluções possíveis para o projeto:

* Separação das funções em arquivos `.c` e `.h`;
* Inclusão de registro histórico das amostras;
* Exportação dos dados para arquivos CSV;
* Interface gráfica;
* Visualização dos dados em gráficos;
* Simulação em tempo real;
* Inclusão de novos sensores;
* Implementação de diferentes cenários de direção.

---

## 👨‍💻 Autor

**Pedro Lucas Romeiro dos Santos**

Projeto acadêmico desenvolvido em linguagem C.

---

## 📄 Licença

Este projeto está disponível para fins acadêmicos e educacionais.
