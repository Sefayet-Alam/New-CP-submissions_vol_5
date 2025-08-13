#include "testlib.h"
using namespace std;

int main(int argc, char** argv) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "t");
    inf.readEoln();

    for (int test = 1; test <= t; ++test) {
        setTestCase(test);

        string visitor = inf.readLine();

        ensuref((visitor=="Mini" || visitor=="Nero" || visitor=="Simba"),"Visitor name not matched");
        inf.readEoln();

        string s = inf.readLine();
        ensuref(1 <= s.size() && s.size() <= 100, "Length of string s must be between 1 and 100");

        long long k = inf.readLong(1LL, 1000000000000000000LL, "k");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
