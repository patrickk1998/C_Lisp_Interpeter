#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "gutil.h"


// Enum of diffrent types of children. 

enum ctype{expression,num,operand,none};

struct children;

typedef struct expression{
    struct children* kids;
    int nkids;
} expr;

typedef struct children{
    enum ctype type;
    struct expression ec;
    double nc;
    op oc;

} child;

typedef struct passInHolder{
    double* list;
    int size;
} passHold;

str* vops;

bool toquit = false;

expr lex(str instr);


str* get_vops(){
    str* o = malloc(5 * sizeof(str));
    o[0] = str_malloc("+");
    o[1] = str_malloc("*");
    o[2] = str_malloc("sqrt");
    o[3] = str_malloc("quit");
    o[4] = NULL;
    return(o);
}

double apply(str oc, passHold args);
/*
    str readIn()
    -- reads in lines of input, of arbitrary length, and returns it when return 
    pressed two times in row. It truncates to return the input without final two \n 
    characters.
*/

str readIn(){
    str line = malloc(51 * sizeof(char));
    int n = 0;
    int s = 1;
    int l = 0;
    char c;
    int b = 0;
    while( (c = getchar()) ){
        if(c == '\n'){
            b++;
        } else{
            b = 0;
        }
        line[n] = c;

        n++;
        l++;
        if(n  == 49){
            s++;
            line = realloc(line,(s*50 + 1) * sizeof(char));
            n = 0;
        }

        if(b == 2){
            break;
        }
    }
    line[l-2] = '\0';
    return(line);
}


/*
    realb(char* buff, str* dest, int bl, int dl)
    -- bufffer for daynamic arrays. Have to manually set 
    bl and dl 
*/

str* realb(char* buff, str* dest, int bl, int dl){
    str* newdest = realloc(dest,(dl + 1) * sizeof(str));
    buff[bl] = '\0';
    newdest[dl] = str_malloc(buff);
    return(newdest);
}

/*  
    str extractx(str instr)
    --extracts first expression that if finds
*/

str extractx(str instr){
    str buff = malloc(256*sizeof(char));
    int ii = -1;
    int bi = 0;
    int pdepth = 0;
    bool in = false;
    do{   
        ii++;
        char c = instr[ii];   
        if(c == ')'){
            pdepth--;
        }
        if(pdepth == 0 && in){
            break;
        }
        if(in){
            buff[bi] = c;
            bi++;
        }
        if(c =='('){
            pdepth++;
            in = true;   
        } 
    }while(instr[ii] != '\0');
    buff[bi] = '\0'; 
    return(buff);  
}

/* 
    str* eargs(str input)
    -- given a string of input, it returns a string 
    argument that are the arguments of an expression
    found the the input. The array ends with a NULL pointer 
*/

// currently working on this!.

str* eargs(str istr){
    str vc = "abcdefghigklmnopqrstuvwxynz1234567890.+-*/()";
    char buff[256];
    int bi = 0;
    str* args = malloc(sizeof(str));
    int ai = 0;
    int i = 0;
    bool af = false;
    char c;
    istr = extractx(istr);
    int pdepth = 0;
    while(1){
        c = istr[i];
        if(c == '\0'){
            args = realb(buff,args,bi,ai);
            ai++;
            break;
        }
        if(c == '('){
            pdepth++;
        }
        if(c == ')'){
            pdepth--;
        }
        bool vcb = vchar(c,vc);
        if(pdepth > 0){
            if(c == ' '){
                vcb = true;
            }
        }
        if(vcb){
            af = true;
            buff[bi] = c;
            bi++;
        }
        if(!vcb && af){

            af = false;
            args = realb(buff,args,bi,ai);
            bi = 0;
            ai++;
        }
        i++;
    }  
    args[ai] = NULL;
    //free(istr) <-- makes all the differnce!
    //freeing stack memory (from lex) 
    //messes up the memory in in lex 
    //something to do with aslr?
    return(args);
}

/*
    chop(str arg)
    -- Checks if the argument is a operand character 
    that is foudn in the string vops.
*/ 

bool chop(str arg){
    return(vstr(arg,vops));
}

/*
    chn(str arg)
    -- Checks if the argument is a number.
*/

bool chn(str arg){
    int i = 0;
    str v = "1234567890.";
    while(arg[i] != '\0'){
        if(!vchar(arg[i],v)){
            return(false);
        }       
        i++;
    }
    return(true);
}

