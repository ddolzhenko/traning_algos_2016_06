#include "stdafx.h"
#include "iostream"
#include "my_vector.h"


int main()
{
   my_vector<int> vec;
   for (int i = 0; i < 10; ++i)
      vec.push_back(i);

   for (int i = 0; i < 10; ++i)
      std::cout << vec[i] << std::endl;

   system("pause");
   return 0;
}

