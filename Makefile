
COMPILER         = g++
OPTIMIZATION_OPT = -O3
OPTIONS          = -g -ggdb -pthread -std=c++11 -W -Wall -W -Wno-long-long -lrt  $(OPTIMIZATION_OPT)
LINKER_OPT       = -L/usr/lib -lstdc++
#VEC_FLAGS		 = -msse2 -msse4.1 -mpclmul
#PROBE_T		 = 256

PREDEF		 	 = -D
OUT_DIR          = ./bin/

DEP = data.h
DC 	= data.cc test.cc

BUILD+=CLUSTERING

all: $(BUILD)


CLUSTERING: $(DEP)
	$(COMPILER) $(OPTIONS) -o $(OUT_DIR)test $(DC) $(LINKER_OPT) $(DEFINE_1)



clean:
	
	
#
# The End !
#







