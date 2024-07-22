//definição de estruturas usadas
struct Process{
    char *process_name;
    int initial_time;
    int end_time;
    int necessary_time;
    struct Process *prox;
};

typedef struct Process Process;

typedef struct{
    struct Process *queue_head;
    struct Process *queue_end;
}Queue;


Queue *queue_start(void);
void queue_insert(Queue *queue, char *process_name, int process_time);
Process *queue_remove(Queue *queue);
void distribuing_process_in_processors(Queue **procs, Process *queue, int num_process, int proc_num);
void setting_times(Queue **procs, int num_procs);
int cmpfunc(const void *a, const void *b);
void show_result(Queue **procs, int proc_num);