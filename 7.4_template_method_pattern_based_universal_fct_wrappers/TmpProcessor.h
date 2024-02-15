// TmpProcessor class
//
// (= Template Method Pattern based Processor).
//
// Implements logic: Factory -> Compute -> Dispatch
// The 3 logic blocks can be set at runtime using std::function objects.
// "Template" refers to the std::function type the 3 logic blocks must
// satisfy, such as FactoryFunction = std::function<T()>.
//
// Tobias Bilgeri, 14.02.2024
#pragma once
#include <functional>
#include <future>

template <typename T> using FactoryFunction = std::function<T()>;
template <typename T> using ComputeFunction = std::function<T(const T& t)>;
template <typename T> using DispatchFunction = std::function<void(T& t)>;

template <typename T>
class TmpProcessor {
private:
    FactoryFunction<T> _factory;
    ComputeFunction<T> _compute;
    DispatchFunction<T> _dispatch;

public:
    TmpProcessor(const FactoryFunction<T>& factory, const ComputeFunction<T>& compute, const DispatchFunction<T>& dispatch)
        : _factory(factory), _compute(compute), _dispatch(dispatch) {}

    virtual void algorithm() final {
        // get value from factory
        std::cout << "About to call _factory.\n";
        T val = _factory();
        // perform computation on value
        std::cout << "About to call _compute.\n";
        T val2 = _compute(val);
        // dispatch result
        std::cout << "About to call _dispatch.\n";
        _dispatch(val2);
    }
};
