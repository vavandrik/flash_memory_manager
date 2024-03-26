#ifndef FLASH_MEMORY_MANAGER_HPP
#define FLASH_MEMORY_MANAGER_HPP

#include <functional>
#include <bitset>

class FlashMemoryManager {
public:
    using ReadBlockFunc = std::function<bool(int, char*)>;
    using WriteBlockFunc = std::function<bool(int, const char*)>;
    using EraseBlockFunc = std::function<bool(int)>;

    FlashMemoryManager(ReadBlockFunc readFunc, WriteBlockFunc writeFunc, EraseBlockFunc eraseFunc, int totalBlocks);

    void findBadBlocks();
    void printBadBlocks() const;

private:
    ReadBlockFunc readBlock;
    WriteBlockFunc writeBlock;
    EraseBlockFunc eraseBlock;
    std::bitset<2048> checkedBlocks; // To track checked blocks, 2 bit per block
    std::bitset<2048> blockStatus;   // to track state of blocks, correct/incorrect

    int totalBlocks;
    bool checkBlock(int blockIndex);
};

#endif // FLASH_MEMORY_MANAGER_HPP
