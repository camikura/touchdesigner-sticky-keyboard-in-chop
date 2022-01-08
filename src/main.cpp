/* Shared Use License: This file is owned by Derivative Inc. (Derivative)
 * and can only be used, and/or modified for use, in conjunction with
 * Derivative's TouchDesigner software, and only if you are a licensee who has
 * accepted Derivative's TouchDesigner license or assignment agreement
 * (which also govern the use of this file). You may share or redistribute
 * a modified version of this file provided the following conditions are met:
 *
 * 1. The shared file or redistribution must retain the information set out
 * above and this list of conditions.
 * 2. Derivative's name (Derivative Inc.) or its trademarks may not be used
 * to endorse or promote products derived from this file without specific
 * prior written permission from Derivative.
 */

#include "main.h"

#include <windows.h>
#include <vector>
#include <string>
#include <iostream>

#include "CHOP_CPlusPlusBase.h"
#include "Parameters.h"

using namespace std;

class StickyKeyboardInCHOP : public CHOP_CPlusPlusBase
{
private:
	vector<string> keydown_keys;
	bool active;
	int modifier;

	bool testModifierKey();
	bool getKeyPressed(string);

	Parameters params;

public:
	StickyKeyboardInCHOP(const OP_NodeInfo *info)
	{
		active = false;
		modifier = 0;
	}

	virtual ~StickyKeyboardInCHOP()
	{
	}

	void getGeneralInfo(CHOP_GeneralInfo *ginfo, const OP_Inputs *inputs, void *reserved1)
	{
		ginfo->cookEveryFrameIfAsked = true;
		ginfo->timeslice = false;
		ginfo->inputMatchIndex = 0;
	}

	bool getOutputInfo(CHOP_OutputInfo *info, const OP_Inputs *inputs, void *reserved1)
	{
		keydown_keys = params.evalKeys(inputs);
		active = params.evalActive(inputs);
		modifier = params.evalModifier(inputs);

		info->numSamples = 1;
		info->numChannels = (int32_t)keydown_keys.size();
		return true;
	}

	void getChannelName(int32_t index, OP_String *name, const OP_Inputs *inputs, void *reserved1)
	{
		name->setString(('k' + keydown_keys[index]).c_str());
	}

	void execute(CHOP_Output *output, const OP_Inputs *inputs, void *reserved)
	{
		for (int i = 0; i < output->numChannels; ++i)
		{
			string key = keydown_keys[i];
			output->channels[i][0] = getKeyPressed(key);
		}
	}

	void setupParameters(OP_ParameterManager *manager, void *reserved1)
	{
		params.setup(manager);
	}
};

bool StickyKeyboardInCHOP::testModifierKey()
{
	// None
	if (modifier == 1)
		return !(GetAsyncKeyState(VK_SHIFT) & 0x8000) && !(GetAsyncKeyState(VK_CONTROL) & 0x8000) && !(GetAsyncKeyState(VK_MENU) & 0x8000);

	// Control
	if (modifier == 2)
		return GetAsyncKeyState(VK_CONTROL) & 0x8000;

	// Alt
	if (modifier == 3)
		return GetAsyncKeyState(VK_MENU) & 0x8000;

	// Control and Alt
	if (modifier == 4)
		return GetAsyncKeyState(VK_CONTROL) & 0x8000 && GetAsyncKeyState(VK_MENU) & 0x8000;

	// Shift
	if (modifier == 5)
		return GetAsyncKeyState(VK_SHIFT) & 0x8000;

	// Shift and Alt
	if (modifier == 6)
		return GetAsyncKeyState(VK_SHIFT) & 0x8000 && GetAsyncKeyState(VK_MENU) & 0x8000;

	// Shift and Control
	if (modifier == 7)
		return GetAsyncKeyState(VK_SHIFT) & 0x8000 && GetAsyncKeyState(VK_CONTROL) & 0x8000;

	// Shift and Control and Alt
	if (modifier == 8)
		return GetAsyncKeyState(VK_SHIFT) & 0x8000 && GetAsyncKeyState(VK_CONTROL) & 0x8000 && GetAsyncKeyState(VK_MENU) & 0x8000;

	return true;
};

bool StickyKeyboardInCHOP::getKeyPressed(string key)
{
	// active flag test
	if (!active)
		return false;

	// modifier key test
	if (!testModifierKey())
		return false;

	if (key == "comma")
		return GetAsyncKeyState(VK_OEM_COMMA) & 0x8000;

	if (key == "period")
		return GetAsyncKeyState(VK_OEM_PERIOD) & 0x8000;

	int code = (int)key[0];

	// 0 to 9
	if (code >= 48 && code <= 57)
	{
		return GetAsyncKeyState(code) & 0x8000;
	}

	// a to z
	if (code >= 97 && code <= 122)
	{
		return GetAsyncKeyState(code - 32) & 0x8000;
	}

	return false;
}

extern "C"
{
	DLLEXPORT void FillCHOPPluginInfo(CHOP_PluginInfo *info)
	{
		info->apiVersion = CHOPCPlusPlusAPIVersion;
		info->customOPInfo.opType->setString("Stickykeyboardin");
		info->customOPInfo.opLabel->setString("Sticky Keyboard In");
		info->customOPInfo.authorName->setString("Akira Kamikura");
		info->customOPInfo.authorEmail->setString("akira.kamikura@gmail.com");

		info->customOPInfo.opIcon->setString("SKI");

		info->customOPInfo.minInputs = 0;
		info->customOPInfo.maxInputs = 0;
	}

	DLLEXPORT CHOP_CPlusPlusBase *CreateCHOPInstance(const OP_NodeInfo *info)
	{
		return new StickyKeyboardInCHOP(info);
	}

	DLLEXPORT void DestroyCHOPInstance(CHOP_CPlusPlusBase *instance)
	{
		delete (StickyKeyboardInCHOP *)instance;
	}
};
