cc=g++
cxx=-std=c++11
rpcPath=../../../../rpc/
protoPath=/usr/local/protobuf/include/
all:receiver.o
	mv receiver.o ../test/tdb
	cp receiver.h queue.h ../test/tdb/include
receiver.o:
	${cc} -c receiver.cpp -I ${rpcPath} -I ${protoPath} -L ${rpcPath}rpc/output/lib -lrpc -lrpcpb -lprotobuf ${cxx}