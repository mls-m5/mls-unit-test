#include "mock.h"
#include "unittest.h"

// This struct would normaly be written in another file
// and the test case would only linked to that file for testing

class IObject {
public:
    virtual int update() = 0;
    virtual void setValue(int) = 0;
};

//! Example of a class that could be tested
struct TestStruct {
    TestStruct(IObject *object) : _object(object) {}

    TestStruct(int value, IObject *object) : _object(object) {
        a(value);
    }

    bool operator==(TestStruct &s) {
        if (a() == s.a()) {
            return true;
        }
        else {
            return false;
        }
    }

    int a() {
        return _a;
    }

    void a(int val) {
        _a = val;
        _object->update();
    }

    int _a = 0;
    IObject *_object;
};

class MockObject : public IObject {
public:
    MOCK_METHOD(int, update)
    MOCK_METHOD1(void, setValue, (int))
};

// Begining of actual test code
// This is what is supposed to be in a test file

TEST_SUIT_BEGIN

SETUP {
    // Do setup required by the test, or just ommit this function
}

TEST_CASE("equalization test") {
    MockObject object;
    TestStruct testStruct1(1, &object), testStruct2(1, &object);

    ASSERT(testStruct1 == testStruct2, "something went wrong");

    // The same test but in another way
    ASSERT_EQ(testStruct1.a(), testStruct2.a());
}

TEST_CASE("failing test") {
    MockObject object;
    TestStruct testStruct1(&object), testStruct2(&object);

    object.mock_update.expectNum(2);

    testStruct1.a(1);
    testStruct2.a(2);

    ASSERT_EQ(testStruct1.a(), testStruct2.a());
}

TEST_SUIT_END
