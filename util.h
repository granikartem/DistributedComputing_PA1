//
// Created by ubuntu on 9/26/23.
//

#ifndef PA1_UTIL_H
#define PA1_UTIL_H

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "process.h"
#include "child.h"
#include "common.h"
#include "logging.h"

local_id parse(int argc, char* argv[]);

ProcessDescription init_process_description(local_id n);

void send_everyone(MessageType msg_type, ProcessDescription * pd);

void receive_from_everyone(MessageType msg_type, ProcessDescription * pd);

#endif //PA1_UTIL_H
