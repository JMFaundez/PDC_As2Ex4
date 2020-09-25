#define N 1000000
#define N_case 100
#include <stdio.h>
#include <sys/time.h>
#include <omp.h>
#include <time.h>
#include <math.h>
#include "stdlib.h" // rand for instance.

int main(){
	double mean = 0;
	double stdv = 0;
	double times[N_case];
	int n_threads;

	// set/check the number of threads
	omp_set_num_threads(32);
#pragma omp parallel 
{
	#pragma omp master
	{
	printf("Number of threads  %d \n",omp_get_num_threads());
	}
}

	for(int j=0; j<N_case;j++){
		double mysecond();
		double t1, t2; // timers
		double x[N];
		double maxval = 0.0; 
		int maxloc = 0;
	
	
		// generate random numbers
		srand(j); // seed from j
	   for(int i=0; i < N;i++){
	     // Generate random number between 0 and 1
	     x[i] = ((double)(rand()) / RAND_MAX)*((double)(rand()) / RAND_MAX)*((double)(rand()) / RAND_MAX)*1000;
	   }
	
	   // find the max
	    t1 = mysecond();
#pragma omp parallel for
	    for (int i=0; i < N; i++){
	       if (x[i] > maxval){ 
	            maxval = x[i]; 
		    maxloc = i;
	       }
	  }
	    t2 = mysecond();
	    //printf("Max number = %11.8f at %10d at Execution time: %11.8f s\n",maxval,maxloc, (t2 - t1));
	    mean += (t2 - t1)/N_case;
	    times[j] = t2 - t1;
	
	}

	for(int j=0; j<N_case;j++){
		stdv += pow(times[j]-mean,2);
	}
	
	printf("Mean = %11.8f, Standard deviation = %11.8f \n",mean,sqrt(stdv/N_case));


  	return 0;
}


// function with timer
double mysecond(){
  struct timeval tp;
  struct timezone tzp;
  int i;

  i = gettimeofday(&tp,&tzp);
  return ( (double) tp.tv_sec + (double) tp.tv_usec * 1.e-6 );
}
