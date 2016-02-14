#include "circular_buffer.h"

int main(){

     Circ_buf_t *c_buf;
     c_buf = new Circ_buf_t();
     if(c_buf)
          std::cout << "Successfully allocated c_buf: " << std::endl;
     else
          std::cout << "failed: " << "\n";
    
     c_buf->Init();

     delete c_buf;
     return 0;

}     
