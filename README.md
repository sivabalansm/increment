# Increment
Increment or decrement a file that contains a singular number by a certain amount.

# Why?
Some Linux environment use files with a single number to denote a setting.
For example, some systems have the volume or brightness stored in a file,
this program can be binded to keybinding to increase or decrease these settings.

# Build
```
git clone https://github.com/sivabalansm/increment.git
cd increment
make
```

After build, test if the the build was successful
```
./bin/inc --help
```


# Usage
```
Usage: inc [OPTION...] FILE
A program to increase/decrease a singular number in a file

  -d, --decrement[=N]        Increase number in FILE by N
  -i, --increment[=N]        Increase number in FILE by N
  -?, --help                 Give this help list
      --usage                Give a short usage message
  -V, --version              Print program version

Mandatory or optional arguments to long options are also mandatory or optional
for any corresponding short options.
```

# Support
This program only supports GNU/Linux compliant systems.
Any POSIX compliant systems must have GNU libraries.
The dependency is arph.h which is a GNU library for argument parsing.

