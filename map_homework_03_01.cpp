#include <iostream>
#include <future>
#include <thread>

void print_array(int arr[], const int& size)
{
	for (int i = 0; i < size; ++i)
	{
		std::cout << arr[i] << ' ';
	}
	std::cout << std::endl;
}

void find_min(int arr[], const int& size, const int& i, std::promise<int> p)
{
	int min = i;
	for (int j = i + 1; j < size; j++)
	{
		min = (arr[j] < arr[min]) ? j : min;
	}
	p.set_value(min);
}

void select_sort(int arr[], const int& size)
{
	std::future<int> ft_p;
	int min{ 0 };
	int tmp{ 0 };

	for (int i = 0; i < size; ++i)
	{
		std::promise<int> prom;
		ft_p = prom.get_future();

		auto ft = std::async(find_min, arr, std::ref(size), std::ref(i), std::move(prom));

		min = ft_p.get();
		if (i != min)
		{
			tmp = arr[i];
			arr[i] = arr[min];
			arr[min] = tmp;
		}
	}

}

int main()
{
	int a[]{ 22,4,95,17,36,57 };
	int n = sizeof(a) / sizeof(a[0]);
	print_array(a, n);
	select_sort(a, n);
	print_array(a, n);
	return 0;
}
