

int main()
{
	return 0;
}

int search_1(int arr[], int size, int key)
{
	for (int i = 0; i < size; i++)
	{
		if (arr[i] == key) return i;
	}
	return -1;
}

int search_2(int arr[], int size, int key)
{
	int i = 0;
	while (i < size)
	{
		if (arr[i] == key) return i;
		i++;
	}
	
	return -1;
}


int search_3(int arr[], int size, int key)
{
	arr[size] = key;
	int i = 0;
	while (arr[i] != key) i++;
	if (size != i) return i;
	else return -1;
}

int search_4(int arr[], int size, int key)
{
	int last = size -1;
	int end = key;

	if (arr[last] == end) return last;
	else arr[last] = end;

	int i = 0;
	while (arr[i] != key) i++;
	if (last != i) return i;
	else return -1;
}
