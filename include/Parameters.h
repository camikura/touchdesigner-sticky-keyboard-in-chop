#pragma once

#include <string>
#include <vector>

using namespace std;

class OP_Inputs;
class OP_ParameterManager;

#pragma region ParNames and ParLabels

// Names of the parameters

constexpr static char ActiveName[] = "Active";
constexpr static char ActiveLabel[] = "Active";

constexpr static char KeysName[] = "Keys";
constexpr static char KeysLabel[] = "Keys";

constexpr static char ModifierName[] = "Modifier";
constexpr static char ModifierLabel[] = "Modifier";

#pragma endregion

#pragma region Menus
#pragma endregion

#pragma region Parameters
class Parameters
{

private:
	vector<string> split(string str, string del);
	vector<string> enable_keys;
	int modifier;

public:
	Parameters();
	~Parameters();

	void setup(OP_ParameterManager*);
	vector<string> evalKeys(const OP_Inputs* input);
	bool evalActive(const OP_Inputs* input);
	int evalModifier(const OP_Inputs* input);
};

#pragma endregion
