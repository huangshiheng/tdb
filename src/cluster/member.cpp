/*
 * @filePath: file content
 * @version: 
 * @Author: huangshiheng
 * @Date: 2022-07-15 08:16:01
 * @LastEditTime: 2022-07-16 16:05:09
 */

#include "member.h"
#include <fstream>
#include <iostream>
#include <string>
#include <chrono>

namespace tdb {
    
    int g_host_num = 0;
    int g_receive_num = 0;
    int g_receive_vote = 0;
    
    void processVoteResponse(rpc::clientStream* cli) {
        std::thread th([&](){
            std::string s;
            cli->getData(s);
            rpc::rpcResponce res;
            res.ParseFromString(s);
            if(!res.has_msg()) {
                return ;
            }
            proto::ClusterResponse cres;
            cres.ParseFromString(res.msg());
            if(cres.type() == proto::ResponseOK) {
                g_receive_vote++;
            }
            g_receive_num++;
        });
        th.detach();
    }

    void processBoardcastLeader(rpc::clientStream* cli) {
        std::thread th([&](){
            std::string s;
            cli->getData(s);
            rpc::rpcResponce res;
            res.ParseFromString(s);
            member[cli] = Identify::FOLLOWER;
        });
        th.datach();
    }

    Members::Members() : time_out(1000) {
        loadHost();
        time_now = 0;
        shutdown = false;
        stoptime = false;
    }

    Members::~Members() {
        shutdown = true;
        stoptime = true;
    }

    void Members::loadHost() {
        host = new proto::Host();
        const string hostPath = "host.conf";
        std::fstream input(hostPath, ios::in);
        if(!input) {
            std::cout << "open hos.conf failed" << std::endl;
            return ;
        }
        if(host->ParseFormIstream(&input)) {
            std::cout << "host parse host.conf failed" << std::endl;
            return ;
        }
    }

    void Members::election() {
        identify = Identify::CONDIDATE;
        term++;
        electionRequest(proto::VOTE, processVoteResponse);
        /*******/
        if(g_host_num == g_receive_num) {
            //rpc::eventLoop::getInstance()->stop();
            if(g_receive_vote >= g_receive_num / 2) {
                identify = Identify::LEADER;
                /* boardcast all node */
                electionRequest(proto::LEADER, processBoardcastLeader);
                stoptime = false;
                std::thread th(&Members::processTime, this);
            } else {
                identify = Identify::FOLLOWER;
            }
        }
    }

    void Member::electionRequest(proto::RequestType type, void (*func)(rpc::clientStream* cli)) {
        if(host == nullptr) {
            std::cout << "electe failed host is nullptr" << std::endl;
            return ;
        }
        proto::ClusterRequest clustRequest;
        clustRequest.set_type(type);
        proto::ClusterVote* cvote = clustRequest.mutable_vote();
        cvote->set_term(term);
        std::string request;
        clustRequest.SerializeToString(&request);
        int host_size = host->ip_port_size();
        g_host_num = host_size;
        for (int i = 0; i < host_size; ++i) {
            proto::IP* h = host->mutable_ip_port(i);
            tdbClient* client = new tdbClient(h->ip(), h->port(), func);
            client->sendData(request, 2);
        }
    }

    bool Members::receiveVoteRequest(proto::ClusterVote* cvote) {
        if(cvote == nullptr) {
            return false;
        }
        if(cvote->term < term) {
            if(is_vote) return false;
            vote_term = term;
            is_vote = true;
            identify = Identify::FOLLOWER;
            return true;
        } else {
            is_vote = true;
            identify = Identify::CONDIDATE;
            std::thread th([&](){
                stoptime = true;
                election();
            });
            th.detach();
            return false;
        }
    }

    void Members::receiveBoardcastLeader(proto::ClusterVote* cvote) {
        if(cvote == nullptr) {
            return ;
        }
        vote_term = -1;
        is_vote = false;
        term = cvote->term;
    }

    void receiveHeart() {
        time_now = 0;
    }

    void Members::receiveSendLog(proto::SyncLog* slog) {

    }

    void Members::work() {
        while(!shutdown) {
            rpc::serverStream* stream = que.get_data();
            std::string s;
            stream->getData(s);
            rpc::rpcRequest re;
            re.ParseFromString(s);
            proto::ClusterRequest cr;
            cr.ParseFromString(re.msg());
            proto::ClusterResponse res;
            switch(cr.type) {
                case proto::VOTE: {
                    if(cr.has_vote() && receiveVoteRequest(cr.mutable_vote())) {
                        res.set_type(proto::ResponseOK);
                    } else {
                        res.set_type(proto::ResponseFailed);
                    }
                    break;
                }
                case proto::SENDLOG: {

                    break;
                }
                case proto::HEART: {
                    receiveHeart();
                    res.set_type(proto::ResponseOK);
                    break;
                }
                case proto::LEADER: {
                    if(cr.has_vote() && receiveBoardcastLeader(cr.mutable_vote())) {
                        res.set_type(proto::ResponseOK);
                    } else {
                        res.set_type(proto::ResponseFailed);
                    }
                    break;
                }
                default: {
                    res.set_type(proto::ResponseFailed);
                    break;
                }
            }
            std::string res_string;
            res.SerializeToString(&res_string);
            rpc::rpcResponce resp;
            resp.set_msg(res_string);
            std::string sx;
            resp.SerializeToString(&sx);
            stream->setDate(sx);
        }
    }

    void Members::processTime() {
        while(!stoptime) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            time_new++;
            if(time_new >= time_out) {
                stoptime = true;
                election();
            }
        }
    }

}