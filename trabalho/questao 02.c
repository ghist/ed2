#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct no{
	int num,altura;
	struct no *esquerdo, *direito;
}No;

No* novoNo(int num){		
	No *aux = (No*)malloc(sizeof(No));
	
	if(aux){
		aux->num = num;
		aux->esquerdo = NULL;
		aux->direito = NULL;
		aux->altura = 0;
		return aux;
	}else
		printf("\nErro ao alocar no aux!\n");
	return aux;
}
int maior(int a, int b){
	if(a>b)
		return a;
	else
		return b;
}
int alturaDoNo(No *no){// retorna altura de um nó
	if(no == NULL)
		return -1;
	else
		return no->altura;
}
int fatorDeBalanceamento(No *no){// calcula e retorna o fator de balanceamento de um nó
	if(no)
		return (alturaDoNo(no->esquerdo) - alturaDoNo(no->direito));
	else
		return 0;
}
No* rotacaoEsquerda(No *r){
	No *y,*f;
	
	y = r->direito;
	f = y->esquerdo;
	
	y->esquerdo = r;
	r->direito = f;
	
	r->altura = maior(alturaDoNo(r->esquerdo),alturaDoNo(r->direito)) + 1;
	y->altura = maior(alturaDoNo(y->esquerdo),alturaDoNo(y->direito)) + 1;
	
	return y;		
}
No* rotacaoDireita(No *r){
	No *y,*f;
	
	y = r->esquerdo;
	f = y->direito;
	
	y->direito = r;
	r->esquerdo = f;
	
	r->altura = maior(alturaDoNo(r->esquerdo),alturaDoNo(r->direito)) + 1;
	y->altura = maior(alturaDoNo(y->esquerdo),alturaDoNo(y->direito)) + 1;
	
	return y;
}
No* rotacaoDireitaEsquerda(No *r){
	r->direito = rotacaoDireita(r->direito);
	return rotacaoEsquerda(r);
}
No* rotacaoEsquerdaDireita(No *r){
	r->esquerdo = rotacaoEsquerda(r->esquerdo);
	return rotacaoDireita(r);
}
/*
	Funcao para realizar o balanceamento da arvore apos uma insercao ou remocao
	recebe o nó que esta desbalanceado e retorna a nova raiz apos o balanceamento
*/
No* balancear(No *raiz){
	int fb = fatorDeBalanceamento(raiz);
	
	// rotacao a esquerda
	if(fb < -1 && fatorDeBalanceamento(raiz->direito) <= 0)
		raiz = rotacaoEsquerda(raiz);
	
	// rotacao a direita
	else if(fb > 1 && fatorDeBalanceamento(raiz->esquerdo) >= 0)
		raiz = rotacaoDireita(raiz);
	
	// rotacao dupla a esquerda
	else if(fb > 1 && fatorDeBalanceamento(raiz->esquerdo) < 0)
		raiz = rotacaoEsquerdaDireita(raiz);
	
	// rotacao a dupla a direita
	else if(fb < -1 && fatorDeBalanceamento(raiz->direito) > 0)
		raiz = rotacaoDireitaEsquerda(raiz);
	return raiz;
}
No* inserir(No *raiz, int x){
	if(raiz == NULL) // arvore vazia
		return novoNo(x);
	else{ // insercao será a esquerda ou a direita
		if(x < raiz->num)
			raiz->esquerdo = inserir(raiz->esquerdo,x);
		else if(x > raiz->num)
			raiz->direito = inserir(raiz->direito,x);
	}
	// recalcula a altura de todos os nos entre a raiz e o novo nó inserido
	raiz->altura = maior(alturaDoNo(raiz->esquerdo), alturaDoNo(raiz->direito)) + 1;
	
	// verifica a necessidade de rebalancear a arvore
	raiz = balancear(raiz);
	
	return raiz;
}
void maior_profun(No *raiz, int nivel,int *maior){
	int i;
	if(raiz){
		if(*maior<raiz->altura)
			*maior=raiz->altura;
		
		maior_profun(raiz->direito, nivel + 1,maior);
	
	 	maior_profun(raiz->esquerdo,nivel + 1,maior);
	 		
	}
}
void menor_profun(No *raiz,int nivel,int *menor){
	if(raiz!=NULL){
		if(raiz->esquerdo==NULL && raiz->direito==NULL)
			{
				if(*menor>nivel)
					*menor=nivel;
			}
		else{
			menor_profun(raiz->esquerdo,nivel+1,menor);
			menor_profun(raiz->direito,nivel+1,menor);
		}
	}
}
int arv_vazia (No* raiz){
 	return raiz==NULL;
}
No* liberar (No* raiz){
	 if (!arv_vazia(raiz)){
		 liberar(raiz->esquerdo); 
		 liberar(raiz->direito); 
		 free(raiz); /* libera raiz */
	 }
 return NULL;
}
No *buscar_elemento(No *raiz, int elemento){
	if(raiz){
		if(elemento == raiz->num)
	       return raiz; //achou		
		else if(elemento < raiz->num)
	 		return buscar_elemento(raiz->esquerdo, elemento);
		else
			return buscar_elemento(raiz->direito, elemento);	
	}
	return NULL;
}
int main(){
	int i,j,valor,vet[100],elemento=1;
	No *raiz = NULL;
	clock_t t;
	
	for(i=0;i<100;i++)
		vet[i]=0;
		
	srand(time(NULL));
	
	for(j=0;j<30;j++){
	
    	t = clock();
		for(i=1;i<1000;i++){
			if(i%2==0)
				valor = rand()%50000;
			else
				valor = rand()%100000;
			
			if(i==888) valor = elemento;
			
			raiz = inserir(raiz,valor);
		}
		t = clock()-t;
		printf("\nTempo de execucao: %.3f milissegundos\n", ((double)t)/((CLOCKS_PER_SEC/1000))); //conversão para double
		printf("\n-------------------------------------------------------------------------------------\n");
		int maior=0,menor=1000;
		// maior profundidade
		maior_profun(raiz,1,&maior);
		// menor profundidade
		menor_profun(raiz,0,&menor);
		printf("\nMaior Profunidadade: %d\nMenor Profunidadade: %d\n",maior,menor);

		if(maior>menor)
			vet[maior - menor] += 1;
		else
			vet[menor - maior] += 1;
		printf("\n-------------------------------------------------------------------------------------\n");
		t = clock();
    	raiz = buscar_elemento(raiz, elemento);
    	t = clock()-t;
    	printf("Tempo de execucao ao buscar o elemento [%d]: %.3f",elemento,((double)t)/((CLOCKS_PER_SEC/1000))); //conversão para double
	    printf("\n-------------------------------------------------------------------------------------\n");

		//libera raiz
		raiz = liberar(raiz);
	}
	printf("\nDiferenca entre as profundidades:\n");
	int k=0;
	printf("Num    Quant\n");
	while(k<=30){
		printf(" %d   ->  %d\n",k,vet[k]);
		k++;
	}
	return 0;
}
