#include "unittest.h"

int main(int argc, char **argv) {
    using namespace unittest;

    Tests::instance().run();
}
