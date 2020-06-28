#include "test_runner.h"

#include <ostream>
using namespace std;

//#define PRINT_VALUES(out, x, y) out << (x) << endl; out << (y) << endl

#define PRINT_VALUES(out, x, y) out << (x) << endl << (y) << endl

int main() {
    TestRunner tr;

    tr.RunTest([] {
        int a;
        cin >> a;

        {
            ostringstream output;
            if (a % 2 == 0)
                PRINT_VALUES(output, 2, "red belt");
            ASSERT_EQUAL(output.str(), "2\nred belt\n");
        }
        {
            ostringstream output;
            for (int i = 0; i < 3 ; ++i)
                PRINT_VALUES(output, i + 1, "red belt");
            ASSERT_EQUAL(output.str(), "1\nred belt\n2\nred belt\n3\nred belt\n");
        }

    }, "PRINT_VALUES usage example");
}
