#include <stdlib.h>
#include <stdio.h>
#include "../include/scheduler.h"
static int compare_ints(const void* a, const void* b) {
    const Process* process_a = (const Process*)a;
    const Process* process_b = (const Process*)b;

    if (process_a->vruntime < process_b->vruntime) {
        return -1; 
    } else if (process_a->vruntime > process_b->vruntime) {
        return 1; 
    } else {
        return 0; 
    }
}

Scheduler* create_scheduler(int capacity) {
    if (capacity <= 0) {
        return NULL; 
    }

    Scheduler* newScheduler = (Scheduler*)malloc(sizeof(Scheduler));
    if (newScheduler == NULL) {
        return NULL;  
    }

    newScheduler->process_queue = heap_create(capacity, sizeof(Process), compare_ints);
    if (newScheduler->process_queue == NULL) {
        free(newScheduler); 
        return NULL;
    }

    newScheduler->time_slice = 1;  
    newScheduler->current_process = NULL;

    return newScheduler;
}
void destroy_scheduler(Scheduler* scheduler) {
    if (scheduler == NULL) {
        return;
    }

    heap_destroy(scheduler->process_queue);

    if (scheduler->current_process != NULL) {
        free(scheduler->current_process);
    }

    free(scheduler);
}
void schedule_process(Scheduler* scheduler, Process process) {
    if (scheduler == NULL) {
        return; 
    }

    if (process.nice < -20) process.nice = -20;
    if (process.nice > 19) process.nice = 19;

    if (!heap_insert(scheduler->process_queue, &process)) {
        printf("Failed to insert process PID %d into the scheduler queue.\n", process.pid);
        return;
    }

    if (scheduler->current_process != NULL) {
        if (process.vruntime < scheduler->current_process->vruntime) {
            if (!heap_insert(scheduler->process_queue, scheduler->current_process)) {
                printf("Failed to reinsert preempted process PID %d into the queue.\n",
                       scheduler->current_process->pid);
            }
            scheduler->current_process = NULL;  
        }
    }

    printf("Process PID %d scheduled successfully.\n", process.pid);
}
Process* get_next_process(Scheduler* scheduler) {
    if (scheduler == NULL || scheduler->process_queue == NULL || scheduler->process_queue->size == 0) {
        return NULL;
    }

    if (scheduler->current_process != NULL) {
        scheduler->current_process->is_running = false;
        if (!heap_insert(scheduler->process_queue, scheduler->current_process)) {
            printf("Failed to reinsert current process PID %d into the queue.\n",
                   scheduler->current_process->pid);
            return NULL; 
        }
    } else {
        scheduler->current_process = (Process*)malloc(sizeof(Process));
        if (scheduler->current_process == NULL) {
            printf("Memory allocation failed for current process.\n");
            return NULL;  
        }
    }

    if (!heap_extract_min(scheduler->process_queue, scheduler->current_process)) {
        printf("Failed to extract the next process from the queue.\n");
        return NULL; 
    }

    scheduler->current_process->is_running = true;

    return scheduler->current_process;
}
void tick(Scheduler* scheduler) {
    if (scheduler == NULL) {
        return;
    }

    if (scheduler->current_process == NULL) {
        return;  
    }

    update_vruntime(scheduler->current_process, scheduler->time_slice);
}