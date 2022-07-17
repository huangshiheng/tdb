/*
 * @filePath: file content
 * @version: 
 * @Author: huangshiheng
 * @Date: 2022-07-15 08:16:00
 * @LastEditTime: 2022-07-16 15:59:44
 */

#pragma once

#include "rpc/output/include/client.h"
#include "rpc/output/include/serverStream.h"
#include <unordered_map>

namespace tdb {

    enum class Identify {
        LEADER,
        FOLLOWER,
        CONDIDATE
    };

    class Members {
    public:
        Members();
        
        ~Members();

        void loadHost();

        void election();

        void electionRequest(proto::RequestType type, void (*func)(rpc::clientStream* cli));

        bool receiveVoteRequest(proto::ClusterVote* cvote);

        void receiveBoardcastLeader(proto::ClusterVote* cvote);

        void receiveHeart();

        void receiveSendLog(proto::SyncLog* slog);

        void work();

        void processTime();

        ReQueue<rpc::serverStream*> que; // 命令请求队列

    private:
        Identify identify;
        std::unordered_map<rpc::clientStream*, Identify> member; 
        int term;
        proto::Host* host; 
        int vote_term;
        bool is_vote;
        const int time_out;
        int time_now;
        bool shutdown;
        bool stoptime;
    };

}