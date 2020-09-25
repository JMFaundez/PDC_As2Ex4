#define N 1000000
#define N_case 100
#include <stdio.h>
#include <sys/time.h>
#include <omp.h>
#include <time.h>
#include <math.h>
#include "stdlib.h" // rand for instance.

int main(){
double silly_maxval = 0.0;
int silly_maxloc = 0;

int threads[9] = {1,2,4,8,16, 20, 24, 28, 32};
for(int k=0;k<9;k++){
double mean = 0;
double stdv = 0;
double times[N_case];
//int mega_maxloc[threads[k]];
//double mega_maxval[threads[k]];
typedef struct {
	double val; 
	int loc; 
	char pad[128];
	} tvals;

// set/check the number of threads
omp_set_num_threads(threads[k]);

// Cycle over number of test cases for averaging
for(int j=0; j<N_case;j++){
	double mysecond();
	double t1, t2; // timers
	double x[N];
	tvals maxinfo[threads[k]];
	double maxval = 0.0; 
	int maxloc = 0;
	// generate random numbers
	srand(j); // seed from j
   	for(int i=0; i < N;i++){
     		// Generate random number between 0 and 1
     		x[i] = ((double)(rand()) / RAND_MAX)*((double)(rand()) / RAND_MAX)*((double)(rand()) / RAND_MAX)*1000;
   	}

    	t1 = mysecond();
	// parallel stuff
	#pragma	omp parallel shared(maxinfo)
    	{
	int id = omp_get_thread_num();
	//mega_maxval[id] = -1.0e30;
	maxinfo[id].val = -1.0e30;
	#pragma omp for
    	for (int i=0; i < N; i++){
       		if (x[i] > maxinfo[id].val){ 
            	maxinfo[id].val = x[i]; 
	    	maxinfo[id].loc = i;
       		}
	}
  	}
	// serial part
	maxloc = maxinfo[0].loc;
       	maxval = maxinfo[0].val;

	for(int i=1; i<threads[k]; i++) {
		if (maxinfo[i].val > maxval) {
		maxval = maxinfo[i].val;
		maxloc = maxinfo[i].loc;
		}
	}
    	t2 = mysecond();

	silly_maxval += maxval;
	silly_maxloc += maxloc;
	// mean/SD stuff
    	mean += (t2 - t1)/N_case;
    	times[j] = t2 - t1;

}

for(int j=0; j<N_case;j++){
	stdv += pow(times[j]-mean,2);
}

#pragma omp parallel 
{
	#pragma omp master
	{
printf("%2d %11.8f %11.8f \n",omp_get_num_threads(),mean,sqrt(stdv/N_case));
	}
}
}

printf("1  %d %11.8f  \n",silly_maxloc,silly_maxval);
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
