#include "Event.h"
#include <iostream>

#include <gtkmm.h>
#include <thread>
#include "Utility.h"

struct Wnd {
  Wnd() {
    static const Gtk::Main main = qd::iife([]() {
      const char* _dummy_argv[] = {""};
      const char** _dummy_argv2 = _dummy_argv;
      char*** const _dummy_argv_ptr = const_cast<char***>(&_dummy_argv2);

      int _dummy_argc = 1;
      return Gtk::Main{&_dummy_argc, _dummy_argv_ptr};
    });

    t = std::thread{[]() {
      Gtk::Window window;
      Gtk::Main::run(window);
    }};
  }

  std::thread t;
};

int main() {
  Wnd wnd;
  std::cout << "Hello World!" << std::endl;
  wnd.t.join();
}