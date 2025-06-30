#include "process_queue.h"

void initialize_process_queue(PROCESS_QUEUE *pq) {
    pq->size = 0;
    pq->rear = -1;
    pq->front = 0;
    pq->priority = 0;
    pq->iteration = 0;
}
bool isFull(PROCESS_QUEUE *pq) {
    return pq->size == QUEUE_SIZE;
}
bool isEmpty(PROCESS_QUEUE *pq) {
    return pq->size == 0;
}
PROCESS peek(PROCESS_QUEUE *pq) {
    if (isEmpty(pq) != true)
    {
        return pq->queue[pq->front];
    }else {
        printf("The PROCESS_QUEUE is empty. You can not peek\n");
        exit(EXIT_FAILURE);    
        }
}
void enqueue(PROCESS_QUEUE *pq, PROCESS data) {
    if (!isFull(pq))
    {
        pq->priority  = data.priority;
        pq->rear =(pq->rear + 1) % QUEUE_SIZE;
        pq->queue[pq->rear] = data;
        pq->size++;
    }else{
        printf("PROCESS_QUEUE is Full. You can not enqueue process");
    }
    
}
PROCESS dequeue(PROCESS_QUEUE *pq) {
    if (!isEmpty(pq))
    {
        PROCESS temp = pq->queue[pq->front];
        pq->front = (pq->front+1) % QUEUE_SIZE;
        pq->size--;
        return temp;
    }else{
        printf("The PROCESS_QUEUE is empty. You can not dequeue\n");
        exit(EXIT_FAILURE);
    }
    
}