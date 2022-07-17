/*
 * @Autor: huangshiheng
 * @Date: 2022-07-09 13:25:52
 * @LastEditTime: 2022-07-10 10:00:20
 * @LastEditors: Please set LastEditors
 */
#pragma once

#include <queue>
#include <condition_variable>
#include <mutex>

namespace tdb {
    template<typename T>
    class ReQueue {
    public:
        ReQueue() { }
        ~ReQueue() { }

        void push(T t);

        T get_data();

    private:
        std::queue<T> qu;
        std::mutex m;
        std::condition_variable cv;
    };

    template<typename T>
    void ReQueue<T>::push(T t) {
        {
            std::unique_lock<std::mutex> lck(m);
            qu.push(t);
        }
        cv.notify_all();
    }

    template<typename T>
    T ReQueue<T>::get_data() {
        std::unique_lock<std::mutex> lck(m);
        while(qu.empty()) {
            cv.wait(lck);
        }
        T t = qu.front();
        qu.pop();
        return t;
    }
}
