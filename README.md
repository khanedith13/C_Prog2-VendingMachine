# C_Prog2-VendingMachine

A simple vending machine simulation project written in C for Programming 2. The program allows users to buy products, manage inventory and stock, track remaining balance from a ₱500 budget, and simulate vending machine operations using functions, arrays, structures, and file handling.

---

# Project Overview

This project simulates a vending machine inside a school canteen. A student starts with ₱500 pocket money and may purchase products from the vending machine as long as there is enough balance and stock available.

The system stores and updates:
- Product stock
- Student inventory
- Remaining money

using text files through file handling in C.

---

# Features

- View available vending machine products
- Buy products with balance validation
- Stock quantity checking
- Inventory tracking
- Remaining balance tracking
- File handling for persistent data storage
- Console-based menu system
- Uses only standard C libraries:
  - `stdio.h`
  - `stdlib.h`
  - `string.h`

---

# Technologies Used

- C Programming Language
- File Handling
- Structures
- Arrays
- Functions
- Conditional Statements
- Loops

---

# Project Structure

```txt
C_Prog2-VendingMachine/
│
├── README.md
├── flowchart.drawio
├── inventory.txt
├── products.txt
└── vendingMachine.c
```

---

# How the Program Works

1. The program loads product data from `products.txt`
2. The student starts with ₱500 balance
3. The user chooses actions from the menu:
   - View Products
   - Buy Product
   - View Inventory
   - Exit
4. Purchased products reduce stock quantity
5. Student balance updates automatically
6. Inventory and stock are saved using file handling

---

# Sample Products

| Product | Price | Stock |
|---|---|---|
| Chips | ₱25 | 10 |
| Soda | ₱30 | 8 |
| Candy | ₱15 | 12 |
| Water | ₱20 | 15 |
| Juice | ₱35 | 6 |

---

# Sample Menu

```txt
===== VENDING MACHINE =====
1. View Products
2. Buy Product
3. View Inventory
4. Exit
```

---

# File Handling

## products.txt
Stores product information:
- Product name
- Price
- Stock quantity

Example:
```txt
Chips 25 10
Soda 30 8
Candy 15 12
Water 20 15
Juice 35 6
```

---

## inventory.txt
Stores:
- Remaining student money
- Purchased product quantities

Example:
```txt
500
Chips 0
Soda 0
Candy 0
Water 0
Juice 0
```

---

# Compilation and Execution

## Using GCC

### Linux / macOS
```bash
gcc vending_machine.c -o vending
./vending
```

### Windows
```bash
gcc vending_machine.c -o vending.exe
vending.exe
```

---

# Learning Objectives

This project demonstrates:
- Flow control in C
- Functions and modular programming
- Arrays and strings
- Structures
- File handling
- Inventory management logic
- Console-based user interaction

---
# Developers

This project was developed by:

- Student 1 : intphilip | Philip II Mendoza
      https://github.com/intphilip
    
- Student 2 : jimbert0609 | Jimbert Catalan
      https://github.com/Jimbert0609
  
- Student 3 : khanedith13 | Delfin Octobre
      https://github.com/khanedith13
  
---

# Course Information

**Course:** Programming 2  
**Project:** Final Project – Vending Machine Simulation  
**Language:** C Programming

---

# Notes

- The program uses only standard C libraries.
- Data is saved automatically using text files.
- Compatible with basic C compilers and environments.
