ETS2/ATS Trip Exporter 2.0

Please read this file before using this tool.
This program works fine with both American Truck Simulator and Euro Truck Simulator 2. Please note: It was originally meant for Euro Truck Simulator 2.

Index:

1 - Pre-requisites
2 - How to use
3 - Reading the results
4 - Thank you
5 - In case of bugs / Contact me
6 - Changelog

1- Pre-requisites

Before we can even start, you have to close the game.

First you need to have the visual c++ runtime libraries and Java installed.
You can download them here (those are direct links, from Microsoft):

x86 https://aka.ms/vs/15/release/vc_redist.x86.exe
x64 https://aka.ms/vs/15/release/vc_redist.x64.exe


-- Link source: https://support.microsoft.com/en-us/help/2977003/the-latest-supported-visual-c-downloads

Java: https://www.java.com/download/

Second you need SII Decrypt.
You can download it here: https://forum.scssoft.com/viewtopic.php?t=245874
Direct link: https://www.dropbox.com/s/1kylnpgknt0g5jd/SII_Decrypt%5Bv1.4.2%5D.zip?dl=1

In the zip file there are two files. You don't need the GUI version. You only need SII_Decrypt.
Extract it in this program's folder.


2- How to use 

Open the program by running the "ETS2 ATS Trip Exporter" JAR file. 
You must choose your save game file (game.sii). Click on the "Open..." button and use the pop-up file explorer to find game.sii.
This file is located in Documents > Euro Truck Simulator 2 > profiles > <profile name> > save.
In this directory there are multiple folders. Open the most recent one (usually autosave) and choose game.sii.
The profile name is written in hexadecimal. There are many hexadecimal to text converters online.
After choosing the file press "Export CSV" and wait for a confirmation window.
The program will check for SII_Decrypt.exe and for game.sii availability.
After that it will run SII_Decrypt.exe to decrypt savegame. 
When it's done (should be quite fast, but if you have a large profile it can take a while) the program will find all trips and write them to a CSV File.
If everything went right you should have two more files: Trips.csv and Log.txt. If you cannot find Trips.csv read Log.txt to check for any error. 
If you need help you can contact me (see section 5).  

3- Reading the results

The results are in a very raw format. Yes, I know it could be improved.
Company names are in the name.location format.
Cargo names are written as the game identifies them, but it's not too hard to understand what is that cargo. 
Trucks are in the brand.model format.

4- Thank you

Thanks for using this tool. I don't own SII_Decrypt and this is why my tool does not come with it.
The source code is available for free, but please keep original credits and download links.
I'm not responsible of what you do with this tool.


5- In case of bugs / Contact me

If you want to contact me about this tool, please write at mrchrhd@gmail.com - mrchrhd[at]gmail[dot]com.
You can also find me on steam: mrchrhd.
Suggestions are always welcome.

6- Changelog

V2.2
+ Bugfix
+ Fixed logger

V2.1
+ Bugfix
+ Now should work fine with any save game

V2.0
+ Added Gui
+ Bugfix