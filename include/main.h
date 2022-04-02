#ifndef STICKY_KEYBOARD_IN_CHOP_INCLUDE_MAIN_H_
#define STICKY_KEYBOARD_IN_CHOP_INCLUDE_MAIN_H_

#include <windows.h>

#include <iostream>
#include <string>

#include "CHOP_CPlusPlusBase.h"
#include "CPlusPlus_Common.h"
#include "keystate.h"
#include "param.h"

using namespace std;

class StickyKeyboardInCHOP : public CHOP_CPlusPlusBase {
 public:
  StickyKeyboardInCHOP(const OP_NodeInfo* info);
  ~StickyKeyboardInCHOP();

  virtual void getGeneralInfo(CHOP_GeneralInfo*, const OP_Inputs*, void*);
  virtual bool getOutputInfo(CHOP_OutputInfo*, const OP_Inputs*, void*);
  virtual void getChannelName(int32_t index, OP_String* name, const OP_Inputs*,
                              void* reserved);

  virtual void execute(CHOP_Output*, const OP_Inputs*, void* reserved);

  virtual void setupParameters(OP_ParameterManager* manager, void* reserved1);

 private:
  Parameters params;
  Keystate* keystate;
};

#endif  // STICKY_KEYBOARD_IN_CHOP_INCLUDE_MAIN_H_
