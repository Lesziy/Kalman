#pragma once
#include "App.h"

class wxGUI
{
    App * wx_;

    public:
        wxGUI(int argc, char **argv);
        ~wxGUI();
};
