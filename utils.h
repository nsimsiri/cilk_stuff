#ifndef UTILS_H
#define UTILS_H


// FUNCTION OBJECTS
template <class E>
struct SumF { E operator() (E &a, E &b) const { return a+b; } };

// FUNCTIONS
template <class E, class F> E* map(E* In, int n, F f);
template <class E> E* cloneA(E* In, int n);
template <class E, class BinaryPredicateF> E* serial_scan(E *In, int n, BinaryPredicateF f);
template <class E, class BinaryPredicateF> E* scan(E *In, int n, BinaryPredicateF f);
template <class E, class F> E reduce(E *In, int n, F f);

#endif