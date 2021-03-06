
#include "zhelpers.h"

int main (void)
{
    void *context = zmq_ctx_new ();

    //  Socket facing clients
    void *frontend = zmq_socket (context, ZMQ_ROUTER);
    int rc = zmq_bind (frontend, "tcp://*:5559");
    assert (rc == 0);

    //  Socket facing services
    void *backend = zmq_socket (context, ZMQ_DEALER);
    rc = zmq_bind (backend, "tcp://*:5560");
    assert (rc == 0);

    // s_catch_signals();
    //  Start the proxy
    zmq_proxy (frontend, backend, NULL);

    printf("Dead");
    //  We never get here…
    zmq_close (frontend);
    zmq_close (backend);
    zmq_ctx_destroy (context);


    return 0;
}