#include "OpenGUI.h"

int main(void)
{
    // entry point
    if (loader_flag)
    {
        show_loader();
    }
    else if (main_app_flag)
    {
        show_main_app();
    }
}