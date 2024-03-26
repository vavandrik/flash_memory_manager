#include "flash_memory_manager.hpp"

bool customReadBlock(int blockIndex, char* buffer) {
    return true;
}

bool customWriteBlock(int blockIndex, const char* data) {
    return true;
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
