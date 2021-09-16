#include <stdlib.h>
#include "gutil.h"

bool streq(str a, str b){
    int i = -1;
    do{
        i++;
        if(a[i] != b[i]){
            return(false);
        }
    }while(a[i] != '\0');
    return(true);
}

void free_strlist(str* list){
    int i = 0;
    while(list[i] != NULL){
        free(list[i]);
        i++;
    }
    free(list);
}

str stripnl(str input){
    str line = malloc(51 * sizeof(char));
    int n = 0;
    int s = 1;
    int i = 0;
    char c;
    while( (c = input[i]) ){
        if(c != '\n'){
            line[n] = c;
            n++;
        }  
        i++;    
        if(n  == 49){
            s++;
            line = realloc(line,(s*50 + 1) * sizeof(char));
            n = 0;
        }
        if(c == '\0'){
            break;
        }
    }
    return(line);
}

bool vchar(char c, str vc){
    int i = 0;
    while(vc[i] != '\0'){
        if(c == vc[i]){
            return(true);
        }
        i++;
    }
    return(false);
}

bool vstr(str s, str* vc){
    int i = 0;
    str a;
    while(vc[i] != NULL){
        a = vc[i];
        if(streq(s,vc[i])){
            return(true);
        }
        i++;
    }
    
    return(false);
}  

str str_malloc(str s){
    int i = 0;
    while(1){
        if(s[i] == '\0'){
            break;
        }
        i++;
    }
    str rt = malloc((i+1) * sizeof(char));
    i = -1;
    do{
        i++;
        rt[i] = s[i];
    }while(s[i] != '\0');
    return(rt);
}