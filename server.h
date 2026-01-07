#ifndef SERVER_H
#define SERVER_H

struct server_config {
    int port;
    const char *wal_path;
    const char *snapshot_path;
    int thread_count;
};

int server_start(struct server_config *cfg);

#endif
