#include "protocol.h"
#include "wal.h"
#include "account_store.h"
#include <stdio.h>
#include <string.h>

int protocol_handle(const char *req,char *resp,int r){
    char cmd[16]; unsigned long long a,b; long long amt;
    if(sscanf(req,"%15s %llu %llu %lld",cmd,&a,&b,&amt)<2){ snprintf(resp,r,"ERR"); return 0; }

    if(!strcmp(cmd,"DEPOSIT")){
        uint64_t s=wal_next_seq();
        wal_append_deposit(s,a,amt);
        snprintf(resp,r,"OK %lld",account_get_balance(a));
    } else if(!strcmp(cmd,"WITHDRAW")){
        uint64_t s=wal_next_seq();
        if(wal_append_withdraw(s,a,amt)==0)
            snprintf(resp,r,"OK %lld",account_get_balance(a));
        else snprintf(resp,r,"ERR insufficient");
    } else if(!strcmp(cmd,"TRANSFER")){
        uint64_t s=wal_next_seq();
        if(wal_append_transfer(s,a,b,amt)==0) snprintf(resp,r,"OK");
        else snprintf(resp,r,"ERR");
    } else if(!strcmp(cmd,"BALANCE")){
        snprintf(resp,r,"BALANCE %llu %lld",a,account_get_balance(a));
    } else snprintf(resp,r,"ERR");
    return 0;
}
