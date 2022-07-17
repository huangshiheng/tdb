/*
 * @Autor: huangshiheng
 * @Date: 2022-07-09 17:41:31
 * @LastEditTime: 2022-07-10 10:20:39
 * @LastEditors: Please set LastEditors
 */



#include "../receive/receiver.h"
#include "../../proto/request.pb.h"
#include "../receive/queue.h"
#include "../process/processer.h"
#include <thread>

std::shared_ptr<tdb::ReQueue<rpc::serverStream*> > que = std::make_shared<tdb::ReQueue<rpc::serverStream*> >();

void addQueue(rpc::serverStream* stream) {
    que->push(stream);
}

int main() {
    tdb::Receiver* recv = new tdb::Receiver("127.0.0.1", 1234, que, addQueue);
    tdb::Processer* process = new tdb::Processer(que);
    std::thread th(&tdb::Processer::processStream, process);
    th.detach();
    recv->start();
    return 0;
}