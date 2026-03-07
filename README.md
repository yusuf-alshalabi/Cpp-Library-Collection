# C++ Library Collection

[![Build Status](https://github.com/yusuf-alshalabi/Cpp-Library-Collection/workflows/CI/badge.svg)](https://github.com/yusuf-alshalabi/Cpp-Library-Collection/actions)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![C++17](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B17)

A modern C++ educational library providing comprehensive string, date, and period operations with robust error handling and performance optimizations.

## 📚 Complete Documentation

📖 **Full Documentation**: [docs/README.md](docs/README.md)  
🚀 **Quick Start**: [docs/QUICK_START.md](docs/QUICK_START.md) - Get started in 5 minutes!

## 🚀 Quick Start

| Resource | Description |
|----------|-------------|
| 🔧 **Installation** | [Installation Guide](docs/INSTALLATION.md) |
| 📚 **API Reference** | [API Documentation](docs/API_REFERENCE.md) |
| 💡 **Examples** | [Usage Examples](docs/EXAMPLES.md) |
| 🧪 **Testing** | [Testing Guide](docs/TESTING.md) |

## 📖 Documentation Overview

| Document | Description |
|----------|-------------|
| � [Quick Start](docs/QUICK_START.md) | Get started in 5 minutes |
| �📖 [Main Documentation](docs/README.md) | Complete project documentation |
| 🔧 [Installation](docs/INSTALLATION.md) | Build and install instructions |
| 📚 [API Reference](docs/API_REFERENCE.md) | Detailed API documentation |
| 💡 [Examples](docs/EXAMPLES.md) | Code examples and usage patterns |
| 🧪 [Testing](docs/TESTING.md) | Testing information and guidelines |
| 🤝 [Contributing](docs/CONTRIBUTING.md) | Contribution guidelines |
| 📄 [License](docs/LICENSE.md) | MIT License information |
| 🏗️ [Project Structure](docs/PROJECT_STRUCTURE.md) | Project organization |

## 🎯 Quick Example

```cpp
#include <iostream>
#include "MyLib/MyString.h"
#include "MyLib/MyDate.h"
#include "MyLib/MyPeriod.h"

int main() {
    using namespace MyLib;
    
    // 🔤 String operations
    MyString text("Hello World");
    std::cout << "Word count: " << text.CountWords() << std::endl;
    
    // 📅 Date operations
    MyDate today = MyDate::GetSystemDate();
    std::cout << "Today is: ";
    today.Print();
    
    // 📅 Period operations
    MyDate start(1, 1, 2023);
    MyDate end(31, 12, 2023);
    MyPeriod year2023(start, end);
    std::cout << "Duration: " << year2023.GetDurationInDays() << " days" << std::endl;
    
    return 0;
}
```

## 🚀 Quick Installation

```bash
# Clone the repository
git clone https://github.com/yusuf-alshalabi/Cpp-Library-Collection.git
cd Cpp-Library-Collection

# Build and install
mkdir build && cd build
cmake ..
make
sudo make install
```

## 📊 Project Status

| Status | Description |
|--------|-------------|
| 🚀 **Development** | Actively developed and ready for use |
| ✅ **Testing** | Comprehensive test suite with 100% pass rate |
| 📚 **Documentation** | Complete documentation in docs/ folder |
| 🌍 **Platform** | Cross-platform (Windows, Linux, macOS) |

## 🤝 Contributing

Contributions are welcome! Please see the [Contributing Guide](docs/CONTRIBUTING.md) for detailed guidelines.

## 📞 Support

If you encounter any issues or have questions:

| Resource | Link |
|----------|------|
| 🐛 **Bug Reports** | [Open an Issue](https://github.com/yusuf-alshalabi/Cpp-Library-Collection/issues) |
| 📚 **Documentation** | [docs/README.md](docs/README.md) |
| 🚀 **Quick Start** | [docs/QUICK_START.md](docs/QUICK_START.md) |
| 💡 **Examples** | [docs/EXAMPLES.md](docs/EXAMPLES.md) |
| 🏗️ **Architecture** | [docs/PROJECT_STRUCTURE.md](docs/PROJECT_STRUCTURE.md) |

---

**⭐ If you find this library helpful, consider giving it a star!**

**📖 For complete documentation, visit: [docs/README.md](docs/README.md)**
