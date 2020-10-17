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
#include <limits>

//! Usage:
//! say you have a class like
//! ```
//! class IObject {
//! public:
//! 	  int doStuff() = 0;
//!     void doStuff2(int a, int b) = 0;
//!     void doStuff3(int a, int b) const = 0;
//! };
//! ```
//!
//! then you can mock it with
//! ```
//! class MockObject: public IObject {
//! public:
//!     MOCK_METHOD(int, doStuff)
//!     MOCK_METHOD2(int, doStuff2, (int, int))
//!     MOCK_METHOD2(int, doStuff3, (int, int), const)
//! };
//! ```
#define MOCK_METHOD(ret, name, args, attr...)                                  \
    MOCK_GET_MACRO_NAME(args)                                                  \
    (ret, name, args, attr)

#define MOCK_METHOD0(ret, name, args, attr...)                                 \
    INTERNAL_MOCK_METHOD_COMMON(ret, name, (), 0)                              \
    ret name() attr {                                                          \
        return (mock_##name##_##0).run();                                      \
    }

#define MOCK_METHOD1(ret, name, args, attr...)                                 \
    INTERNAL_MOCK_METHOD_COMMON(ret, name, args, 1)                            \
    ret name(typename unittest::MockedFunction<name##1##T>::ArgT<0>::type a)   \
        attr {                                                                 \
        return (mock_##name##_##1).run(a);                                     \
    }

#define MOCK_METHOD2(ret, name, args, attr...)                                 \
    INTERNAL_MOCK_METHOD_COMMON(ret, name, args, 2)                            \
    ret name(typename unittest::MockedFunction<name##2##T>::ArgT<0>::type a,   \
             typename unittest::MockedFunction<name##2##T>::ArgT<1>::type b)   \
        attr {                                                                 \
        return (mock_##name##_##2).run(a, b);                                  \
    }

#define MOCK_METHOD3(ret, name, args, attr...)                                 \
    INTERNAL_MOCK_METHOD_COMMON(ret, name, args, 3)                            \
    ret name(typename unittest::MockedFunction<name##3##T>::ArgT<0>::type a,   \
             typename unittest::MockedFunction<name##3##T>::ArgT<1>::type b,   \
             typename unittest::MockedFunction<name##3##T>::ArgT<2>::type c)   \
        attr {                                                                 \
        return (mock_##name##_##3).run(a, b, c);                               \
    }

#define MOCK_METHOD4(ret, name, args, attr...)                                 \
    INTERNAL_MOCK_METHOD_COMMON(ret, name, args, 4)                            \
    ret name(typename unittest::MockedFunction<name##4##T>::ArgT<0>::type a,   \
             typename unittest::MockedFunction<name##4##T>::ArgT<1>::type b,   \
             typename unittest::MockedFunction<name##4##T>::ArgT<2>::type c,   \
             typename unittest::MockedFunction<name##4##T>::ArgT<3>::type d) { \
        return (mock_##name##_##4).run(a, b, c, d);                            \
    }

#define MOCK_METHOD5(ret, name, args, attr...)                                 \
    INTERNAL_MOCK_METHOD_COMMON(ret, name, args, 5)                            \
    ret name(typename unittest::MockedFunction<name##5##T>::ArgT<0>::type a,   \
             typename unittest::MockedFunction<name##5##T>::ArgT<1>::type b,   \
             typename unittest::MockedFunction<name##5##T>::ArgT<2>::type c,   \
             typename unittest::MockedFunction<name##5##T>::ArgT<3>::type d,   \
             typename unittest::MockedFunction<name##5##T>::ArgT<4>::type e)   \
        attr {                                                                 \
        return (mock_##name##_##5).run(a, b, c, d, e);                         \
    }

#define MOCK_METHOD6(ret, name, args, attr...)                                 \
    INTERNAL_MOCK_METHOD_COMMON(ret, name, args, 6)                            \
    ret name(typename unittest::MockedFunction<name##6##T>::ArgT<0>::type a,   \
             typename unittest::MockedFunction<name##6##T>::ArgT<1>::type b,   \
             typename unittest::MockedFunction<name##6##T>::ArgT<2>::type c,   \
             typename unittest::MockedFunction<name##6##T>::ArgT<3>::type d,   \
             typename unittest::MockedFunction<name##6##T>::ArgT<4>::type e,   \
             typename unittest::MockedFunction<name##6##T>::ArgT<5>::type f) { \
        return (mock_##name##_##6).run(a, b, c, d, e, f);                      \
    }

#define MOCK_METHOD7(ret, name, args)                                          \
    INTERNAL_MOCK_METHOD_COMMON(ret, name, args, 7)                            \
    ret name(typename unittest::MockedFunction<name##7##T>::ArgT<0>::type a,   \
             typename unittest::MockedFunction<name##7##T>::ArgT<1>::type b,   \
             typename unittest::MockedFunction<name##7##T>::ArgT<2>::type c,   \
             typename unittest::MockedFunction<name##7##T>::ArgT<3>::type d,   \
             typename unittest::MockedFunction<name##7##T>::ArgT<4>::type e,   \
             typename unittest::MockedFunction<name##7##T>::ArgT<5>::type f,   \
             typename unittest::MockedFunction<name##7##T>::ArgT<6>::type g)   \
        attr {                                                                 \
        return (mock_##name##_##7).run(a, b, c, d, e, f, g);                   \
    }

#define MOCK_METHOD8(ret, name, args, attr...)                                 \
    INTERNAL_MOCK_METHOD_COMMON(ret, name, args, 8)                            \
    ret name(typename unittest::MockedFunction<name##8##T>::ArgT<0>::type a,   \
             typename unittest::MockedFunction<name##8##T>::ArgT<1>::type b,   \
             typename unittest::MockedFunction<name##8##T>::ArgT<2>::type c,   \
             typename unittest::MockedFunction<name##8##T>::ArgT<3>::type d,   \
             typename unittest::MockedFunction<name##8##T>::ArgT<4>::type e,   \
             typename unittest::MockedFunction<name##8##T>::ArgT<5>::type f,   \
             typename unittest::MockedFunction<name##8##T>::ArgT<6>::type g,   \
             typename unittest::MockedFunction<name##8##T>::ArgT<7>::type h)   \
        attr {                                                                 \
        return (mock_##name##_##8).run(a, b, c, d, e, f, g, h);                \
    }

#define MOCK_METHOD9(ret, name, args, attr...)                                 \
    INTERNAL_MOCK_METHOD_COMMON(ret, name, args, 9)                            \
    ret name(typename unittest::MockedFunction<name##9##T>::ArgT<0>::type a,   \
             typename unittest::MockedFunction<name##9##T>::ArgT<1>::type b,   \
             typename unittest::MockedFunction<name##9##T>::ArgT<2>::type c,   \
             typename unittest::MockedFunction<name##9##T>::ArgT<3>::type d,   \
             typename unittest::MockedFunction<name##9##T>::ArgT<4>::type e,   \
             typename unittest::MockedFunction<name##9##T>::ArgT<5>::type f,   \
             typename unittest::MockedFunction<name##9##T>::ArgT<6>::type g,   \
             typename unittest::MockedFunction<name##9##T>::ArgT<7>::type h,   \
             typename unittest::MockedFunction<name##9##T>::ArgT<8>::type i)   \
        attr {                                                                 \
        return (mock_##name##_##9).run(a, b, c, d, e, f, g, h, i);             \
    }

#define MOCK_METHOD10(ret, name, args, attr...)                                \
    INTERNAL_MOCK_METHOD_COMMON(ret, name, args, 10)                           \
    ret name(typename unittest::MockedFunction<name##10##T>::ArgT<0>::type a,  \
             typename unittest::MockedFunction<name##10##T>::ArgT<1>::type b,  \
             typename unittest::MockedFunction<name##10##T>::ArgT<2>::type c,  \
             typename unittest::MockedFunction<name##10##T>::ArgT<3>::type d,  \
             typename unittest::MockedFunction<name##10##T>::ArgT<4>::type e,  \
             typename unittest::MockedFunction<name##10##T>::ArgT<5>::type f,  \
             typename unittest::MockedFunction<name##10##T>::ArgT<6>::type g,  \
             typename unittest::MockedFunction<name##10##T>::ArgT<7>::type h,  \
             typename unittest::MockedFunction<name##10##T>::ArgT<8>::type i,  \
             typename unittest::MockedFunction<name##10##T>::ArgT<9>::type j)  \
        attr {                                                                 \
        return (mock_##name##_##10).run(a, b, c, d, e, f, g, h, i, j);         \
    }

#define INTERNAL_MOCK_METHOD_COMMON(ret, name, args, uniqueid)                 \
    using name##uniqueid##T = ret(args);                                       \
    unittest::MockedFunction<ret(args)> mock_##name##_##uniqueid =             \
        unittest::MockedFunction<ret(args)>(#name, uniqueid);

namespace unittest {

//! Struct for handling return values of different types
template <typename T>
struct ReturnStruct {
    using type = T;
    type value = {};

    type &&get() {
        return std::move(value);
    }

    type get() const {
        return value;
    }
};

//! Specialization for reference type return value
template <typename T>
struct ReturnStruct<T &> {
    using type = T &;
    T *value = {};
    ReturnStruct() = default;
    ReturnStruct(T &value) : value(&value) {}

    type &get() const {
        if (value) {
            return *value;
        }
        throw std::runtime_error(
            std::string("no return value for reference set ") +
            typeid(type).name());
    }
};

//! For handling void arguments
template <>
struct ReturnStruct<void> {
    using type = char;
    void get() const {}
};

template <typename T>
class MockedFunction {};

//! Note that some functions are marked as const. That is to make it possible
//! to be used in a const expression
template <typename ReturnT, typename... ArgsT>
class MockedFunction<ReturnT(ArgsT...)> {
public:
    // Return argument type at the specified index
    template <int i>
    struct ArgT {
        using type = typename std::tuple_element_t<i, std::tuple<ArgsT...>>;
    };

    using RetT = ReturnT;

    MockedFunction(std::string name, size_t num)
        : _name(name + " (" + std::to_string(num) + ")") {}

    ~MockedFunction() {
        checkCalls();
    }

    //! Call the function
    ReturnT run(ArgsT... args) const {
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
        return ReturnStruct<ReturnT>().get();
    }

    //! Set the number times the function is expected to be called
    //! If expectCall is set previously a check is done before
    //! resetting the number of calls required
    auto &expectNum(int num) const {
        checkCalls();
        _expectedNumCalls = num;

        return *this;
    }

    void expectMinNum(int num) const {
        checkCalls();
        _expectedNumCalls = -num;
    }

    //! Be nice to the user of the function: do not care about number of
    //! times called at all
    void nice() const {
        _expectedNumCalls = std::numeric_limits<int>::max();
    }

    //! Pass a function to check if arguments fullfill the
    auto &expectArgs(std::function<bool(ArgsT...)> matcher) const {
        _expectedArgs = matcher;

        if (!_expectedArgs) {
            expectMinNum(1);
        }

        return *this;
    }

    //! Set values that is to be compared with a function call
    auto &expectArgs(ArgsT... args) const {
        auto argTuple = std::tuple<ArgsT...>{args...};

        _expectedArgs = [argTuple](ArgsT &&... a) -> bool {
            auto comparisonTuple = std::tuple<ArgsT...>{a...};
            return comparisonTuple == argTuple;
        };

        if (!_expectedNumCalls) {
            expectMinNum(1);
        }

        return *this;
    }

    //! Function to be called when the mocked function is used
    auto &onCall(std::function<ReturnT(ArgsT...)> f) const {
        _onCall = f;
        if (!_expectedNumCalls) {
            nice();
        }
        return *this;
    }

    //! Sets the value to return if no function if set with onCall
    //! function
    void returnValue(typename ReturnStruct<ReturnT>::type value) const {
        static_assert(!std::is_same<ReturnT, void>::value,
                      "cannot set return value of void type");
        onCall([value = ReturnStruct<ReturnT>{value}](ArgsT...) {
            return value.get();
        });
    }

    //! Same as above but return reference
    void returnValueRef(
        std::remove_reference_t<typename ReturnStruct<ReturnT>::type> &value)
        const {
        static_assert(!std::is_same<ReturnT, void>::value,
                      "cannot set return value of void type");
        onCall(
            [&value](ArgsT...)
                -> std::remove_reference_t<typename ReturnStruct<ReturnT>::type>
                    & { return value; });
    }

    //! Specify a variable to move from for return values that is not copy
    //! constructable
    //! for example:
    //!
    //! std::unique_ptr<int> p;
    //! mock_x.returnValueMoved(p);
    void returnValueMoved(
        typename ReturnStruct<ReturnT>::type &moveFrom) const {
        static_assert(!std::is_same<ReturnT, void>::value,
                      "cannot set return value of void type");
        onCall([&moveFrom](ArgsT...) mutable { return std::move(moveFrom); });
    }

private:
    //! Check and resets the the number set with expectCall
    void checkCalls() const {
        if (_expectedNumCalls == std::numeric_limits<int>::max()) {
            return;
        }

        if (_expectedNumCalls < 0) {
            if (-_numCalls > _expectedNumCalls) {
                std::cerr << "function " << _name
                          << " expected to be called at least "
                          << -_expectedNumCalls << " times but was called "
                          << _numCalls << " times \n";
                unittest::failTest();
            }
            return;
        }

        if (_numCalls != _expectedNumCalls) {
            std::cerr << "function " << _name << " expected to be called "
                      << _expectedNumCalls << " times but was called "
                      << _numCalls << " times \n";
            unittest::failTest();
        }

        _numCalls = 0;
        _expectedNumCalls = 0;
    }

    mutable std::function<ReturnT(ArgsT...)> _onCall;
    mutable std::function<bool(ArgsT...)> _expectedArgs;
    mutable int _numCalls = 0;
    mutable int _expectedNumCalls = 0;
    std::string _name;
};

} // namespace unittest
