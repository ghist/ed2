#include <stdio.h>
#include <stdlib.h>

#define MAX_MEMORY 1024 // tamanho máximo da memória em bytes

typedef struct {
    char status;
    int inicioInicio;
    int finalFinal;
    int inicio;
    int final;
} Informations;

typedef struct Arv23 Arv23; // declaração antecipada do tipo Arv23

struct Arv23 {
    Informations info1, info2;
    int nkeys;
    Arv23 *esquerda;
    Arv23 *centro;
    Arv23 *direita;
    Arv23 *pai;
};

Arv23 *criaNo(Informations info, Arv23 *FE, Arv23 *FC, Arv23 *FD);

int ehfolha(Arv23 *node);

Arv23 *quebraNo(Arv23 **No, Informations info, Informations *sobe, Arv23 *filho);

void adicionaNo(Arv23 **No, Informations info, Arv23 *filho);

Arv23 *insere(Arv23 **Raiz, Informations info, Arv23 **pai);

Arv23 *criaNo(Informations info, Arv23 *FE, Arv23 *FC, Arv23 *FD) {
    Arv23 *No = (Arv23 *) malloc(sizeof(Arv23));
    No->info1 = info;
    No->esquerda = FE;
    No->centro = FC;
    No->direita = FD;
    No->nkeys = 1;
    return No;
}

int ehfolha(Arv23 *node) {
    return (node->esquerda == NULL && node->centro == NULL && node->direita == NULL);
}

Arv23 *quebraNo(Arv23 **No, Informations info, Informations *sobe, Arv23 *filho) {
    Arv23 *NoNoNo = NULL;
    if (info.final < (*No)->info1.inicio) {
        *sobe = (*No)->info1;
        (*No)->info1 = info;
        NoNoNo = criaNo((*No)->info2, (*No)->centro, (*No)->direita, NULL);
        (*No)->centro = filho;
        (*No)->direita = NULL;
        (*No)->nkeys = 1;
    } else if ((*No)->nkeys == 1 || info.final < (*No)->info2.inicio) {
        *sobe = info;
        NoNoNo = criaNo((*No)->info2, filho, (*No)->direita, NULL);
        (*No)->direita = NULL;
        (*No)->nkeys = 1;
    } else {
        *sobe = (*No)->info2;
        NoNoNo = criaNo(info, (*No)->direita, filho, NULL);
        (*No)->direita = NULL;
        (*No)->nkeys = 1;
    }
    return NoNoNo;
}

void adicionaNo(Arv23 **No, Informations info,Arv23 *filho){
	if(info.inicio > (*No)->info1.final){
		(*No)->info2 = info;
		(*No)->direita = filho;
		(*No)->nkeys = 2;
	}else{
		(*No)->info2 = (*No)->info1;
		(*No)->direita = (*No)->centro;
		(*No)->info1 = info;
		(*No)->centro = filho;
		(*No)->nkeys = 2;
	}
}

Arv23 *insere(Arv23 **Raiz, Informations info, Arv23 **pai){
    Arv23 *MaiorNo = NULL;
    Informations sobe;
    if(*Raiz == NULL){
        *Raiz = criaNo(info, NULL, NULL, NULL);
    }else if(ehfolha(*Raiz)){
        if((*Raiz)->nkeys == 1){
            adicionaNo(Raiz, info, NULL);
        }else{
            MaiorNo = quebraNo(Raiz, info, &sobe, NULL);
            if(pai == NULL){
                *Raiz = criaNo(sobe, *Raiz, MaiorNo, NULL);
                MaiorNo = NULL;
            }
        }
    }else{
        if(info.final < (*Raiz)->info1.inicio){
            MaiorNo = insere(&((*Raiz)->esquerda), info, *Raiz);         
        }else if((*Raiz)->nkeys == 1 || info.final < (*Raiz)->info2.inicio){
            MaiorNo = insere(&((*Raiz)->centro),info,*Raiz);
        }else if((*Raiz)->nkeys == 2 && info.inicio > (*Raiz)->info2.final){
            MaiorNo = insere(&((*Raiz)->direita),info,*Raiz);
        }   
    }
    if(MaiorNo == NULL){
        if((*Raiz)->nkeys == 1){
            adicionaNo(Raiz,sobe,MaiorNo);
        }else{
            Informations sobe1;
            MaiorNo=quebraNo(Raiz,sobe,&sobe1,MaiorNo);
            if(pai == NULL){
                *Raiz = criaNo(sobe1,*Raiz,MaiorNo,NULL);
                MaiorNo = NULL;
            }
        }
    }
    return(MaiorNo);
}

int main(){
	Arv23 *node = NULL;
    Informations memory[MAX_MEMORY];
    int i = 0;

    printf("Informe se o primeiro no eh livre (L) ou ocupado (O): ");
    scanf(" %c", &memory[i].status);

    if(memory[i].status == 'L' || memory[i].status == 'O'){
        printf("informe o endereco inicial do no: ");
        scanf("%d", &memory[i].inicio);
        printf("Informe o endereco final do no: ");
        scanf("%d", &memory[i].final);

        memory[i].inicioInicio = memory[i].inicio / 1024;
        memory[i].finalFinal = memory[i].final / 1024;

        node = insere(&node, memory[i], NULL);
    }else{
        printf("Entrada invalida. O primeiro no deve ser livre (L) ou ocupado (O).\n");
        return 0;
    }

    i++;

    while (memory[i - 1].final != MAX_MEMORY - 1) {
        printf("informe o endereco inicial do no: ");
        scanf("%d", &memory[i].inicio);
        printf("Informe o endereco final do no: ");
        scanf("%d", &memory[i].final);

        if (memory[i].inicio == memory[i - 1].final + 1) {
            memory[i].status = (memory[i - 1].status == 'L') ? 'O' : 'L';
        } else {
            printf("Endereco inicial invalido. Deve ser igual ao endereco final do no anterior + 1.\n");
            return 0;
        }

        memory[i].inicioInicio = memory[i].inicio / 1024;
        memory[i].finalFinal = memory[i].final / 1024;

        node = insere(&node, memory[i], NULL);

        i++;
    }

    return 0;
}
