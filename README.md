### Making & Installation
*Note: the game is made specifically to be run on the pic32 Microcontroller with UNO32 Basic I/O Shield*

To compile the code, you need the following:
* The files (simply download the zip by clicking on code and "Download ZIP")
* MCB32 toolchain
* A pic32 board connected to the computer via USB

Enter the MCB32 environment, navigate to the extracted folder for Snakeshooter2 and execute the following commands:

The first command is for compiling the code. Here, you'll see if you got any errors:
```
make;
```

The second command will install the compiled files on the chip kit:
```
make install;
```

The game should now start right away.

### Controls are listed as follows:

* Button 1 is to shoot the dart (NOTE: only one dart can be on the screen at a time, so select snake to begin with wisely)
* Buttons 2 and 3 are to move up and down respectively
* The objective is to kill all 5 snakes before any of them reach the position of the gun
* Victory is shown if objective is completed; otherwise a Game Over screen is displayed

