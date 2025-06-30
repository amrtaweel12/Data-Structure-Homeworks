#include "execution_functions.h"
void read_process_file(const char *filename, PROCESS_MANAGER *pm) {
    FILE * file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Can not open file \n");
        return;
    }
    char line [256];
    PROCESS_QUEUE proccesQueue;
    initialize_process_queue(&proccesQueue);
    while (fgets(line,256,file) != NULL)
    {
        int prioritoy, isHead, id;
        if (sscanf(line ,"%d, %d, %d", &id, &prioritoy, &isHead) == 3)
        {
            PROCESS procces;
            initialize_process(&procces,id,prioritoy);
            enqueue(&proccesQueue, procces);
            if (isHead == 1)
            {
                if (prioritoy == 1)
                {
                    printf("%d", id);
                    insert_front(pm, proccesQueue);                
                
            }else{
                insert_rear(pm, proccesQueue);
            }
            initialize_process_queue(&proccesQueue);
            
        }
    }
}
fclose(file);
}
void read_insertion_file(const char *filename, INSERTION_QUEUE *eq){
    FILE * file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Can not open file \n");
        return;
    }
    char line [256];
    PROCESS_QUEUE proccesQueue;
    initialize_process_queue(&proccesQueue);
    while (fgets(line,256,file) != NULL)
    {
        int prioritoy, isHead, id ,iteration;
        if (sscanf(line ,"%d, %d, %d, %d", &iteration, &id, &prioritoy, &isHead) == 4)
        {
            PROCESS procces;
            initialize_process(&procces,id,prioritoy);
            enqueue(&proccesQueue, procces);
            proccesQueue.iteration = iteration;
            proccesQueue.priority = prioritoy;
            if (isHead == 1)
            {
                if (prioritoy == 1)
                {
                    printf("%d", id);
                    
                    enqueue(eq, proccesQueue);                
                
            }else{
                enqueue(eq, proccesQueue);
            }
            initialize_process_queue(&proccesQueue);
            
        }
    }
}
fclose(file);

}
void execution_loop(PROCESS_MANAGER *pm, INSERTION_QUEUE *eq, FAILURE_STACK *fs) {
    int iteration = 0;
    FILE* file = fopen("execution_run.txt", "w");
    while (pm->size != 0)
    {
        PROCESS_QUEUE queue = delete_front(pm);
        while (queue.size != 0)
        {
             if (eq->size != 0)
    {
        if (peek(eq).iteration == iteration)
        {
            PROCESS_QUEUE process = dequeue(eq);
            if (process.priority == 1)
            {
                insert_front(pm, process);
            }else {
                insert_rear(pm,process);
            }
            
        }
        
    }
            PROCESS a = peek(&queue);
            if (a.pid % 8 == 0)
            {
                push(fs,queue);
                fprintf(file,"%d f \n", a.pid);
                iteration++;
                break;
            }else {
                dequeue(&queue);
                fprintf(file,"%d s \n", a.pid);
            }
            iteration++;
            
        }
        }
        fclose(file);
    
    
}