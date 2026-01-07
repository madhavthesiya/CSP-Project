#ifndef WAL_H
#define WAL_H
#include <stdint.h>
int wal_open(const char*);
int wal_replay(void);
uint64_t wal_next_seq(void);
int wal_append_deposit(uint64_t,uint64_t,int64_t);
int wal_append_withdraw(uint64_t,uint64_t,int64_t);
int wal_append_transfer(uint64_t,uint64_t,uint64_t,int64_t);
#endif
