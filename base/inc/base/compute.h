#pragma once

#include "base/memory.h"

#include <iostream>
#include <fstream>

/**
 * @class Compute
 * @brief Base class for CPU
 * @details Compute contains base functionality for each CPU: Run, Reset and Load ROM.
 * Also, Compute holds cycles counter
 */
class Compute {
    public:
    /**
     * @brief Static function to read a binary file.
     * @param filename Path to the binary file.
     * @param [out] fileSize Number of bytes read.
     * @return Char pointer to data (or nullptr if any error).
     */
    static char* ReadBinary(const char *filename, long long &fileSize) {
        std::ifstream file{filename, std::ios::binary | std::ios::ate};

        if (!file.is_open()) {
            fileSize = 0;
            return nullptr;
        }

        fileSize = file.tellg();

        if (fileSize <= 0) {
            fileSize = 0;
            return nullptr;
        }

        char* const data = new char[fileSize];

        file.seekg(0, std::ios::beg);
        file.read(data, fileSize);

        return data;
    }

    /**
     * @brief Load data into memory from a binary file
     * @param filename Path to the binary file.
     * @param memory Memory struct instance.
     * @return True if the load was successful, false otherwise.
     */
    bool LoadROM(const char *filename, Memory &memory) {
        long long numBytesRead = 0;

        const char* data = ReadBinary(filename, numBytesRead);
        if (!data)
            return false;

        Reset(memory);
        const bool SetSuccess = memory.SetMemory(data, numBytesRead);
        delete[] data;

        return SetSuccess;
    }

protected:

    /**
     * @brief CPU execution loop function. Stops execution on invalid instruction.
     * @param memory Memory struct instance.
     * @return Cycles count.
     */
    virtual U32 Run(Memory &memory) = 0;

    /**
     * @brief Resets CPU to its default values.
     * @param memory Memory struct instance.
     */
    virtual void Reset(Memory &memory) noexcept = 0;

public:
    U32 cycles = 0;
};