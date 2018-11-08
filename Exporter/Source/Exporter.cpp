#include <iostream>
#include <string>
#include <fstream>
#include <exception>
#include <cstdio>
#include <windows.h>
#include <ShellApi.h>
#include <vector>
#include <sstream>
#include <stdio.h>
#include <tchar.h>
#include <conio.h>
using namespace std;

bool Decrypt(string game);
bool Read();
bool CSVExport();
bool IsDecryptorHere();
bool isFileHere(const char* path);

//Data Structure
struct trip
{
    string sourceCity;
    string sourceCompany;
    string destinationCity;
    string destinationCompany;
    string cargo ;
    string gainedXP;
    string income;
    string fines;
    string distance;
    string damage;
    string truck;
    string typeContract;
};


//Global variables
vector<trip> tripList; //List of saved trips

/*
    Main. Calls more specific functions and checks for correct execution.
    If execution fails, it will try to call again the function, for a maximum of 3 tries.
    Gets game.sii path from CLI arguments.
*/
int main(int argc,char* argv[]) //Get path from program call
{
    //Logger Start
    ofstream logger;
    logger.open("Log.txt");

    logger << "[INFO] ETS2/ATS Trip Exporter V 2.0 started" << endl;

    //Console handle for better verbose readability
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    //Number of tries made to call a function - Counter
    int nRetries = 0;
    //Boolean checking result of function execution - true = success / false = failure
    bool success = false;
    do
    {
        try
        {
            //Counter update
            nRetries++;
            //Gets path from CLI arguments to call Decrypt function
            string gamepath = argv[1];
            logger << "[INFO] Game.sii path: " << gamepath << endl;

            //Calls function that returns either true or false
            logger.close();
            success = Decrypt(gamepath); //Decrypt will execute SII Decrypt and create a .txt file. It returns true if everything went right or false if something failed.
            if(success == false)
            {
                SetConsoleTextAttribute(hConsole, 12); //Set console text color to red
                logger.open("Log.txt", std::ofstream::app);
                cout << "[GRAVE ERROR] Error. Retrying." << endl;
                logger << "[GRAVE ERROR] Error. Retrying." << endl;
                logger.close();
                SetConsoleTextAttribute(hConsole, 15); //Reset console text color
            }
        }
        catch(exception& e) //In case of an exception it will terminate the process
        {
            terminate();
        }
    }
    while(nRetries < 3 && success == false);
    //If it didn't work after 3 times the program will exit - Should never be triggered
    if(success == false)
    {
        SetConsoleTextAttribute(hConsole, 12); //Set console text color to red
        logger.open("Log.txt", std::ofstream::app);
        cout << "[GRAVE ERROR] Too many errors. The program is terminating." << endl;
        logger << "[GRAVE ERROR] Too many errors. The program is terminating." << endl;
        logger.close();
        SetConsoleTextAttribute(hConsole, 15); //Reset console text color
        return EXIT_FAILURE;
    }
    //if it worked resets counter and status
    else
    {
        nRetries = 0;
        success = false;
        do
        {
            try
            {
                //Counter update
                nRetries++;
                //Calls function that returns either true or false
                success = Read(); //Read will read the .txt file created in Decrypt function and format all the data.
                if(success == false)
                {
                    SetConsoleTextAttribute(hConsole, 12); //Set console text color to red
                    logger.open("Log.txt", std::ofstream::app);
                    cout << "[GRAVE ERROR] Error. Retrying." << endl;
                    logger << "[GRAVE ERROR] Error. Retrying." << endl;
                    logger.close();
                    SetConsoleTextAttribute(hConsole, 15); //Reset console text color
                }
            }
            catch(exception& e) //In case of an exception it will terminate the process - Should never be triggered
            {
                terminate();
            }
        }
        while(nRetries < 3 && success == false);
        //If it didn't work after 3 times the program will exit
        if(success == false)
        {
            SetConsoleTextAttribute(hConsole, 12); //Set console text color to red
            logger.open("Log.txt", std::ofstream::app);
            cout << "[GRAVE ERROR] Too many errors. The program is terminating." << endl;
            logger << "[GRAVE ERROR] Too many errors. The program is terminating." << endl;
            logger.close();
            SetConsoleTextAttribute(hConsole, 15); //Reset console text color
            return EXIT_FAILURE;
        }
        //if it worked resets counter and status
        else
        {
            nRetries = 0;
            success = false;
            do
            {
                try
                {
                    //Counter update
                    nRetries++;
                    //Calls function that returns either true or false
                    success = CSVExport(); //CSVExport will create a .csv excel file with all the data obtained in Read().
                    if(success == false)
                    {
                        SetConsoleTextAttribute(hConsole, 12); //Set console text color to red
                        logger.open("Log.txt", std::ofstream::app);
                        cout << "[GRAVE ERROR] Error. Retrying." << endl;
                        logger << "[GRAVE ERROR] Error. Retrying." << endl;
                        logger.close();
                        SetConsoleTextAttribute(hConsole, 15); //Reset console text color
                    }
                }
                catch(exception& e) //In case of an exception it will terminate the process - Should never be triggered
                {
                    terminate();
                }
            }
            while(nRetries < 3 && success == false);
            //If it didn't work after 3 times the program will exit
            if(success == false)
            {
                SetConsoleTextAttribute(hConsole, 12); //Set console text color to red
                logger.open("Log.txt", std::ofstream::app);
                cout << "[GRAVE ERROR] Too many errors. The program is terminating." << endl;
                logger << "[GRAVE ERROR] Too many errors. The program is terminating." << endl;
                logger.close();
                SetConsoleTextAttribute(hConsole, 15); //Reset console text color
                return EXIT_FAILURE;
            }
            //Program executed correctly so no point in leaving it open. :P
            else
            {
                return 0;
            }
        }
    }
}

