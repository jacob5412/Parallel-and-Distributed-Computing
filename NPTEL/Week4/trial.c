#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <omp.h>


#define MAXDIM 17 
#define SLOW_THREAD 2
int twork[16] ;
int arr[MAXDIM][MAXDIM+1] ;

void PTUpdateEntry( int arr[MAXDIM][MAXDIM+1], int i, int j, int value  )
{
  int tnum = omp_get_thread_num() ;
  //printf( "%d,%d\n", i, j ) ;
  #pragma omp critical
  twork[tnum]++ ;

  arr[i][j] = value ;

  if ( ( (tnum == SLOW_THREAD) && (rand()%1 == 0) ) || ( (tnum != SLOW_THREAD) && (rand()%100 == 0) ) )
  {
     double timex = time(NULL) ;
     while ( time(NULL) < (timex+.01) ) ;
  }

}

int binomialCoeff(int n, int k)
{
    int res = 1, i = 0;
    if (k > n - k)
       k = n - k;
    for (i = 0; i < k; ++i)
    {
        res *= (n - i);
        res /= (i + 1);
    }
    return res;
}


int main( int argc, char** argv )
{
	double time1, time2;
	time1=time(NULL);
	int numt;
	int i, j ;
	int value=0;
	#pragma omp parallel 
	{
		#pragma omp single 
		numt=omp_get_num_threads();
		#pragma omp for
                for( i = 0 ; i < MAXDIM ; i++ ){
                        for( j = 0 ; j<=i  ; j++ ){

                          #pragma omp task firstprivate(i,j) shared(arr) 
                          PTUpdateEntry( arr, i, j,binomialCoeff(i,j) ) ;
                        }
                }

	}

	#pragma omp taskwait	
	time2=time(NULL);
	for(i = 0 ; i < MAXDIM ; i++ ){
		for( j = 0 ; j<=i  ; j++ ){
			printf("data(%d,%d)%d\n", i,j,arr[i][j]);
	}
}




printf("time taken time=%g with thread=%d\n", time2-time1,numt ) ; 
}