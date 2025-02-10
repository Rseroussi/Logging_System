#include <thread>
#include <iostream>
#include <syslog.h>
#include <unistd.h>
#include <string>
#include <vector>
#include "inputhandler.h"
#include "outputhandler.h"

using namespace std;


Syslog::Syslog() {
    //initialize input handlers
    for(int i = 0; i < INPUT_STREAMS; i++) {
        input_streams.push_back(queue<string>());
        // input_handlers.push_back(thread(&Syslog::InputHandler, this, i));
    }
    //initialize output handler
    // thread output_handler(&Syslog::OutputHandler, this);
    // output_handler.join();
}

void Syslog::Start() {
    //initialize input handlers
    for(int i = 0; i < INPUT_STREAMS; i++) {
        input_handlers.push_back(thread(&Syslog::InputHandler, this, i));
    }
    //initialize output handler
    thread output_handler(&Syslog::OutputHandler, this);

    //fake input
    thread input_thread(&Syslog::RunInput, this);
    //join input handlers
    for(auto &handler : input_handlers) {
        handler.join();
    }
    output_handler.join();
    input_thread.join();
}


///fake input
void Syslog::RunInput() {
    while(true) {
        for(int i = 0; i < INPUT_STREAMS; i++) {
            input_streams[i].push(to_string(rand() % 7) + " This is a test message for input stream " + to_string(i));
            cv_input[i].notify_one();
        }
        sleep(1);
    }
}