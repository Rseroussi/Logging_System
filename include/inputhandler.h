#include "syslog.h"
#include <chrono>
#include <iomanip>

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
            buffer_output.push_back(ConvertLog(input_streams[id].front()));
            input_streams[id].pop();
        }
        lck.unlock();
        // cout << "Input Handler " << id << " got input" << endl;
        //process input
        if(buffer_output.size() >= INPUT_MAX) {
            unique_lock<mutex> lck_out(mtx_output);
            cv_output.wait(lck_out, [this] { return output_stream.size() < OUTPUT_MAX; });
            for(auto msg = --buffer_output.end(); msg >= buffer_output.begin(); msg--) {
                output_stream.push_back(*msg);
            }
            buffer_output.clear();
            lck_out.unlock();
            cv_output.notify_one();
        }
        
    }
}

string Syslog::ConvertLog(string message) {
    string log_level;
    string time_stamp;
    string log_message;
    //parse message
    //get log level
    log_level = message.substr(0, message.find(" "));
    message = message.substr(message.find(" ") + 1);
    //get time stamp
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
    stringstream time_temp;
    time_temp << std::put_time(std::localtime(&currentTime), "%Y-%m-%d %H:%M:%S");
    time_stamp = time_temp.str();
    //get log message
    return log_level + " " + time_stamp + " " + message;
}