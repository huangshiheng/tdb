cc=g++
cxx=-std=c++11
rpcPath=../../../../rpc/
protoPath=/usr/local/protobuf/include/
all:client.o
	mv client.o ../test/tdb
	cp client.h ../test/tdb/include
client.o:
	${cc} -c client.cpp -I ${rpcPath} -I ${protoPath} -L ${rpcPath}rpc/output/lib -lrpc -lrpcpb -lprotobuf ${cxx}
clean:
	rm -rf client.o