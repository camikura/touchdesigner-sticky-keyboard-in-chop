#include "keystate.h"

Keystate::Keystate() {}

Keystate::~Keystate() { stop(); }

void Keystate::start() {
  if (!get_running()) {
    set_running(true);
    main_thread_ = thread([this]() {
      while (get_running()) scan();
    });
  }
}

void Keystate::stop() {
  set_running(false);
  if (main_thread_.joinable()) main_thread_.join();
}

void Keystate::scan() {
  if (!get_active() || !test_modifier()) return;

  for (uint8_t i = 0; i < get_keys().size(); i++) {
    if (test_pressed(keys_[i])) {
      if (!get_stat(i)) get_pressed_handler()(i);
      set_stat(i, true);
    } else {
      if (get_stat(i)) get_released_handler()(i);
      set_stat(i, false);
    }
  }

  this_thread::sleep_for(3ms);
}

handler Keystate::get_pressed_handler() { return pressed_handler_; }
void Keystate::set_pressed_handler(handler handler) {
  pressed_handler_ = handler;
}

handler Keystate::get_released_handler() { return released_handler_; }
void Keystate::set_released_handler(handler handler) {
  released_handler_ = handler;
}

bool Keystate::get_stat(uint8_t i) { return stats_.size() > i && stats_[i]; }
void Keystate::set_stat(uint8_t i, bool stat) {
  if (stats_.size() > i) stats_[i] = stat;
}

bool Keystate::get_running() { return running_; }
void Keystate::set_running(bool running) { running_ = running; }

bool Keystate::get_active() { return active_; }
void Keystate::set_active(bool active) { active_ = active; }

vector<string> Keystate::get_keys() { return keys_; }
void Keystate::set_keys(vector<string> keys) {
  keys_ = keys;
  stats_.resize(keys_.size(), false);
}

Modifier Keystate::get_modifier() { return modifier_; }
void Keystate::set_modifier(Modifier modifier) { modifier_ = modifier; }

bool Keystate::test_modifier() {
  // None
  if (get_modifier() == Modifier::kNone)
    return !(GetAsyncKeyState(VK_SHIFT) & 0x8000) &&
           !(GetAsyncKeyState(VK_CONTROL) & 0x8000) &&
           !(GetAsyncKeyState(VK_MENU) & 0x8000);

  // Control
  if (get_modifier() == Modifier::kControl)
    return GetAsyncKeyState(VK_CONTROL) & 0x8000;

  // Alt
  if (get_modifier() == Modifier::kAlt)
    return GetAsyncKeyState(VK_MENU) & 0x8000;

  // Control and Alt
  if (get_modifier() == Modifier::kControlAlt)
    return GetAsyncKeyState(VK_CONTROL) & 0x8000 &&
           GetAsyncKeyState(VK_MENU) & 0x8000;

  // Shift
  if (get_modifier() == Modifier::kShift)
    return GetAsyncKeyState(VK_SHIFT) & 0x8000;

  // Shift and Alt
  if (get_modifier() == Modifier::kShiftAlt)
    return GetAsyncKeyState(VK_SHIFT) & 0x8000 &&
           GetAsyncKeyState(VK_MENU) & 0x8000;

  // Shift and Control
  if (get_modifier() == Modifier::kShiftControl)
    return GetAsyncKeyState(VK_SHIFT) & 0x8000 &&
           GetAsyncKeyState(VK_CONTROL) & 0x8000;

  // Shift and Control and Alt
  if (get_modifier() == Modifier::kShiftControlAlt)
    return GetAsyncKeyState(VK_SHIFT) & 0x8000 &&
           GetAsyncKeyState(VK_CONTROL) & 0x8000 &&
           GetAsyncKeyState(VK_MENU) & 0x8000;

  return true;
}

bool Keystate::test_pressed(string key) {
  if (key == "comma") return GetAsyncKeyState(VK_OEM_COMMA) & 0x8000;
  if (key == "period") return GetAsyncKeyState(VK_OEM_PERIOD) & 0x8000;

  int c = (int)key[0];
  if (c >= 48 && c <= 57) return GetAsyncKeyState(c) & 0x8000;        // 0-9
  if (c >= 97 && c <= 122) return GetAsyncKeyState(c - 32) & 0x8000;  // a-z

  return false;
}
