#include "server.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

int main(int argc, char **argv) {
    struct server_config cfg = {
        .port = 15000,
        .wal_path = "data/wal.log",
        .snapshot_path = "data/snap.json",
        .thread_count = 8
    };

    mkdir("data", 0755);
    server_start(&cfg);
    return 0;
}
