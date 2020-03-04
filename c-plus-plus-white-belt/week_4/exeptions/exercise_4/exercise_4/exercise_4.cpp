#include <iostream>
#include <exception>
#include <string>
using namespace std;

string AskTimeServer()
{
    //return "01:02:03";
    //throw std::system_error(ECONNABORTED, std::generic_category(), "Connection aborted");
    throw overflow_error("Something went wrong");
}

class TimeServer {
public:
    string GetCurrentTime() {
        try
        {
            last_fetched_time = AskTimeServer();
        }
        catch (system_error& ex)
        {
        }
        return last_fetched_time;
    }
private:
    string last_fetched_time = "00:00:00";
};

int main() {
    TimeServer ts;
    try {
        cout << ts.GetCurrentTime() << endl;
    }
    catch (exception& e) {
        cout << "Exception got: " << e.what() << endl;
    }
    return 0;
}
