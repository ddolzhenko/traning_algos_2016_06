#include "algos.h"

namespace NTest
{
	// F*cking modern way, ya:
	template <typename T, std::size_t N>
	constexpr std::size_t sizeof_array(T const (&)[N]) noexcept
	{
		return N;
	}

	// Min element: ----------------------------------------

	void min_search_empty_array()
	{
		int *a = 0;
		assert( a == NAlgos::min_search(a, a + 0) );
	}

	void min_search_one_element()
	{
		int a[] = { 666 };
		assert(666 == *NAlgos::min_search(a, a + sizeof_array(a)));
	}

	void min_search_repeatable_elements()
	{
		int a[] = { 1, 0, 0, 0, 2, 3 };
		int *result = NAlgos::min_search(a, a + sizeof_array(a));

		assert(result == (a + 1)); //founds first 
	}

	// selection_sort: ---------------------------------------

	void selection_sort_empty_array()
	{
		int *a = 0;
		NAlgos::selection_sort(a, a + 0);
	}

	void selection_sort_one_element()
	{
		int a[] = { 666 };
		//NAlgos::selection_sort(a, a + sizeof_array(a));

		assert(*a == 666);
	}

	void selection_sort_array()
	{
		int a[] = { 3, 5, 1, 2, 8 };
		NAlgos::selection_sort(a, a + sizeof_array(a));
	}



	void run_tests()
	{
		min_search_empty_array();
		min_search_one_element();
		min_search_repeatable_elements();

		selection_sort_empty_array();
		selection_sort_one_element();
	}
}