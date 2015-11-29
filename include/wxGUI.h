#pragma once
#include "App.h"

class wxGUI
{
    App * wx_;

    public:
        wxGUI::wxGUI(int argc, char **argv);
        ~wxGUI();
};
