#include <stdio.h>
#include <stdlib.h>
#include "declarations.h"

int main()
{
    data head={.num=0, .next=NULL};
    int result=0;
    int check=0;

    check=ReadPostfix(&result, &head);
    if(check!=0){
        return -1;
    }

    printf("%d\n", result);
    return 0;
}
