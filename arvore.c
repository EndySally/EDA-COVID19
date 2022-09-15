#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct Nobin
{
    char key[100];
    struct Nobin * esquerda;
    struct Nobin * direita;
} TnoBin;

void toLower(char* s) {
  for(char *p=s; *p; p++) *p=tolower(*p);
}

TnoBin *alocaNo(){
    TnoBin *arv = (TnoBin*)malloc(sizeof(TnoBin));
    return arv;
}

TnoBin *criaNo(TnoBin *A, char n[100]){
    if (A != NULL)
    {
        if(strcmp(n,A->key) < 0)
            if(A->esquerda == NULL)
                A->esquerda = criaNo(A->esquerda, n);
            else
                criaNo(A->esquerda, n);
        else
            if(A->direita == NULL)
                A->direita = criaNo(A->direita, n);
            else
                criaNo(A->direita, n);
    }
    else{
        A = alocaNo();
        A->esquerda = NULL;
        A->direita = NULL;
        strcpy(A->key, n);
    }
}

TnoBin * criaArvore (TnoBin * A, char n[100]){
    A = alocaNo();
        A->esquerda = NULL;
        A->direita = NULL;
        strcpy(A->key, n);
    return A;
}

int main(){
    TnoBin *arvore = NULL;
    printf("Digite o número de nós: ");
    int num;
    scanf("%d",&num);
    char valorNo[100];
    for (int i = 0; i < num; i++)
    {
        printf("Digite o texto do nó: ");
        scanf(" %[^\n]", valorNo);
        toLower(valorNo);
        if(i == 0)
            arvore = criaArvore(arvore, valorNo);
        else
            criaNo(arvore, valorNo);
    }

    printf("%s\n",arvore->direita->key);    
    return 0;
}