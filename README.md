# Mini Projeto 02 - Central de Comunicações Alienígenas

Disciplina: Introdução à Programação - Ciência da Computação - UFG

## 1. Identificação

- Davi Santos de Oliveira Mota
- Caio Battisti Nogueira

## 2. Instruções de compilação e execução

O programa foi escrito em C, seguindo o padrão C89, e utiliza apenas a biblioteca `stdio.h`.

**Compilação** (no terminal do Ubuntu):

```bash
gcc -std=c89 -Wall -pedantic mp2.c -o mp2
```

**Execução** (digitando a entrada manualmente):

```bash
./mp2
```

**Execução com arquivo de entrada** (redirecionamento):

```bash
./mp2 < teste1.txt
```

### Exemplo de uso

Entrada:

```
Mensagem Secreta 2026!
2 3
1
0
```

Saída:

```
!9535 dwhufhV phjdvqhP
```

## 3. Visão geral do sistema

O programa simula uma central de comunicações que transforma uma mensagem através de uma sequência de operações escolhidas pelo usuário. Cada operação é aplicada sobre o **estado atual** da mensagem, ou seja, o resultado de uma operação é a entrada da próxima.

Não há menus nem mensagens intermediárias, para permitir a correção automática (Sharif e redirecionamento de entrada).

### Operações disponíveis

| Código | Operação | Função |
|---|---|---|
| 1 | Inverter mensagem | `inverter` |
| 2 | Deslocar caracteres (lê um inteiro `n`) | `deslocar` |
| 3 | Trocar pares e ímpares | `trocarParesImpares` |
| 4 | Inverter maiúsculas/minúsculas | `inverterCaixa` |
| 5 | Rotacionar mensagem (lê um inteiro `n`) | `rotacionar` |
| 6 | Trocar metades | `trocarMetades` |
| 0 | Finalizar protocolo | - |

### Fluxo da função `main`

A `main` apenas controla o fluxo, faz as leituras e chama as funções:

1. Lê a primeira linha inteira (até 10.000 caracteres) e guarda no vetor `mensagem`, que tem 10.001 posições (10.000 caracteres + `\0`).
2. Entra em um laço `while` que lê um número inteiro com `scanf`. O laço continua enquanto a leitura for bem-sucedida e o número estiver entre 1 e 6.
3. Dentro do laço, uma estrutura `if / else if` chama a função correspondente à operação lida. Nas operações 2 e 5, a `main` lê também o valor inteiro `n` antes de chamar a função.
4. O laço termina quando o usuário informa `0`, qualquer número que não seja uma operação válida, ou quando a entrada acaba.
5. Imprime a mensagem final seguida de uma quebra de linha (`\n`).

## 4. Decisões de implementação

Todas as funções recebem a mensagem por ponteiro (`char *s`) e modificam a string diretamente. Nenhuma função da biblioteca `string.h` foi utilizada: o tamanho da string é calculado manualmente, percorrendo os caracteres até encontrar `\0`.

### `inverter(char *s)`

Se a string for vazia, a função retorna imediatamente. Caso contrário, usa dois ponteiros: `s` aponta para o início e `fim` é levado até o último caractere. Enquanto `s < fim`, os caracteres apontados são trocados, `s` avança e `fim` recua. Quando os ponteiros se encontram, a string está invertida.

### `deslocar(char *s, int n)`

Percorre a string com o ponteiro. Para cada caractere:

- Se for número (`'0'` a `'9'`), é incrementado `passos_numero` vezes, voltando para `'0'` ao passar de `'9'`.
- Se for letra minúscula, é incrementado `passos_letra` vezes, voltando para `'a'` ao passar de `'z'`.
- Se for letra maiúscula, é incrementado `passos_letra` vezes, voltando para `'A'` ao passar de `'Z'`.
- Qualquer outro caractere permanece inalterado.

**Escolha de projeto:** para evitar repetições desnecessárias quando `n` é muito grande, o valor é reduzido antes do laço: `passos_letra = n % 26` (o alfabeto tem 26 letras) e `passos_numero = n % 10` (existem 10 dígitos). Para `n` negativo, o resto em C também é negativo, então somamos 26 (ou 10) ao resultado. Assim, deslocar `-1` equivale a deslocar `25` nas letras, o que mantém o comportamento circular.

### `trocarParesImpares(char *s)`

Troca a posição 0 com a 1, a 2 com a 3, e assim por diante. O laço só realiza a troca se existirem o caractere atual e o seu vizinho. Se a string tiver quantidade ímpar de caracteres, o último fica sozinho, o laço termina e ele permanece na sua posição.

### `inverterCaixa(char *s)`

Percorre a string e, para cada letra, soma ou subtrai 32, que é a diferença entre as letras minúsculas e maiúsculas na tabela ASCII (`'a'` = 97 e `'A'` = 65). Letras minúsculas viram maiúsculas e vice-versa. Os demais caracteres não são alterados.

### `rotacionar(char *s, int n)`

Calcula o tamanho da string. Se ela tiver 0 ou 1 caractere, nada muda e a função retorna.

**Tratamento de valores positivos e negativos:**

- Valores positivos rotacionam para a **direita**.
- Valores negativos rotacionam para a **esquerda**.

Primeiro, `n = n % tamanho`, pois girar `tamanho` posições retorna à string original. Se o resultado for negativo, somamos `tamanho`: girar `k` posições para a esquerda equivale a girar `tamanho - k` posições para a direita. Assim, o código só precisa implementar a rotação para a direita.

Cada rotação de uma posição guarda o último caractere em `temp`, desloca todos os outros uma posição para a direita e coloca `temp` na posição 0. Isso é repetido `n` vezes.

### `trocarMetades(char *s)`

Calcula o tamanho e a variável `metade = tamanho / 2`. A variável `ini2` indica onde começa a segunda metade:

- Tamanho **par**: `ini2 = metade`.
- Tamanho **ímpar**: `ini2 = metade + 1`, pulando o caractere central, que permanece no meio.

Um único laço de `i = 0` até `metade - 1` troca `s[i]` com `s[i + ini2]`.

Exemplos: `ABCDEF` vira `DEFABC` e `ABCDE` vira `DECAB`.

### Funções auxiliares

Não foram criadas funções auxiliares. O cálculo do tamanho da string, que se repete em `rotacionar` e `trocarMetades`, foi feito diretamente com um laço em cada função.

### Outras escolhas

- Os comentários usam `/* ... */`, pois o C89 não aceita `//`.
- A leitura da mensagem usa `%10000[^\n]` para ler a linha inteira, incluindo espaços, e limitar a leitura a 10.000 caracteres.
- A condição do laço da `main` verifica o retorno do `scanf`, evitando laço infinito caso a entrada termine sem o `0`.
