#include "mock.h"
#include "unittest.h"

// This struct would normaly be written in another file
// and the test case would only linked to that file for testing

class IObject {
public:
    virtual int update() = 0;
    virtual void value(int) = 0;
    virtual int value() const = 0;

    virtual ~IObject() = default;
};

//! Example of a class that could be tested
struct TestStruct {
    TestStruct(IObject *object) : _object(object) {}

    TestStruct(int value, IObject *object) : _a(0), _object(object) {}

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
    MOCK_METHOD0(int, update, (), override)
    MOCK_METHOD1(void, value, (int), override)
    MOCK_CONST_METHOD0(int, value, (), override);
};

//! Test of all macros
struct A {
    MOCK_METHOD0(int, value, (), );
    MOCK_METHOD1(int, value, (int), );
    MOCK_METHOD2(int, value, (int, int), );
    MOCK_METHOD3(int, value, (int, int, int), );
    MOCK_METHOD4(int, value, (int, int, int, int), );
    MOCK_METHOD5(int, value, (int, int, int, int, int), );
    MOCK_METHOD6(int, value, (int, int, int, int, int, int), );
    MOCK_METHOD7(int, value, (int, int, int, int, int, int, int), );
    MOCK_METHOD8(int, value, (int, int, int, int, int, int, int, int), );
    MOCK_METHOD9(int, value, (int, int, int, int, int, int, int, int, int), );
};

//! Const macros
struct B {

    MOCK_CONST_METHOD0(int, value, (), );
    MOCK_CONST_METHOD1(int, value, (int), );
    MOCK_CONST_METHOD2(int, value, (int, int), );
    MOCK_CONST_METHOD3(int, value, (int, int, int), );
    MOCK_CONST_METHOD4(int, value, (int, int, int, int), );
    MOCK_CONST_METHOD5(int, value, (int, int, int, int, int), );
    MOCK_CONST_METHOD6(int, value, (int, int, int, int, int, int), );
    MOCK_CONST_METHOD7(int, value, (int, int, int, int, int, int, int), );
    MOCK_CONST_METHOD8(int, value, (int, int, int, int, int, int, int, int), );
    MOCK_CONST_METHOD9(int,
                       value,
                       (int, int, int, int, int, int, int, int, int), );
};

// Begining of actual test code
// This is what is supposed to be in a test file

TEST_SUIT_BEGIN(Mocks)

TEST_CASE("equalization test") {
    MockObject object;
    auto testStruct1 = TestStruct(1, &object);
    auto testStruct2 = TestStruct(1, &object);

    ASSERT(testStruct1 == testStruct2, "something went wrong");

    // The same test but in another way
    EXPECT_EQ(10, 10);
    EXPECT_EQ(testStruct1.a(), testStruct2.a());
}

TEST_CASE("failing test") {
    MockObject object;
    TestStruct testStruct1(&object), testStruct2(&object);

    object.mock_update_0.expectNum(2);

    testStruct1.a(1);
    testStruct2.a(2);

    EXPECT_EQ(testStruct1.a(), testStruct2.a());
}

TEST_SUIT_END
