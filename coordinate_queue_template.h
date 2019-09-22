//
// Created by Matias on 15/09/2019.
//

#ifndef TP1_PROJECT_SAFE_QUEUE_H
#define TP1_PROJECT_SAFE_QUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>


template <class T>
class coordinated_queue{
private:
    std::mutex m;
    std::mutex m2;
    std::condition_variable get_cv;
    std::condition_variable put_cv;
    unsigned int max_elements{};
    bool closed{};
    std::queue<T> queue;

public:
    coordinated_queue();

    coordinated_queue(const coordinated_queue& sq);

    //POS sets the max_elements of a queue
    void init(int max_elements);

    //POS sets the max_elements of a queue
    //also fills de queues with compress_result (could use a template)
    void init_full(int max_elements);

    //POS: adds element to queue if enough space, otherwise yields
    //until space is made or queue is closed
    void add_element(const T &result);

    //why use poinconst ter? its possi&ble that this function
    //fails to retrieve an element when the qs are closed and thread
    //is waiting in an empty queue

    //POS: attemps to retrieve element from queue
    //if queue is emtpy, yields until not empty
    //if queue is closed, returns -1
    //if successful elem points to element
    //and returns 0
    int get_element(T* &elem);

    //POS moves the front element to the back
    void move_front_to_back();

    void pop_element();

    //closes the queue to signal no new elements will arrive
    void close_queue();

    //POS true when close_queue has been called once before
    bool is_closed();

    bool is_empty();

    void release();
};

template <class T>
void coordinated_queue<T>::init(const int max_elements) {
    this->max_elements = max_elements;
    this->closed = false;
    this->queue = std::queue<T>();
}

template <class T>
void coordinated_queue<T>::init_full(const int max_elements) {
    this->init(max_elements);
    for (int j=0; j<max_elements; j++){
        this->queue.push(T());
    }
}

template <class T>
void coordinated_queue<T>::add_element(const T& result) {
    std::unique_lock<std::mutex> lock(this->m2);
    while (this->queue.size() == this->max_elements) {
        if (is_closed()) return;
        this->put_cv.wait(lock);
    }
    this->queue.push(result);
    get_cv.notify_all();
    //lock gets released by destructor
}

template <class T>
int coordinated_queue<T>::get_element(T* &elem) {
    std::unique_lock<std::mutex> lock(this->m);
    while (this->queue.empty()) {
        if (is_closed()) return 1;
        this->get_cv.wait(lock);
    }

    elem = &(this->queue.front());
    lock.unlock();
    return 0;
}

template <class T>
void coordinated_queue<T>::pop_element() {
    if (!this->queue.empty()){
        this->queue.pop();
        put_cv.notify_all();
    }
}

template <class T>
void coordinated_queue<T>::close_queue() {
    this->closed = true;
    this->get_cv.notify_all();
    this->put_cv.notify_all();
}

template <class T>
bool coordinated_queue<T>::is_closed(){
    return (this->closed);
}

template <class T>
bool coordinated_queue<T>::is_empty(){
    return this->queue.empty();
}

template <class T>
void coordinated_queue<T>::release() {
    //nothing to release;
}

template<class T>
coordinated_queue<T>::coordinated_queue(const coordinated_queue &sq) {
    this->max_elements = sq.max_elements;
    this->closed = sq.closed;
    this->queue = sq.queue;
}

template<class T>
coordinated_queue<T>::coordinated_queue() {
    this->queue = std::queue<T>();
    this->max_elements = 0;
    this->closed = false;
}

template<class T>
void coordinated_queue<T>::move_front_to_back(){
    T elem = this->queue.front();
    this->queue.pop();
    this->queue.push(elem);
}

#endif //TP1_PROJECT_SAFE_QUEUE_H
