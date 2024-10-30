# Quine-McCluskey Implementation

This utility is a two-level logic minimization tool that employs the Quine-McCluskey algorithm. It is designed to simplify Boolean functions, which is instrumental in reducing the complexity of digital logic circuits.

## Installation
To compile and build the tool, follow these steps:
```bash
mkdir build; cd build;
cmake ..;
make -j128
```

## Usage
After building, you can run the application using:
```bash
./QuineMcCluskeyMinimizer 
```
You have the option to select a test case or input your own Boolean function. The tool will process the input to generate the truth table, identify prime implicants, and determine the essential prime implicants.

## Input Format
The tool accepts Boolean expressions in the following formats:
- "a'b'c'+a'bc'+a'b'c+ab'c"
- "AB'CD+A'BCD'+A'BC'D"