#ifndef AS_H
#define AS_H
#include <stdint.h>
int account_store_init(void);
int64_t account_get_balance(uint64_t);
int account_apply_deposit(uint64_t,int64_t,uint64_t);
int account_apply_withdraw(uint64_t,int64_t,uint64_t);
int account_apply_transfer(uint64_t,uint64_t,int64_t,uint64_t);
#endif
