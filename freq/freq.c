#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

typedef struct str_t str_t;

struct str_t{
    char* word;
    int count;
    struct str_t* next;
};

int line = 0;
int nextline = 1;
char* read(){
    int c;
    size_t length = 0;
   line+=1;
   size_t cap = 10;
   char* str = malloc(sizeof(char)*cap);
    
    while((c=getchar())!='\n' && c != EOF){
         if (length + 1 >= cap) {
            cap *= 2;
            str = realloc(str, sizeof(char) * cap);
        }
        str[length++] = (char) c;
    }
    str[length] = '\0';
    if(length == 0){
        nextline = 0;
    }
    
    
    return str;
}
//int find(word, str_t* s){}

void delete(char* word, str_t* s){
    
    str_t* temp, *start;
    char* tempstr;
    start = s;
   
    if(s->count == 0){
        printf("trying to delete %s: not found\n", word);
        free(word);
        return;
    }
    if(s->next == NULL){
        if(!strcmp(s->word, word)){
                free(s->word);
        
                s->count = 0;
                printf("trying to delete %s: deleted\n",word);
                free(word);
                return;
        }else{
            printf("trying to delete %s: not found\n", word);
            free(word);
            return;
        }

    }
    
    while(s->next!=NULL){ 
        if(!strcmp(s->next->word, word)){
                temp = s->next;
                tempstr = s->next->word;
                s->next = s->next->next;
                free(tempstr);
                free(temp);
                printf("trying to delete %s: deleted\n",word);
                free(word);
                s=start;
                return;
        }
        s = s->next;
    }
    printf("trying to delete %s: not found\n", word);
    free(word);
    s = start;
}
void add(char* word, str_t* s){
    str_t* start;
    
    int found = 0;
    start = s;

    if(s->count == 0){
        s->count = 1;

        s->word = word;
        s->next = NULL;
        printf("added %s\n", word);
        return;
    }
    
    if(s->next == NULL){
        if(!strcmp(s->word, word)){
                s->count +=1;
                printf("counted %s\n", word);
                free(word);
                return;
        }else{
            
        }
    }
    
    
    while(s->next != NULL){
        if(!strcmp(s->next->word, word)){
            s->next->count+=1;
            found = 1;
            printf("counted %s\n", word);
            free(word);
        }
        
        s = s->next;
    }
    if(!found){
        s->next = malloc(sizeof(str_t));
        s->next->count = 1;
        s->next->word = word;
        s->next->next = NULL;
        printf("added %s\n", word);
    }
    s = start;
}
int is_prime(){
    int i;
    int temp = line;
    if(temp==1){
        return 0;
    }
    for(i=2; i<=temp/2; i++){
        if(temp % i == 0){

            return 0;
        }
    }
    return 1;
}

void free_nodes(str_t* s){
    if(s == NULL){
        return;
    }

    free_nodes(s->next);
    free(s->word);
    free(s);
    
}
void print_highest(str_t* s){
    int count = 0;
    char* word = s->word;
    str_t* temp = s;
    while(temp!=NULL){
        if(temp->count > count){
            word = temp->word;
            count = temp->count;
        }else if(temp->count == count){
            int res = strcmp(word, temp->word);
            if(res > 0){
                word = temp->word;
                count = temp->count;
            }
        }
        temp = temp->next;
    }
    printf("result: %s %d\n",word,count);
    
}


int main(void){
    str_t* s = malloc(sizeof(str_t));
    s->count = 0;
    s->word = NULL;
    while(nextline){
    char* str = read();
    if(!nextline){
        print_highest(s);
        free(str);
    }else if(is_prime()){
        delete(str, s);
    }else{
        add(str, s);
    }
   }
   
    free_nodes(s);
}