/*
 * @filePath: file content
 * @version: 
 * @Author: huangshiheng
 * @Date: 2022-07-10 14:11:45
 * @LastEditTime: 2022-07-16 21:41:11
 */

#include "skipList.h"

namespace tdb {
    SkipList::SkipList() {
        list.clear();
    }
    
    SkipList::~SkipList() { }

    void SkipList::insert(long k, std::string v) {
        if(list.size() == 0) {
            SkipNode* node = new SkipNode(k ,v);
            list.push_back(node);
            return ;
        }
        bool isInsert = false;
        SkipNode* upNode = nullptr;
        SkipNode* newNode = nullptr;
        int col = list.size() -1 ;
        if(list[col]->num >= 3) {
            SkipNode* node = new SkipNode(k ,v);
            list.push_back(node);
            isInsert = true;
            upNode = node;
        }
        while(col >= 0) {
            SkipNode* node = newNode ? newNode : list[col];
            if(k < node->key) {
                if((col > 0 && list[col]->num * 3 < list[col - 1]->num + 1) || (col == 0 ) || isInsert) {
                    SkipNode* insert_node = new SkipNode(k ,v);
                    insert_node->num = node->num + 1;
                    insert_node->next = node;
                    list[col] = insert_node;
                    col--;
                    isInsert = true;
                    if(upNode) {
                        upNode->flow = insert_node;
                    }
                    upNode = insert_node;
                    continue;
                }
                col--;
            }
            SkipNode* p = node->next;
            while(true) {
                if(p) {
                    if(k > p->key) {
                        p = p->next;
                        node = node->next;
                        continue;
                    } else if(k < p->key) {
                        if((col > 0 && list[col]->num * 3 < list[col - 1]->num + 1) || (col == 0 ) || isInsert) {
                            SkipNode* insert_node = new SkipNode(k ,v);
                            list[col]->num = list[col]->num + 1;
                            insert_node->next = p;
                            node->next = insert_node;
                            isInsert = true;
                            newNode = node->flow;
                            if(upNode) {
                                upNode->flow = insert_node;   
                            }
                            upNode = insert_node;
                        }
                        col--;
                        break;
                    }
                } else {
                    if((col > 0 && list[col]->num * 3 < list[col - 1]->num + 1) || (col == 0 ) || isInsert) {
                        SkipNode* insert_node = new SkipNode(k ,v);
                        list[col]->num = list[col]->num + 1;
                        node->next = insert_node;
                        isInsert = true;
                        newNode = node->flow;
                        if(upNode) {
                            upNode->flow = insert_node;
                        }
                        upNode = insert_node;
                    }
                    col--;
                    break;
                }
            }
        }
    }
    
    void SkipList::delet(long k) {
        int col = list.size() - 1;
        SkipNode* p = nullptr;
        while(col >= 0) {
            SkipNode* node = p != nullptr ? p : list[col];
            if(k < node->key) {
                node = list[col];
            }
            if(node->key == k) {
                if(node->next) {
                    list[col] = node->next;
                    list[col]->num = node->num - 1;
                } else {
                    list.erase(list.begin() + col);
                }
                node->~SkipNode();
                col--;
                continue;
            }
            while(true) {
                if(node->next == nullptr) {
                    p = node->flow;
                    col--;
                    break;
                }
                if(node->next->key < k) {
                    node = node->next;
                    continue;
                }
                p = node->flow;
                if(node->next->key == k) {
                    SkipNode* p1 = node->next;
                    node->next = p1->next;
                    p1->~SkipNode();
                    list[col]->num--;
                }
                col--;
                break;
            }
        }
    }
    
    bool SkipList::find(long k, std::string& res) {
        int col = list.size() - 1;
        SkipNode* p = nullptr;
        while(col >= 0) {
            SkipNode* node = p != nullptr ? p : list[col];
            if(k < node->key) {
                node = list[col];
            }
            if(node->key == k) {
                res = node->val;
                return true;
            }
            while(true) {
                if(node->next == nullptr) {
                    p = node->flow;
                    col--;
                    break;
                }
                if(node->next->key < k) {
                    node = node->next;
                    continue;
                }
                if(node->next->key == k) {
                    res = node->next->val;
                    return true;
                }
                p = node->flow;
                col--;
                break;
            }
        }
        return false;
    }
  
    long SkipList::sign(std::string& s) {
        
    }

    void SkipList::print() {
        std::cout << "list'Node num: " << list.size() << std::endl;
        for (int i = list.size() - 1; i >= 0; --i) {
            SkipNode* p = list[i];
            std::cout << "num:[ " << p->num << " ] ->  ";
            while(p) {
                std::cout << p->key << ":" << p->val << "  ";
                p = p->next;
            }
            std::cout << std::endl;
        }
    }

    void SkipList::print_flow() {
        std::cout << "print node as flow" << std::endl;
        for (int i = list.size() - 1; i >= 0; --i) {
            SkipNode* p = list[i];
            while(p) {
                SkipNode* n = p;
                while(n) {
                    std::cout << n->key << " ";
                    n = n->flow;
                }
                std::cout << std::endl;
                p = p->next;
            }
            std::cout << "**" << std::endl;
        }
    }
}