// #include <cilk/cilk.h>
#include <cilk/cilk.h>
#include <assert.h>
#include <stdio.h>

int fib(int n) {
  if (n < 2)
    return n;
  int a = cilk_spawn fib(n-1);
  int b = fib(n-2);
  cilk_sync;
  return a + b;
}

int main() {
  int result = fib(30);
  printf("%d\n", result);
  assert(result == 832040);
  return 0;
} 