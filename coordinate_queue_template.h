//
// Created by Matias on 15/09/2019.
//

#ifndef TP1_PROJECT_SAFE_QUEUE_H
#define TP1_PROJECT_SAFE_QUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>


template <class T>
class CoordinatedQueue{
private:
    std::mutex m;
    std::mutex m2;
    std::condition_variable get_cv;
    std::condition_variable put_cv;
    unsigned int max_elements{};
    bool closed{};
    std::queue<T> queue;

public:
    CoordinatedQueue();

    CoordinatedQueue(const CoordinatedQueue& sq);

    //POS sets the max_elements of a queue
    void Init(int max_elements);

    //POS sets the max_elements of a queue
    //also fills de queues with CompressResult (could use a template)
    void InitFull(int max_elements);

    //POS: adds element to queue if enough space, otherwise yields
    //until space is made or queue is closed
    void AddElement(const T &result);

    //why use poinconst ter? its possi&ble that this function
    //fails to retrieve an element when the qs are closed and thread
    //is waiting in an empty queue

    //POS: attemps to retrieve element from queue
    //if queue is emtpy, yields until not empty
    //if queue is closed, returns -1
    //if successful elem points to element
    //and returns 0
    int GetElement(T &elem);

    //POS moves the front element to the back
    void MoveFrontToBack();

    void PopElement();

    //closes the queue to signal no new elements will arrive
    void CloseQueue();

    //POS true when close_queue has been called once before
    bool IsClosed();

    bool IsEmpty();

    void Release();
};

template <class T>
void CoordinatedQueue<T>::Init(const int max_elements) {
    this->max_elements = max_elements;
    this->closed = false;
}

template <class T>
void CoordinatedQueue<T>::InitFull(const int max_elements) {
    this->Init(max_elements);
    for (int j=0; j<max_elements; j++){
        this->queue.push(T());
    }
}

template <class T>
void CoordinatedQueue<T>::AddElement(const T& result) {
    std::unique_lock<std::mutex> lock(this->m2);
    while (this->queue.size() == this->max_elements) {
        if (IsClosed()) return;
        this->put_cv.wait(lock);
    }
    this->queue.push(result);
    get_cv.notify_all();
    //lock gets released by destructor
}

template <class T>
int CoordinatedQueue<T>::GetElement(T &elem) {
    std::unique_lock<std::mutex> lock(this->m);
    while (this->queue.empty()) {
        if (IsClosed()) return 1;
        this->get_cv.wait(lock);
    }

    elem = (this->queue.front());
    //lock gets released by destructor
    return 0;
}

template <class T>
void CoordinatedQueue<T>::PopElement() {
    if (!this->queue.empty()){
        this->queue.pop();
        put_cv.notify_all();
    }
}

template <class T>
void CoordinatedQueue<T>::CloseQueue() {
    this->closed = true;
    this->get_cv.notify_all();
    this->put_cv.notify_all();
}

template <class T>
bool CoordinatedQueue<T>::IsClosed(){
    return (this->closed);
}

template <class T>
bool CoordinatedQueue<T>::IsEmpty(){
    return this->queue.empty();
}

template <class T>
void CoordinatedQueue<T>::Release() {
    //nothing to release;
}

template<class T>
CoordinatedQueue<T>::CoordinatedQueue(const CoordinatedQueue &sq) {
    this->max_elements = sq.max_elements;
    this->closed = sq.closed;
    this->queue = sq.queue;
}

template<class T>
CoordinatedQueue<T>::CoordinatedQueue() {
    this->queue = std::queue<T>();
    this->max_elements = 0;
    this->closed = false;
}

template<class T>
void CoordinatedQueue<T>::MoveFrontToBack(){
    T elem = this->queue.front();
    this->queue.pop();
    this->queue.push(elem);
}

#endif //TP1_PROJECT_SAFE_QUEUE_H
