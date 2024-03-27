#include "flash_memory_manager.hpp"
#include <iostream>

FlashMemoryManager::FlashMemoryManager(ReadBlockFunc readFunc, WriteBlockFunc writeFunc, EraseBlockFunc eraseFunc, int totalBlocks)
    : readBlock(readFunc), writeBlock(writeFunc), eraseBlock(eraseFunc), totalBlocks(totalBlocks) {}

void FlashMemoryManager::findBadBlocks() {
    for (int i = 0; i < totalBlocks; ++i) {
        checkBlock(i);
    }
}

void FlashMemoryManager::printBadBlocks() const {
    std::cout << "Bad Blocks:" << std::endl;
    for (int i = 0; i < totalBlocks; ++i) {
        int bitIndex = i * 2;
        if (checkedBlocks.test(bitIndex) && !blockStatus.test(bitIndex)) {
            std::cout << i << std::endl;
        }
    }
}

bool FlashMemoryManager::checkBlock(int blockIndex) {
    char testData[blockSize];
    char readData[blockSize];
    memset(testData, blockIndex % 256, blockSize);

    if (!writeBlock(blockIndex, testData)) {
        std::cout << "Write failed for block " << blockIndex << std::endl;
        return false;
    }
    if (!readBlock(blockIndex, readData)) {
        std::cout << "Read failed for block " << blockIndex << std::endl;
        return false;
    }
    if (memcmp(testData, readData, blockSize) != 0) {
        std::cout << "Data mismatch for block " << blockIndex << std::endl;
        return false;
    }

    int bitIndex = blockIndex * 2;
    checkedBlocks.set(bitIndex, true);
    blockStatus.set(bitIndex, true);
    return true;
}
