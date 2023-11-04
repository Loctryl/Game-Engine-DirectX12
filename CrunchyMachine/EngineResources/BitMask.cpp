#include "BitMask.h"

BitMask::BitMask()
{
	m_data = std::uint32_t();
}

BitMask::~BitMask()
{
	Clear();
}

void BitMask::Clear()
{
	m_data = std::uint32_t();
}

void BitMask::SetMask(int index)
{
	unsigned int bit_value = 1 << index;
	m_data = m_data ^ bit_value;
}

bool BitMask::HasCommonMask(BitMask* pBitset)
{
	std::uint32_t result = m_data & pBitset->GetData();
	if (result >= 1) return true;
	return false;
}

