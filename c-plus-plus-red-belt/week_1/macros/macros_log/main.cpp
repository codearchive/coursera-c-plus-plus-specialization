#include "test_runner.h"
#include "logger.h"

#include <sstream>
#include <string>

using namespace std;

void TestLog() {

    ostringstream logs;
    Logger l(logs);
    LOG(l, "hello");

    l.SetLogFile(true);
    #line 10 "logger.cpp"
    LOG(l, "hello");

    l.SetLogLine(true);
    #line 10 "logger.cpp"
    LOG(l, "hello");

    l.SetLogFile(false);
    #line 13 "logger.cpp"
    LOG(l, "hello");

    string expected = "hello\n";
    expected += "logger.cpp hello\n";
    expected += "logger.cpp:10 hello\n";
    expected += "Line 13 hello\n";
    ASSERT_EQUAL(logs.str(), expected);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestLog);
}
