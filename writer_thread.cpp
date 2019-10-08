//
// Created by Matias on 16/09/2019.
//

#include "writer_thread.h"
#include <vector>

WriterThread::WriterThread(SafeStream &stream, size_t block_size,\
                            std::vector<CoordinatedQueue<CompressResult>>&qs)\
                            : Thread(stream, block_size) {
    this->qs.Init(qs.size());
    for (auto & q : qs){
        this->qs.AddElement(&q);
    }
}

void WriterThread::_Run(const int order, const int total_threads){
    int s = 0;
    //I can use is_empty without fear because this q is never added to again
    while (!this->qs.IsEmpty()){
       CoordinatedQueue<CompressResult> *q;
       s = this->qs.GetElement(q);
       if (s == 0){
            CompressResult res;
            s = (q)->GetElement(res);
            if (s==0){
                std::vector<char> msg;
                res.ToVector(msg);
                this->GetStream()->Write(msg.data(), msg.size());
                (q)->PopElement(); //remove the result from the list
                this->qs.MoveFrontToBack();
            }
        }
       if (s != 0){
            //the queue is closed so lets remove it
           qs.PopElement();
       }
    }
}
