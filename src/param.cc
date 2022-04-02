#include "param.h"

Parameters::Parameters() {
  for (char c = '0'; c <= '9'; c++) {
    string str(1, c);
    enable_keys.push_back(str);
  }
  for (char c = 'a'; c <= 'z'; c++) {
    string str(1, c);
    enable_keys.push_back(str);
  }
}

Parameters::~Parameters() {}

vector<string> Parameters::split(string str, string del = " ") {
  vector<string> result;
  size_t start = 0;
  size_t end = str.find(del);
  while (end != -1) {
    result.push_back(str.substr(start, end - start));
    start = end + del.size();
    end = str.find(del, start);
  }
  result.push_back(str.substr(start, end - start));
  return result;
}

vector<string> Parameters::evalKeys(const OP_Inputs *input) {
  string str = input->getParString(KeysName);

  vector<string> keys;
  for (auto k : split(str)) {
    if (k == "keycomma")
      keys.push_back("comma");
    else if (k == "keyperiod")
      keys.push_back("period");
    else {
      for (auto ek : enable_keys) {
        if (k == ek) keys.push_back(k);
      }
    }
  }

  return keys;
}

bool Parameters::evalActive(const OP_Inputs *input) {
  return input->getParInt(ActiveName) == 0;
}

Modifier Parameters::evalModifier(const OP_Inputs *input) {
  return (Modifier)input->getParInt(ModifierName);
}

void Parameters::setup(OP_ParameterManager *manager) {
  {
    const char *names[] = {"On", "Off"};
    const char *labels[] = {"On", "Off"};

    OP_StringParameter p;
    p.name = ActiveName;
    p.label = ActiveLabel;
    p.page = "Keys";
    p.defaultValue = names[0];
    OP_ParAppendResult res = manager->appendMenu(p, 2, names, labels);

    assert(res == OP_ParAppendResult::Success);
  }
  {
    OP_StringParameter p;
    p.name = KeysName;
    p.label = KeysLabel;
    p.page = "Keys";
    OP_ParAppendResult res = manager->appendString(p);
    assert(res == OP_ParAppendResult::Success);
  }
  {
    const char *names[] = {"Ignore",
                           "None",
                           "Control",
                           "Alt",
                           "Controlandalt",
                           "Shift",
                           "Shiftandalt",
                           "Shiftandcontrol",
                           "Shiftandcontrolandalt"};
    const char *labels[] = {"Ignore",
                            "None",
                            "Control",
                            "Alt",
                            "Control and Alt",
                            "Shift",
                            "Shift and Alt",
                            "Shift and Control",
                            "Shift and Control and Alt"};

    OP_StringParameter p;
    p.name = ModifierName;
    p.label = ModifierLabel;
    p.page = "Keys";
    p.defaultValue = names[0];
    OP_ParAppendResult res = manager->appendMenu(p, 9, names, labels);

    assert(res == OP_ParAppendResult::Success);
  }
}
