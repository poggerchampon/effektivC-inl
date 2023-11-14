#include <stdio.h>
#include <ctype.h>
#define MAX_SIZE  (10)

int stack[MAX_SIZE];
int items = -1;
int error = 0;
int running = 1;
int line = 1;

int empty(){
    return items = -1;
}
int full(){
    return items = MAX_SIZE -1;
}

int push(int i){
    if(full()){
        return 0;
    }
    items++;
    stack[items] = i;
    return 1;
}
int pop(int* i){
    if(empty()){
        return 0;
    }
    *i = stack[items];
    items--;
    return 1;
}
int peek(int* i){
	if(empty()){
		return 0;
	}

	*i = stack[items];
	return 1;
}



static int isdigit_etc(int c){
    return isdigit(c) || c == '-' || c == '+' || c == '*' || c == '/';
}

void skip_line(char c){
    while(c != '\n'){
            c = getchar();
        }
    line++;
}

int main(void){
    int c = 0, num = 0;

    while(running){ //currentlky never stopping
       start:
       c = getchar();
       if(!isdigit_etc(c)){ //not allowed character
        printf("Line %d: error at %c\n", line, c);
        skip_line(c);
        goto start;
       }else{ //otherwise is allowed
         if(full()){ //check if stack full
            printf("Line %d: error at %c\n", line, c);
            skip_line(c);
            goto start;
         }
         
         while(isdigit(c)){ //is a digit
            num = num * 10 + (c - '0');
            c = getchar();
         }
         
         if(!push(num)){ // pushing to stack and error if no success
            printf("Line %d: error at %d\n", line, num);
            skip_line(c);
            goto start;
         }
        
       }    

       

    }
    return 0;
}