/*
    chexpr(str arg)
    -- Checks if the argument is a expression 
    by checking if it starts with a '(' and ends 
    with a ')'.
*/

bool chexpr(str arg){
    int l = 0;
    while(arg[l] != '\0'){
        l++;
    }
    if(arg[0] == '('){
        if(arg[l-1] == ')'){
            return(true);
        }
    }
    return(false);
}

/*
    chkct(str arg)
    -- Returns the type of the argument (see ctype enum).
*/

enum ctype chkct(str arg){
    enum ctype r = none;
    if(chop(arg)){
        return((enum ctype) operand);
    }
    if(chn(arg)){
        return((enum ctype) num);
    }
    if(chexpr(arg)){
        return((enum ctype) expression);
    }
    return((enum ctype) none);
}

child atcn(str arg){
    child k;
    k.type = num;
    double a;
    a = strtod(arg, NULL);
    k.nc = a;
    return(k);
}

child atcop(str arg){
    child k;
    k.type = operand;
    k.oc = arg;
    return(k);
}

child atcexpr(str arg){
    child rc;
    rc.type = expression;
    rc.ec = lex(arg);
    return(rc);
}

child atc(str arg,int ii,int i){
    child r;
    r.type = none; 
    switch(chkct(arg)){
        case num:
            return(atcn(arg));
        case operand:
            return(atcop(arg));
        case expression:
            return(atcexpr(arg));
    }
    return(r);
}

str* test(){
    str* rt = malloc(3 * sizeof(str));
    rt[0] = str_malloc("sqrt");
    rt[1] = str_malloc("100");
    rt[3] = NULL;
    return(rt);
}

//do not use input, use istr instead.
expr lex(str istr){
    str *args = eargs(istr);
    //str* args = test(); // pointer [2] not a null pointer?
    child* kids;
    int nkids = 0;
    int kl = 0;
    int i = 0;
    while(args[i] != NULL){    
        i++;
    }
    kids = malloc((i + 1) * sizeof(child));
    int l = i + 1;
    for(int ii = 0; ii < i;ii++){
       kids[ii] = atc(args[ii],ii,i);
    }
    expr rt;
    rt.kids = kids;
    rt.nkids = i;
    return(rt);
}

/* Computation section */

double add(passHold args){
    double s = 0;
    double a;
    for(int i = 0; i < args.size;i++){
        a = args.list[i];
        s = s + args.list[i];
    }
    return(s);
}

double subtract(passHold args){
    double s = args.list[0];
    double a;
    for(int i = 1; i < args.size;i++){
        a = args.list[i];
        s = s - args.list[i];
    }
    return(s); 
}

double divide(passHold args){
    
}

double multi(passHold args){   
   double s = 1;
    for(int i = 0; i < args.size;i++){
        s = s * args.list[i];
    } 
    return(s);
}

/*
    default behavior for the squareroot function when 
    passed in multiple inputs is the multiply them first,
    taking the output of the result
*/

double squareroot(passHold args){
    double s = multi(args);
    return(sqrt(s));
}

double quit(passHold args){
    toquit = true;
    return(0);
}

double eval(expr rt){
    str oc = rt.kids[0].oc;
    passHold passIn;
    passIn.list = malloc((rt.nkids - 1) * sizeof(double));
    passIn.size = rt.nkids - 1;
    child a;
    for(int i = 1; i < rt.nkids;i++){
        a = rt.kids[i];
        if(a.type == num){
            passIn.list[i-1] = rt.kids[i].nc; 
        }
        if(a.type == expression){
            passIn.list[i-1] = eval(rt.kids[i].ec);
        }
    }
    double t = apply(oc, passIn);
    return(t);
}

double apply(str oc, passHold args){
    if(streq(oc,"+")){
        return(add(args));
    }
    if(streq(oc,"*")){
        return(multi(args));
    } 
    if(streq(oc,"sqrt")){
        return(squareroot(args));
    }
    if(streq(oc,"quit")){
        return(quit(args));
    }
}

int main(){
    vops = get_vops();
    str line;
    while(1){
        printf(">" );
        line = readIn();
        expr rt = lex(line);
        double line_eval = eval(rt);
        if(toquit){
            break;
        }
        printf("\n< %f \n", line_eval);
    }
}