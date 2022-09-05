#include <stdio.h>
#include <stdlib.h>

struct Node{
 char num[20];
 struct Node *prox;
}; 
typedef struct Node nodeList;

int tam;

void inicia(nodeList *LISTA);
int menu(void);
void opcao(nodeList *LISTA, int op);
nodeList *criaNo();
void insereFim(nodeList *LISTA);
void insereInicio(nodeList *LISTA);
void exibe(nodeList *LISTA);
void libera(nodeList *LISTA);
void insere (nodeList *LISTA);
nodeList *retiraInicio(nodeList *LISTA);
nodeList *retiraFim(nodeList *LISTA);
nodeList *retira(nodeList *LISTA);


int main(void)
{
 nodeList *LISTA = (nodeList *) malloc(sizeof(nodeList));
 if(!LISTA){
  printf("Sem memoria disponivel!\n");
  exit(1);
 }else{
 inicia(LISTA);
 printf("LISTA");
 int opt;
 
 do{
  opt=menu();
  opcao(LISTA,opt);
 }while(opt);

 free(LISTA);
 return 0;
 }
}

void inicia(nodeList *LISTA)
{
 LISTA->prox = NULL;
 tam=0;
}

int menu(void)
{
 int opt;
 
 printf("Escolha a opcao\n");
 printf("0. Sair\n");
 printf("1. Zerar lista\n");
 printf("2. Exibir lista\n");
 printf("3. Adicionar elemento no inicio\n");
 printf("4. Adicionar elemento no final\n");
 printf("5. Escolher onde inserir\n");
 printf("6. Retirar do inicio\n");
 printf("7. Retirar do fim\n");
 printf("8. Escolher de onde tirar\n");
 printf("Opcao: "); scanf("%d", &opt);
 
 return opt;
}

void opcao(nodeList *LISTA, int op){
 nodeList *tmp;
 switch(op){
  case 0:
   libera(LISTA);
   break;
   
  case 1:
   libera(LISTA);
   inicia(LISTA);
   break;
  
  case 2:
   exibe(LISTA);
   break;
  
  case 3:
   insereInicio(LISTA);
   break;  
   
  case 4:
   insereFim(LISTA);
   break;
   
  case 5:
   insere(LISTA);
   break;
  
  case 6:
   tmp= retiraInicio(LISTA);
   printf("Retirado: %3d\n\n", tmp->num);
   break;
   
  case 7:
   tmp= retiraFim(LISTA);
   printf("Retirado: %3d\n\n", tmp->num);
   break;
  
  case 8:
   tmp= retira(LISTA);
   printf("Retirado: %3d\n\n", tmp->num);
   break;
  
  default:
   printf("Comando invalido\n\n");
 }
}

int vazia(nodeList *LISTA)
{
 if(LISTA->prox == NULL)
  return 1;
 else
  return 0;
}

nodeList *aloca()
{
 nodeList *novo=(nodeList *) malloc(sizeof(nodeList));
 if(!novo){
  printf("Sem memoria disponivel!\n");
  exit(1);
 }else{
  printf("Novo elemento: "); scanf("%s", &novo->num);
  return novo;
 }
}


void insereFim(nodeList *LISTA)
{
 nodeList *novo=aloca();
 novo->prox = NULL;
 
 if(vazia(LISTA))
  LISTA->prox=novo;
 else{
  nodeList *tmp = LISTA->prox;
  
  while(tmp->prox != NULL)
   tmp = tmp->prox;
  
  tmp->prox = novo;
 }
 tam++;
}

void insereInicio(nodeList *LISTA)
{
 nodeList *novo=aloca(); 
 nodeList *oldHead = LISTA->prox;
 
 LISTA->prox = novo;
 novo->prox = oldHead;
 
 tam++;
}

void exibe(nodeList *LISTA)
{
 system("clear");
 if(vazia(LISTA)){
  printf("Lista vazia!\n\n");
  return ;
 }
 
 nodeList *tmp;
 tmp = LISTA->prox;
 printf("Lista:");
 while( tmp != NULL){
  printf("%5s",tmp->num);

  tmp = tmp->prox;
 }
 printf("\n        ");
 int count;
 for(count=0 ; count < tam ; count++)
  printf("  ^  ");
 printf("\nOrdem:");
 for(count=0 ; count < tam ; count++)
  printf("%5d", count+1);
 
  
 printf("\n\n");
}

void libera(nodeList *LISTA){
 if(!vazia(LISTA)){
  nodeList *proxNode,
     *atual;
  
  atual = LISTA->prox;
  while(atual != NULL){
   proxNode = atual->prox;
   free(atual);
   atual = proxNode;
  }
 }
}

void insere(nodeList *LISTA)
{
 int pos,
  count;
 printf("Em que posicao, [de 1 ate %d] voce deseja inserir: ", tam);
 scanf("%d", &pos);
 
 if(pos>0 && pos <= tam){
  if(pos==1)
   insereInicio(LISTA);
  else{
   nodeList *atual = LISTA->prox,
     *anterior=LISTA; 
   nodeList *novo=aloca();
     
   for(count=1 ; count < pos ; count++){
     anterior=atual;
     atual=atual->prox;
   }
   anterior->prox=novo;
   novo->prox = atual;
   tam++;
  }
   
 }else
  printf("Elemento invalido\n\n");  
}

nodeList *retiraInicio(nodeList *LISTA)
{
 if(LISTA->prox == NULL){
  printf("Lista ja esta vazia\n");
  return NULL;
 }else{
  nodeList *tmp = LISTA->prox;
  LISTA->prox = tmp->prox;
  tam--;
  return tmp;
 }
    
}

nodeList *retiraFim(nodeList *LISTA)
{
 if(LISTA->prox == NULL){
  printf("Lista ja vazia\n\n");
  return NULL;
 }else{
  nodeList *ultimo = LISTA->prox,
    *penultimo = LISTA;
    
  while(ultimo->prox != NULL){
   penultimo = ultimo;
   ultimo = ultimo->prox;
  }
    
  penultimo->prox = NULL;
  tam--;
  return ultimo;  
 }
}

nodeList *retira(nodeList *LISTA)
{
 int opt,
  count;
 printf("Que posicao, [de 1 ate %d] voce deseja retirar: ", tam);
 scanf("%d", &opt);
 
 if(opt>0 && opt <= tam){
  if(opt==1)
   return retiraInicio(LISTA);
  else{
   nodeList *atual = LISTA->prox,
     *anterior=LISTA; 
     
   for(count=1 ; count < opt ; count++){
    anterior=atual;
    atual=atual->prox;
   }
   
  anterior->prox=atual->prox;
  tam--;
  return atual;
  }
   
 }else{
  printf("Elemento invalido\n\n");
  return NULL;
 }
}