#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct Nobin
{
    char key[50];
    int linha;
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

TnoBin *criaNo(TnoBin *A, char n[50], int linha){
    if (A != NULL)
    {
        if(strcmp(n,A->key) < 0)
            if(A->esquerda == NULL)
                A->esquerda = criaNo(A->esquerda, n, linha);
            else
                criaNo(A->esquerda, n, linha);
        else
            if(A->direita == NULL)
                A->direita = criaNo(A->direita, n, linha);
            else
                criaNo(A->direita, n, linha);
    }
    else{
        A = alocaNo();
        A->esquerda = NULL;
        A->direita = NULL;
        strcpy(A->key, n);
        A->linha = linha;
    }
}

TnoBin * criaArvore (TnoBin * A, char n[50], int linha){
    A = alocaNo();
        A->esquerda = NULL;
        A->direita = NULL;
        strcpy(A->key, n);
        A->linha = linha;
    return A;
}

int contaChar(char* s) {
    int contador = 0;
  for(char *p=s; *p; p++) contador++;
  return contador;
}

void retiraAspas(char * a){
    int tamanho = strlen(a);
    int i;
    for ( i = 0; i < tamanho - 2; i++)
    {
        a[i] = a[i + 1];
    }
    a[i] = '\0';
}

int main(){
    FILE * ptr = fopen("amostra.csv","r");
    TnoBin *arvore = NULL;
    int continuar = 1;
    int contador = 0;
    char string[1000];
    char key[50];
    char claim_uid[12],cord_uid[12],title[200],doi[100],numerical_claims[250],publish_time[12],authors[150],journal[100],country[50],institution[100];
    // while(fscanf(ptr,"%[^\n]", string) != EOF)
    // {
    //     // printf("Digite o texto do nó: ");
    //     // scanf(" %[^\n]", valorNo);
    //     // toLower(valorNo);
    //     // if(i == 0)
    //     //     arvore = criaArvore(arvore, valorNo);
    //     // else
    //     //     criaNo(arvore, valorNo);
    //     contador++;
    // }
    while (1)
            {
                if(fscanf(ptr," %[^\n]", string) == EOF){break;}
                contador++;
            }
        fseek(ptr,0, SEEK_SET);
        
        int hash[contador];

        printf("1. Carregar Dados da árvore\n");
        printf("2. Gerar relatório\n");
        printf("3. Sair\n");
        int linha = 0;
        hash[0] = 114;
    
    do
    {
        scanf("%d", &continuar);
        system("clear");
        switch (continuar)
        {
        case 1:
            while (1)
            {
                int tamanho;
                if(fscanf(ptr," %[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]", claim_uid,cord_uid,title,doi,numerical_claims,publish_time,authors,journal,country,institution) == EOF){break;}
                
                if(linha != 0){
                    int n1 = contaChar(claim_uid); 
                    int n2 = contaChar(cord_uid); 
                    int n3 = contaChar(title); 
                    int n4 = contaChar(doi);
                    int n5 = contaChar(numerical_claims); 
                    int n6 = contaChar(publish_time); 
                    int n7 = contaChar(authors); 
                    int n8 = contaChar(journal); 
                    int n9 = contaChar(country);
                    int n10 = contaChar(institution);
                    tamanho = n1+n2+n3+n4+n5+n6+n7+n8+n9+n10+9;
                    hash[linha] = tamanho + 1 + hash[linha - 1];
                    retiraAspas(country);
                    strcat(country, publish_time);
                    strcpy(key,country);
                    if(linha == 1)
                        arvore = criaArvore(arvore, key, linha);
                    else
                        criaNo(arvore, key, linha);
                }
                linha++;
            }
            break;

        case 2:
            break;
        
        case 3:
            break;
        
        default:
            break;
        }
    } while (continuar);
    

    return 0;
}