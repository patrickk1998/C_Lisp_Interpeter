#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int multi(int a, int b){
    int s = 0;
    for(int i = 0; i < a;i++){
        s = s + b;
    }
    return(s);
}

bool overTen(int a){
    bool over = false;
    if(a > 10){
        over = true;
    }
    return(over);
}

int main(){
    int a = 3;
    int b = 4;
    int r = multi(3,4);
    bool o = overTen(r);
    printf("\n over: %d \n",o);
}