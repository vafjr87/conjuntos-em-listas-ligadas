//--------------------------------------------------------------
// NOME: Matheus Takao Harada Guerrero, Virgílio Aparecido Fernandes Jr.
//--------------------------------------------------------------

// #include <conio.h>
// #include <malloc.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define true 1
#define false 0

// elemento da lista
typedef struct estr {
	int chave;
	struct estr *prox;
} NO;


// lista
typedef struct {
	NO* inicio;
} LISTA;


typedef int bool;

void inicializar(LISTA* l);
LISTA conjunto(int op, NO* p1, NO *p2);
NO* buscaSeqOrd(int ch, NO* p, NO* *ant);
bool inserirElemListaOrd(int ch , LISTA *l);
void uniao(LISTA* resp, NO* p1, NO* p2);
void interseccao(LISTA* resp, NO* p1, NO* p2);
void imprimir(LISTA *l, char* msg);

void inicializar(LISTA *l) {
	l->inicio = NULL;
}


NO* buscaSeqOrd(int ch, NO* p, NO* *ant) {
  *ant = NULL;
  
  while(p) {
    if(p->chave >= ch)
			break;
			
    *ant = p;
    p = p->prox;
  }
  
  if(p) 
    if(p->chave == ch)
      return(p);
      
  return NULL;
}


bool inserirElemListaOrd(int ch , LISTA *l) {
  NO* novo;
  NO* ant;
  NO* p = l->inicio;
  
  novo = buscaSeqOrd(ch, p, &ant);
  if(novo)
    return false;
  
  novo = (NO*) malloc(sizeof(NO));
  novo->chave = ch;
   
   if(!l->inicio) { // 1a. inserção em lista vazia
     l->inicio = novo;
     novo->prox = NULL;
   } else {
     if(!ant) { // inserção no início da lista
       novo->prox = l->inicio;
       l->inicio = novo;
     } else { // inserção após um nó existente
       novo->prox = ant->prox;
       ant->prox = novo;
     }
   }
   
   return true;
}


void uniao(LISTA* resp, NO* p1, NO* p2) {
	// 1a lista
	while (p1) {
	  inserirElemListaOrd(p1->chave, resp);
	
	  // Pula os nós com chaves repetidas e atribui o próximo não-repetido
	  while ((p1->prox) && (p1->chave == p1->prox->chave))
	    p1 = p1->prox;

    p1 = p1->prox;
	}
	
	// 2a lista
	while(p2){
	  inserirElemListaOrd(p2->chave, resp);
	
	  // Pula os nós com chaves repetidas e atribui o próximo não-repetido
		while ((p2->prox) && (p2->chave == p2->prox->chave))
	    p2 = p2->prox;
    
		p2 = p2->prox;     
	}
}


void interseccao(LISTA* resp, NO* p1, NO* p2) {
  NO* existente;
  NO* ant;
  
  // Percorre a 1a lista verificando se o nó existe na 2a
  // e faz a atribuição em caso afirmativo
  while (p1) {
    existente = buscaSeqOrd(p1->chave, p2, &ant);
    
  	if(existente)
    	inserirElemListaOrd(p1->chave, resp);
  
	  // Pula os nós com chaves repetidas e atribui o próximo não-repetido
    while ((p1->prox) && (p1->chave == p1->prox->chave))
      p1 = p1->prox;
    
    p1 = p1->prox;      
  }
}


void imprimir(LISTA *l, char* msg) {
  
  NO* p = l->inicio;
  
  printf("%s:  \t", msg);

	while(p) {
		printf("%d ", p->chave);
		p = p->prox;
	}
	
	printf("\n");
}


//------------------------------------------
// O EP consiste em implementar esta funcao
//------------------------------------------
LISTA conjunto(int op, NO* p1, NO *p2) {

	LISTA resp;
	resp.inicio = NULL; 
	
	switch(op) {
		case 1:
			uniao(&resp, p1, p2);
			break;
    case 2:
      interseccao(&resp, p1, p2);
      break;      
	}
	
	return resp;
}


LISTA randomList(int size, int max) {
	int key = 1;
	LISTA list;
	list.inicio = (NO*)malloc(sizeof(NO));
	key += rand() % ++max;
	list.inicio->chave = key;
	NO* inte = list.inicio;
	for (; size > 1; size--) {
	  key += rand() % max;
	  inte->prox = (NO*)malloc(sizeof(NO));
	  inte = inte->prox;
	  inte->chave = key;
	
	}
	
	inte->prox = NULL;
	
	return list;
}


//---------------------------------------------------------
// use main() para fazer chamadas de teste ao seu programa
//---------------------------------------------------------
int main() {
	srand(time(NULL));
	int i;
	for (i = 1; i < 10; i++){
	    LISTA a = randomList( 10, i);
	    LISTA b = randomList( 10, i);
	    imprimir(&a, "Lista 1");
	    imprimir(&b, "Lista 2");  
	    LISTA uniao = conjunto(1, a.inicio, b.inicio);
	    LISTA inter = conjunto(2, a.inicio, b.inicio);
	    imprimir(&uniao, "Uniao");
	    imprimir(&inter, "Interseccao");
	}
    
	return 0;
}

// por favor nao inclua nenhum codigo abaixo da funcao main()
