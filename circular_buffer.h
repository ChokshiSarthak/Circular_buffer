#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include<iostream>
#include<pthread.h>

class Circ_buf_t{

public:

     static void *ProducerHelper(void *obj);
     static void *ConsumerHelper(void *obj);
     void Produce();
     void Consume();
     void Init();
     Circ_buf_t();
     ~Circ_buf_t();

private:

     struct node{
          int hash;
          int status;
     };
     node q_node[1024];
     int start_index;
     int num_full;
     static const int qsize = 10;
     int data[qsize];
     pthread_mutex_t m_mutex;
     pthread_cond_t m_notfull;
     pthread_cond_t m_nonempty;
     pthread_t produce_thread, consume_thread;

};
     
#endif
