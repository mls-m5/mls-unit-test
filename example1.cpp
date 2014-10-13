#include "unittest.h"

//This struct would normaly be written in another file
//and the test case would only linked to that file for testing

struct TestStruct{
	TestStruct(){}	
	
	TestStruct(int value){
		a(value);
	}	
	
	bool operator== (TestStruct& s){
		if (a() == s.a()){
			return true;
		}
		else{
			return false;
		}
	}
	
	int a() {
		return _a;
	}
	
	void a(int val){
		_a = val;
	}
	
	int _a;
};


//Begining of actual test code
//This is what is supposed to be in a test file

TEST_SUIT_BEGIN

TEST_CASE("equalization test"){
	TestStruct testStruct1(1), testStruct2(1);
	
	ASSERT(testStruct1 == testStruct2, "something went wrong");
	
	//The same test but in another way
	ASSERT_EQ(testStruct1.a(), testStruct2.a());
	
	return 0;
}

TEST_CASE("failing test"){
	TestStruct testStruct1, testStruct2;
	testStruct1.a(1);
	testStruct2.a(2);
	
	ASSERT_EQ(testStruct1.a(), testStruct2.a());
	return 0;
}

TEST_SUIT_END
