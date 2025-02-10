#pragma once

#include <thread>
#include <iostream>
#include <syslog.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <queue>

#define INPUT_STREAMS 5
#define INPUT_MAX 1
#define OUTPUT_MAX 20
using namespace std;

class Syslog {
    private:
        //temp values for testing to be replaced later with actual way to get the log queue
        vector<queue<string>> input_streams;
        mutex mtx_input[INPUT_STREAMS];
        condition_variable cv_input[INPUT_STREAMS];
        // end of temp variables used for fake input

        vector<thread> input_handlers;
        vector<string> output_stream;
        mutex mtx_output;
        condition_variable cv_output;

        //private functions
        string ConvertLog(string message);
    public:
        Syslog();
        void InputHandler(int id);
        void Start();
        void OutputHandler();
        //pretend input
        void RunInput();

};