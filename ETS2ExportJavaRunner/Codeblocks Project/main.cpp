#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
#include <ShellApi.h>
#include <stdio.h>
#include <tchar.h>
#include <conio.h>

using namespace std;

int main(int argc,char* argv[])
{
    //Extract game.sii path from CLI arguments
    string temp = argv[1];

    //Formatting
    string gamepath = "\"" + temp + "\"";
    ifstream exporter("ETS2Export.exe");
    if(exporter.good()) //Checks for exporter in directory
    {

        //Execute exporter and read exit code
        SHELLEXECUTEINFO ShExecInfo = {0};
        ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
        ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
        ShExecInfo.hwnd = NULL;
        ShExecInfo.lpVerb = NULL;
        ShExecInfo.lpFile = "ETS2Export.exe";
        ShExecInfo.lpParameters = gamepath.c_str();
        ShExecInfo.lpDirectory = NULL;
        ShExecInfo.nShow = SW_SHOW;
        ShExecInfo.hInstApp = NULL;
        ShellExecuteEx(&ShExecInfo);
        WaitForSingleObject(ShExecInfo.hProcess, INFINITE);
        CloseHandle(ShExecInfo.hProcess);

        //Check success

        long unsigned int exe;

        exe = GetExitCodeProcess(ShExecInfo.hProcess, &exe);

        if(exe == 0)
        {
           //Success
            return EXIT_SUCCESS;
        }
        else
        {
            //Error
            return EXIT_FAILURE;
        }
    }
    else
    {
        //Error
        return EXIT_FAILURE;
    }
}
