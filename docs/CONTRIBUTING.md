# Contributing to C++ Library Collection

Thank you for your interest in contributing to this educational C++ library! This document provides comprehensive guidelines for contributors.

## 🎯 How to Contribute

### Reporting Issues
- Use [GitHub Issues](https://github.com/yusuf-alshalabi/Cpp-Library-Collection/issues) to report bugs
- Provide clear descriptions and minimal reproducible examples
- Include error messages and system information
- Search existing issues before creating new ones

### Submitting Pull Requests
1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Make your changes
4. Commit your changes (`git commit -m 'Add amazing feature'`)
5. Push to the branch (`git push origin feature/amazing-feature`)
6. Open a Pull Request

## 📝 Code Style

### C++ Standards
- Use C++17 features appropriately
- Follow existing naming conventions
- Use meaningful variable and function names
- Add comments for complex logic

### Naming Conventions
- **Classes**: PascalCase (e.g., `MyString`, `MyDate`)
- **Functions**: PascalCase for public methods, camelCase for private
- **Variables**: camelCase (e.g., `stringValue`, `dateObject`)
- **Constants**: UPPER_SNAKE_CASE (e.g., `MAX_BUFFER_SIZE`)
- **Files**: PascalCase for headers (e.g., `MyString.h`)

### Formatting
- Use consistent indentation (4 spaces)
- Keep lines under 100 characters
- Add proper spacing around operators
- Use braces for all control blocks

### Example Code Style
```cpp
// Good example
MyString text("Hello World");
if (text.Contains("World")) {
    std::cout << "Found World!" << std::endl;
}

// Function naming
class MyString {
public:
    size_t CountWords() const;                    // Public method
    static std::string UpperAllString(const std::string& input);  // Static method
    
private:
    void validateInput(const std::string& input);  // Private method
    std::string internalValue;                     // Member variable
};
```

## 📚 Documentation

### Code Documentation
- Add comments to complex functions
- Document public APIs in header files
- Include parameter descriptions
- Add return value documentation

### Example Documentation
```cpp
/**
 * Counts the number of words in the string.
 * 
 * @return The number of words in the string
 * 
 * @example
 * MyString text("Hello World");
 * size_t count = text.CountWords();  // Returns 2
 */
size_t CountWords() const;
```

### Updating Documentation
- Update README.md for new features
- Add examples to EXAMPLES.md
- Update API_REFERENCE.md for new methods
- Update CHANGELOG.md for significant changes

## 🧪 Testing

### Before Submitting
- Ensure code compiles without warnings
- Test new functionality with examples
- Verify existing functionality still works
- Update documentation if needed
- Run the full test suite

### Writing Tests
- Write tests for all new functionality
- Test both success and failure cases
- Include edge cases and boundary conditions
- Follow existing test patterns

### Test Structure
```cpp
void test_new_functionality() {
    std::cout << "Testing new functionality...\n";
    
    // Clear errors
    MyClass::ClearError();
    
    // Test normal case
    try {
        MyClass obj(valid_parameters);
        assert(obj.NewMethod() == expected_result);
        std::cout << "✓ Normal case passed\n";
    } catch (const std::exception& e) {
        std::cout << "❌ Normal case failed: " << e.what() << std::endl;
        assert(false);
    }
    
    // Test error case
    try {
        MyClass obj(invalid_parameters);
        assert(false); // Should not reach here
    } catch (const std::exception& e) {
        assert(MyClass::GetLastError() == expected_error);
        std::cout << "✓ Error case passed\n";
    }
    
    std::cout << "✓ New functionality tests passed\n";
}
```

### Building and Running Tests
```bash
# Build tests
mkdir build && cd build
cmake ..
ninja tests

# Run tests
./tests/tests.exe

# Or use ctest
ctest
```

## 🏗️ Development Workflow

### Setting Up Development Environment
1. Clone the repository
2. Install dependencies (CMake, C++17 compiler)
3. Build the library
4. Run tests to verify setup

### Development Process
1. **Create Issue**: Discuss major changes in an issue first
2. **Create Branch**: Use descriptive branch names
3. **Implement Changes**: Follow code style guidelines
4. **Add Tests**: Ensure comprehensive test coverage
5. **Update Documentation**: Keep docs current
6. **Submit PR**: Include clear description of changes

### Branch Naming
- `feature/feature-name` - New features
- `bugfix/bug-description` - Bug fixes
- `docs/documentation-update` - Documentation changes
- `test/test-improvement` - Test improvements

### Commit Messages
- Use present tense ("Add feature" not "Added feature")
- Be descriptive but concise
- Include issue number if applicable
- Examples:
  - `feat: Add string palindrome detection`
  - `fix: Resolve date validation edge case`
  - `docs: Update API reference for new methods`
  - `test: Add comprehensive error handling tests`

## 🔧 Build System

### CMake Guidelines
- Keep CMakeLists.txt files clean and readable
- Use modern CMake practices (3.16+)
- Add proper dependencies
- Support multiple build systems (Ninja, Make)

### Adding New Files
1. Add headers to `include/MyLib/`
2. Add source to `src/MyLib.cpp` if needed
3. Update `CMakeLists.txt` if adding new source files
4. Add tests to `tests/`
5. Update documentation

### Build Options
- Support debug and release builds
- Provide configuration options
- Document new build options
- Test on multiple platforms

## 🤝 Code Review Process

### Review Criteria
- **Functionality**: Does the code work as intended?
- **Style**: Does it follow project conventions?
- **Tests**: Are tests comprehensive and passing?
- **Documentation**: Is documentation updated?
- **Performance**: Is the implementation efficient?

### Review Guidelines
- Be constructive and respectful
- Provide specific feedback
- Suggest improvements
- Help resolve issues

### Submitting for Review
1. Ensure all tests pass
2. Update documentation
3. Self-review your changes
4. Request review from maintainers
5. Address feedback promptly

## 🐛 Bug Reports

### Bug Report Template
```markdown
## Bug Description
Brief description of the bug

## Steps to Reproduce
1. Step 1
2. Step 2
3. Step 3

## Expected Behavior
What should happen

## Actual Behavior
What actually happens

## Environment
- OS: [e.g., Ubuntu 20.04]
- Compiler: [e.g., GCC 9.0]
- Build Type: [e.g., Release]

## Additional Context
Any other relevant information
```

### Debugging Information
- Include error messages
- Provide stack traces
- Share minimal reproducible example
- Include system information

## ✨ Feature Requests

### Feature Request Template
```markdown
## Feature Description
Clear description of the feature

## Use Case
Why is this feature needed?

## Proposed Solution
How should it be implemented?

## Alternatives Considered
Other approaches considered

## Additional Context
Any other relevant information
```

## 🌍 Community Guidelines

### Code of Conduct
- Be respectful and inclusive
- Welcome newcomers
- Provide constructive feedback
- Focus on what is best for the community

### Communication
- Use GitHub issues for bugs and features
- Use discussions for questions and ideas
- Be patient with response times
- Help others when you can

## 📖 Resources

### Documentation
- [API Reference](API_REFERENCE.md)
- [Examples](EXAMPLES.md)
- [Installation Guide](INSTALLATION.md)
- [Testing Guide](TESTING.md)

### External Resources
- [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/)
- [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)
- [CMake Best Practices](https://cliutils.gitlab.io/modern-cmake/chapters/intro.html)

## 🏆 Recognition

### Contributors
- All contributors are acknowledged in the repository
- Significant contributions are highlighted in releases
- Community involvement is valued and appreciated

### Ways to Contribute
- Code contributions
- Bug reports and feature requests
- Documentation improvements
- Community support and discussions
- Testing and feedback

## 📞 Getting Help

If you need help contributing:

1. **Check Documentation**: Review existing documentation first
2. **Search Issues**: Look for similar questions or problems
3. **Ask Questions**: Use GitHub Discussions for general questions
4. **Contact Maintainers**: Reach out for specific guidance

---

**Thank you for contributing to the C++ Library Collection! Your contributions help make this project better for everyone. 🚀**
```

### Running Examples
```bash
make basic_demo
./basic_demo
```

## 📚 Development Guidelines

### Adding New Features
- Consider educational value
- Maintain backward compatibility
- Add appropriate error handling
- Include examples in documentation

### Bug Fixes
- Identify root cause
- Fix without breaking existing functionality
- Add tests to prevent regression
- Document the fix

## 🤝 Code Review Process

### What We Look For
- Code quality and readability
- Educational value
- Performance considerations
- Proper error handling
- Documentation completeness

### Review Criteria
- [ ] Code follows project style
- [ ] Functionality works as expected
- [ ] Documentation is updated
- [ ] Examples are provided
- [ ] No breaking changes

## 📄 License

By contributing, you agree that your contributions will be licensed under the MIT License.

## 🙏 Recognition

Contributors will be recognized in:
- README.md acknowledgments
- Release notes
- Commit history

## 📞 Getting Help

- Create an issue for questions
- Check existing issues for similar problems
- Review the codebase for examples

---

Thank you for contributing to this educational C++ library! 🎓
