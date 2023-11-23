#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "error.h"
#include "poly.h"


struct poly_t {
    int c;
    int exp;
    poly_t* next;
};

poly_t* getTail(poly_t* cur) 
{ 
    while (cur != NULL && cur->next != NULL) 
        cur = cur->next; 
    return cur; 
} 


void swap(poly_t* p1, poly_t* p2){
    int tempc = p1->c;
    int tempexp = p1->exp;
    p1->c = p2->c;
    p1->exp = p2->exp;
    p2->c = tempc;
    p2->exp = tempexp;
}
void sort(poly_t* p){
   poly_t* start = p;
   poly_t* traverse, *min;

   while(start->next){
    min = start;
    traverse = start->next;
    while(traverse){
        if(min->exp < traverse->exp){
            min = traverse;
        }
        traverse = traverse->next;
    }
    swap(start, min);
    start = start->next;
   }

}


void free_poly(poly_t* p){
    if(p == NULL){
        return;
    }
    free_poly(p->next);
    free(p);
}
void simplify(poly_t* p){
     poly_t *running, *temp;

  if (p == NULL) {
    return;
  }

  while (p != NULL) {
    running = p;
    while (running->next != NULL) {
      if (running->next->exp == p->exp) {
        p->c += running->next->c;

        temp = running->next;
        running->next = running->next->next;
        free(temp);
      }
      running = running->next;
    }
    p = p->next;
  }
    
}

poly_t* mul(poly_t* p, poly_t* q){
    poly_t* res, *pstart, *qstart;
    res = malloc(sizeof(poly_t));
    pstart = res;
    qstart = q;
    while(p != NULL){
        while(q != NULL){
            res->c = p->c * q->c;
            res->exp = p->exp + q->exp;
            if(p->next == NULL && q->next ==NULL){
                res->next = NULL;
            }else{
                res->next = malloc(sizeof(poly_t));
                res = res->next;
            }
            q = q->next;
        }
        p = p->next;
        q = qstart;      
    }
    
    simplify(pstart);
    sort(pstart);
    return pstart;
}

void print_poly(poly_t* p){
    if(p==NULL){
        printf("\n");
        return;
    }
    int co = p->c;

    if(co !=1 || p->exp==0){
        if(co<0){
            co = -co;
             printf(" - %d",co);
        }else{
           printf("%d",co); 
        }    
    }
    
    if(p->exp == 0){
        
    }else if(p->exp != 1){
       printf("x^%d", p->exp); 
    }else{
        printf("x");
    }

    if(p->next !=NULL){
    if(p->next->c>0){
        printf(" + ");
    }
    }
    print_poly(p->next);
    
}

static int expo(const char *s, int *i){
    int e = 0;

    if(s[*i] != 'x'){
        return 0;
    }else if(s[++(*i)]!='^'){
        return 1;
    }

    while(s[*i]!='\0' && s[*i] != ' '){
        if (isdigit(s[*i])) {
        e = e * 10 + s[*i]- '0';
        }
        ++(*i);
    }

    return e;

}
static int coeff(const char *s, int *i){
    int negative = 0, c = 0;
    while(s[*i]!='\0' && s[*i] != 'x'){
        if(isdigit(s[*i])){
        c = c * 10 + (s[*i]- '0');
        }else if(s[*i]=='-'){
            negative = 1;
        }
        ++(*i);
    }
    if(c == 0){
        return 1;
    }
    if(negative){
     c *= -1;
    }
    return c;
}

poly_t* new_poly_from_string(const char *s){
    poly_t *poly;
    int i = 0;
    if(*s == '\0'){
        return NULL;
    }

    poly = malloc(sizeof(poly_t));

    poly->c = coeff(s, &i);
    poly->exp = expo(s, &i);
    poly->next = new_poly_from_string(s + i);
    return poly;
}