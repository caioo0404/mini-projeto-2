//Código Mini-Projeto 2(incompleto)-Davi Santos de Oliveira Mota e Caio Battisti Nogueira

#include <stdio.h>

//1-Inverte a ordem de todos os caracteres da string
void inverter(char *s) {
    char *fim;
    char temp;

    if(*s == '\0')
    {
        return;
    }

    fim = s;

    while(*fim != '\0')
    {
        fim++;
    }

    fim--;

    while(s < fim) {
        temp = *s;
        *s = *fim;
        *fim = temp;

        s++;
        fim--;
    }
}

//2-Desloca cada letra e número da mensagem n posições
void deslocar(char *s, int n) {
    int i;

    int passos_letra;
    int passos_numero;

    passos_letra = n % 26;
    if(passos_letra < 0)
    {
        passos_letra = passos_letra + 26;
    }

    passos_numero = n % 10;
    if(passos_numero < 0)
    {
        passos_numero = passos_numero + 10;
    }

    while(*s != '\0')
    {
        if(*s >= '0' && *s <= '9')
        {
            for(i = 0; i < passos_numero; i++)
            {
                (*s)++;
                if (*s > '9')
                {
                    *s = '0';
                }
            }
        }
        else if(*s >= 'a' && *s <= 'z')
        {
            for (i = 0; i < passos_letra; i++)
            {
                (*s)++;
                if (*s > 'z')
                {
                    *s = 'a';
                }
            }
        }
        else if(*s >= 'A' && *s <= 'Z') {
            for(i = 0; i < passos_letra; i++)
            {
                (*s)++;
                if(*s > 'Z')
                {
                    *s = 'A';
                }
            }
        }
        s++;
    }
}

//3-Troca os caracteres de posições vizinhas da string
void trocarParesImpares(char *s) {
    char temp;

    while (*s != '\0') {

        if (*(s + 1) != '\0' && *s != '\0')
        {
            temp = *s;
            *s = *(s + 1);
            *(s + 1) = temp;
            s += 2;
        }
        
        else
        {
            break;
        }
    }
}
//4-Transforma todas as letras maiúsculas em minúsculas e todas as letras minúsculas em maiúsculas.Os demais caracteres permanecem inalterados.
void inverterCaixa(char *s){
    int i;

    for(i=0; s[i] != '\0'; i++)
    {
        if(s[i] >= 'a' && s[i] <= 'z')//Caso as letras forem minusculas
        {
            s[i] -= 32;//Converte em letra maiuscula
        }

        else if(s[i] >= 'A' && s[i] <= 'Z')//Caso as letras forem maiuculas
        {
            s[i] += 32;//Converte em letra minuscula
        }
    }
}

//5-Rotaciona todos os caracteres da string n posições.Os caracteres que ultrapassarem uma extremidade devem reaparecer na outra extremidade da string.
void rotacionar(char *s, int n){
    int i, j;
    int tamanho;//Calcula o tamanho da string
    int temp;//variavel temporaria

    tamanho = 0;//Inicializa o tamanho da string em 0
    while(s[tamanho] != '\0')
    {
        tamanho++;
    }

    if (tamanho <= 1)//Caso a string estiver vazia
    {
        return;
    }

    //Verifica o tamanho de n
    n = n % tamanho;
    if (n < 0)
    {
        n = n + tamanho;
    }

    //Rotaciona para a direita n vezes
    for (j = 0; j < n; j++) {
        temp = s[tamanho - 1];//Armazena o ultimo caracter
        
        //Desloca todos uma posicao a direita
        for (i = tamanho - 1; i > 0; i--) {
            s[i] = s[i - 1];
        }
        
        s[0] = temp;
    }

}

//6-Troca a primeira metade da string pela segunda metade.Caso a quantidade de caracteres seja ímpar, o caractere central deve permanecer no centro da mensagem
void trocarMetades(char *s){
    int i;
    int tamanho;//Tamanho da string
    int temp;//variavel temporaria
    int metade;
    int ini2;

    tamanho = 0;
    while(s[tamanho] != '\0')//Calcula o tamanho  da string
    {
        tamanho ++;
    }

    if (tamanho <= 1)//Caso a string esteja vazia
    {
        return;
    }

    metade = tamanho / 2;
    if(tamanho % 2 == 0)//Caso o tamamho da string seja par:troca a primeira metade pela segunda
    {
        ini2 = metade;
    }

    else//Caso for impar o caracter central deve ocupar o centro
    {
        ini2 = metade + 1;
    }

        for(i = 0; i < tamanho / 2; i++)
        {
            temp = s[i];
            s[i] = s[i + ini2];
            s[i + ini2] = temp;
        }

}

int main(void){

    char mensagem[10001];
    int operacao;//Operação escolhida pelo usuario
    int N;

    scanf(" %10000[^\n]", mensagem);//Leitura da mensagem 

    //Enquanto forem enviadas operações validas pelo usuario
    while(scanf("%d", &operacao) == 1 && operacao >= 1 && operacao <= 6)
    {
       if(operacao == 1)//Realizar a operação 1
       {
        inverter( mensagem);
       }

       else if(operacao == 2)//Realizar a operação 2
       {
        scanf("%d", &N);
        deslocar(mensagem, N);
       }

       else if(operacao == 3)//Realizar a operação 3
       {
        trocarParesImpares(mensagem);
       }

       else if(operacao == 4)//Realizar a operação 4
       {
        inverterCaixa(mensagem);
       }

       else if(operacao == 5)//Realizar a operação 5
       {
        scanf("%d", &N);
        rotacionar(mensagem, N);
       }

       else if(operacao == 6)//Realizar a operacao 6
       {
        trocarMetades(mensagem);
       }

    }

    printf("%s\n", mensagem);//Impressão do resultado final
}