#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>
#include "process.h"
#include "child.h"
#include "util.h"

void wait_children(void) {
    pid_t child_pid = 0;
    int status = 0;
    while ((child_pid = wait(&status)) > 0) {
        printf("child process %d finished with %d.\n", child_pid, status);
    }
}

int main(int argc, char* argv[]) {
    local_id n = parse(argc, argv);
    ProcessDescription pd = init_process_description(n);
    fflush(pd.pipes_log);
    for(local_id i = 1; i <= n;  i++){
        switch(fork()){
            case 0:
                pd.ld = i;
                child_routine(pd);
                exit(0);
            case -1:
                printf("error\n");
                exit(1);
            default:
                wait_children();
                break;
        }
    }
    fclose(pd.events_log);
    fclose(pd.pipes_log);

    return 0;
}


