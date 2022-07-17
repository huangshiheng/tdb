/*
 * @filePath: file content
 * @version: 
 * @Author: huangshiheng
 * @Date: 2022-07-10 10:36:01
 * @LastEditTime: 2022-07-17 08:50:35
 */

# pragma once 

#include <string>
#include <vector>

namespace tdb {

    struct HashNode {
        HashNode() {
            next = nullptr;
        }
        HashNode(std::string& k, std::string& v) : HashNode() {
            key = k;
            val = v;
        }
        ~HashNode() { }
        HashNode* next;
        std::string key;
        std::string val;
    };

    class HashTable {
    public:
        HashTable() {
            table.reserve(1023);
            table1.clear();
            is_rehash = false;
        }
        
        void insert(std::string& key, std::string& val);
        void delet(std::string& key);
        void delet(std::string& key, std::string& val);
        bool find(std::string& key, std::string& val);
        void change(std::string& key, std::string& val);
        int  sign(std::string& key);
        void rehash();

    private:
        std::vector<HashNode*> table;
        std::vector<HashNode*> table1;
        bool is_rehash;
    }


}