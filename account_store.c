#include "account_store.h"
#include <pthread.h>
#include <stdlib.h>

typedef struct A { uint64_t id; int64_t bal; pthread_mutex_t m; struct A*next;}A;
#define SZ 4096
static A*tab[SZ];

static A*get(uint64_t id){
    int h=id%SZ;
    A*c=tab[h];
    while(c){ if(c->id==id)return c; c=c->next;}
    c=calloc(1,sizeof(A)); c->id=id; pthread_mutex_init(&c->m,0); c->next=tab[h]; tab[h]=c;
    return c;
}

int account_store_init(void){ for(int i=0;i<SZ;i++)tab[i]=0; return 0; }

int64_t account_get_balance(uint64_t id){
    A*a=get(id); pthread_mutex_lock(&a->m); int64_t b=a->bal; pthread_mutex_unlock(&a->m); return b;
}

int account_apply_deposit(uint64_t id,int64_t amt,uint64_t s){
    A*a=get(id); pthread_mutex_lock(&a->m); a->bal+=amt; pthread_mutex_unlock(&a->m); return 0;
}

int account_apply_withdraw(uint64_t id,int64_t amt,uint64_t s){
    A*a=get(id); pthread_mutex_lock(&a->m);
    if(a->bal<amt){ pthread_mutex_unlock(&a->m); return -1;}
    a->bal-=amt; pthread_mutex_unlock(&a->m); return 0;
}

int account_apply_transfer(uint64_t a,uint64_t b,int64_t amt,uint64_t s){
    if(a==b)return 0;
    uint64_t lo=a<b?a:b, hi=a<b?b:a;
    A*A1=get(lo), *A2=get(hi);
    pthread_mutex_lock(&A1->m);
    pthread_mutex_lock(&A2->m);
    if(a<b){ if(A1->id!=a?A2->bal<amt:A1->bal<amt){ pthread_mutex_unlock(&A2->m); pthread_mutex_unlock(&A1->m); return -1;} }
    // Simplified apply
    get(a)->bal -= amt;
    get(b)->bal += amt;
    pthread_mutex_unlock(&A2->m); pthread_mutex_unlock(&A1->m);
    return 0;
}
