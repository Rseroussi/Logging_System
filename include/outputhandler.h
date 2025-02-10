#include "syslog.h"


void Syslog::OutputHandler() {
    vector<string> buffer_output;
    //run loop for outputhandler
    while(true) {
        //wait for output
        unique_lock<mutex> lck(mtx_output);
        cv_output.wait(lck, [this] { return !output_stream.empty(); });
        //get output
        while(!output_stream.empty()) {
            //this is where the db would be updated with the whole output stream
            buffer_output.push_back(output_stream.back());
            output_stream.pop_back();
        }
        lck.unlock();
        //process output
        if(buffer_output.size() >= OUTPUT_MAX) {
            for(auto &msg : buffer_output) {
                cout << msg << endl;
            }
            buffer_output.clear();
        }
        cv_output.notify_one();
        
    }
}