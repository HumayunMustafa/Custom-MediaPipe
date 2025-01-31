//
// Created by MSD on 31/01/2025.
//

#ifndef NO_DESTRUCTOR_H
#define NO_DESTRUCTOR_H

#include <type_traits>
#include <utility>

namespace mediapipe {
    // NoDestructor<T> is a wrapper around an object of type T that
    // * stores the object of type T inline inside NoDestructor<T>
    // * eagerly forwards constructor arguments to it (i.e. acts like T in terms
    //   of construction)
    // * provides access to the object of type T like a pointer via ->, *, and get()
    //   (note that const NoDestructor<T> works like a pointer to const T)
    // * never calls T's destructor for the object
    //   (hence NoDestructor<T> objects created on the stack or as member variables
    //   will lead to memory and/or resource leaks)
    //
    // One key use case of NoDestructor (which in itself is not lazy) is optimizing
    // the following pattern of safe on-demand construction of an object with
    // non-trivial constructor in static storage without destruction ever happening:
    //   const std::string& MyString() {
    //     static std::string* x = new std::string("foo");  // note the "static"
    //     return *x;
    //   }
    // By using NoDestructor we do not need to involve heap allocation and
    // corresponding pointer following (and hence extra CPU cache usage/needs)
    // on each access:
    //   const std::string& MyString() {
    //     static NoDestructor<std::string> x("foo");
    //     return *x;
    //   }
    // Since C++11 this static-in-a-function pattern results in exactly-once,
    // thread-safe, on-demand construction of an object, and very fast access
    // thereafter (the cost is a few extra cycles).
    // NoDestructor makes accesses even faster by storing the object inline in
    // static storage.
    //
    // Note that:
    // * Since destructor is never called, the object lives on during program exit
    //   and can be safely accessed by any threads that have not been joined.
    // * This static-in-a-function NoDestructor usage pattern should be preferred
    //   to uses of gtl::LazyStaticPtr in new code.
    //
    // Also note that
    //   static NoDestructor<NonPOD> ptr(whatever);
    // can safely replace
    //   static NonPOD* ptr = new NonPOD(whatever);
    // or
    //   static NonPOD obj(whatever);
    // at file-level scope when the safe static-in-a-function pattern is infeasible
    // to use for some good reason.
    // All three of the NonPOD patterns above suffer from the same issue that
    // initialization of that object happens non-thread-safely at
    // a globally-undefined point during initialization of static-storage objects,
    // but NoDestructor<> usage provides both the safety of having the object alive
    // during program exit sequence and the performance of not doing extra memory
    // dereference on access.
    //

    template <typename T>
    class NoDestructor {
      public:
        typedef T element_type;

        // Forwards arguments to the T's constructor: calls T(args...).
        template <typename... Ts,
                  // Disable this overload when it might collide with copy/move.
                  typename std::enable_if<sizeof...(Ts) == sizeof...(Ts)>::type* = nullptr>
    }
}

#endif //NO_DESTRUCTOR_H
