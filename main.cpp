/*
 * Copyright 2025 luynar
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <iomanip>
#include <windows.h>

namespace fs = std::filesystem;

enum class OutputMode { HEX, DECIMAL };

void convertToByteArray(const std::string& inputPath, const std::string& exePath, OutputMode mode, bool lineBreaks) {
    std::ifstream inputFile(inputPath, std::ios::binary);
    if (!inputFile.is_open()) {
        std::cout << "Failed to open " << inputPath << std::endl;
        return;
    }

    std::vector<unsigned char> bytes((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
    inputFile.close();

    fs::path execPath = fs::path(exePath).parent_path();
    fs::path outputDir = execPath / "outputs"; fs::create_directory(outputDir);

    std::string filename = fs::path(inputPath).stem().string();
    std::string outputPath = (outputDir / filename).string() + ".h";

    std::ofstream outputFile(outputPath);
    if (!outputFile.is_open()) {
        std::cout << "Failed to create " << outputPath << std::endl;
        return;
    }

    outputFile << "/*\n";
    outputFile << " * Created by luynar software named file-to-bytes\n";
    outputFile << " * You can download it from https://github.com/luynrs\n";
    outputFile << " * files-to-bytes licensed under Apache License 2.0\n";
    outputFile << " * https://www.apache.org/licenses/LICENSE-2.0\n";
    outputFile << " */\n\n";
    outputFile << "#ifndef FILE_" << filename << "_H\n#define FILE_" << filename << "_H\n\n";
    outputFile << "unsigned char " << filename << "_data[] = {";

    if (mode == OutputMode::HEX) {
        outputFile << std::hex << std::setfill('0');
        for (size_t i = 0; i < bytes.size(); ++i) {
            outputFile << "0x" << std::setw(2) << (int)bytes[i];
            if (i < bytes.size() - 1) outputFile << ",";
            if (lineBreaks && i % 16 == 15) outputFile << "\n";
        }
    }
    else {
        for (size_t i = 0; i < bytes.size(); ++i) {
            outputFile << (int)bytes[i];
            if (i < bytes.size() - 1) outputFile << ",";
            if (lineBreaks && i % 16 == 15) outputFile << "\n";
        }
    }

    outputFile << "};\n\n"; outputFile << std::dec;
    outputFile << "unsigned int " << filename << "_size = " << bytes.size() << ";\n\n";
    outputFile << "#endif"; outputFile.close();


    std::cout << "Converted " << inputPath << " to " << outputPath << std::endl;
}

void loadOrCreateSettings(const std::string& exePath, OutputMode& mode, bool& lineBreaks) {
    fs::path execPath = fs::path(exePath).parent_path();
    std::string settingsPath = (execPath / "settings.ini").string();

    if (!fs::exists(settingsPath)) {
        std::ofstream settingsFile(settingsPath);
        settingsFile << "Mode=HEX\n"; settingsFile << "LineBreaks=1\n"; settingsFile.close();
        mode = OutputMode::HEX;
        lineBreaks = true;
        return;
    }

    std::ifstream settingsFile(settingsPath);
    std::string line;
    while (std::getline(settingsFile, line)) {
        if (line.find("Mode=") == 0) {
            std::string value = line.substr(5); mode = (value == "HEX") ? OutputMode::HEX : OutputMode::DECIMAL;
        }
        else if (line.find("LineBreaks=") == 0) {
            std::string value = line.substr(11); lineBreaks = (value == "1");
        }
    }
    settingsFile.close();
}

void saveSettings(const std::string& exePath, OutputMode mode, bool lineBreaks) {
    fs::path execPath = fs::path(exePath).parent_path(); std::string settingsPath = (execPath / "settings.ini").string();

    std::ofstream settingsFile(settingsPath);
    settingsFile << "Mode=" << (mode == OutputMode::HEX ? "HEX" : "DECIMAL") << "\n";
    settingsFile << "LineBreaks=" << (lineBreaks ? "1" : "0") << "\n"; settingsFile.close();
}

void text(OutputMode mode, bool lineBreaks, char* argv[]) {
    std::cout << "https://github.com/luynrs\n\n";
    std::cout << "Current mode: " << (mode == OutputMode::HEX ? "HEX" : "DECIMAL") << "\n";
    std::cout << "Line breaks: " << (lineBreaks ? "Enabled" : "Disabled") << "\n";
    std::cout << "Usage:\n";
    std::cout << "1. Drag and drop a file onto the executable\n";
    std::cout << "2. Or run from command line: " << argv[0] << " <filename>\n";
    std::cout << "3. To change mode, enter 'hex' or 'dec'\n";
    std::cout << "4. To toggle line breaks, enter 'line' or 'noline': ";
}

int main(int argc, char* argv[]) {
    OutputMode mode;
    bool lineBreaks;
    loadOrCreateSettings(argv[0], mode, lineBreaks);
    SetConsoleTitle(L"luynar's software | github.com/luynrs | Files-to-Bytes");
   
    if (argc < 2) {
        while (true) {
            text(mode, lineBreaks, argv);

            std::string input; std::getline(std::cin, input);

            bool settingsChanged = false;

            if (input == "hex" || input == "dec") {
                mode = (input == "hex") ? OutputMode::HEX : OutputMode::DECIMAL; settingsChanged = true;
            }
            else if (input == "line" || input == "noline") {
                lineBreaks = (input == "line"); settingsChanged = true;
            }
            else if (input.empty()) {
                std::cout << "Exiting...\n";
                break;
            }
            else {
                std::cout << "Invalid input. Try again.\n";
            }

            if (settingsChanged) {
                saveSettings(argv[0], mode, lineBreaks); system("cls");
            }
        }
        return 0;
    }

    for (int i = 1; i < argc; ++i) {
        convertToByteArray(argv[i], argv[0], mode, lineBreaks);
    }

    std::cout << "All good! Press Enter to exit..."; std::cin.get(); return 0;
}