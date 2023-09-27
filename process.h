//
// Created by ubuntu on 9/25/23.
//

#ifndef PA1_PROCESS_H
#define PA1_PROCESS_H

#include <unistd.h>
#include <stdio.h>
#include "ipc.h"

typedef struct{
    int write;
    int read;
} my_pipe;

typedef struct {
    my_pipe** pipes;
    local_id ld;
    local_id size;
    FILE * events_log;
    FILE * pipes_log;
} ProcessDescription;

#endif //PA1_PROCESS_H
