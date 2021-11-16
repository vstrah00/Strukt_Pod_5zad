#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "declarations.h"

data* CreateElement(int number)
{
    data* newElement=NULL;

    newElement=(data*)malloc(sizeof(data));
    if(!newElement){
        perror("Cannot allocate memory!\n");
        return NULL;
    }

    newElement->num=number;

    return newElement;
}

int ReadPostfix(int* resultDestination, data* head)
{
    char fileName[30]={0};
    char* buffer=NULL;
    char* currentBuffer=NULL;
    char operation;
    int fileLenght=0;
    int check=0;
    int bytesRead=0;
    int num=0;
    FILE* fp=NULL;

    printf("Input postfix file name:\t");
    check=scanf(" %s", fileName);
    if(check!=1){
        return -1;
    }

    fp=fopen(fileName, "rb");
    if(fp==NULL){
        perror("ERROR");
        return -1;
    }

    fseek(fp, 0, SEEK_END);
    fileLenght=ftell(fp);

    buffer=(char*)calloc(fileLenght+1, sizeof(char));
    if(buffer==NULL){
        perror("ERROR");
        return -2;
    }

    rewind(fp);
    fread(buffer, sizeof(char), fileLenght, fp);
    printf("| %s |\n", buffer);
    fclose(fp);

    currentBuffer=buffer;
    while(strlen(currentBuffer)>0){
        check=sscanf(currentBuffer, " %d %n", &num, &bytesRead);
        if(check==1){
            check=Push(head, num);
            if(check!=0){
                free(buffer);
                deleteAll(head);
                return -3;
            }
        }
        else{
            check=sscanf(currentBuffer, " %c %n", &operation, &bytesRead);
            if(check==1){
                check=PerformOperation(head, operation);
                if(check!=0){
                    free(buffer);
                    deleteAll(head);
                    return -4;
                }
            }
        }
        currentBuffer+=bytesRead;
    }

    free(buffer);
    check=Pop(resultDestination, head);
    if(check!=0){
        deleteAll(head);
        return -5;
    }
    if(head->next){
        printf("Postfix file error!\n");
        return -6;
    }

    deleteAll(head);

    return 0;
}

int PerformOperation(data* head, char operation)
{
	int operand1 = 0;
	int operand2 = 0;
	int result = 0;
	int status1 = EXIT_SUCCESS;
	int status2 = EXIT_SUCCESS;

	status2 = Pop(&operand2, head);
	if (status2 != EXIT_SUCCESS)
	{
		return -1;
	}

	status1 = Pop(&operand1, head);
	if (status1 != EXIT_SUCCESS)
	{
		return -2;
	}

	switch (operation)
	{
	case '+':
		result = operand1 + operand2;
		break;
	case '-':
		result = operand1 - operand2;
		break;
	case '*':
		result = operand1 * operand2;
		break;
	case '/':
		if (operand2 == 0)
		{
			perror("Cannot divide with zero!\n");
			return -3;
		}
		result = operand1 / operand2;
		break;
	default:
		printf("This operation is not supported!\n");
		return -4;
	}

	return Push(head, result);
}

int deleteAfter(data* position)
{
    data* deleteData=position->next;
    if(deleteData==NULL){
        return 0;
    }

    position->next=deleteData->next;
    free(deleteData);
    return 0;
}

int deleteAll(data* head)
{
    data* temp=NULL;
    while(head->next){
        temp=head->next;
        head->next=temp->next;
        free(temp);
    }
    return 0;
}

int insertAfter(data* position, data* newPosition)
{
    if(newPosition==NULL){
        printf("Error! Nothing to insert!\n");
        return -1;
    }

    newPosition->next=position->next;
    position->next=newPosition;

    return 0;
}

int Push(data* head, int number)
{
    data* newData=NULL;

    newData=CreateElement(number);
    if(!newData){
        return -1;
    }

    return insertAfter(head, newData);
}

int Pop(int* result, data* head)
{
    data* first=head->next;
    if(!first){
        printf("Postfix file error");
        return -1;
    }

    *result=first->num;

    return deleteAfter(head);
}
