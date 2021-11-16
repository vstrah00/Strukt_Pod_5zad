#ifndef DECLARATIONS_H
#define DECLARATIONS_H

typedef struct _data{
    int num;
    struct _data* next;
}data;

int ReadPostfix(int* resultDestination, data* head);
int deleteAfter(data* position);
int deleteAll(data* head);
int insertAfter(data* position, data* newPosition);
int Push(data* head, int number);
int Pop(int* result, data* head);
data* CreateElement(int number);
int PerformOperation(data* head, char operation);


#endif // DECLARATIONS_H
