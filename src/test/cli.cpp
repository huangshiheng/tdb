/*
 * @Autor: huangshiheng
 * @Date: 2022-07-09 17:41:31
 * @LastEditTime: 2022-07-16 10:58:20
 * @LastEditors: Please set LastEditors
 */

#include "../client/client.h"
#include "tdb/include/request.pb.h"

void func(rpc::clientStream* cli) {
    std::string s;
    cli->getData(s);
    rpc::rpcResponce res;
    res.ParseFromString(s);
    if(res.has_msg()) {
        std::cout << "client read : " << res.msg() << std::endl;
    }
    rpc::eventLoop::getInstance()->stop();
}

int main() {
    tdb::tdbClient* client = new tdb::tdbClient("127.0.0.1", 1234, func);
    tdb::proto::TkvRequest kvr;
    kvr.set_type(tdb::proto::FIND);
    
    tdb::proto::KV* kv = kvr.mutable_kv();
    kv->set_key("Hello Worldss");
    
    std::string s;
    kvr.SerializeToString(&s); // SerializeToString
    
    client->sendData(s, 1);
    rpc::eventLoop::getInstance()->run();
    return 0;
}