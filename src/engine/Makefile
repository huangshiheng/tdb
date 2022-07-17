cc=g++
cxx=-std=c++11
rpcPath=../../../../rpc/
protoPath=/usr/local/protobuf/include/
all:skipList.o
	${cc} -o test_skip test_skip.cpp skipList.cpp ${cxx} 
skipList.o:
	${cc} -c skipList.cpp ${cxx} 