#include <iostream>
#include <thread>
#include <vector>
#include "syslog.cpp"

using namespace std;

int main() {
    Syslog system_log;
    system_log.Start();
    return 0;
}