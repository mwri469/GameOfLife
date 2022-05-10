# GameOfLife
 My beginner project in C

 ## Usage
 To change the size of the map used in the game, change the global variables: NUM_ROWS and NUM_COLS.

 I have created the following functions to create objects within the map:
    -CreateGlider()
    -CreatePentaDecathlon()
    -CreateGliderGun()
    -CreateSquare()
Note that for this implementation, I have used 'position' as the input for where to create the top left corner of the patterns.
I understand this is very unintuitive to use, so have also included the PrintPositions() function that will display every position
available to the terminal. 

When the code is running, it will ask for a number of iterations to run through. To run forever, use a very big number.
To iterate automatically, simply enter "1\n" to the input when asked to do another iteration.
