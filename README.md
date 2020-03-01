# Matrices

About
------
This program allows a user to multiply MxN matrices and transpose a MxN matrix.

How it's built
--------------
I used Meson as the build compiler for my program. The program uses one .hpp
file located in src/matrix. In addition, I used Google Tests to perform unit
tests when constructing my Matrix class. The main driver for this program is in
the file main.cpp. This handles all of the logic regarding building a matrix and
its operations. There are additional features when running this program, such as
storing each matrix created in an vector called "storage". For matrix numbers,
start with 0.

How to run
----------
I have several bash scripts that allowed me to run my code with ease. Enter the
following commands

```bash
bash run-script.sh
bash test.sh
bash run-tester.sh
```

To sum up the commands used to run this program, the following commands should
be entered

```bash
meson build
ninja -C build
ninja -C build test
./build/test/matrix/main.cpp.executable
```

Future plans
------------
To my dismay, this program does not work as well as I wish it would. Here is a
list of things that I wish to work on
- Implement a graphical user interface to appeal to UI
- Fix the tester file's style and organization (create more unit tests rather
    than check equivalences under one super test
- Allow more flexibility with the storage matrix
- Better populate a matrix rather than initialize each cell one-by-one in the
  command line
- Allow more error checking (command-line, commands list, etc)
- Try to get memset to work for simplicity in code
- More detailed documentation throughout code and in README
- Organize the constant strings defined in main.cpp
- Fix logic behind entering invalid characters for inserting transposed or
  product matrices into storage
- Fix logic behind removing two matrices from storage in a row
