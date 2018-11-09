# Euro Truck Simulator 2/American Truck Simulator Trip Exporter
Exports all trips from ETS2/ATS Save game

This tool can be improved and it's nowhere near perfect. There might be bugs so please open an issue and I will try to help you.

# Prerequisites
* Windows 7+
* [Microsoft visual C++](https://support.microsoft.com/help/2977003/the-latest-supported-visual-c-downloads)
* [Java](https://www.java.com/download/)
* [SII_Decrypt](https://forum.scssoft.com/viewtopic.php?t=245874) - Unzip the archive and grab SII_Decrypt.exe only. GUI is not needed.
* An ETS2 or ATS Profile

# How to use
Run "ETS2 ATS Trip Exporter.jar" and click the "Open Button". Use the file explorer to open your profile's game.sii file.
Default location of this file's latest version is C:\Users\yourUser\Documents\Euro Truck Simulator 2\profiles\HEXValueOfYourProfile\save\autosave. You may notice that profile names are written in hexadecimal values. You can use an hexadecimal to text converter to read the name in plain text. There are plenty of these tools online, like [this one](https://www.browserling.com/tools/hex-to-text).
After choosing the right file you can click on "Export CSV". The program will use SII_Decrypt to decrypt your save game and it will start reading and saving all the trips. When it's done it will write the CSV file and delete game.txt (result of the decryption process).
You can use Excel or similar programs to read the CSV file (doesn't work with google sheets).

This tool logs any action in the log.txt file. You can use it to troubleshoot issues.

# Reading the data
The results are in a very raw format. Yes, I know it could be improved.
Company names are in the name.location format.
Cargo names are written as the game identifies them, but it's not too hard to understand what is that cargo. 
Trucks are in the brand.model format.
Special deliveries are not supported yet.

# Troubleshooting
### If you can't find any CSV file, please read log.txt to check for any errors.
I'm here to help, so if you can't figure it out on your own you can open a new issue and attach your log.txt file.

# Thank you
Thanks for using this tool. 
Please, keep original credits and download links.

This was inspired by a user request on an Italian ETS2 Forum.
