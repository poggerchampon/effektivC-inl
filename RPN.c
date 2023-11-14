#include <stdio.h>
#include <ctype.h>
#define MAX_SIZE  (10)

int stack[MAX_SIZE];
int items = -1;
int error = 0;
int running = 1;

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

int main(int argc, char** argv){
    while(running){
        
    }
    return 0;
}