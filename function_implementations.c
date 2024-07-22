#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function_headers.h"

//Inicializa uma fila
Queue *queue_start(void){
    Queue *process_queue;
    process_queue = (Queue*)malloc(sizeof(Queue));
    process_queue->queue_head = NULL;
    process_queue->queue_end = NULL;
    return process_queue;
}

//Insere um novo elemento na fila 
void queue_insert(Queue *queue, char *process_name, int process_time){
    Process *new_process;
    new_process = (Process*)malloc(sizeof(Process));
    new_process->necessary_time = process_time;
    new_process->process_name = process_name;
    new_process->prox = NULL;

    if (queue->queue_head == NULL){
        queue->queue_head = new_process;
    }
    else{
        queue->queue_end->prox = new_process;
    }
    queue->queue_end = new_process;
}

//Remove elementos da fila
Process *queue_remove(Queue *queue){
    if (queue->queue_head == NULL){
        return NULL;
    }
    
    Process *aux = (Process*)malloc(sizeof(Process));;
    aux = queue->queue_head;
    queue->queue_head = aux->prox;
    return aux;
}

//Distribui cada processo na lista ordenada no respectivo processador
//A lógica utilizada foi de que, pelo vetor estar ordenado, os processos são jogados de acordo com a posição atual do vetor
//processes[i] == Processador[j],  0 < i < num_process e 0 < j < proc_num(numero de processadores) 
void distribuing_process_in_processors(Queue **procs, Process *queue, int num_process, int proc_num){
    int j = 0;
    while (j < num_process){
        for (int i = 0; i < proc_num; i++){
            if (j == num_process){
                break;
            }
            queue_insert(procs[i], queue[j].process_name, queue[j].necessary_time);
            j++;   
        }
    }
        
}

//Organiza os tempos de inicio e fim de cada processo
void setting_times(Queue **procs, int num_procs){
    Process *aux;
    int current_time = 0;
    
    for (int i = 0; i < num_procs; i++){
        aux = procs[i]->queue_head;
        current_time = 0;
        while (aux != NULL){
            aux->initial_time = current_time;
            aux->end_time = current_time + aux->necessary_time;
            current_time += aux->necessary_time;
            aux = aux->prox;
        }
    }
}

//função usada para ordenar o vetor de processos com a função qsort()
int cmpfunc(const void *a, const void *b) {
    Process *processA = (Process *)a;
    Process *processB = (Process *)b;
    return (processA->necessary_time - processB->necessary_time);
}
void show_result(Queue **procs, int proc_num){
    FILE *result;
    result = fopen("result.txt", "w+");

        //Impressão do resultado em um arquivo .txt separado com o nome de result.txt
        for (int proc_indice = 0; proc_indice < proc_num; proc_indice++){
            fprintf(result, "%s %d", "Processador -", proc_indice+1);
            fprintf(result, "\n");    
            while(procs[proc_indice]->queue_head != NULL){
                Process *aux;
                aux = queue_remove(procs[proc_indice]);
                if ( aux != NULL){
                    printf("%s;%d;%d", aux->process_name, aux->initial_time, aux->end_time);
                    fprintf(result, "%s;%d;%d", aux->process_name, aux->initial_time, aux->end_time);
                    fprintf(result, "\n");
                }     
            }
        }
        fclose(result);
}

