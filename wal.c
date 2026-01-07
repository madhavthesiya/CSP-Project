#include "wal.h"
#include "account_store.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

static char path[256];
static FILE *f;
static uint64_t seq=1;

int wal_open(const char *p){
    strncpy(path,p,255);
    f=fopen(path,"a+");
    return f?0:-1;
}
uint64_t wal_next_seq(void){ return seq++; }

static void append(const char *s){
    fputs(s,f); fputc('\n',f);
    fflush(f); fsync(fileno(f));
}

int wal_append_deposit(uint64_t s,uint64_t a,int64_t amt){
    char buf[128]; sprintf(buf,"%llu DEPOSIT %llu 0 %lld",s,a,amt);
    append(buf);
    account_apply_deposit(a,amt,s);
    return 0;
}
int wal_append_withdraw(uint64_t s,uint64_t a,int64_t amt){
    char buf[128]; sprintf(buf,"%llu WITHDRAW %llu 0 %lld",s,a,amt);
    append(buf);
    return account_apply_withdraw(a,amt,s);
}
int wal_append_transfer(uint64_t s,uint64_t a,uint64_t b,int64_t amt){
    char buf[128]; sprintf(buf,"%llu TRANSFER %llu %llu %lld",s,a,b,amt);
    append(buf);
    return account_apply_transfer(a,b,amt,s);
}

int wal_replay(void){
    FILE *r=fopen(path,"r"); if(!r)return -1;
    char line[256],op[16]; unsigned long long a,b; long long amt,s;
    while(fgets(line,256,r)){
        if(sscanf(line,"%llu %15s %llu %llu %lld",&s,op,&a,&b,&amt)==5){
            if(!strcmp(op,"DEPOSIT")) account_apply_deposit(a,amt,s);
            else if(!strcmp(op,"WITHDRAW")) account_apply_withdraw(a,amt,s);
            else if(!strcmp(op,"TRANSFER")) account_apply_transfer(a,b,amt,s);
        }
    }
    fclose(r);
    return 0;
}
