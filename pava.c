/*
Maximilien Danisch
April 2016
http://bit.ly/maxdan94
maximilien.danisch@telecom-paristech.fr

Info:
This is an implementation of the Pool Adjacent Violators Algorithm (PAV algorithm or PAVA) for isotonic regression (with all intial weights equal to one) such as detail here:
http://stat.wikia.com/wiki/Isotonic_regression
https://en.wikipedia.org/wiki/Isotonic_regression

to compile:
gcc pava.c -o pava -O9

to execute:
./pava val.txt res.txt
val.txt should contain the values to fit with isotonic regression separated by any white space.
Will print the result in res.txt "n v" on each line.
"n" is the number of values equal to "v".
*/

#include <stdlib.h>
#include <stdio.h>

#define NVAL 1000000000 //maximum number of values, will increase if needed

//fit data structure:
typedef struct {
	unsigned n;//total number of aggregated points
	unsigned *nag;//num[i]=nuber of aggregated points
	double *val;//val[i]=value of the aggregated points
} isoreg;

//Pool Adjacent Violators Algorithm. Values to fit in vect and size of vect.
isoreg *pava(double *vect,unsigned n){
	isoreg *fit=malloc(sizeof(isoreg));
	unsigned *nag=malloc(n*sizeof(unsigned));
	double *val=malloc(n*sizeof(double));
	unsigned i,j;
	nag[0]=1;
	val[0]=vect[0];
	j=0;
	for (i=1;i<n;i++){
		j+=1;
		val[j]=vect[i];
		nag[j]=1;
		while ((j>0) && (val[j]<val[j-1])){//change into val[j]>val[j-1] to have a non-increasing monotonic regression.
			val[j-1]=(nag[j]*val[j]+nag[j-1]*val[j-1])/(nag[j]+nag[j-1]);
			nag[j-1]+=nag[j];
			j--;
		}
	}
	fit->n=j+1;
	fit->nag=nag;
	fit->val=val;
	return fit;
}

double* readvalues(char* input,unsigned *n){
	*n=NVAL;
	double *vect=malloc((*n)*sizeof(double));
	unsigned i=0;
	FILE* file=fopen(input,"r");
	while (fscanf(file,"%le ", vect+i)==1) {
		if (i++==*n) {
			(*n)+=NVAL;
			vect=realloc(vect,(*n)*sizeof(double));
		}
	}
	fclose(file);
	*n=i;
	vect=realloc(vect,(*n)*sizeof(double));
	return vect;
}

//printing the result in file output: "nag val" on each line
void printres(isoreg *fit,char* output){
	unsigned i;
	FILE *file=fopen(output,"w");
	for (i=0;i<fit->n;i++){
		fprintf(file,"%u %le\n",fit->nag[i],fit->val[i]);
	}
	fclose(file);
}

void freeisoreg(isoreg *fit){
	free(fit->nag);
	free(fit->val);
	free(fit);
}

int main(int argc,char** argv){
	double *vect;
	unsigned n;
	isoreg* fit;
	printf("Reading values from file %s\n",argv[1]);
	vect=readvalues(argv[1],&n);
	printf("%u values read\n",n);
	printf("Doing Isotonic regression with the PAV algorithm\n");
	fit=pava(vect,n);
	printf("Printing result in file %s\n",argv[2]);
	printres(fit,argv[2]);
	free(fit);
	return 0;
}