/*
    Decrypt. Cheks for SII_Decrypt.exe. Checks input passed from main and decrypts file to game.txt.
    In case of errors function terminates back to main.
*/
bool Decrypt(string game)
{
    //Logger
    ofstream logger;
    logger.open("Log.txt", std::ofstream::app);

    //Console handle for better verbose readability
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(hConsole, 14); //Set console text color to yellow
    cout << endl << "---- Step 1 of 3: Decrypt save data ----" << endl;
    logger << endl << "---- Step 1 of 3: Decrypt save data ----" << endl;
    SetConsoleTextAttribute(hConsole, 15); //Reset console text color

    cout << "[INFO] Trying to find SII_Decrypt.exe..." << endl;
    logger << "[INFO] Trying to find SII_Decrypt.exe..." << endl;
    //Checks if SII_Decrypt.exe is available
    bool fileFound = IsDecryptorHere();
    if(fileFound == false)
    {
        //If not returns an error end exits Decrypt() function
        SetConsoleTextAttribute(hConsole, 12); //Set console text color to red
        cout << "[ERROR] Error: SII_Decrypt.exe not found." << endl << endl;
        logger << "[ERROR] Error: SII_Decrypt.exe not found." << endl << endl;
        SetConsoleTextAttribute(hConsole, 15); //Reset console text color
        logger.close();
        return false;
    }
    else
    {
        //Verbose
        SetConsoleTextAttribute(hConsole, 10); //Set console text color to green
        cout << "[SUCCESS] SII_Decrypt.exe found." << endl;
        logger << "[SUCCESS] SII_Decrypt.exe found." << endl;
        SetConsoleTextAttribute(hConsole, 15); //Reset console text color

        //Else checks game.sii availability
        cout << endl << "[INFO] Checking input..." << endl;
        fileFound = isFileHere(game.c_str()); //Checks if game.sii is there
        if(fileFound == false)
        {
            SetConsoleTextAttribute(hConsole, 12); //Set console text color to red
            //If not returns an error end exits Decrypt() function
            cout << "[ERROR] Error: game.sii not found." << endl << endl;
            logger << "[ERROR] Error: game.sii not found." << endl << endl;
            SetConsoleTextAttribute(hConsole, 15); //Reset console text color
            logger.close();
            return false;
        }
        else
        {
            SetConsoleTextAttribute(hConsole, 10); //Set console text color to green
            cout << "[SUCCESS] game.sii found." << endl << endl;
            SetConsoleTextAttribute(hConsole, 15); //Reset console text color

            //Decrypt
            cout << "[INFO] Decrypting..." << endl;

            //Variables to call SII_Decrypt
            string variables = "\"" + game + "\" game.txt";

            //SII_Decrypt Execution. Gets return code.
            SHELLEXECUTEINFO ShExecInfo = {0};
            ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
            ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
            ShExecInfo.hwnd = NULL;
            ShExecInfo.lpVerb = NULL;
            ShExecInfo.lpFile = "SII_Decrypt.exe";
            ShExecInfo.lpParameters = variables.c_str();
            ShExecInfo.lpDirectory = NULL;
            ShExecInfo.nShow = SW_SHOW;
            ShExecInfo.hInstApp = NULL;
            ShellExecuteEx(&ShExecInfo);
            WaitForSingleObject(ShExecInfo.hProcess, INFINITE);
            CloseHandle(ShExecInfo.hProcess);


            long unsigned int exe = GetExitCodeProcess(ShExecInfo.hProcess, &exe);

            //Checks for successful execution (return code > than 32)
            if(exe == 0)
            {
                SetConsoleTextAttribute(hConsole, 10); //Set console text color to green
                cout << "[SUCCESS] Decrypted!" << endl;
                logger << "[SUCCESS] Decrypted!" << endl;
                SetConsoleTextAttribute(hConsole, 15); //Reset console text color
                Sleep(2000); //Wait for file building
                logger.close();
                return true;
            }
            else
            {
                SetConsoleTextAttribute(hConsole, 12); //Set console text color to red
                cout << "[ERROR] Error code: " << exe << " Please retry. If errors still occur, please contact dev (write down this error code!!!)." << endl;
                logger << "[ERROR] Error code: " << exe << " Please retry. If errors still occur, please contact dev (write down this error code!!!)." << endl;
                SetConsoleTextAttribute(hConsole, 15); //Reset console text color
                logger.close();
                return false;
            }

        }
    }

}

