This software is architectured as follows. 

iptools -This folder hosts the files that are compiled into a static library. 
	image - This folder hosts the files that define an image.
	utility- this folder hosts all operations that can be applied on an image.
	
lib- This folder hosts the static libraries associated with this software.

project- This folder hosts the files that will be compiled into executables.
	bin- This folder hosts the binary executables created in the project directory. includes testimages and examples


***COMPILATION ***

On Linux Enter the project directory in terminal and run make


*** PARAMETERS FILE ***

These are the parameters:
1. the input file name;
2. the output file name;
3. the number of ROIs 1-3;
4. ROI x starting position;
5. ROI y starting position;
6. ROI width Sx;
7. ROI height Sy;
8. the name of the function;
9. the parameters of the function

if multiple ROIs repeat from step 4 for second and third ROI

Ex, input.pgm output.pgm 1 0 0 511 511 func
	input.pgm output.pgm 2 0 0 20 50 func1 funcParam1... 100 150 200 200 func2 funcParam1...

*** Run the program: 
paramteres.txt located in project/bin
go to bin folder and run ./iptool parameters.txt
