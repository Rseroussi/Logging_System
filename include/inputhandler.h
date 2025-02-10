#include "syslog.h"

void Syslog::InputHandler(int id) {
    vector<string> buffer_output;
    //run loop for inputhandler
    while(true) {

        //wait for input
        unique_lock<mutex> lck(mtx_input[id]);
        // cout << "Input Handler " << id << " waiting for input" << endl;
        cv_input[id].wait(lck, [this, id] { return !input_streams[id].empty(); });
        //get input
        while(!input_streams[id].empty()) {
            buffer_output.push_back(input_streams[id].front());
            input_streams[id].pop();
        }
        lck.unlock();
        // cout << "Input Handler " << id << " got input" << endl;
        //process input
        if(buffer_output.size() >= INPUT_MAX) {
            unique_lock<mutex> lck_out(mtx_output);
            cv_output.wait(lck_out, [this] { return output_stream.size() < OUTPUT_MAX; });
            for(auto &msg : buffer_output) {
                output_stream.push_back(msg);
            }
            buffer_output.clear();
            lck_out.unlock();
            cv_output.notify_one();
        }
        
    }
}