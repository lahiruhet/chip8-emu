#include <fstream>
#include <iostream>
#include <vector>
#include <cstdint>

class Chip8 {
private:
    std::vector<uint8_t> memory;
    // ... other members as before ...

public:
    Chip8() : memory(4096, 0) {
        // ... other initializations as before ...
    }

    bool loadROM(const std::string& filename) {
        std::ifstream file(filename, std::ios::binary | std::ios::ate);

        if (!file.is_open()) {
            std::cout << "Failed to open ROM file." << std::endl;
            return false;
        }

        std::streampos size = file.tellg();
        if (size > 4096 - 0x200) {
            std::cout << "ROM too large to fit in memory." << std::endl;
            return false;
        }

        file.seekg(0, std::ios::beg);
        file.read(reinterpret_cast<char*>(memory.data() + 0x200), size);

        if (!file) {
            std::cout << "Failed to read ROM file." << std::endl;
            return false;
        }

        std::cout << "ROM loaded successfully. Size: " << size << " bytes" << std::endl;
        return true;
    }
};

int main() {
    Chip8 emulator;
    if (emulator.loadROM("./roms/flightrunner.ch8")) {
        std::cout << "ROM loaded, ready to start emulation." << std::endl;
    } else {
        std::cout << "Failed to load ROM." << std::endl;
    }
    return 0;
}