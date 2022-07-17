/*
 * @Autor: huangshiheng
 * @Date: 2022-07-08 10:12:05
 * @LastEditTime: 2022-07-09 14:06:26
 * @LastEditors: Do not edit
 */
// ctl + win + i

#pragma once

#include "rpc/output/include/client.h"
#include "rpc/output/include/eventLoop.h"
#include "rpc/output/include/service.pb.pb.h"
#include <string>

namespace tdb {
    class tdbClient {
    public:
        tdbClient();
        tdbClient(std::string h, int p);
        tdbClient(std::string h, int p, void (*f)(rpc::clientStream*));
        ~tdbClient();

        void setHost(std::string h);
        void setPort(int p);
        void init();
        void sendData(std::string data, int choice);
        void setFunc(void (*f)(rpc::clientStream*));
        
    private:
        rpc::eventLoop* event;
        rpc::clientStream* client;
        std::string host;
        int port;
        void (*fun)(rpc::clientStream*);
    };
}
