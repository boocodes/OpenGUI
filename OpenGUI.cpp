#include "OpenGUI.h"



int main(int argc, char* argv[])
{
    // entry point
    if (loader_flag)
    {
        show_loader();
        loader_flag = false;
    }
    else if (main_app_flag)
    {
        show_main_app();
    }
}