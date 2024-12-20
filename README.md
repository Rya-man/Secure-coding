# SecureAuth

SecureAuth is a simple C++ application that demonstrates secure password hashing using the OpenSSL library. It implements SHA-256 hashing and provides a user-friendly way to hash passwords directly from the command line. This project highlights secure coding practices and leverages OpenSSL to ensure robust security for password management.

---

## Features

- **Secure Password Hashing**: Uses SHA-256 hashing via OpenSSL.
- **Interactive CLI**: Input a password via the terminal to generate its hash.
- **Hexadecimal Output**: Outputs the hashed password in a human-readable hexadecimal format.
- **Cross-Platform Compatibility**: Compatible with Linux and macOS systems where OpenSSL is installed.

---

## Prerequisites

### Required Tools
- **g++**: GCC compiler supporting C++11 or above.
- **CMake**: Version 3.10 or later.
- **OpenSSL**: Installed development libraries.

### Installing Dependencies

#### Ubuntu/Debian
```bash
sudo apt update
sudo apt install build-essential cmake libssl-dev
```

#### Fedora
```bash
sudo dnf install gcc gcc-c++ cmake openssl-devel
```

#### macOS (Using Homebrew)
```bash
brew install cmake openssl
```

---

## Building and Running SecureAuth

### Option 1: Using Precompiled Executable

The project includes a precompiled executable (`SecureAuth`) located at the root directory. To run it:

```bash
./SecureAuth
```

Follow the interactive prompts to input a password and see its SHA-256 hash output.

---

### Option 2: Build from Source

You can build the project using CMake and GNU Make.

#### Steps:

1. **Create a Build Directory**

```bash
mkdir build
cd build
```

2. **Generate Build Files**

```bash
cmake ..
```

3. **Compile the Project**

```bash
make
```

4. **Move the Executable**

Move the generated executable to the root directory for easy access:

```bash
mv SecureAuthCPP ../
```

5. **Run the Application**

Go back to the root directory and execute the program:

```bash
cd ../
./SecureAuthCPP
```

---

## How to Use SecureAuth

1. **Run the Application**:
   ```bash
   ./SecureAuth
   ```

2. **Enter a Password**:
   - The application will prompt you to input a password.

3. **View the Hashed Output**:
   - The password hash is displayed in hexadecimal format.

Example:
```bash
Enter Password: mySecurePassword

Hash: 5e884898da28047151d0e56f8dc6292773603d0d6aabbdd9f144b4e6e284f59c
```

---

## Project Structure

```plaintext
SecureAuth/
├── CMakeLists.txt       # Build configuration file for CMake
├── README.md            # Project documentation
├── SecureAuthCPP          # Precompiled executable (optional)
├── src/                 # Source code directory
│   ├── main.cpp         # Main program entry point
├── build/               # Directory for build artifacts
```

---

## Implementation Details

### Technologies Used
- **OpenSSL**: Provides secure cryptographic functions for password hashing.
- **C++**: Implements the core application logic.
- **CMake**: Automates the build process.

### Hashing Process
- The application reads a user-provided password from standard input.
- It uses the SHA-256 algorithm via OpenSSL’s EVP interface to compute the hash.
- The result is displayed as a hexadecimal string.

---

## Contributing

Contributions are welcome! To contribute:

1. Fork the repository.
2. Create a new branch for your feature or bug fix.
3. Commit your changes and push them to your branch.
4. Open a pull request.

---


## Troubleshooting

### Common Issues

#### OpenSSL Linker Errors
Ensure OpenSSL development libraries are installed. On Ubuntu/Debian, install them with:
```bash
sudo apt install libssl-dev
```

#### Undefined Reference Errors
Ensure you’re linking OpenSSL libraries when building manually:
```bash
g++ src/main.cpp -o SecureAuth CPP-lssl -lcrypto
```

### Reporting Issues
If you encounter any problems, please open an issue in the project’s GitHub repository with detailed information about the error and your environment.

---

## Acknowledgments
- OpenSSL documentation for cryptographic APIs.
- CMake for simplifying cross-platform builds.
