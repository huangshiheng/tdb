cc=g++
cxx=-std=c++11
rpcPath=../../../../rpc/
protoPath=/usr/local/protobuf/
all:
	/usr/local/protobuf/bin/protoc --cpp_out=./ request.proto
	/usr/local/protobuf/bin/protoc --cpp_out=./ ip.proto
	${cc} -c request.pb.cc -I ${protoPath}include -L ${protoPath}lib -lprotobuf ${cxx}
	cp request.pb.o ../src/test/tdb/
	cp request.pb.h ../src/test/tdb/include