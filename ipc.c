#include "ipc.h"
#include "process.h"


/** Send a message to the process specified by id.
 *
 * @param self    Any data structure implemented by students to perform I/O
 * @param dst     ID of recepient
 * @param msg     Message to send
 *
 * @return 0 on success, any non-zero value on error
 */
int send(void * self, local_id dst, const Message * msg){
    ProcessDescription * pd = (ProcessDescription *) self;
    if (write(pd->pipes[pd->ld][dst].write, msg, sizeof(MessageHeader) + msg->s_header.s_payload_len) <= 0) {
        return 1;
    }
    return 0;
}

//------------------------------------------------------------------------------

/** Send multicast message.
 *
 * Send msg to all other processes including parrent.
 * Should stop on the first error.
 *
 * @param self    Any data structure implemented by students to perform I/O
 * @param msg     Message to multicast.
 *
 * @return 0 on success, any non-zero value on error
 */
int send_multicast(void * self, const Message * msg){
    ProcessDescription * pd = (ProcessDescription *) self;
    for(local_id i = 0; i < pd->size; i++){
        if(i != pd->ld) {
            if(send(pd, i, msg) != 0) return 1;
        }
    }
    return 0;
}

//------------------------------------------------------------------------------

/** Receive a message from the process specified by id.
 *
 * Might block depending on IPC settings.
 *
 * @param self    Any data structure implemented by students to perform I/O
 * @param from    ID of the process to receive message from
 * @param msg     Message structure allocated by the caller
 *
 * @return 0 on success, any non-zero value on error
 */
int receive(void * self, local_id from, Message * msg){
    ProcessDescription * pd = (ProcessDescription *) self;
    if(read(pd->pipes[from][pd->ld].read, &msg->s_header, sizeof(MessageHeader)) < 0) return 1;
    if(read(pd->pipes[from][pd->ld].read, msg->s_payload, msg->s_header.s_payload_len) < 0) return 1;
    return 0;
}

//------------------------------------------------------------------------------

/** Receive a message from any process.
 *
 * Receive a message from any process, in case of blocking I/O should be used
 * with extra care to avoid deadlocks.
 *
 * @param self    Any data structure implemented by students to perform I/O
 * @param msg     Message structure allocated by the caller
 *
 * @return 0 on success, any non-zero value on error
 */
int receive_any(void * self, Message * msg){
    return 1;
}


