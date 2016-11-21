#include "Event.h"
#include <iostream>

struct A {
  void f(int i) { std::cout << i << " called in A" << std::endl; }
};

int main() {
  qd::Event<int> e;
  qd::ObserverSlot<int> a_slot;
  qd::ObserverSlot<int> s1;

  A a;

  e.addObserver(a_slot, std::bind(&A::f, std::addressof(a), std::placeholders::_1));
  e.addObserver(s1, [](int i) { std::cout << i << " called 1" << std::endl; });

  auto s2 = std::move(s1);

  // e.~Event<int>();
  // new (std::addressof(e)) qd::Event<int>{};

  e.notifyObservers(5);
}