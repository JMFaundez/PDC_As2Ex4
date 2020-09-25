#define N 1000000
#define N_case 100
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <math.h>
#include "stdlib.h" // rand for instance.

int main(){
	double mean = 0;
	double stdv = 0;
	// do something silly
	double silly_maxval = 0.0;
	int silly_maxloc = 0;
	double times[N_case];

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
	  for (int i=0; i < N; i++){
	       if (x[i] > maxval){ 
	            maxval = x[i]; 
		    maxloc = i;
	       }
	  }
	    t2 = mysecond();
	    silly_maxval += maxval;
	    silly_maxloc += maxloc;
	    mean += (t2 - t1)/N_case;
	    times[j] = t2 - t1;
	
	}

	for(int j=0; j<N_case;j++){
		stdv += pow(times[j]-mean,2);
	}
printf("1 %11.8f %11.8f \n",mean,sqrt(stdv/N_case));
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
