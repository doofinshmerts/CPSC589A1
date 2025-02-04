# CPSC589A1Q4
Build instructions:
Originaly built in Ubuntu Linux
1. open the Terminal
2. navigate to the root directory containing CMakeLists.txt
3. run the command: cmake -Bbuild
4. navigate to the build directory that was created
5. run the command: make
6. to run the program, run the command: ./CPSC589A1Q5

## INFO:
The vertical and horizontal white lines are the y and x axis lines. 
The green points are the input points P0, P1, P2, P3.
The blue points are the input points after being translated by x and y
The red curve is the polynomial curve P(u)
The orange curve is the bezier curve Q(u)


## Controlls:
* Mouse drag points: To move the points, select a point (by left clicking on it, and holding the left mouse button) then drag the point to the desired location and release the left mouse button.
* Show Bezier Q(u) / Show P(u) : Shows the bezier curve Q(u) created from the input points, or the polynomial curve P(u) from the input points.
* Apply Translation: Applies the affine transformation by translating the points defining the curve by x and y
* Translate X: the x component of the translation
* Translate Y: the y component of the translation

