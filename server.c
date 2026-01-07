#include "server.h"
#include "worker.h"
#include "wal.h"
#include "account_store.h"
#include "util.h"
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

int server_start(struct server_config *cfg) {
    account_store_init();
    wal_open(cfg->wal_path);
    wal_replay();

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr = { .sin_family=AF_INET, .sin_addr.s_addr=INADDR_ANY, .sin_port=htons(cfg->port) };
    bind(sock,(void*)&addr,sizeof(addr));
    listen(sock, 128);

    worker_pool_start(cfg->thread_count);

    while(1){
        int c = accept(sock, NULL, NULL);
        worker_submit(c);
    }
    return 0;
}
