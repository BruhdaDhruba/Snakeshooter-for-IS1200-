### Making & Installation

To compile the code, you need the following:
* The files (simply download the zip by clicking on code and "Download ZIP")
* MCB32 toolchain
* A pic32 board connected to the computer via USB

Now, you simply have to enter the MCB32 environment, navigate to the folder and execute the following commands:

The first command is for compiling the code. Here, you'll see if you got any errors:
```
make;
```

The second command will install the compiled files on the chip kit:
```
make install;
```

The game should now start right away, as a menu is not included.

Victory screen is shown if you manage to kill all 5 snakes; otherwise it is game over if a snake touches the gun.
