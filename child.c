//
// Created by ubuntu on 9/25/23.
//


#include "child.h"

void child_routine(ProcessDescription pd){
    log_process_startup(&pd);
    send_everyone(STARTED, &pd);
    receive_from_everyone(STARTED, &pd);
    log_start_message_receival(&pd);
    log_process_completion(&pd);
    send_everyone(DONE, &pd);
    receive_from_everyone(DONE, &pd);
    log_completion_message_receival(&pd);
    exit(0);
}
