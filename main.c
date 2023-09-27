#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "process.h"
#include "util.h"

int main(int argc, char* argv[]) {
    local_id n = parse(argc, argv);
    ProcessDescription pd = init_process_description(n);
    for(local_id i = 1; i <= n;  i++){
        switch(fork()){
            case 0:
                pd.ld = i;
                child_routine(pd);
            case -1:
                printf("error\n");
                exit(1);
            default:
                break;
        }
    }
    parent_routine(pd);
    return 0;
}


