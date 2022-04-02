#ifndef STICKY_KEYBOARD_IN_CHOP_INCLUDE_PARAM_H_
#define STICKY_KEYBOARD_IN_CHOP_INCLUDE_PARAM_H_

#pragma once

#include <string>
#include <vector>

#include "CPlusPlus_Common.h"
#include "keystate.h"

using namespace std;

class OP_Inputs;
class OP_ParameterManager;

constexpr static char ActiveName[] = "Active";
constexpr static char ActiveLabel[] = "Active";

constexpr static char KeysName[] = "Keys";
constexpr static char KeysLabel[] = "Keys";

constexpr static char ModifierName[] = "Modifier";
constexpr static char ModifierLabel[] = "Modifier";

class Parameters {
 public:
  Parameters();
  ~Parameters();

  void setup(OP_ParameterManager*);
  vector<string> evalKeys(const OP_Inputs* input);
  bool evalActive(const OP_Inputs* input);
  Modifier evalModifier(const OP_Inputs* input);

 private:
  vector<string> split(string str, string del);
  vector<string> enable_keys;
};

#endif  // STICKY_KEYBOARD_IN_CHOP_INCLUDE_PARAM_H_
