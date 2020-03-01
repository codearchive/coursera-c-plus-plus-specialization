#include <vector>

using namespace std;

/*
class Incognizable
{
public:
    Incognizable(){}
    Incognizable(int num_1) : number_1(num_1){}
    Incognizable(int num_1, int num_2) : number_1(num_1), number_2(num_2){}
private:
    int number_1;
    int number_2;
};
*/

struct Incognizable
{
    int x = 0;
    int y = 0;
};

int main() {
    Incognizable a;
    Incognizable b = {};
    Incognizable c = { 0 };
    Incognizable d = { 0, 1 };
    return 0;
}