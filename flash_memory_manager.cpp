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
    int bitIndex = blockIndex * 2;
    if (checkedBlocks.test(bitIndex)) {
        return blockStatus.test(bitIndex);
    }
    // impl of block checking, assume that all block are correct
    bool isGood = true;
    checkedBlocks.set(bitIndex, true);
    blockStatus.set(bitIndex, isGood);
    return isGood;
}
