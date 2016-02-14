CCFLAGS = g++ -Wall
LDFLAGS = -lpthread
SRC = main.cc circular_buffer.cc
OBJ = $(SRC:.cc=.o)

circularbuffer: $(OBJ)
	$(CCFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY : clean

clean:
	rm -f $(OBJ) circularbuffer


