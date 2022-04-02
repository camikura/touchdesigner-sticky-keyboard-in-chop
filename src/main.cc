#include "main.h"

StickyKeyboardInCHOP::StickyKeyboardInCHOP(const OP_NodeInfo *info) {
  keystate = new Keystate();
  keystate->start();
}

StickyKeyboardInCHOP::~StickyKeyboardInCHOP() { delete keystate; }

void StickyKeyboardInCHOP::getGeneralInfo(CHOP_GeneralInfo *ginfo,
                                          const OP_Inputs *inputs,
                                          void *reserved1) {
  ginfo->cookEveryFrameIfAsked = true;
  ginfo->timeslice = false;
  ginfo->inputMatchIndex = 0;
}

bool StickyKeyboardInCHOP::getOutputInfo(CHOP_OutputInfo *info,
                                         const OP_Inputs *inputs,
                                         void *reserved1) {
  keystate->set_keys(params.evalKeys(inputs));
  keystate->set_active(params.evalActive(inputs));
  keystate->set_modifier(params.evalModifier(inputs));

  info->numSamples = 1;
  info->numChannels = (int32_t)keystate->get_keys().size();
  return true;
}

void StickyKeyboardInCHOP::getChannelName(int32_t index, OP_String *name,
                                          const OP_Inputs *inputs,
                                          void *reserved1) {
  name->setString(("k" + keystate->get_keys()[index]).c_str());
}

void StickyKeyboardInCHOP::execute(CHOP_Output *output, const OP_Inputs *inputs,
                                   void *reserved) {
  for (uint8_t i = 0; i < output->numChannels; ++i) {
    output->channels[i][0] = keystate->get_stat(i);
  }
}

void StickyKeyboardInCHOP::setupParameters(OP_ParameterManager *manager,
                                           void *reserved1) {
  params.setup(manager);
}

extern "C" {
DLLEXPORT void FillCHOPPluginInfo(CHOP_PluginInfo *info) {
  info->apiVersion = CHOPCPlusPlusAPIVersion;
  info->customOPInfo.opType->setString("Stickykeyboardin");
  info->customOPInfo.opLabel->setString("Sticky Keyboard In");
  info->customOPInfo.authorName->setString("Akira Kamikura");
  info->customOPInfo.authorEmail->setString("akira.kamikura@gmail.com");

  info->customOPInfo.opIcon->setString("SKI");

  info->customOPInfo.minInputs = 0;
  info->customOPInfo.maxInputs = 0;
}

DLLEXPORT CHOP_CPlusPlusBase *CreateCHOPInstance(const OP_NodeInfo *info) {
  return new StickyKeyboardInCHOP(info);
}

DLLEXPORT void DestroyCHOPInstance(CHOP_CPlusPlusBase *instance) {
  delete (StickyKeyboardInCHOP *)instance;
}
};
