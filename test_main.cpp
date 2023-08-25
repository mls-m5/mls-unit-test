#include "unittest.h"

int main(int argc, char **argv) {
    using namespace unittest;

    return Tests::instance().run(argc, argv);
}
