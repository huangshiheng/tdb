/*
 * @filePath: file content
 * @version: 
 * @Author: huangshiheng
 * @Date: 2022-07-10 16:00:02
 * @LastEditTime: 2022-07-16 21:44:34
 */

#include "skipList.h"
#include <string>

int main() {
    tdb::SkipList* list = new tdb::SkipList();
    std::string s = "Hello";
    list->insert(1, "a");
    list->insert(3, "b");
    list->insert(2, "c");
    list->insert(8, "d");
    list->insert(5, "e");
    list->insert(9, "f");
    list->insert(7, "g");
    list->insert(6, "h");
    list->insert(4, "i");
    list->insert(0, "j");

    list->print();

    std::cout << "list->find(5): " << list->find(5, s) << " " << s << std::endl;
    
    list->delet(1);
    list->delet(5);
    list->delet(4);
    list->delet(3);

    list->print();
    std::cout << "list->find(5): " << list->find(5, s) << " " << s << std::endl;
    std::cout << "list->find(3): " << list->find(3, s) << " " << s << std::endl;
    std::cout << "list->find(9): " << list->find(9, s) << " " << s << std::endl;
    return 0;
}