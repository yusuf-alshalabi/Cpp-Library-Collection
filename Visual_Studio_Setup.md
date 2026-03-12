# Visual Studio Setup Guide

## 🚀 Quick Setup for Visual Studio

### Step 1: Open Visual Studio
1. Open Visual Studio 2019 or later
2. Select "Create a new project"
3. Choose "Empty Project (C++)"

### Step 2: Configure Project Properties
1. Right-click on project → Properties
2. Go to Configuration Properties → C/C++ → General
3. In "Additional Include Directories", add:
   ```
   $(ProjectDir)include
   ```
4. Go to Configuration Properties → C/C++ → Preprocessor
5. In "Preprocessor Definitions", add:
   ```
   _CRT_SECURE_NO_WARNINGS
   ```

### Step 3: Add Source Files
1. Right-click on "Source Files" → Add → Existing Item
2. Add these files:
   - `src/MyLib.cpp`
   - `examples/VS_Demo.cpp`

### Step 4: Set Main File
1. Right-click on `VS_Demo.cpp` → Set as Startup Project

### Step 5: Build and Run
1. Press F7 to build
2. Press Ctrl+F5 to run without debugging

## 📁 Project Structure
```
Cpp-Library-Collection/
├── include/MyLib/
│   ├── MyString.h
│   ├── MyDate.h
│   ├── MyPeriod.h
│   ├── MyUtil.h
│   └── MyInputValidate.h
├── src/
│   └── MyLib.cpp
├── examples/
│   └── VS_Demo.cpp
└── docs/
    └── ...
```

## 🔧 Include Paths
All includes should use this format:
```cpp
#include "MyLib/MyString.h"
#include "MyLib/MyDate.h"
#include "MyLib/MyPeriod.h"
#include "MyLib/MyUtil.h"
#include "MyLib/MyInputValidate.h"
```

## ✅ Verification
After running, you should see:
```
=== C++ Library Collection - Visual Studio Demo ===

1. String Operations:
Original: Hello World From Visual Studio
Word Count: 4
Upper Case: HELLO WORLD FROM VISUAL STUDIO
Is Palindrome: No

2. Date Operations:
Today: DD/MM/YYYY
Birthday: 15/08/1990
Is Valid Birthday: Yes

3. Period Operations:
Year 2024 Period: 01/01/2024
31/12/2024
Duration: 366 days
Period 1 overlaps with Period 2: Yes

4. Utility Functions:
Random Number (1-100): 42
Random Key: ABCD-1234-EFGH-5678

5. Input Validation Demo:
Enter a number between 1 and 10: 5
You entered: 5

6. Error Handling:
Caught error: MyString: Cannot create with empty value
Last error: Cannot create MyString with empty value
Caught error: MyDate: Invalid date format
Last error: Invalid date format. Expected DD/MM/YYYY

=== Demo Complete ===
```

## 🎯 Success!
Your C++ Library Collection is now working perfectly in Visual Studio!
