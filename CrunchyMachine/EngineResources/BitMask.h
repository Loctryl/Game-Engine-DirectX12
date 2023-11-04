#pragma once
#include <cstdint>

class BitMask
{
public:
	BitMask();
	~BitMask();

	/* Clear the bitmask with zeros only */
	void Clear();

	/* @return uint32_t data. */
	std::uint32_t GetData() const { return m_data; }

	/*
	* Set/UnSet a new mask on the bitMask.
	* It curently revert the bit on the given index.
	* 
	* @param Index where the bit will be revert.
	*/
	void SetMask(int index);

	/*
	* Test if there is a common Mask between two BitMasks.
	* 
	* @param pointer of the other BitMask to compare.
	* @return True if there is a common Mask, false otherwise.
	*/
	bool HasCommonMask(BitMask* pBitset);

protected:
	std::uint32_t m_data;
};