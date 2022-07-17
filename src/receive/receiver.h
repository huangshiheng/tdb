/*
 * @Autor: huangshiheng
 * @Date: 2022-07-09 14:05:11
 * @LastEditTime: 2022-07-10 10:11:49
 * @LastEditors: Please set LastEditors
 */

#pragma once

#include "rpc/output/include/serverStream.h"
#include "rpc/output/include/eventLoop.h"
#include "rpc/output/include/rpcServer.h"
#include "rpc/output/include/service.pb.pb.h"
#include "queue.h"
#include <memory>
#include <string>

namespace tdb {
    //class rpc::serverStream;

    class Receiver {
    public:
        Receiver(std::shared_ptr<ReQueue<rpc::serverStream*> > q, void (*func)(rpc::serverStream* stream));
        Receiver(std::string h, int p, std::shared_ptr<ReQueue<rpc::serverStream*> > q, void (*func)(rpc::serverStream* stream));
        ~Receiver();

        void start();

    private:
        std::shared_ptr<ReQueue<rpc::serverStream*> > que;
        rpc::eventLoop* event;
        rpc::rpcServer* server;
        std::string host;
        int port;
    };

}