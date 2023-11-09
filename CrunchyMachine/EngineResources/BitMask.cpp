#include "BitMask.h"

BitMask::BitMask() { mData = uint32_t(); }

BitMask::~BitMask() { Clear(); }

void BitMask::Clear() { mData = uint32_t(); }

void BitMask::SetMask(int index)
{
	unsigned int bit_value = 1 << index;
	mData = mData ^ bit_value;
}

bool BitMask::IsBitMask(int index) const
{
	unsigned int bit_value = 1 << index;
	uint32_t result = mData & bit_value;
	if (result) return true;
	return false;
}

bool BitMask::HasCommonMask(BitMask* pBitset) const
{
	uint32_t result = mData & pBitset->GetData();
	if (result) return true;
	return false;
}