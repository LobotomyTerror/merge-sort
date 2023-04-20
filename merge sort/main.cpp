//
//  main.cpp
//  merge sort
//
//  Created by Daniel Fishbein on 4/17/23.
//

#include <iostream>
#include <ctime>
#include <chrono>
#include <fstream>

const int threshhold = 10;

int* merge(int arr[], int len, int ls_s, int ls_e, int rs_s, int rs_e)
{
    int* temp = new int[len];
    int index = 0;
    while (ls_s <= rs_s && ls_e <= rs_e)
    {
        if (arr[ls_s] <= arr[ls_e]){
            temp[index] = arr[ls_s];
            ++index;
            ++ls_s;
        }
        else{
            temp[index] = arr[ls_e];
            ++index;
            ++ls_e;
        }
    }
    while (ls_s <= rs_s)
    {
        temp[index] = arr[ls_s];
        ++index;
        ++ls_s;
    }
    while (ls_e <= rs_e)
    {
        temp[index] = arr[ls_e];
        ++index;
        ++ls_e;
    }
    return temp;
}

void mergeSort(int arr[], int len)
{
    int ls_start, ls_end, rs_start, rs_end;
    int* temp;
    
    int i = 1;
    while (i < len)
    {
        int j = 0;
        while (j < len)
        {
            ls_start = j; //the beginning of the left side
            rs_start = j + i - 1; //the end of the left side
            ls_end = j + i; //the beginning of the right side
            rs_end = j + 2 * i - 1; //the end of the right side
            
            if (ls_end >= len){
                break;
            }
            else if (rs_end >= len){
                rs_end = len - 1;
            }
            temp = merge(arr, len, ls_start, ls_end, rs_start, rs_end);
            
            for (int k = 0; k < rs_end - ls_start + 1; ++k)
                arr[j + k] = temp[k];
            j = j + 2 * i;
        }
        i = 2 * i;
    }
}

void mergeR(int arr[], int leftSide, int rightSide, int mid)
{
    int lowEnd = mid - leftSide + 1;
    int highEnd = rightSide - mid;
    int k = leftSide;
    int i, j;
    
    int* tempArr1 = new int[lowEnd];
    int* tempArr2 = new int[highEnd];
    
    for (i = 0; i < lowEnd; ++i){
        tempArr1[i] = arr[leftSide + i];
    }
    
    for (j = 0; j < highEnd; ++j){
        tempArr2[j] = arr[j + 1 + mid];
    }
    
    i = 0;
    j = 0;
    
    while (i < lowEnd && j < highEnd){
        if (tempArr1[i] < tempArr2[j]){
            arr[k] = tempArr1[i];
            ++i;
        }
        else{
            arr[k] = tempArr2[j];
            ++j;
        }
        ++k;
    }
    while (i < lowEnd){
        arr[k] = tempArr1[i];
        ++i;
        ++k;
    }
    while (j < highEnd){
        arr[k] = tempArr2[j];
        ++j;
        ++k;
    }
}

//void insertionSort(int arr[], int ls, int rs)
//{
//    for (int i = 1; i < rs; ++i){
//        int temp = arr[i];
//        int j = i - 1;
//        while (j >= 0 && arr[j] > temp){
//            arr[j + 1] = arr[j];
//            --j;
//        }
//        arr[j + 1] = temp;
//    }
//}

void mergeSortR(int arr[], int leftSide, int rightSide)
{
    if (leftSide < rightSide){
        int mid = (leftSide + rightSide) / 2;
        mergeSortR(arr, leftSide, mid);
        mergeSortR(arr, mid + 1, rightSide);
        mergeR(arr, leftSide, rightSide, mid);
    }
}

int main(int argc, const char * argv[])
{
    std::ofstream outf;
    outf.open("/Users/danielfishbein/Documents/computerProjects/Xcode/merge sort/merge sort/data.txt");
    
    if (!outf.is_open())
        std::cout << "Error opening file\n";
    
    int arr[1000000];
    int len = sizeof(arr) / sizeof(int);

    std::srand((int)std::time(0));
    for (int n=0; n<1000000; n++)
        arr[n]=rand()%79315+1;

    auto start = std::chrono::high_resolution_clock::now();
    mergeSort(arr, len);
    auto finish = std::chrono::high_resolution_clock::now();

    auto duration1 = duration_cast<std::chrono::microseconds>(finish - start);

    for (int i = 0; i < len; ++i)
        outf << arr[i] << ' ';
    outf << '\n';
    
    int arr2[1000000];
    int len2 = sizeof(arr) / sizeof(int);
    
    for (int n=0; n<1000000; n++)
        arr2[n]=rand()%79315+1;
    
    auto start2 = std::chrono::high_resolution_clock::now();
    mergeSortR(arr2, 0, len2 - 1);
    auto finish2 = std::chrono::high_resolution_clock::now();
    
    auto duration2 = duration_cast<std::chrono::microseconds>(finish2 - start2);
    
    for (int i = 0; i < len2; ++i)
        outf << arr2[i] << ' ';
    outf << '\n';
    
    outf<<"Iterative Merge Sort time was: "<< duration1.count()<<" micro seconds!\n";
    outf<<"Recursive Merge Sort time was: "<< duration2.count()<<" micro seconds!\n";
    
    return 0;
}
