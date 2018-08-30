/*threadprivate only applies to file scope/static variables*/

#include <stdio.h>
#include <omp.h>

static int glb;
static int glb_tp;

#pragma omp threadprivate(glb_tp)
int main()
{
    int numt;
    #pragma omp threadprivate(numt)
    //cannot declare numt as it is a local variable
    //exists only in the stack
}

/*
thread_private_scope.c: In function 'main':
thread_private_scope.c:13:30: error: automatic variable 'numt' cannot be 'threadprivate'
     #pragma omp threadprivate(numt)
*/