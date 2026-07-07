# C_Prog2-VendingMachine

A console-based **Multi-Store Vending Machine Simulation** written in
**C** for Programming 2. The application simulates a vending machine
system where users can purchase products from different stores, manage
their shopping cart, cancel purchases, track their remaining cash, and
maintain persistent inventory records through file handling.

------------------------------------------------------------------------

# Project Overview

This project simulates a vending machine found in a school canteen that
contains multiple stores. The user starts with **₱500** and can purchase
products from any available store as long as there is sufficient balance
and stock.

The program automatically updates and saves all transactions using text
files, allowing data to persist even after the application closes.

The system keeps track of:

-   Available stores
-   Product inventory
-   Product stock
-   User cash balance
-   Purchased products
-   Inventory records
-   Final receipt

------------------------------------------------------------------------

# Features

-   Multiple store support
-   Product selection using Product ID
-   Purchase products from different stores
-   Automatic stock validation
-   Cash balance validation
-   Persistent cash tracking using `cash.txt`
-   Persistent product inventory using `products.txt`
-   Live inventory tracking using `inventory.txt`
-   Shopping cart system
-   Merge duplicate purchases automatically
-   Purchase cancellation with partial quantity refunds
-   Automatic stock restoration after cancellation
-   Automatic inventory synchronization
-   Receipt generation after transaction completion
-   Runtime file reloading to reflect external file modifications
-   Comprehensive input validation for menus, quantities, and product
    selection
-   Console-based user interface

------------------------------------------------------------------------

# Technologies Used

-   C Programming Language
-   File Handling
-   Structures
-   Arrays
-   Functions
-   Loops
-   Conditional Statements
-   String Manipulation
-   Standard C Libraries
    -   `stdio.h`
    -   `stdlib.h`
    -   `string.h`

------------------------------------------------------------------------

# Project Structure

``` txt
C_Prog2-VendingMachine/
│
├── README.md
├── cash.txt
├── flowchart.drawio
├── inventory.txt
├── products.txt
└── vendingMachine.c
```

------------------------------------------------------------------------

# Program Workflow

1.  Load available stores and products from `products.txt`.
2.  Load the user's available cash from `cash.txt`.
3.  Display the list of available stores.
4.  Allow the user to select stores, purchase products, view inventory,
    and finish the transaction.
5.  Validate stock, balance, and user input.
6.  Save all updates immediately.
7.  Allow purchase cancellation with refunds and stock restoration.
8.  Generate a final receipt.

------------------------------------------------------------------------

# File Handling

## `products.txt`

Stores store names, product IDs, prices, and stock quantities.

## `cash.txt`

Stores the user's remaining cash balance.

## `inventory.txt`

Stores purchased products, quantities, totals, starting cash, and
remaining balance.

------------------------------------------------------------------------

# Compilation and Execution

## Windows

``` bash
gcc vendingMachine.c -o vending.exe
vending.exe
```

## Linux / macOS

``` bash
gcc vendingMachine.c -o vending
./vending
```

------------------------------------------------------------------------

# Learning Objectives

-   Modular programming
-   Structures
-   Arrays
-   File handling
-   Persistent storage
-   String manipulation
-   Input validation
-   Inventory management
-   Shopping cart logic

------------------------------------------------------------------------

# Developers

-   **Student 1:** intphilip \| Philip II Mendoza
    https://github.com/intphilip

-   **Student 2:** jimbert0609 \| Jimbert Catalan
    https://github.com/Jimbert0609

-   **Student 3:** khanedith13 \| Delfin Octobre
    https://github.com/khanedith13

------------------------------------------------------------------------

# Course Information

**Course:** Programming 2

**Project:** Final Project -- Multi-Store Vending Machine Simulation

**Language:** C Programming
