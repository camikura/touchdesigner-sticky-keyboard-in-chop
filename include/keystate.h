#ifndef STICKY_KEYBOARD_IN_CHOP_INCLUDE_KEYSTATE_H_
#define STICKY_KEYBOARD_IN_CHOP_INCLUDE_KEYSTATE_H_

#include <windows.h>

#include <functional>
#include <future>
#include <iostream>
#include <thread>
#include <vector>

using namespace std;

enum class Modifier {
  kIgnore = 0,
  kNone = 1,
  kControl = 2,
  kAlt = 3,
  kControlAlt = 4,
  kShift = 5,
  kShiftAlt = 6,
  kShiftControl = 7,
  kShiftControlAlt = 8,
};

class Keystate;
using handler = std::function<void(uint8_t i)>;

class Keystate {
 public:
  Keystate();
  ~Keystate();

  void start();
  void stop();
  void scan();

  bool get_running();
  void set_running(bool running);

  bool get_active();
  void set_active(bool active);

  vector<string> get_keys();
  void set_keys(vector<string> keys);

  Modifier get_modifier();
  void set_modifier(Modifier modifier);

  bool get_stat(uint8_t i);
  void set_stat(uint8_t i, bool stat);

  void set_pressed_handler(handler handler);
  handler get_pressed_handler();

  void set_released_handler(handler handler);
  handler get_released_handler();

  bool test_modifier();
  bool test_pressed(string key);

 private:
  bool running_ = false;
  bool active_ = false;

  vector<string> keys_ = {};
  vector<bool> stats_ = {};

  thread main_thread_;

  handler pressed_handler_ = [](uint8_t i) {};
  handler released_handler_ = [](uint8_t i) {};

  Modifier modifier_ = Modifier::kIgnore;
};

#endif  // STICKY_KEYBOARD_IN_CHOP_INCLUDE_KEYSTATE_H_
