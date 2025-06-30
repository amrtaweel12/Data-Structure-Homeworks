#include "process_manager.h"
void initialize_process_manager(PROCESS_MANAGER *pm) {
    pm->rear = -1;
    pm->front = 0;
    pm->size = 0;
}
bool isFull(PROCESS_MANAGER *pm) {
    return pm->size == MAX_PROCESS;

}
bool isEmpty(PROCESS_MANAGER *pm) {
    return pm->size == 0;
}
void insert_front(PROCESS_MANAGER *pm, PROCESS_QUEUE pq) {
    if (isFull(pm))
    {
        printf("The Process manger is FUll you can not insert");
        return;
    }
    pm->front = (pm->front - 1 + MAX_PROCESS) % MAX_PROCESS;
    pm->deque[pm->front] = pq;
    pm->size++;
    if (pm->size == 1)
    {
        pm->rear = pm->front;
    }
    

}
void insert_rear(PROCESS_MANAGER *pm, PROCESS_QUEUE pq) {
    if (isFull(pm)) {
        printf("The Process manger is FUll you can not insert \n");
        return;
    }
    pm->rear = (pm->rear + 1) % MAX_PROCESS;
    pm->deque[pm->rear] = pq;
    pm->size++;
    
}
PROCESS_QUEUE delete_front(PROCESS_MANAGER *pm) {
    if (isEmpty(pm))
    {
        printf("You can not delete front from Empty PROCESS_MANAGER \n");
        exit(EXIT_FAILURE);
    }
    PROCESS_QUEUE queue= pm->deque[pm->front];
    pm->front = (pm->front + 1) %MAX_PROCESS;
    pm->size--;
    return queue;
}
PROCESS_QUEUE delete_rear(PROCESS_MANAGER *pm) {
      if (isEmpty(pm))
    {
        printf("You can not delete front from rear PROCESS_MANAGER \n");
        exit(EXIT_FAILURE);
    }
    PROCESS_QUEUE queue = pm->deque[pm->rear];
    pm->rear = (pm->rear - 1 + MAX_PROCESS) % MAX_PROCESS;
    pm->size--;
    return queue;

}
