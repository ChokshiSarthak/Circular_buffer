#include "circular_buffer.h"

using namespace std;

Circ_buf_t::Circ_buf_t(){

     num_full = 0;
     start_index = 0;
     pthread_mutex_init(&m_mutex,NULL);
     pthread_cond_init(&m_notfull,NULL);
     pthread_cond_init(&m_nonempty,NULL);
};


Circ_buf_t::~Circ_buf_t(){

     pthread_mutex_destroy(&m_mutex);
     pthread_cond_destroy(&m_notfull);
     pthread_cond_destroy(&m_nonempty);

}

void Circ_buf_t::Init(){

     cout << __FUNCTION__ << endl;
     pthread_create(&produce_thread,NULL,&Circ_buf_t::ProducerHelper,this);
     pthread_create(&consume_thread,NULL,&Circ_buf_t::ConsumerHelper,this);
     pthread_join(produce_thread,NULL);
     pthread_join(consume_thread,NULL);
}

void *Circ_buf_t::ProducerHelper(void *obj){

     static_cast<Circ_buf_t*>(obj)->Produce();
     return NULL;
}

void Circ_buf_t::Produce(){
     
     cout << __FUNCTION__ << endl;
     pthread_mutex_lock(&m_mutex);
     while(1){
          while(num_full == Circ_buf_t::qsize){
               pthread_cond_wait(&m_notfull,&m_mutex);
          }
          q_node[(start_index + num_full) % Circ_buf_t::qsize].hash = 0;
          q_node[(start_index + num_full) % Circ_buf_t::qsize].status = 1;
          num_full++;
          pthread_cond_signal(&m_nonempty);
          pthread_mutex_unlock(&m_mutex);
     }
}

void *Circ_buf_t::ConsumerHelper(void *obj){

     static_cast<Circ_buf_t*>(obj)->Consume();
}

void Circ_buf_t::Consume(){

     cout << __FUNCTION__ << endl;
     pthread_mutex_lock(&m_mutex);
     while(1){
          while(num_full == 0){
               pthread_cond_wait(&m_nonempty,&m_mutex);
          }
          cout << q_node[(start_index)].hash << endl;
          cout << q_node[(start_index)].status << endl;
          num_full--;
          pthread_cond_signal(&m_notfull);
          pthread_mutex_unlock(&m_mutex);
     }
}

  


 








 
             
 










