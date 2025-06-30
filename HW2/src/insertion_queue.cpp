#include "insertion_queue.h"
void initialize_execution_queue(INSERTION_QUEUE *iq) {
    iq->size = 0;
    iq->rear = -1;
    iq->front = 0;
}
bool isFull(INSERTION_QUEUE *iq) {
    return iq->size == MAX_OPERATION;
}
bool isEmpty(INSERTION_QUEUE *iq) {
    return iq->size == 0;
}
PROCESS_QUEUE peek(INSERTION_QUEUE *iq) {
    if (isEmpty(iq))
    {
        printf("INSERTION_QUEUE is empty you can not peek");
        exit(EXIT_FAILURE);
    }
    return iq->queue[iq->front];
    

}
void enqueue(INSERTION_QUEUE *iq, PROCESS_QUEUE data) {
       if (!isFull(iq))
    {
        iq->rear =(iq->rear + 1) % MAX_OPERATION;
        iq->queue[iq->rear] = data;
        iq->size++;
    }else{
        printf("PROCESS_QUEUE is Full. You can not enqueue process");
    }
}
PROCESS_QUEUE dequeue(INSERTION_QUEUE *iq) {
     if (!isEmpty(iq))
    {
        PROCESS_QUEUE temp = iq->queue[iq->front];
        iq->front = (iq->front+1) % QUEUE_SIZE;
        iq->size--;
        return temp;
    }else{
        printf("The PROCESS_QUEUE is empty. You can not dequeue\n");
        exit(EXIT_FAILURE);
    }
}