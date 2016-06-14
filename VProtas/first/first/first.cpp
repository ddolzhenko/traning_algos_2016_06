#include <iostream>
using namespace std;

const int INVALID_INDEX = -1;

const int linearSearch(const int arr[], const int key);

int main()
{
   int arr[] = {3, 6, 7, 12 };
   cout << linearSearch(arr, 12) << endl;
   system("pause");
   return 0;
}

const int linearSearch(const int arr[], const int key)
{
   int size = sizeof(arr);
   if (size <= 0)
   {
      return INVALID_INDEX;
   }
   for (int i = 0; i < size; i++)
   {
      if (arr[i] == key)
      {
         return i;
      }
   }
   return INVALID_INDEX;
}