/*
    Reads, formats and stores all the data.
*/
bool Read()
{
    //Logger
    ofstream logger;
    logger.open("Log.txt", std::ofstream::app);

    //Console handle for better verbose readability
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(hConsole, 14); //Set console text color to yellow
    cout << endl << "---- Step 2 of 3: Read and format data ----" << endl;
    logger << endl << "---- Step 2 of 3: Read and format data ----" << endl;
    SetConsoleTextAttribute(hConsole, 15); //Reset console text color

    string deliverylog = "";
    ifstream game;
    string temp = "";
    int line1 = 0;
    bool found = false;
    //Open File
    game.open("game.txt");
    while(getline(game, temp))
    {
        line1++;
        //Find ID
        if(temp.find("delivery_log:", 0) != string::npos )
        {
            deliverylog =  temp;

            SetConsoleTextAttribute(hConsole, 10); //Set console text color to green
            cout << "[SUCCESS] Delivery Log ID found: " << deliverylog << " - Line " << line1 << "." << endl;
            logger << "[SUCCESS] Delivery Log ID found: " << deliverylog << " - Line " << line1 << "." << endl;
            SetConsoleTextAttribute(hConsole, 15); //Reset console text color
            found = true;
            break;
        }
    }
    game.close();
    if(found == false) //Error while finding id. It's possible to get this if save format is not default.
    {
        SetConsoleTextAttribute(hConsole, 12); //Set console text color to red
        cout << "[GRAVE ERROR] Error. Could not find Delivery Log ID. Check your save format (config.cfg). Please retry. If it doesn't work, contact dev." << endl;
        logger << "[GRAVE ERROR] Error. Could not find Delivery Log ID. Check your save format (config.cfg). Please retry. If it doesn't work, contact dev." << endl;
        SetConsoleTextAttribute(hConsole, 15); //Reset console text color
        logger.close();
        return false;
    }
    else //Formatting ID and saving array
    {
        //Since the found string is like delivery_log: _nameless.24f.4266.54d0 we have to get the string from the second _ so the program cuts the string twice
        size_t position = deliverylog.find("_");
        deliverylog = deliverylog.substr(position+1);
        position = deliverylog.find("_");
        deliverylog = deliverylog.substr(position);

        SetConsoleTextAttribute(hConsole, 10); //Set console text color to green
        cout << "[SUCCESS]Formatted ID is: " << deliverylog << endl;
        logger << "[SUCCESS]Formatted ID is: " << deliverylog << endl;
        SetConsoleTextAttribute(hConsole, 15); //Reset console text color

        found = false; //Check
        string parameter = "delivery_log : " + deliverylog;

        //Now the list of the jobs is needed so we must obtain the array from the file. Since it's variable it will be saved in a string vector
        vector<string> jobsIDS;

        string formatted = "";
        int line2 = 0;
        game.open("game.txt");
        while(getline(game, temp))
        {
            line2++;
            //Find array
            if(temp.find(parameter, 0) != string::npos && line2 > line1)
            {
                SetConsoleTextAttribute(hConsole, 10); //Set console text color to green
                cout << "[SUCCESS] Array Found." << endl;
                logger << "[SUCCESS] Array Found." << endl;
                SetConsoleTextAttribute(hConsole, 15); //Reset console text color

                getline(game, temp); //version, no need so skip
                getline(game, temp); //entries, more useful
                if(temp == "entries: 0")
                {
                    cout << "[INFO] No trips found. -- !This is not an error!" << endl;
                    logger << "[INFO] No trips found. -- !This is not an error!" << endl;
                    break;
                }
                else
                {
                    while(getline(game, temp))
                    {
                        if(temp.find("entries[", 0) != string::npos)
                        {
                            position = temp.find("_");
                            formatted = temp.substr(position); //String is like entries[0]: _nameless.24f.4150.fa80 so the program cuts the whole thing from _ to the end of the line

                            SetConsoleTextAttribute(hConsole, 10); //Set console text color to green
                            cout << "[SUCCESS] Found: " << formatted << " - Saving!"<< endl;
                            logger << "[SUCCESS] Found: " << formatted << " - Saving!"<< endl;
                            SetConsoleTextAttribute(hConsole, 15); //Reset console text color

                            jobsIDS.push_back(formatted); //Save array entry inside vector
                            found = true; //Check
                        }
                    }
                    break;
                }
            }
        }
        game.close();
        if(found == false)
        {
            logger.close();
            return false;
        }


        bool done = false; //Checks if a job's data is saved
        //After obtaining job ids we have to record their data. as always, it's variable so vector it is!

        game.open("game.txt");
        string sourceCity, sourceCompany, destinationCity, destinationCompany, cargo, XP, income, km, damage, fines, truck, type;
        while(getline(game, temp) && jobsIDS.size() > 0)
        {
            if(temp.find("delivery_log_entry : " + jobsIDS.at(0), 0) != string::npos)
            {
                //After finding the log entry just select things that are needed
                getline(game, temp); // params: 23, useless, so skip
                while(getline(game, temp))
                {
                    type == "";
                    if(temp.find("params[1]", 0) != string::npos) //Source data
                    {
                        position = temp.find("\"");
                        formatted = temp.substr(position+1);                     //String is like params[1]: "company.volatile.exomar.roma" so the program cuts from p to " inculded

                        //Remove company
                        position = formatted.find(".");
                        formatted = formatted.substr(position+1);
                        position = formatted.find("\"");
                        formatted = formatted.substr(0,position); //Remove final "


                        //remove second entry
                        position = formatted.find(".");
                        formatted = formatted.substr(position+1);

                        sourceCompany = formatted; //Save company

                        //remove third entry
                        position = formatted.find(".");
                        formatted = formatted.substr(position+1);
                        //Uppercase first letter
                        formatted[0] = toupper(formatted[0]);

                        sourceCity = formatted; //Save city

                        cout << endl << "[INFO] Src. comp.: " << sourceCompany << " - Src. city: " << sourceCity << endl;
                        logger << endl << "[INFO] Src. comp.: " << sourceCompany << " - Src. city: " << sourceCity << endl;

                    }
                    if(temp.find("params[2]", 0) != string::npos) //Destination data
                    {
                        position = temp.find("\"");
                        formatted = temp.substr(position+1); //String is like params[1]: "company.volatile.exomar.roma" so the program cuts the whole thing from p to "

                        //Remove company
                        position = formatted.find(".");
                        formatted = formatted.substr(position+1);
                        position = formatted.find("\"");
                        formatted = formatted.substr(0,position); //Remove final "

                        //remove second entry
                        position = formatted.find(".");
                        formatted = formatted.substr(position+1);

                        destinationCompany = formatted; //Save company

                        //remove third entry
                        position = formatted.find(".");
                        formatted = formatted.substr(position+1);

                        //Uppercase first letter
                        formatted[0] = toupper(formatted[0]);

                        destinationCity =  formatted; //Save city

                        cout << "[INFO] Dest. comp.: " << destinationCompany << " - Dest. city: " << destinationCity << endl;
                        logger << "[INFO] Dest. comp.: " << destinationCompany << " - Dest. city: " << destinationCity << endl;
                    }
                    if(temp.find("params[3]", 0) != string::npos) //Cargo
                    {
                        position = temp.find("\"");
                        formatted = temp.substr(position+1);

                        //Remove cargo
                        position = formatted.find(".");
                        formatted = formatted.substr(position+1);
                        position = formatted.find("\"");
                        formatted = formatted.substr(0,position); //Remove final "
                        cargo = formatted;

                        cout << "[INFO] Cargo: " << cargo << endl;
                        logger << "[INFO] Cargo: " << cargo << endl;
                    }
                    if(temp.find("params[4]", 0) != string::npos) //XP
                    {
                        position = temp.find(": ");
                        formatted = temp.substr(position+1);
                        XP = formatted;

                        cout << "[INFO] XP: " << XP << endl;
                        logger << "[INFO] XP: " << XP << endl;
                    }
                    if(temp.find("params[5]", 0) != string::npos) //Income
                    {
                        position = temp.find(": ");
                        formatted = temp.substr(position+1);
                        income = formatted;

                        cout << "[INFO] Income: " << income << endl;
                        logger << "[INFO] Income: " << income << endl;
                    }
                    if(temp.find("params[6]", 0) != string::npos) //Distance
                    {
                        position = temp.find(": ");
                        formatted = temp.substr(position+1);
                        km = formatted;

                        cout << "[INFO] Distance: " << km << endl;
                        logger << "[INFO] Distance: " << km << endl;
                    }
                    if(temp.find("params[7]", 0) != string::npos) //Cargo damage
                    {
                        position = temp.find("\"");
                        formatted = temp.substr(position+1);
                        position = formatted.find("\"");
                        formatted = formatted.substr(0,position); //Remove final "
                        //Damage formatting
                        float temp1 = stof(formatted); //converts string to float 0.061
                        temp1 = temp1 * 100; //6.1
                        ostringstream convert;
                        convert << temp1;

                        formatted = convert.str(); //Puts back into string

                        damage = formatted + "%"; //Final formatting

                        cout << "[INFO] Cargo damage: " << damage << endl;
                        logger << "[INFO] Cargo damage: " << damage << endl;
                    }
                    if(temp.find("params[14]", 0) != string::npos) //Fines
                    {
                        position = temp.find(": ");
                        formatted = temp.substr(position+1);
                        fines = formatted;

                        cout << "[INFO] Total fines: " << fines << endl;
                        logger << "[INFO] Total fines: " << fines << endl;
                    }
                    if(temp.find("params[16]", 0) != string::npos) //Truck
                    {
                        position = temp.find("\"");
                        formatted = temp.substr(position+1, temp.length()-1); //String is like params[1]: "vehicle.iveco.strails" so the program cuts the whole thing from v to s

                        //Remove vehicle
                        position = formatted.find(".");
                        formatted = formatted.substr(position+1);
                        position = formatted.find("\"");
                        formatted = formatted.substr(0,position); //Remove final "

                        truck = formatted;

                        cout << "[INFO] Truck: " << truck << endl;
                        logger << "[INFO] Truck: " << truck << endl;
                    }
                    if(temp.find("params[18]", 0) != string::npos) //Cargo Type
                    {
                        position = temp.find(": ");
                        formatted = temp.substr(position+1);

                        if(formatted == " quick")
                        {
                            formatted = "Quick Job";
                        }
                        if(formatted == " compn")
                        {
                            formatted = "Freight Market";
                        }
                        if(formatted == " on_compn")
                        {
                            formatted = "External Contract (World of Trucks)";
                        }
                        if(formatted == " freerm")
                        {
                            formatted = "Free Roam";
                            sourceCompany = "Free Roam";
                            sourceCity = "Free Roam";
                            destinationCity = "Free Roam";
                            destinationCompany = "Free Roam";
                            damage = "0%"; //Bugged better set it to 0%
                            truck = "Free Roam";
                        }
                        if(formatted == " spec_oversize")
                        {
                            formatted = "Special"; //Special but unsupported (have to review this)
                        }

                        type = formatted;
                        cout << "[INFO] Cargo Type: " << type << endl;
                        logger << "[INFO] Cargo Type: " << type << endl;

                        //Other ways crashed so yay
                        trip temporary = (trip)
                        {
                            sourceCity, sourceCompany, destinationCity, destinationCompany, cargo, XP, income, fines, km, damage, truck, type
                        };
                        tripList.push_back(temporary);
                        done = true;

                    }
                    if(temp.find("}", 0) != string::npos) //If array ends
                    {
                        //Other ways crashed so yay
                        trip temporary = (trip)
                        {
                            sourceCity, sourceCompany, destinationCity, destinationCompany, cargo, XP, income, fines, km, damage, truck, type
                        };
                        tripList.push_back(temporary);
                        done = true;
                    }
                    if(done == true) //Checks if it's done with a job
                    {
                        break;
                    }
                }
                jobsIDS.erase(jobsIDS.begin());
                done = false;
            }
        }
        game.close();
        logger.close();
    }
    return true;
}

