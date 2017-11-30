#ifndef MACROS_H
#define MACROS_H

// @def DISALLOW_COPY_AND_ASSIGN(Foo)
// @brief Creates dummy copy constructor and assignment operator declarations.
//
// Use this in the private: section of a class to prevent copying / assignment.
//
// @examplepara
//   @code
//   class Foo {
//     public:
//       Foo() { ... }
//
//     private:
//       DISALLOW_COPY_AND_ASSIGN(Foo);
//     };
//   @endcode
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);               \
  void operator=(const TypeName&)

// @brief A helper to determine the size of a statically allocated array.
// @private
// @tparam T is the type of your object.
// @tparam N is the size of your type T.
//
// @note
// Please see
// http://src.chromium.org/svn/trunk/src/third_party/cld/base/macros.h
// for all the gory details
template <typename T, size_t N>
  char (&ArraySizeHelper(T (&array)[N]))[N];

// @brief Part of a helper to determine the size of a statically allocated
// const array
// @private
//
// @tparam T is your class or variable
// @tparam N is the size of your type T
template <typename T, size_t N>
  char (&ArraySizeHelper(const T (&array)[N]))[N];

// @def arraysize(array)
// @brief Computes the size of the statically allocated array.
// @param array the array to get the size of.
// @return the number of elements in the array.
#define arraysize(array) (sizeof(ArraySizeHelper(array)))

#endif  // MACROS_H
