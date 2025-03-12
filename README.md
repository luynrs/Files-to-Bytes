# Files-to-Bytes

[🇬🇧 English](README.md) | [🇷🇺 Русский](README.RU.md)

---

![FILES-to-bytres](https://github.com/user-attachments/assets/fac37f14-3472-4039-b7d0-7aaa0c711278)

---

  Online version (with limitations) - https://luynar.space/files-to-bytes

---

## 🇬🇧 English

Files-to-Bytes is a command-line utility that converts files into byte arrays (HEX or DECIMAL) and saves them as C++ header files (.h). The program automatically creates an `outputs` directory and stores the generated files there.

### Features
- Supports two output modes: **HEX** and **DECIMAL**.
- Automatically generates a header file containing a byte array and its size.
- Supports line breaks for better readability.
- Automatically creates a `settings.ini` file.
- Can be used via the command line or by dragging and dropping files onto the executable.

### Installation and Usage

#### 1. Running the Program
- **Drag and drop a file** onto the `.exe` executable for automatic processing.
- **Or run it from the command line**:
  ```sh
  files-to-bytes.exe <file_path>
  ```

#### 2. Settings
Upon first launch, a `settings.ini` file is created with the following parameters:
```ini
Mode=HEX       # Output mode (HEX or DECIMAL)
LineBreaks=1   # Line breaks (1 - enabled, 0 - disabled)
```
You can modify these settings manually or through the console interface:
- Enter `hex` or `dec` to switch output mode.
- Enter `line` or `noline` to enable/disable line breaks.

#### 3. Output Files
The processed files are saved in the `outputs` folder, e.g.:
```
outputs/
 ├── example.h
```
Example content of `example.h`:
```cpp
#ifndef FILE_EXAMPLE_H
#define FILE_EXAMPLE_H

unsigned char example_data[] = {0x4D, 0x5A, 0x90, 0x00, ...};
unsigned int example_size = 1234;

#endif
```

> File_Name - the name of the input file is formed without the extension (example.exe > example)
The names of the variables are formed as follows:
```
File_Name_data - Array of bytes
File_Name_size - File length
```
This data is needed for use in the code.

### Compile in Visual Studio
1. Set the C++ standard to **C++17** or higher.
2. Build the project

### Using in Code
To restore the original file from the generated `.h` file:
```cpp
#include <fstream>
#include "example.h"

int main() {
    std::ofstream outFile("example.bin", std::ios::binary); // after dot place format of the file
    outFile.write(reinterpret_cast<const char*>(example_data), example_size);
    outFile.close();
    return 0;
}
```
This will save the byte array as `restored_example.bin`.

### License
This project is distributed under the **Apache License 2.0**.

---
