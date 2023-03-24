#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<sys/time.h>

struct arv{
	int num;
	struct arv *esq;
	struct arv *dir;
};
typedef struct arv Arvore;

Arvore *inicializar(){
	return NULL;
}
Arvore *inserir(Arvore *raiz, int num){
	if(raiz == NULL){
		Arvore *aux = (Arvore*)malloc(sizeof(Arvore));
		aux->num = num;
		aux->esq = NULL;
		aux->dir = NULL;
		return aux;
	}else{
		if(num < raiz->num){
			raiz->esq = inserir(raiz->esq, num);
		}else if(num>raiz->num){
			raiz->dir = inserir(raiz->dir,num);
		}
	}
	return raiz;
}
int maior_profun(Arvore *raiz){  //	  250 						pilha: dir250,dir200
	if(raiz==NULL){			//   200	   300					pilha: dir300
		return -1;
	}else{
		int esq = maior_profun(raiz->esq); // esq = ?  
		int dir = maior_profun(raiz->dir); // dir = ? 
										   //alt.250 = ?
		if(esq > dir)
			return esq + 1;
		else
			return dir + 1;
	}
}
void menor_profun(Arvore *raiz,int nivel,int *menor){
	if(raiz!=NULL){
		if(raiz->esq==NULL && raiz->dir==NULL) // se a raiz for uma folha  
			{
				if(*menor>nivel) 
					*menor=nivel;
			}
		else{ // se n for folha, nivel recebe +1
			menor_profun(raiz->esq,nivel+1,menor);
			menor_profun(raiz->dir,nivel+1,menor);
		}
	}
}
void liberar(Arvore *raiz){
	if(raiz != NULL){ 
		liberar(raiz->esq); 
		liberar(raiz->dir);
		free(raiz);
	}
}
Arvore* buscar_elemento(Arvore *raiz, int elemento){
	if(raiz){
		if(elemento == raiz->num) // se o elemento for a propria raiz
			return raiz;
		else if(elemento < raiz->num)// se o elemento for menor que a raiz
			return buscar_elemento(raiz->esq, elemento);
		else // se o elemento for maior que a raiz
			return buscar_elemento(raiz->dir, elemento);	
	}
	return NULL;
}
int main(int argc, char *argv[]){
	int i,j,valor,vet[100],elemento=500;
    clock_t t;
	
	for(i=0;i<100;i++) 
		vet[i]=0; // atribui zero em todas as posicoes do vetor, pois ira receber a diferenca max e min de profundidades
		
	srand(time(NULL)); 
		
	for(j=0;j<30;j++){
		Arvore *raiz = inicializar(); // inicializa a arvore com nulo
		
    	t = clock();
		for(i=0;i<1000;i++){ // loop de 1000 insercoes
			if(i%2==0)valor = rand()%50000; // numeros aleatorios
			else valor = rand()%100000;
		
			if(i==888) elemento = valor; // elemento a ser buscado

			raiz = inserir(raiz,valor); // funcao inserir os mil elementos aleatorios
		}
		t = clock()-t;
		printf("Tempo de execucao: %.3f\n", ((double)t)/((CLOCKS_PER_SEC/1000))); //conversão para double
		//Maior profundidade
		int maior;
		maior = maior_profun(raiz);
		printf("\n----------------------------------\n");
		printf("\nMaior nivel de profundidade %d\n",maior);
		// menor profundidade
		int menor = 100;
		menor_profun(raiz,0,&menor);
		printf("\nMenor nivel de profundidade %d\n",menor);
		printf("\n----------------------------------\n");
		if(maior>menor)
			vet[maior - menor] += 1;
		else
			vet[menor - maior] += 1;
		

		t = clock();
		raiz = buscar_elemento(raiz, elemento);
		t = clock()-t;
		printf("Tempo de execucao ao buscar o elemento[%d]: %.5f\n",elemento,((double)t)/((CLOCKS_PER_SEC/1000))); //conversão para double
			
		liberar(raiz);	
	}
	printf("\nDiferenca maxima e minima de profundidade:\n");
	int k=0;
	printf("Num    Quant\n");
	while(k<=30){
		printf(" %d   ->  %d\n",k,vet[k]);
		k++;
	}
	
	return 0;
}

