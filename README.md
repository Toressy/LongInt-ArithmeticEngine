# 🔢 LongInt-ArithmeticEngine

This C++ project provides a custom implementation of arbitrary-length integers using a doubly linked list. It includes support for:

- Addition and subtraction of large integers
- Base conversion and digit-by-digit access
- Comparison operators (`==`, `!=`, `<`, `>`)
- **Karatsuba multiplication** for efficient large-number operations
- **Toom–Cook (TomKyk)** multiplication for even faster performance
- Input/output stream operator overloading

## 🧱 Features

- Internal digit storage using a doubly linked list
- Supports negative numbers and custom number systems (default base 10)
- Implements recursive multiplication methods: Karatsuba and Toom–Cook
- Operator overloading for intuitive arithmetic use

## 💻 Example Usage

```cpp
longNumber a, b, result;

cin >> a >> b;

result = a + b;
cout << "a + b = " << result << endl;

result = a.karatsyba(b);
cout << "Karatsuba multiplication: " << result << endl;

result = a.tomKyk(b);
cout << "Toom–Cook multiplication: " << result << endl;
```

## 📁 Files

  ├── 2lab.cpp           # Main source file with class implementation and test
  └── README.md          # Project documentation

## 📌 Algorithms Implemented
  
  Karatsuba Multiplication: Recursive divide-and-conquer algorithm with O(n^1.58) complexity
  Toom–Cook Multiplication: More efficient for very large numbers using 3-way splitting
  Standard Long Addition/Subtraction: Manual digit-by-digit with carry/borrow logic
  
## 🧪 How to Run

Compile and execute:
```cpp
g++ 2lab.cpp -o longint
./longint
```
Input two long integers when prompted, and the program will output results for:

    Addition
    Subtraction
    Comparisons
    Karatsuba and Toom–Cook multiplications
    
## 📦 Class Overview: longNumber

### Method	Description

    insertLeft() / insertRight()	Add digits to head/tail
    operator+, operator-	Add/subtract longNumbers
    karatsyba()	Perform Karatsuba multiplication
    tomKyk()	Perform Toom–Cook multiplication
    toInt()	Convert to integer (when within limits)
    print() / operator<<	Output longNumber


Language: C++
Module: Advanced Algorithms / Number Theory

