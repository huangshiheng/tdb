cc=g++
cxx=-std=c++11
rpcPath=../../../../rpc/
protoPath=/usr/local/protobuf/include/
all:processer.o
	mv processer.o ../test/tdb
	cp processer.h ../test/tdb/include
processer.o:
	${cc} -c processer.cpp -I ${rpcPath} -I ${protoPath} -L ${rpcPath}rpc/output/lib -lrpc -lrpcpb -lprotobuf ${cxx}