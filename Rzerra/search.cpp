#include <iostream>
#include <stdlib.h>

using namespace std;

void init(int iArray[], int iSize)
{
	for(int i=0; i<iSize; ++i)
		iArray[i] = i+10; // (rand()%89)+10;
}

void show(int iArray[], int iSize)
{
	for(int i=0; i<iSize; ++i)
		cout<<iArray[i]<<' ';
}

int search1(int iArray[], int iSize, int iKey)
{
	for(int i=0; i<iSize; ++i)
	{
		if(iArray[i]==iKey)
			return i;
	}
	return -1;
}

int search2(int iArray[], int iSize, int iKey)
{
	int i=0;
	while(i<iSize)
	{
		if(iArray[i]==iKey)
			return i;
		++i;
	}
	return -1;
}

int search3(int iArray[], int iSize, int iKey)
{
	iArray[iSize] = iKey;
	int i=0;
	while(iArray[i]!=iKey)
		++i;
	if(i!=iSize)
		return i;
	return -1;
}

int search4(int iArray[], int iSize, int iKey)
{
	if(iSize==0)
		return -1;

	int end = iSize-1;
	int last = iArray[end];
	if(last==iKey)
		return end;

	int i=0;
	while(iArray[i]!=iKey)
		++i;
	iArray[end] = last;
	if(i!=iSize)
		return i;
	return -1;
}

void main()
{
	const int size = 10;
	int arr[size];
	init(arr, size);
	show(arr, size);
	cout<<search1(arr, size, 11)<<' ';
	cout<<search2(arr, size, 11)<<' ';
	cout<<search3(arr, size, 11)<<' ';
	cout<<search4(arr, size, 11)<<' ';
}
