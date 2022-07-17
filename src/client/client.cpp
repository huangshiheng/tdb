/*
 * @Autor: huangshiheng
 * @Date: 2022-07-09 10:17:43
 * @LastEditTime: 2022-07-09 18:56:03
 * @LastEditors: Do not edit
 */

#include "client.h"
#include "../../proto/request.pb.h"
#include <iostream>

namespace tdb {
    tdbClient::tdbClient() { }

    tdbClient::tdbClient(std::string h, int p) {
        host = h;
        port = p;
        init();
    }

    tdbClient::tdbClient(std::string h, int p, void (*f)(rpc::clientStream*)) : tdbClient(h, p) {
        fun = f;
    }

    tdbClient::~tdbClient() {
        client->~clientStream();
    }

    void tdbClient::setHost(std::string h) {
        host = h;
    }

    void tdbClient::setPort(int p) {
        port = p;
    }

    void tdbClient::setFunc(void (*f)(rpc::clientStream*)) {
        fun = f;
    }

    void tdbClient::init() {
        event = rpc::eventLoop::getInstance();
        client = new rpc::clientStream();
        client->doConnect(host, port);
    }
 
    void tdbClient::sendData(std::string data, int choice) {
        rpc::rpcRequest re;
        re.set_head(choice);
        re.set_msg(data);
        std::string s;
        re.SerializeToString(&s);
        client->setData(s, fun);
    }
}