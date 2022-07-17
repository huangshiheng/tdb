cc=g++
cxx=-std=c++11
rpcPath=../../../../rpc/
protoPath=/usr/local/protobuf/include/
all:
	cp /usr/local/protobuf/lib/libprotobuf.a .
	${cc} -o cli cli.cpp tdb/request.pb.o tdb/client.o -I ${rpcPath} -I ${protoPath} -L . -L ${rpcPath}rpc/output/lib -lrpc -lrpcpb -lprotobuf ${cxx}
	${cc} -o ser ser.cpp tdb/request.pb.o tdb/receiver.o tdb/processer.o -I ${rpcPath} -I ${protoPath} -L . -L ${rpcPath}rpc/output/lib -lrpc -lrpcpb -lprotobuf ${cxx} -lpthread
	mv cli ser bin
	rm -rf libprotobuf.a
clean:
	rm -rf bin/* tdb/*