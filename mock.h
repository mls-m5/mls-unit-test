/*
 * mock.h
 *
 * Contains mocking functionality for the mls-unit-test
 *
 * Author: Mattias Larsson Sköld 2020
 *
 */

#pragma once

#include "unittestvars.h"
#include <functional>
#include <iostream>
#include <optional>

#define INTERNAL_MOCK_METHOD_COMMON(ret, name, args)                           \
    using name##T = ret(args);                                                 \
    unittest::MockedFunction<ret(args)> mock_##name =                          \
        unittest::MockedFunction<ret(args)>(#name);

#define MOCK_METHOD(ret, name)                                                 \
    INTERNAL_MOCK_METHOD_COMMON(ret, name, ())                                 \
    ret name() {                                                               \
        return mock_##name();                                                  \
    }

#define MOCK_METHOD1(ret, name, args)                                          \
    INTERNAL_MOCK_METHOD_COMMON(ret, name, args)                               \
    ret name(typename unittest::MockedFunction<name##T>::ArgT<0>::type a) {    \
        return mock_##name(a);                                                 \
    }

#define MOCK_METHOD2(ret, name, args)                                          \
    INTERNAL_MOCK_METHOD_COMMON(ret, name, args)                               \
    ret name(typename unittest::MockedFunction<name##T>::ArgT<0>::type a,      \
             typename unittest::MockedFunction<name##T>::ArgT<1>::type b) {    \
        return mock_##name(a, b);                                              \
    }

#define MOCK_METHOD3(ret, name, args)                                          \
    INTERNAL_MOCK_METHOD_COMMON(ret, name, args)                               \
    ret name(typename unittest::MockedFunction<name##T>::ArgT<0>::type a,      \
             typename unittest::MockedFunction<name##T>::ArgT<1>::type b,      \
             typename unittest::MockedFunction<name##T>::ArgT<2>::type c) {    \
        return mock_##name(a, b, c);                                           \
    }

#define MOCK_METHOD4(ret, name, args)                                          \
    INTERNAL_MOCK_METHOD_COMMON(ret, name, args)                               \
    ret name(typename unittest::MockedFunction<name##T>::ArgT<0>::type a,      \
             typename unittest::MockedFunction<name##T>::ArgT<1>::type b,      \
             typename unittest::MockedFunction<name##T>::ArgT<2>::type c,      \
             typename unittest::MockedFunction<name##T>::ArgT<3>::type d) {    \
        return mock_##name(a, b, c, d);                                        \
    }

#define MOCK_METHOD5(ret, name, args)                                          \
    INTERNAL_MOCK_METHOD_COMMON(ret, name, args)                               \
    ret name(typename unittest::MockedFunction<name##T>::ArgT<0>::type a,      \
             typename unittest::MockedFunction<name##T>::ArgT<1>::type b,      \
             typename unittest::MockedFunction<name##T>::ArgT<2>::type c,      \
             typename unittest::MockedFunction<name##T>::ArgT<3>::type d,      \
             typename unittest::MockedFunction<name##T>::ArgT<4>::type e) {    \
        return mock_##name(a, b, c, d, e);                                     \
    }

#define MOCK_METHOD6(ret, name, args)                                          \
    INTERNAL_MOCK_METHOD_COMMON(ret, name, args)                               \
    ret name(typename unittest::MockedFunction<name##T>::ArgT<0>::type a,      \
             typename unittest::MockedFunction<name##T>::ArgT<1>::type b,      \
             typename unittest::MockedFunction<name##T>::ArgT<2>::type c,      \
             typename unittest::MockedFunction<name##T>::ArgT<3>::type d,      \
             typename unittest::MockedFunction<name##T>::ArgT<4>::type e,      \
             typename unittest::MockedFunction<name##T>::ArgT<5>::type f) {    \
        return mock_##name(a, b, c, d, e, f);                                  \
    }

#define MOCK_METHOD7(ret, name, args)                                          \
    INTERNAL_MOCK_METHOD_COMMON(ret, name, args)                               \
    ret name(typename unittest::MockedFunction<name##T>::ArgT<0>::type a,      \
             typename unittest::MockedFunction<name##T>::ArgT<1>::type b,      \
             typename unittest::MockedFunction<name##T>::ArgT<2>::type c,      \
             typename unittest::MockedFunction<name##T>::ArgT<3>::type d,      \
             typename unittest::MockedFunction<name##T>::ArgT<4>::type e,      \
             typename unittest::MockedFunction<name##T>::ArgT<5>::type f,      \
             typename unittest::MockedFunction<name##T>::ArgT<6>::type g) {    \
        return mock_##name(a, b, c, d, e, f, g);                               \
    }

#define MOCK_METHOD8(ret, name, args)                                          \
    INTERNAL_MOCK_METHOD_COMMON(ret, name, args)                               \
    ret name(typename unittest::MockedFunction<name##T>::ArgT<0>::type a,      \
             typename unittest::MockedFunction<name##T>::ArgT<1>::type b,      \
             typename unittest::MockedFunction<name##T>::ArgT<2>::type c,      \
             typename unittest::MockedFunction<name##T>::ArgT<3>::type d,      \
             typename unittest::MockedFunction<name##T>::ArgT<4>::type e,      \
             typename unittest::MockedFunction<name##T>::ArgT<5>::type f,      \
             typename unittest::MockedFunction<name##T>::ArgT<6>::type g,      \
             typename unittest::MockedFunction<name##T>::ArgT<7>::type h) {    \
        return mock_##name(a, b, c, d, e, f, g, h);                            \
    }

#define MOCK_METHOD9(ret, name, args)                                          \
    INTERNAL_MOCK_METHOD_COMMON(ret, name, args)                               \
    ret name(typename unittest::MockedFunction<name##T>::ArgT<0>::type a,      \
             typename unittest::MockedFunction<name##T>::ArgT<1>::type b,      \
             typename unittest::MockedFunction<name##T>::ArgT<2>::type c,      \
             typename unittest::MockedFunction<name##T>::ArgT<3>::type d,      \
             typename unittest::MockedFunction<name##T>::ArgT<4>::type e,      \
             typename unittest::MockedFunction<name##T>::ArgT<5>::type f,      \
             typename unittest::MockedFunction<name##T>::ArgT<6>::type g,      \
             typename unittest::MockedFunction<name##T>::ArgT<7>::type h,      \
             typename unittest::MockedFunction<name##T>::ArgT<8>::type i) {    \
        return mock_##name(a, b, c, d, e, f, g, h, i);                         \
    }

#define MOCK_METHOD10(ret, name, args)                                         \
    INTERNAL_MOCK_METHOD_COMMON(ret, name, args)                               \
    ret name(typename unittest::MockedFunction<name##T>::ArgT<0>::type a,      \
             typename unittest::MockedFunction<name##T>::ArgT<1>::type b,      \
             typename unittest::MockedFunction<name##T>::ArgT<2>::type c,      \
             typename unittest::MockedFunction<name##T>::ArgT<3>::type d,      \
             typename unittest::MockedFunction<name##T>::ArgT<4>::type e,      \
             typename unittest::MockedFunction<name##T>::ArgT<5>::type f,      \
             typename unittest::MockedFunction<name##T>::ArgT<6>::type g,      \
             typename unittest::MockedFunction<name##T>::ArgT<7>::type h,      \
             typename unittest::MockedFunction<name##T>::ArgT<8>::type i,      \
             typename unittest::MockedFunction<name##T>::ArgT<9>::type j) {    \
        return mock_##name(a, b, c, d, e, f, g, h, i, j);                      \
    }

namespace unittest {

template <typename T>
struct ReturnStruct {
    using type = T;
    T value = {};
    T get() {
        return value;
    }
};

template <>
struct ReturnStruct<void> {
    using type = char;
    void get() {}
};

template <typename T>
class MockedFunction {};

template <typename ReturnT, typename... ArgsT>
class MockedFunction<ReturnT(ArgsT...)> {
public:
    // Return argument type at the specified index
    template <int i>
    struct ArgT {
        using type = typename std::tuple_element_t<i, std::tuple<ArgsT...>>;
    };

    using RetT = ReturnT;

    MockedFunction(std::string name) : _name(name) {}

    ~MockedFunction() {
        checkCalls();
    }

    //! Call the function
    ReturnT operator()(ArgsT... args) {
        ++_numCalls;
        if (_expectedArgs) {
            if (!_expectedArgs(args...)) {
                std::cerr << "Argument value(s) does not match expected "
                             "value(s) for function '"
                          << _name << "'\n";
                failTest();
            }
        }
        if (_onCall) {
            return _onCall(args...);
        }
        else {
            return _returnValue.get();
        }
    }

    //! Set the number times the function is expected to be called
    //! If expectCall is set previously a check is done before
    //! resetting the number of calls required
    MockedFunction &expectNum(size_t num) {
        checkCalls();
        _expectedNumCalls = num;

        return *this;
    }

    //! Pass a function to check if arguments fullfill the
    MockedFunction &expectArgs(std::function<bool(ArgsT...)> matcher) {
        _expectedArgs = matcher;
        return *this;
    }

    //! Set values that is to be compared with a function call
    MockedFunction &expectArgs(ArgsT... args) {
        auto argTuple = std::tuple<ArgsT...>{args...};

        _expectedArgs = [argTuple](ArgsT &&... a) -> bool {
            auto comparisonTuple = std::tuple<ArgsT...>{a...};
            return comparisonTuple == argTuple;
        };

        return *this;
    }

    //! Function to be called when the mocked function is used
    MockedFunction &onCall(std::function<ReturnT(ArgsT...)> f) {
        _onCall = f;
        return *this;
    }

    //! Sets the value to return if no function if set with onCall
    //! function
    void returnValue(typename ReturnStruct<ReturnT>::type value) {
        _returnValue = value;
        static_assert(!std::is_same<ReturnT, void>::value,
                      "cannot set return value of void type");
    }

private:
    //! Check and resets the the number set with expectCall
    void checkCalls() {
        if (_numCalls != _expectedNumCalls) {
            std::cerr << "function " << _name << " expected to be called "
                      << _expectedNumCalls << " but was called " << _numCalls
                      << " times \n";
            unittest::failTest();
        }

        _numCalls = 0;
        _expectedNumCalls = 0;
    }

    ReturnStruct<ReturnT> _returnValue = {};
    std::function<ReturnT(ArgsT...)> _onCall;
    std::function<bool(ArgsT...)> _expectedArgs;
    size_t _numCalls = 0;
    size_t _expectedNumCalls = 0;
    std::string _name;
};

} // namespace unittest
