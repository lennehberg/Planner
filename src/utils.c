#include "utils.h"

/**
 * Lower bound search implemetation using binary search
 * Finds a pointer in an array to the smallest element
 * that is bigger than the key.
 *
 * @param key pointer to the value to search for
 * @param base pointer to the start of the array
 * @param num number of elements in the array
 * @param size size of each element in the array
 * @param compare comparison function, must return <0 if elem1 < elem2,
 * 						0 if eleme1 == elem2, <0 if elem1 > elem2
 * @return pointer to the first element >= key, or null if no such value exists
 */
void *find_lower_bound(const void *key, const void *base, size_t num, size_t size, 
			int (*compare)(const void *, const void *))
{
	const char *arr = base;
	size_t count = num;
	size_t step;
	size_t idx = 0;

	// start binary search from middle of array
	while (count > 0)
	{
		idx = 0;
		step = count / 2;
		idx += step;
		const void *mid_element =  arr + (idx * size);

		if (compare(mid_element, key) < 0)
		{
			// advance base pointer and reduce count
			arr += (step + 1) * size;
			count -= (step + 1);
		}
		else
		{
			// mid element is a candidate, search to the left including
			count = step;	
		}
	}
	return (void *)arr;
}
