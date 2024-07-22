
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function_headers.h"

#define MAX_NAME_SIZE 3
#define MAX_TIME_SIZE 3

int main(int argc, char **argv){
    //Inicialização de variáveis
    FILE *tasks;
    int proc_num = atoi(argv[2]);
    int num_process = 0;
    int i = 0, j = 0;
    char buffer_name, buffer_time; 

    tasks = fopen("tarefas.txt", "r");//abre o arquivo de tarefas

    Queue *queue;
    queue = queue_start();//inicializa a fila principal


    //Loop de inserção de processos na fila principal
    while (!feof(tasks)){

        char *actual_process = (char*)malloc(sizeof(char)*MAX_NAME_SIZE);
        buffer_name = fgetc(tasks);
        while (buffer_name != ' '){
            actual_process[i] = buffer_name;
            i++;
            buffer_name = fgetc(tasks);
        }
        actual_process[i] = '\0';
        i = 0;
        //actual_process[i] = buffer_name;
        buffer_time = fgetc(tasks);
        if (buffer_time == '\n' || buffer_time == ' '){
            buffer_time = fgetc(tasks);
        }
        char *actual_process_value = (char*)malloc(sizeof(char)*MAX_TIME_SIZE);
        while (buffer_time != '\n' && buffer_time != EOF){
            actual_process_value[j] = buffer_time;
            j++;
            buffer_time = fgetc(tasks);
        }
        j = 0;
        queue_insert(queue, actual_process, atoi(actual_process_value));
        num_process++;
    }
    //Inicializa um vetor em que cada posição dele é um processo da fila(basicamente transformo a fila em uma lista encadeada para para ordenação)
    Process *processes = (Process *)malloc(num_process * sizeof(Process)); //lista com todos os processos pra ordenar
    for (int i = 0; i < num_process; i++){
        Process *aux = queue_remove(queue);
        if (aux == NULL)
        {
            break;
        }
        processes[i] = *aux;
        processes[i].prox = NULL; 
    }
    //Ordena o vetor de processos
    //void qsort(void *base, size_t nitems, size_t size, int (*compar)(const void *, const void*))
    qsort(processes, num_process, sizeof(Process), cmpfunc);

    fclose(tasks);
    
    free(queue);

    //inicializa um vetor com diferentes filas, sendo cada uma indicada a um dos processadores
    Queue **procs = (Queue**)malloc(sizeof(Queue*) * proc_num);
    for (int proc_indice = 0; proc_indice < proc_num; proc_indice++){
        procs[proc_indice] = queue_start();
    }

    //distribui todos os processos, que estão no vetor de processos ordenado, em diferentes filas do vetor de processadores
    distribuing_process_in_processors(procs, processes, num_process, proc_num);
    
    free(processes);

    //organiza os tempos de inicio e fim de cada processo
    setting_times(procs, proc_num);

    //imprime todos os processos de cada processador 
    show_result(procs, proc_num);
    
    
}   