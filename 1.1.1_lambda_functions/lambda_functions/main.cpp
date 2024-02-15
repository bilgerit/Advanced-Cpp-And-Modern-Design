// In this exercise, we will explore the use of lambda functions, different ways of capturing variables, etc.
// Tobias Bilgeri, 18 Nov. 2023
#include <iostream>
#include <tuple>
#include <algorithm>

using namespace std;


int main()
{
	// Exercise a
	int a{ 2 };
	int arr[5]{ 1,2,3,4,5 };
	
	int size = sizeof(arr) / sizeof(arr[0]);

	cout << "original array: ";
	for (auto el : arr) { cout << el << " "; }
	cout << endl;
	
	auto capture_via_copy = [a](int* arr, int& size) -> void
	{
		// multiply elements of an array.
		cout << "after multiplication: capture via copy: ";
		for (int i = 0; i < size; i++)
		{
			arr[i] *= a;
			cout << arr[i] << " ";
		}
		cout << endl;
	};

	auto capture_via_ref = [&a](int* arr, int& size) -> void
	{
		// multiply elements of an array.
		cout << "after multiplication: capture via reference: ";
		for (int i = 0; i < size; i++)
		{
			arr[i] *= a;
			cout << arr[i] << " ";
		}
		cout << endl;
	};

	cout << "constant multiplier: " << a << endl;
	capture_via_copy(arr, size);
	capture_via_ref(arr, size);
	a = 1;
	cout << "now set constant multiplier to: " << a << endl;
	capture_via_copy(arr, size);
	capture_via_ref(arr, size);

	cout << "  .. note how using capture via copy-by-value kept on using the old multiplier" <<
		" which was presented when the lambda function was first defined." << endl;
	
	
	// b
	auto auto_initialized_iterator = [&a](int* arr, int& size) -> void
	{
		// multiply elements of an array.
		cout << "after multiplication: capture via reference, and auto initialized iterator: ";
		for (auto i = 0; i < size; i++)
		{
			arr[i] *= a;
			cout << arr[i] << " ";
		}
		cout << endl;
	};
	
	auto_initialized_iterator(arr, size);


	// c
	auto find_min_max = [](int* arr, int& size) -> tuple<int, int>
	{
		int min = arr[0];
		int max = arr[0];
		for (int i = 1; i < size; i++)
		{
			if (arr[i] < min) min = arr[i];
			if (arr[i] > max) max = arr[i];
		}
		cout << "Custom min-max fct: min: " << min << ", max: " << max << endl;
		return make_tuple(min, max);
	};
	
	auto [x, y] = find_min_max(arr, size);
	

	// d
	cout << "now using std::minmax_element to compute the result: ";
	auto [min, max] = minmax_element(begin(arr), end(arr));
	cout << "min: " << *min << ", max: " << *max << endl;
	
	return 0;
}
