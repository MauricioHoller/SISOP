#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/support.h"
#include "../include/cthread.h"
#include "../include/cdata.h"

PFILA2 fila_apto_alta_prioridade;
PFILA2 fila_apto_media_prioridade;
PFILA2 fila_apto_baixa_prioridade;
PFILA2 fila_bloqueado;

#define ALTA_PRIORIDADE 0
#define MEDIA_PRIORIDADE 1
#define BAIXA_PRIORIDADE 2

int somadortid=1;
int ccreateusado=0;

ucontext_t retContext;//    Contexto de execução que será usado quando uma thread acabar


void inicializalistas(){

    CreateFila2 (fila_apto_alta_prioridade);

    CreateFila2 (fila_apto_baixa_prioridade);

    CreateFila2 (fila_apto_media_prioridade);

    CreateFila2 (fila_bloqueado);

    ccreateusado=1;
}











int ccreate (void* (*start)(void*), void *arg, int prio) {

	if (ccreateusado==1){ //inicializa todas as listas de prioridades.
	inicializalistas();
	}

	printf("CC create iniciado\n\n");


	if(prio<0 || prio>2){
		printf("erro de prioridade");
		return -1;
	}

	ucontext_t contexto_nova_thread;    //  cria variavel com o contexto da tread

	char pilha_thread[SIGSTKSZ]; 	//pilha para a thread em criação  SIGSTKSZ tamanho da pilha ja definido pelo linux

	int t_tid; // numero da tread criada

	//clearTerminatedThread(); 	//se existe thread em estado de término elimina ela da memória ADD

	TCB_t* tcb; //ponteiro do tcb

	tcb = (TCB_t*) malloc(sizeof(TCB_t)); //thread control block

	 if( 0 == getcontext(&contexto_nova_thread)){
	//contexto para o qual o fluxo de execução deve voltar após a
	//finalização da thread

	contexto_nova_thread.uc_link = &retContext;
	//configuração da pilha da nova thread

	contexto_nova_thread.uc_stack.ss_sp = pilha_thread;

	contexto_nova_thread.uc_stack.ss_size = SIGSTKSZ;
	//cria o contexto da nova thread que deve iniciar na função
	//start que receberá um argumento passado em arg, isso será
	//feito usando o stub passado abaixo

	makecontext(&contexto_nova_thread, (void (*) (void)) start, 1,arg);
	//administração do novo tid

	t_tid = somadortid;

	somadortid++;

	printf("Criada thread com tid: %d\n", t_tid);

	tcb->tid = t_tid;

	tcb->state = PROCST_APTO; //verificar com o professor se precisa colocar como estado de criação

	tcb->prio = prio;

	tcb->context = contexto_nova_thread;
		return -1;

    if (prio == ALTA_PRIORIDADE){

    AppendFila2 (fila_apto_alta_prioridade, (void *)tcb);
    }
    if (prio == BAIXA_PRIORIDADE){
    AppendFila2 (fila_apto_baixa_prioridade, (void *) tcb);
    }
    if (prio==MEDIA_PRIORIDADE){
    AppendFila2(fila_apto_media_prioridade,(void *)tcb);
    }

    return tcb->tid;
  		}
	printf("error");
	return -1;
	}


int cyield(void) {
	return -1;
}

int cjoin(int tid) {
	return -1;
}

int csem_init(csem_t *sem, int count) {
	return -1;
}

int cwait(csem_t *sem) {
	return -1;
}

int csignal(csem_t *sem) {
	return -1;
}

int cidentify (char *name, int size) {
	strncpy (name, "Mauricio Holler Guntzel-00273108;.", size);
	return 0;
}


