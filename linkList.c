#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define CR '\n'

/****
 * 双向循环链表，可用于栈和队列实现
 * 存在头节点，头节点值代表长度
 * 任何面向用户交互均从1开始
 * 右边 = next = 1
 * 左边 = prev = last
 */

typedef int ElemType;

typedef struct node{
    ElemType data;
    struct node *prev;
    struct node *next;
} Node, *Link;


Link link_init(){
    Link L = malloc(sizeof(Node));

    L->data = 0;
    L->prev = L->next = L; //自指向
    return L;
}

void node_insert(Link p, ElemType e, bool after){

    Node *new = malloc(sizeof(Node));
    new->data = e;
    
    if (after) {
        new->next = p->next;
        new->prev = p;
        p->next->prev = new;
        p->next = new;
    }else{
        new->prev = p->prev;
        new->next = p;
        p->prev->next = new;
        p->prev = new;
    }
}

void node_delete(Link p, ElemType *e){
    *e = p->data;
    p->prev->next = p->next;
    p->next->prev = p->prev;

    p->next = p->prev = NULL;
    free(p);
}

Link node_find(Link L, int i){

    if (L->data <= 0 || i>L->data || i<1 ) return NULL;
    if (L->data == 1) return L->next;

    //判断从那边走比较近
    int cur = 0;
    int length = L->data;
    int mid = (int)length/2;

    Link ret = NULL;

    //大的走prev, 小的走next
    if ( i > mid ){
        printf("select right");
        cur = length;
        ret = L->prev;

        while(cur-- > i){
            ret = ret->prev;
        }
    } else {
        printf("select left");
        cur = 1;
        ret = L->next; 
        
        while(cur++ < i){
            ret = ret->next;
        }
    }

    return ret;
}


void link_rpush(Link L, ElemType e){
    node_insert(L, e, false);
    L->data++;
}

void link_lpush(Link L, ElemType e){
    node_insert(L, e, true);
    L->data++;
}

void link_rpop(Link L, ElemType *e){
    if (L->data == 0) return;
    
    node_delete(L->prev, e);
    L->data--;
}

void link_lpop(Link L, ElemType *e){
    if (L->data == 0) return;
    
    node_delete(L->next, e);
    L->data--;
}

void link_insert(Link L, int i, ElemType e){
    if ( i<1 || i>L->data+1 ) return;
    if ( i == 1 ) return link_lpush(L, e);
    if ( i == L->data+1 ) return link_rpush(L, e);
    
    Link p = node_find(L, i);
    node_insert(p, e, false);
    L->data++;
    return;
}

void link_delete(Link L, int i, ElemType *e){
    if ( i<1 || i>L->data ) return;
    if ( i == 1 ) return link_lpop(L, e);
    if ( i == L->data ) return link_rpop(L, e);

    Link p = node_find(L, i);
    node_delete(p, e);
    L->data--;
    return;
}

void link_print(Link L){
    Link p = L;
    Link s = L; 
    
    p = p->next;

    printf("len: %d ", L->data);

    while( p != s){
        printf("[%d]", p->data);
        p = p->next;
    }

    printf("\n");
}


int main(){
    Link L = link_init();

    link_print(L);
    link_lpush(L, 333);
    link_lpush(L, 444);
    link_lpush(L, 555);
    link_lpush(L, 666);
    link_lpush(L, 777);
    link_lpush(L, 888);
    link_lpush(L, 999);
    link_print(L);
    link_rpush(L, 333);
    link_rpush(L, 444);
    link_rpush(L, 555);
    link_rpush(L, 666);
    link_rpush(L, 777);
    link_rpush(L, 888);
    link_rpush(L, 999);
    link_print(L);

    ElemType * e;
    link_rpop(L, e);
    link_rpop(L, e);
    link_rpop(L, e);
    link_lpop(L, e);
    link_lpop(L, e);
    link_print(L);
    
    link_insert(L, 1, 777);
    link_insert(L, 2, 777);
    link_insert(L, 8, 111);
    link_insert(L, 0, 123);
    link_print(L);

    link_delete(L, 1, e);
    link_delete(L, 5, e);
    link_delete(L, 7, e);
    link_delete(L, 9, e);
    link_print(L);
    return 0;
}
