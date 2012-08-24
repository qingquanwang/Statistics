uname_S := $(shell sh -c 'uname -s 2>/dev/null || echo not')

OPT = -O2



AR = ar

TARGET = sample

all: $(TARGET)

%.o:%.c
	$(CC) $(CFLAGS) $(OPT) $(PROF)  -c $<

$(TARGET): sample.o
	$(CC) $(LDFLAGS) $(OPT) $(PROF) sample.o -o $(TARGET)


	
.PHONY: all clean 

clean:
	rm -rf $(TARGET) *.a *.o *.gcda *.gcno *.gcov


gprof:
	$(MAKE) PROF="-pg" OPT=" -O0"
valgrind:
	$(MAKE) PROF="-g" OPT=" -O0"

gcov:
	$(MAKE) PROF="-fprofile-arcs -ftest-coverage" OPT="-O0"



