/*
 * @filePath: file content
 * @version: 
 * @Author: huangshiheng
 * @Date: 2022-07-10 09:11:37
 * @LastEditTime: 2022-07-10 10:02:35
 */

#pragma once

#include "rpc/output/include/serverStream.h"
#include "../../proto/request.pb.h"
#include "../receive/receiver.h"
#include "../receive/queue.h"
#include <memory>

namespace tdb {
    class Processer {
    public:
        Processer(std::shared_ptr<ReQueue<rpc::serverStream*> > q);
        ~Processer();

        void processStream();

    private:
        void dispatcher(rpc::serverStream* stream);

        void insert(const tdb::proto::KV& kv, rpc::serverStream* stream);
        void delet(const tdb::proto::KV& kv, rpc::serverStream* stream);
        void find(const tdb::proto::KV& kv, rpc::serverStream* stream);
        void cluster(rpc::serverStream* stream);
        
        std::shared_ptr<ReQueue<rpc::serverStream*> > que;
    	bool shutdown;
    };

}
