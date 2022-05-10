
CXX      = g++   
LIBGAB   = /home/gabriel/lib/libgab/

CXXFLAGS = -Wall -lm -O3 -lz -I${LIBGAB} -I${LIBGAB}/gzstream/ -c
LDFLAGS  = -lz


all: testFD pipeFD pipeFDcout pipeFDcoutcin

testFD.o:	testFD.cpp
	${CXX} ${CXXFLAGS} testFD.cpp

testFD:	testFD.o ${LIBGAB}utils.o  
	${CXX} -o $@ $^ $(LDLIBS) $(LDFLAGS)

pipeFD.o:	pipeFD.cpp
	${CXX} ${CXXFLAGS} pipeFD.cpp

pipeFD:	pipeFD.o ${LIBGAB}utils.o  
	${CXX} -o $@ $^ $(LDLIBS) $(LDFLAGS)

pipeFDcout.o:	pipeFDcout.cpp
	${CXX} ${CXXFLAGS} pipeFDcout.cpp

pipeFDcout:	pipeFDcout.o ${LIBGAB}utils.o  
	${CXX} -o $@ $^ $(LDLIBS) $(LDFLAGS)

pipeFDcoutcin.o:	pipeFDcoutcin.cpp
	${CXX} ${CXXFLAGS} pipeFDcoutcin.cpp

pipeFDcoutcin:	pipeFDcoutcin.o ${LIBGAB}utils.o  
	${CXX} -o $@ $^ $(LDLIBS) $(LDFLAGS)

clean :
	rm -f testFD.o testFD pipeFD.o pipeFD pipeFDcout.o pipeFDcout pipeFDcoutcin.o pipeFDcoutcin

