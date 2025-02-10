#include <vector>
#include <unistd.h>
#include <iostream>
#include <string>
#include <map>

using namespace std;
//not defined, needs a lot of requirements on what to do, should pull in from a file that defines it for each piece its a part of.
class Monitor {
    private:
        map<string, int> alerts;
        
    public:

        Monitor();
        
        void Check(string message);
}