#include "worker.h"
#include "protocol.h"
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

static int q[1024],h,t;
static pthread_mutex_t m=PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t c=PTHREAD_COND_INITIALIZER;

void *thr(void *_) {
    while(1){
        pthread_mutex_lock(&m);
        while(h==t) pthread_cond_wait(&c,&m);
        int fd=q[h++%1024];
        pthread_mutex_unlock(&m);

        FILE *f=fdopen(fd,"r+");
        char buf[256],resp[256];
        while(fgets(buf,256,f)){
            protocol_handle(buf,resp,256);
            fprintf(f,"%s
",resp);
            fflush(f);
        }
        fclose(f);
    }
}

void worker_pool_start(int n){
    while(n--) {
        pthread_t thid;
        pthread_create(&thid,NULL,thr,NULL);
    }
}

void worker_submit(int fd){
    pthread_mutex_lock(&m);
    q[t++%1024]=fd;
    pthread_cond_signal(&c);
    pthread_mutex_unlock(&m);
}