/*
    The data is written in a .csv file
*/
bool CSVExport()
{
    //Log output
    ofstream logger;
    logger.open("Log.txt", std::ofstream::app);

    //Console handle for better verbose readability
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(hConsole, 14); //Set console text color to yellow
    cout << endl << "---- Step 3 of 3: Export data to CSV ----" << endl;
    logger << endl << "---- Step 3 of 3: Export data to CSV ----" << endl;
    SetConsoleTextAttribute(hConsole, 15); //Reset console text color

    ofstream csv;
    csv.open("Trips.csv");
    cout << "[INFO] Writing data..." << endl;
    logger << "[INFO] Writing data..." << endl;
    csv << "Source City; Source Company; Destination City; Destination Company; Cargo; Cargo Damage; Gained XP; Income; Fines; Distance; Truck; Cargo Type;\n";
    csv << "\n";
    while(tripList.size() > 0)
    {
        csv << tripList.at(0).sourceCity << ";" << tripList.at(0).sourceCompany << ";" << tripList.at(0).destinationCity << ";" << tripList.at(0).destinationCompany << ";" << tripList.at(0).cargo  << ";" << tripList.at(0).damage << ";" << tripList.at(0).gainedXP << ";" << tripList.at(0).income << ";" << tripList.at(0).fines << ";" << tripList.at(0).distance << ";" << tripList.at(0).truck << ";" << tripList.at(0).typeContract << ";\n";
        tripList.erase(tripList.begin());
    }

    SetConsoleTextAttribute(hConsole, 10); //Set console text color to green
    cout << "[SUCCESS] Done. Removing temp game.txt file..." << endl;
    logger << "[SUCCESS] Done. Removing temp game.txt file..." << endl;
    remove("game.txt");
    SetConsoleTextAttribute(hConsole, 15); //Reset console text color
    logger << endl << "[SUCCESS] Success! Terminated." << endl;
    logger.close();
    csv.close();
    return true;
}

/*
    Checks if SII_Decrypt.exe is in this program's folder
*/
bool IsDecryptorHere()
{
    ifstream decryptor("SII_Decrypt.exe");
    return decryptor.good();
}

/*
    Checks if file exists
*/
bool isFileHere(const char* path)
{
    ifstream file(path);
    return file.good();
}
