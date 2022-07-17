/*
 * @filePath: file content
 * @version: 
 * @Author: huangshiheng
 * @Date: 2022-07-17 08:24:16
 * @LastEditTime: 2022-07-17 10:01:59
 */

#include "hash.h"
#include <thread>

namespace tdb {

    void HashTable::insert(std::string& key, std::string& val) {
        int k = sign(key);
        int index = k % table.size();
        if(table[index] == nullptr) {
            table[index] = new HashNode(key, val);
        } else {
            HashNode* p = new HashNode(key, val);
            p->next = table[index];
            table[index] = p;
        }
    }
        
    void HashTable::delet(std::string& key) {
        int k = sign(key);
        int index = k % table.size();
        if(table[index] == nullptr) {
            return ;
        }
        HashNode* p = table[index];
        table[index] = nullptr;
        while(p) {
            HashNode* node = p->next;
            p->~HashNode();
            p = node;
        }
    }
        
    void HashTable::delet(std::string& key, std::string& val) {
        int k = sign(key);
        int index = k % table.size();
        if(table[index] == nullptr) {
            return ;
        }
        HashNode* p = table[index];
        if(p->key == key) {
            table[index] = p->next;
            p->~HashNode();
            return ;
        }
        while(p->next) {
            HashNode* node = p->next;
            if(node->key == key) {
                p->next = node->next;
                node->~HashNode();
                return ;
            }
            p = node;
        }
    }
        
    bool HashTable::find(std::string& key, std::string& val) {
        int k = sign(key);
        int index = k % table.size();
        if(table[index] == nullptr) {
            return false;
        }
        HashNode* p = table[index];
        while(p) {
            if(p->key == key) {
                val = p->val;
                return true;
            }
            p = p->next;
        }
        if(is_rehash) {
            int index1 = k % table1.size();
            if(table1[index1] == nullptr) {
                return false;
            }
            HashNode* p1 = table1[index];
            while(p1) {
                if(p1->key == key) {
                    val = p1->val;
                    return true;
                }
                p1 = p1->next;
            }
        }
        return false;
    }
        
    void HashTable::change(std::string& key, std::string& val) {
        int k = sign(key);
        int index = k % table.size();
        if(table[index] == nullptr) {
            return ;
        }
        HashNode* p = table[index];
        while(p) {
            if(p->key == key) {
                p->val = val;
                return ;
            }
            p = p->next;
        }
    }
        
    int HashTable::sign(std::string& key) {
        int h = 0;
        for (int i = 0; i < key.length(); ++i) {
            h = 31 * h + key[i];
        }
        return h;
    }
        
    void HashTable::rehash() {
        is_rehash = true;
        table1.reserve(2*(table.size() + 1) - 1);
        swap(table, table1);
        std::thread th([&]() {
            std::for_each(table1.begin(), table1.end(), [&](HashNode* head){
                while(head) {
                    insert(head->key, head->val);
                    HashNode* p = head;
                    head = head->next;
                    p->~HashNode();
                }
            });
            is_rehash = false;
        });
        th.detach();
    }

}