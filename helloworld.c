#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINE
#include <math.h>
#include <time.h>

double runi(){
    double r = (double) rand() / RAND_MAX;
    return(r);
}

double* gaussArray(int n){
    int size = n;
    if(n % 2 == 1){
        size = n + 1;
    }
    double *ga = malloc(size * sizeof(double));
    for(int i = 0; i < size / 2;i++){
        double u1 = runi();
        double u2 = runi();
        double theta = 2*M_PI*u1;
        double R = sqrt(-2 * log(u2));
        ga[2*i] = sin(theta)*R;
        ga[2*i+1] = cos(theta)*R;
    }

    if(size != n){
        double *gan = malloc(n * sizeof(double));
        for(int i = 0;i < n;i++){
            gan[i] = ga[i];
        }
        free(ga);
        return(gan);
    } else{
        return(ga);
    }
}

void prtg(int n){
    double *ga = gaussArray(n);
    for(int i = 0; i < n; i++){
        printf("%f ",ga[i]);
    } 
    printf("\n");
}

void gaussTest(int n){
    printf("generating %d random numbers\n", n);
    double *ga = gaussArray(n);
    int pos = 0;
    for(int i = 0; i < n; i++){
        if(ga[i] > 0){
            pos++;
        }
    }
    printf("symetry: %f \n",(double) pos / n);
}

double** genHashCode(n,k){
    double** hash = malloc(n * sizeof(double*));
    for(int i = 0; i < k; i++){
        hash[i] = gaussArray(n);
    }  
    return(hash);  
}

double dotp(double* a, double* b, int n){
    double s = 0;
    for(int i= 0; i < n;i++){
        s = s + a[i]*b[i];
    }
    return(s);
}

double length(double* v, int n){
    double s = 0;
    for(int i = 0; i < n; i++){
        s = s + v[i]*v[i];
    }
    return(sqrt(s));
}

double angle(double*  a, double* b, int n){
    double cs = dotp(a,b,n) / (length(a,n) * length(b,n));
    return(acos(cs));
}

char* hashing(double** code, double* data,int n, int k){
    char* hash = malloc(k * sizeof(char*));
    for(int i = 0; i < k; i++){
        double dp = dotp(code[i],data,n);
        if(dp > 0){
            hash[i] = 1;
        } else {
            hash[i] = 0;
        }   
    }
    return(hash);
}

char* hashStr(char* hash, int k){
    char* str = malloc((k+1) * sizeof(char));
    for(int i = 0; i < k; i++){
        if(hash[i] == 0){
            str[i] = '0';
        } else {
            str[i] = '1';
        }
    }
    str[k+1] = '\0';
    return(str);
}

double* getVect(int n){
    printf("Enter a vector of dimension %d ",n);
    double* vect = malloc(n * sizeof(double));
    for(int i = 0;i < n; i++){
        scanf("%lf",&vect[i]);
    }
    return(vect);
}

void printVect(double* vect, int n){
    for(int i = 0; i < n; i++){
        printf("%f ", vect[i]);
    }   
    printf("\n");
}

int main(void){
    // name[n] is the same as *(name + n*sizeOfType) but a array 
    // is immutable

    int n = 3;
    int k = 4;

    srand(time(0));
    double **hashCode = genHashCode(n,k);

    double* v1 = getVect(n);
    double* v2 = getVect(n);
    printVect(v1,n);
    printVect(v2,n);
    
    char* h1 = hashing(hashCode,v1,n,k);
    char* h2 = hashing(hashCode,v2,n,k);
    printf("hash: %s \n", hashStr(h1,k));
    printf("hash: %s \n", hashStr(h2,k));
    printf("angle: %f \n", angle(v1,v2,n));
}
