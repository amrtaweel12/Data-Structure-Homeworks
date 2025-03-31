#include <stddef.h>
#include <stdbool.h>
#include "../include/min_heap.h"
MinHeap* heap_create(size_t capacity, size_t element_size, int (*compare)(const void*, const void*)){
MinHeap* newHeap = (MinHeap*) malloc(sizeof(MinHeap));
    if (!newHeap) return NULL; 

    newHeap->data = calloc(capacity, element_size);
    if (!newHeap->data) {
        free(newHeap);  
        return NULL;
    }

    newHeap->element_size = element_size;
    newHeap->capacity = capacity;
    newHeap->size = 0;
    newHeap->compare = compare;

    return newHeap;
}
void heap_destroy(MinHeap* heap) {
if (heap == NULL) {
        return; 
    }
    free(heap->data); 
    heap->data = NULL; 
    free(heap); 
    heap = NULL; 
}
int heap_insert(MinHeap* heap, const void* element) {
    if (heap == NULL || element == NULL) {
        return 0;
    }
    if (heap->capacity <= heap->size) {
        void* newData = realloc(heap->data, heap->element_size * heap->capacity * 2);
        if (newData == NULL) {
            return 0; 
        }
        heap->data = newData;
        heap->capacity *= 2;
    }

    int currentItemIndex = heap->size;
    void* data = heap->data;
    memcpy((char*)data + currentItemIndex * heap->element_size, element, heap->element_size);
    heap->size++; 

    while (currentItemIndex != 0) {
        int parentIndex = (currentItemIndex - 1) / 2;
        char* parentPtr = (char*)data + parentIndex * heap->element_size;
        char* childPtr = (char*)data + currentItemIndex * heap->element_size;

        if (heap->compare((void*)childPtr, (void*)parentPtr) < 0) {
            for (size_t i = 0; i < heap->element_size; i++) {
                char temp = *(parentPtr + i);
                *(parentPtr + i) = *(childPtr + i);
                *(childPtr + i) = temp;
            }
            currentItemIndex = parentIndex;
        } else {
            break;
        }
    }
    return 1;
}
int heap_extract_min(MinHeap* heap, void* result) {
    if (heap->size == 0) {
        return 0;
    }

    
    memcpy(result, heap->data, heap->element_size);

    if (heap->size == 1) {
        heap->size--;
        return 1;
    }

    void* last = (char*)heap->data + heap->element_size * (heap->size - 1);
    memcpy(heap->data, last, heap->element_size);
    heap->size--;

    int index = 0;
    while (true) {
        int leftChildIdx = 2 * index + 1;
        int rightChildIdx = 2 * index + 2;
        int smallest = index;

        void* current = (char*)heap->data + heap->element_size * index;
        void* leftChild = (char*)heap->data + heap->element_size * leftChildIdx;
        void* rightChild = (char*)heap->data + heap->element_size * rightChildIdx;

        if (leftChildIdx < heap->size && heap->compare(leftChild, current) < 0) {
            smallest = leftChildIdx;
        }
        if (rightChildIdx < heap->size && heap->compare(rightChild, (char*)heap->data + heap->element_size * smallest) < 0) {
            smallest = rightChildIdx;
        }

        if (smallest != index) {
            char temp[heap->element_size];
            memcpy(temp, (char*)heap->data + heap->element_size * smallest, heap->element_size);
            memcpy((char*)heap->data + heap->element_size * smallest, current, heap->element_size);
            memcpy(current, temp, heap->element_size);
            index = smallest;
        } else {
            break;
        }
    }

    return 1;
}
size_t heap_size(const MinHeap* heap) {
    if (heap == NULL) {
        return 0;  
    }
    return heap->size;
}
int heap_peek(const MinHeap* heap, void* result) {
    if (heap == NULL || result == NULL || heap->size == 0) {
        return 0;  
    }
    memcpy(result, heap->data, heap->element_size);
    return 1;
}
int heap_merge(MinHeap* heap1, const MinHeap* heap2) {
    if (heap1 == NULL || heap2 == NULL) {
        return 0;  
    }

    size_t requiredCapacity = heap1->size + heap2->size;
    if (heap1->capacity < requiredCapacity) {
        size_t newCapacity = heap1->capacity;
        while (newCapacity < requiredCapacity) {
            newCapacity *= 2;  
        }
        void* newData = realloc(heap1->data, heap1->element_size * newCapacity);
        if (newData == NULL) {
            return 0; 
        }
        heap1->data = newData;
        heap1->capacity = newCapacity;
    }

    for (size_t i = 0; i < heap2->size; i++) {
        void* elementToAdd = (char*)heap2->data + i * heap2->element_size;
        if (!heap_insert(heap1, elementToAdd)) {
            return 0; 
        }
    }
    return 1;
}
                    