// Spengine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include "lib/core/environment.h"
#include "lib/templates/Windows/winapi_hardware.h"


int main()
{
    HWND window = GetConsoleWindow();
    LPOSVERSIONINFO info=new OSVERSIONINFO;

    spengine::events::Evtquene_tracker tracker = { 
        new spengine::events::EvtQuene(),
        new spengine::events::EvtQuene() 
    };

    spengine::evt_quene_utils::add_evt(
        tracker.system_quene,
        static_cast<uint8_t>(spengine::specification::Capabilities_query),
        static_cast<uint8_t>(spengine::specification::API_Query),
        (void*)NULL
    );

    spengine::evt_quene_utils::consume_evt(
        tracker.system_quene,
        spengine_winapi::capability_query_handler,
        (void*)info
    );
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
