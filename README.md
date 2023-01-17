# Blob-Educational-Game

Requires Raylib and windows (I have not been able to download and make raylib work on mac)

Instructions:

Raylib Download
Download Raylib from: https://www.raylib.com/

Open Notepad++, which was installed with Raylib

Open blob.cpp in Notepad++

Hit F6, then follow the steps below:

Updating Run Script
In the command box, replace with text at the bottom of READ ME

Then hit ok.
If adding new classes
In the script, find the line that is SET CPPFILES, add filename.cpp to the existing file names. This adds the cpp to the compile command.







Use text below for set up
---------------------------------------------------------------------------------------------------------------

echo > Setup required Environment
echo -------------------------------------
SET RAYLIB_PATH=C:\raylib\raylib
SET COMPILER_PATH=C:\raylib\w64devkit\bin
ENV_SET PATH=$(COMPILER_PATH)
SET CC=g++
SET CFLAGS=$(RAYLIB_PATH)\src\raylib.rc.data -s -static -O2 -Wall -I$(RAYLIB_PATH)\src -Iexternal -DPLATFORM_DESKTOP
SET LDFLAGS=-lraylib -lopengl32 -lgdi32 -lwinmm
SET CPPFILES=Player.cpp Entity.cpp Door.cpp Wall.cpp Platform.cpp Box.cpp Lever.cpp Plate.cpp

cd $(CURRENT_DIRECTORY)
echo
echo > Clean latest build
echo ------------------------
cmd /c IF EXIST $(NAME_PART).exe del /F $(NAME_PART).exe
echo
echo > Saving Current File
echo -------------------------
npp_save
echo
echo > Compile program
echo -----------------------
$(CC) $(CPPFILES) -o $(NAME_PART).exe $(FILE_NAME) $(CFLAGS) $(LDFLAGS)
echo
echo > Reset Environment
echo --------------------------
ENV_UNSET PATH
echo
echo > Execute program
echo -----------------------
cmd /c IF EXIST $(NAME_PART).exe $(NAME_PART).exe


