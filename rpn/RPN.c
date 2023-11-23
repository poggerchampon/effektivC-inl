#include <stdio.h>
#include <ctype.h>
#define MAX_SIZE  (10)

int stack[MAX_SIZE];
int items = -1;
int error = 0;
int running = 1;
int line = 1;

void skip_line(char c){
    while(c != '\n'){
            c = getchar();
        }
    line+=1;
    items = -1;
}
void char_err(int c){
printf("line %d: error at %d\n", line, c);
skip_line(c);
}
int empty(){
    return items == -1;
}
int full(){
    return items == MAX_SIZE - 1;
}

int push(int i){
    //printf("pushing\n");
    if(full()){
        char_err(i);
        return -1;
    }
    items+=1;
    stack[items] = i;
    return 1;
}
int pop(){
    //printf("popping\n");
    int res = 0;
    if(empty()){

        return -1;
    }
    res = stack[items];
    items-=1;
    return res;
}
int peek(){
    //printf("peeking\n");
	if(empty()){
		return 0;
	}
    int res = stack[items];
	return res;
}



void line_err(){
    printf("line %d: error at \\n\n", line);
    items = -1;
}
void op_err(int c){
printf("line %d: error at %c\n", line,c);
skip_line(c);
}

int resolve_digit(int c){
    int k = -1;
    int num = 0;
    while(isdigit(c)){
        num = num * 10 +(c - '0');
        c = getchar();
        if(!isdigit(c)){
            k=c;
            
        }
    }
    push(num);
    return k;
}
static int is_operator(int c){
    return c == '-' || c == '+' || c == '*' || c == '/';
}


int whitespace(char c){
    return c == '\n' || c == '\t' || c == ' ';
}
void resolve_whitespace(char c){
    if(c != '\n'){
        return;
    }
    if(items == 0){
        printf("line %d: %d\n",line, pop());
    }else{
        line_err();
    }
    line+=1;
}

int legal_char(char c){
    return isdigit(c) || is_operator(c) || whitespace(c);
}

int calc(char c){
          int rhs = pop();
         int  lhs = pop(); 
         if(rhs == -1 ||lhs == -1){
            op_err(c);
         }
    if (c == '+') {
            push(lhs + rhs); 
            
        }
    if (c == '-') {
        push(lhs - rhs);
       
        } 
    if (c == '*') {
        push(lhs * rhs);
        
        }
     if (c == '/') {
        if (rhs == 0) {
            op_err(c);
        } else {
            push(lhs / rhs);
        }     
       }    
    return 0;
}



int main(void){
    int c = 0, k = -1;
    
    
    while(k != -1 || (c = getchar()) != EOF){ 
        if(k!=-1){
            c = k;
            k =-1;
        }
        if(whitespace(c)){
            resolve_whitespace(c);
            continue;
        }
        if(!legal_char(c)){
            op_err(c);
        }
        if(isdigit(c)){
            k = resolve_digit(c);
        }
        if(is_operator(c)){
            calc(c);
        }
    }
    return 0;
}

