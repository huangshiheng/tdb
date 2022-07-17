/*
 * @Autor: huangshiheng
 * @Date: 2022-07-09 14:40:02
 * @LastEditTime: 2022-07-10 10:10:20
 * @LastEditors: Please set LastEditors
 */

#include "receiver.h"
#include "../../proto/request.pb.h"
#include <iostream>

namespace tdb {

Receiver::Receiver(std::shared_ptr<ReQueue<rpc::serverStream*> > q, void (*func)(rpc::serverStream* stream)) {
    que = q; 
    event = rpc::eventLoop::getInstance();
    event->setDispatcher(func);
    server = new rpc::rpcServer();
    host = "127.0.0.1";
    port = 8888;
}

Receiver::Receiver(std::string h, int p, std::shared_ptr<ReQueue<rpc::serverStream*> > q, void (*func)(rpc::serverStream* stream)) : Receiver(q, func) {
    host = h;
    port = p;
}

Receiver::~Receiver() {
    event->stop();
    server->~rpcServer();
}

void Receiver::start() {
    server->doListen(host, port);
    event->run();
}

}