
#include "process_manager.h"
#include "process_queue.h"
#include "type_process.h"
#include "failure_stack.h"
#include "insertion_queue.h"
#include "execution_functions.h"
#include <stdio.h>
int main(){
     PROCESS_MANAGER pm;
     int ** a;
     a = (int**)malloc(sizeof(int*));
     a = (int**)malloc(sizeof(int*));
     a = (int**)malloc(sizeof(int*));
    initialize_process_manager(&pm);

    read_process_file("initial_processes.txt", &pm);

    PROCESS_QUEUE pq = delete_front(&pm);
    PROCESS p = dequeue(&pq);
 
    return 0;
}