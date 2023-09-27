#include "util.h"

local_id parse(int argc, char* argv[]){
    int n;
    int a = getopt(argc, argv, "p:");
    if(a == 'p'){
        n = atoi(optarg);
    }else{
        exit(EXIT_FAILURE);
    }
    return (local_id) n;
}

ProcessDescription init_process_description(local_id n){
    ProcessDescription pd;
    pd.ld = 0;
    pd.size = n + 1;
    pd.events_log = fopen(events_log, "a+");
    pd.pipes_log = fopen(pipes_log, "a+");
    pd.pipes = (my_pipe ** ) malloc(sizeof(my_pipe *) * (n + 1));
    for(int i = 0; i < n + 1; i++){
        pd.pipes[i] = (my_pipe *) malloc(sizeof(my_pipe) * (n + 1));
    }
    for(int i = 0; i < n + 1; i++){
        for(int j = 0; j < n + 1; j++){
            if(i != j) {
                int p[2];
                if(pipe(p) == 0) {
                    pd.pipes[i][j].read = p[0];
                    pd.pipes[i][j].read = p[1];
                    log_pipe_opening(pd.pipes_log, i, j);
                }else{
                    exit(1);
                }
            }
        }
    }
    return pd;
}

void send_everyone(MessageType msg_type, ProcessDescription * pd){
    MessageHeader header ={.s_magic = MESSAGE_MAGIC, .s_type = msg_type};
    Message msg = {.s_header = header};
    int len = 0;
    if(msg_type == STARTED){
        len = sprintf(msg.s_payload, log_started_fmt, pd->ld, getpid(), getppid());
    }else if(msg_type == DONE) {
        len = sprintf(msg.s_payload, log_done_fmt, pd->ld);
    }
    header.s_payload_len = len;
    send_multicast(pd, &msg);
}

void receive_from_everyone(MessageType msg_type, ProcessDescription * pd){
    local_id n = pd->size;
    for(local_id i = 1; i < n; i++){
        if(i != pd->ld){
            Message msg;
            receive(pd, i, &msg);
            if(msg.s_header.s_type != msg_type){
                printf("wrong message type\n");
                if(msg.s_header.s_type == STARTED){
                    printf("STARTED\n");
                }else if(msg.s_header.s_type == STARTED == DONE){
                    printf("DONE\n");
                }else{
                    printf("nothing\n");
                }
            }
        }
    }
}
