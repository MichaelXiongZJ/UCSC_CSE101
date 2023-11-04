#include <iostream>
#include <cstdlib> 
using namespace std;

//helpers

//print array
void printArray(int arr[], int size){
    for(int i = 0; i < size; i++){
        cout << arr[i] << " ";
    }
    cout << endl;
}

//quick sort

// Persudo Code Practice Problems

// Array Questions:

// 1. Given a number x, find if two numbers add up to x (or the closest sum to x)
//Persudo Code:
    // 1. Sort the array
    // 2. Use two pointers, one at the beginning and one at the end
    // 3. If the sum of the two pointers is greater than x, move the right pointer to the left
    // 4. If the sum of the two pointers is less than x, move the left pointer to the right
    // 5. If the sum of the two pointers is equal to x, return true
//Code Answer:
void findSum(int arr[], int size, int x){   //runtime O(nlogn)
    //sort with quick sort
    //quickSort(arr, 0, size - 1);
    int i = 0;
    int j = size - 1;
    int sum = 0;
    int closestSum = 0;
    int closestSumDiff = 0;
    while(i < j){
        sum = arr[i] + arr[j];
        if(sum == x){
            cout << "Sum found: " << arr[i] << " + " << arr[j] << " = " << x << endl;
            return;
        }
        else if(sum < x){
            if(x - sum < closestSumDiff){
                closestSum = sum;
                closestSumDiff = x - sum;
            }
            i++;
        }
        else{
            if(sum - x < closestSumDiff){
                closestSum = sum;
                closestSumDiff = sum - x;
            }
            j--;
        }
    }
    cout << "Sum not found, closest sum is: " << closestSum << endl;
}

//2. Find the median of the union of 2 sorted arrays
//persudo code answer:
// Iterate over the 2 arrays with variables i and j. 
// Insert min(array1[i], array2[j]) into a new array for every iteration. 
// Only increment the variable of the index that got inserted so if array2[j] gets inserted increase j and keep i the same for the next iteration. 
// Then you can perform the operation in O(1) time. 
// runtime = O(2n) + O(1)

//3. Find the kth smallest element in the union of two sorted arrays
//persudo code answer:



int main(){
    int unsorted_arr[] = {5,9,6,3,4,7,2,8,1};
    int sorted_arr[] = {1,2,3,4,5,6,7,8,9};
    int size = 9;

    return 0;
}
