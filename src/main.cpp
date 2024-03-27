#include "flash_memory_manager.hpp"

const int blockSize = 256;

bool customReadBlock(int blockIndex, char* buffer) {
    // Write simulation based on block indexes 
    memset(buffer, blockIndex % 256, blockSize);
    return true;
}


bool customWriteBlock(int blockIndex, const char* data) {
    return true; // simulation assume that writing correct all the time 
}


bool customEraseBlock(int blockIndex) {
    return true;
}

int main() {
    const int totalBlocks = 1024; // for example
    FlashMemoryManager manager(customReadBlock, customWriteBlock, customEraseBlock, totalBlocks);

    manager.findBadBlocks();
    manager.printBadBlocks();

    return 0;
}
