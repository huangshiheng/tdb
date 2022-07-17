/*
 * @filePath: file content
 * @version: 
 * @Author: huangshiheng
 * @Date: 2022-07-10 10:35:32
 * @LastEditTime: 2022-07-16 21:13:59
 */

#pragma once

#include <string>
#include <vector>
#include <iostream>

namespace tdb {
    struct SkipNode {
        SkipNode() {
            key = -1;
            val = "";
            num = 1;
            next = nullptr;
            flow = nullptr;
        }
        SkipNode(long k, std::string v) : SkipNode() {
            key = k;
            val = v;
        }
        ~SkipNode() { }
        long key;
        std::string val;
        SkipNode* next; // 在跳表中指向横着的下一个节点
        SkipNode* flow; // 在跳表中指向竖着的下一个节点
        int num;        // 如果是头节点，表示该行所有节点数量
    };

    class SkipList {
    public:
        SkipList();
        ~SkipList();

        void insert(long k, std::string v);
        void delet(long k);
        bool find(long k, std::string& res);
        long sign(std::string& s);
        void print();
        void print_flow();
    private:
        std::vector<SkipNode*> list;

    };
}
/**
 *  1                               9
 *  1               5               9
 *  1       3       5       7       9       11
 *  1   2   3   4   5   6   7   8   9   10  11
**/