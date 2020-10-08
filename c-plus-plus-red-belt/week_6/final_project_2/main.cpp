#include "test_runner.h"
#include "tests.h"

using namespace std;

int main() {
    TestRunner tr;
    {
        //LOG_DURATION("---TestSerpFormat");
        RUN_TEST(tr, TestSerpFormat);
    }
    {
        // LOG_DURATION("---TestTop5");
        RUN_TEST(tr, TestTop5);
    }
    {
        //LOG_DURATION("---TestHitcount");
        RUN_TEST(tr, TestHitcount);
    }

    {
        //LOG_DURATION("---TestRanking");
        RUN_TEST(tr, TestRanking);
    }
    {
        //LOG_DURATION("---TestBasicSearch");
        RUN_TEST(tr, TestBasicSearch);
    }
}
