#pragma once
#include <cstdint>

// Manages the layers for collisions
class BitMask
{
public:
	BitMask();
	~BitMask();

	// Clear the bitmask with zeros only
	void Clear();
	
	uint32_t GetData() const { return mData; }
	
	void SetMask(int index);

	bool IsBitMask(int index) const;
	
	bool HasCommonMask(BitMask* pBitset) const;

protected:
	uint32_t mData;
};