# CS 210 Portfolio: Airgead Banking Investment Calculator

## Project overview

This C++ application was developed for CS 210 Programming Languages at Southern New Hampshire University. The goal of Project Two was to help users compare the growth of an initial investment with and without additional monthly deposits. The calculator accepts an initial investment, a monthly deposit, an annual interest rate, and a number of years. It then prints two reports showing the year-end balance and interest earned each year. The comparison helps users see how regular contributions affect long-term savings.

## Build and run

The application requires a C++11-compatible compiler and runs in a terminal. From the repository directory:

```bash
g++ -std=c++11 -Wall -Wextra -pedantic main.cpp AirgeadBanking.cpp -o airgead-banking
./airgead-banking
```

To run the regression tests, Python 3 and a C++ compiler are required:

```bash
python3 -m unittest discover -s tests -v
```

## Project files

- `main.cpp`: Creates the application object and starts the program.
- `AirgeadBanking.h`: Declares the calculator class and its interface.
- `AirgeadBanking.cpp`: Handles input, validation, calculations, and reports.
- `ProjectTwoPseudocode.txt`: Documents the planned program logic.
- `tests/test_investment.py`: Checks key calculations and input validation.

## Module Eight reflection

### What problem did this project solve?

The project provides a simple way to estimate investment growth over time and compare the results of making additional monthly contributions against leaving the initial amount invested. It presents the results in annual tables rather than asking users to work through the calculations manually.

### What did I do particularly well?

I organized the application around an `AirgeadBanking` class, keeping `main()` small and separating input collection, validation, report generation, and program flow into individual functions. The validation routines reject malformed input and repeat the prompt instead of allowing an invalid value to enter the calculations. I also used consistent naming and formatting and wrote pseudocode before implementing the program. My instructor specifically recognized the organization, correspondence between pseudocode and implementation, and input validation.

### Where could I enhance the code?

The initial version incorrectly compounded interest monthly in the report without deposits. After reviewing the feedback, I changed that path to calculate annual interest and add it once at year-end, while preserving monthly calculations in the report with deposits. I also updated the pseudocode and added regression tests for both calculation paths. For a larger financial application, I would improve handling of currency rounding and numerical precision, add bounds for unusually large inputs, and expand the test coverage. These improvements would make the results more reliable and help prevent regressions.

### What was challenging, and how did I overcome it?

The most challenging part was managing two different interest calculation methods while keeping the report format consistent. My original approach reused the same monthly loop for both reports, which seemed simpler but produced an incorrect result for the no-deposit case. Comparing the expected calculation to the implementation helped me identify the difference between accumulating monthly interest and applying interest at the end of the year. I addressed it by separating the two calculation paths and checking their outputs against independently calculated examples. Course materials, compiler diagnostics, C++ reference documentation, and GitHub are resources I can continue using when solving similar problems.

### What skills will transfer to other projects or coursework?

This project reinforced object-oriented design, decomposing a problem into smaller functions, validating user input, translating pseudocode into C++, and testing calculations against expected results. These skills also apply to the engineering and automation work I do professionally, where it is important to verify behavior rather than assume a program is correct simply because it runs.

### How did I make the program maintainable, readable, and adaptable?

I used a dedicated class, private data members, descriptive function names, and constants instead of repeating numeric values. The reporting function distinguishes the annual and monthly calculation rules explicitly, making the difference easier to follow and modify. The pseudocode, build instructions, and regression tests provide context for future changes. As a result, another developer can understand the program structure and check whether updates preserve the expected behavior.
