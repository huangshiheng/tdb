/*
 * @filePath: file content
 * @version: 
 * @Author: huangshiheng
 * @Date: 2022-07-10 09:11:39
 * @LastEditTime: 2022-07-13 13:20:43
 */

#include "processer.h"

namespace tdb {
    
    void sendData(rpc::serverStream* stream, const std::string& s1) {
        rpc::rpcResponce res;
        res.set_msg(s1);
        std::string sx;
        res.SerializeToString(&sx);
        stream->setData(sx);
    }

    Processer::Processer(std::shared_ptr<ReQueue<rpc::serverStream*> > q) {
        que = q;
	    shutdown = false;
    }
    
    Processer::~Processer() {
	    shutdown = true;
    }
    
    void Processer::processStream() {
        while(!shutdown) {
            rpc::serverStream* stream =  que->get_data();
            dispatcher(stream);
        }
    }

    void Processer::dispatcher(rpc::serverStream* stream) {
        std::string s;
        stream->getData(s);
        rpc::rpcRequest re;
        re.ParseFromString(s);    
        tdb::proto::TkvRequest kvr;
        kvr.ParseFromString(re.msg());
        switch(kvr.type()) {
            case tdb::proto::INSERT : {
                insert(kvr.kv(), stream);
                break;
            }
            case tdb::proto::DELETE : {
                delet(kvr.kv(), stream);
                break;
            }
            case tdb::proto::FIND : {
                find(kvr.kv(), stream);
                break;
            }
            case tdb::proto::CLUSTER : {
                cluster(stream);
                break;
            }
            default : {
                std::cout << " DEFALUT" << std::endl;
                break;
            }
        }
    }

    void Processer::insert(const tdb::proto::KV& kv, rpc::serverStream* stream) {
        std::cout << " INSERT: " << kv.key() << std::endl;
        sendData(stream, "INSERT");
    }

    void Processer::delet(const tdb::proto::KV& kv, rpc::serverStream* stream) {
        std::cout << " DELETE: " << kv.key() << std::endl;
        sendData(stream, "DELETE");
    }

    void Processer::find(const tdb::proto::KV& kv, rpc::serverStream* stream) {
        std::cout << " FIND: " << kv.key() << std::endl;
        sendData(stream, "FIND");
    }

    void Processer::cluster(rpc::serverStream* stream) {
        std::cout << " CLUSTER"<< std::endl;
        sendData(stream, "CLUSTER");
    }

}
