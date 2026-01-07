#include <iostream>
#include <vector>
using namespace std;

int binarySearch(int toSearch, vector<int> nums) {
    int size = nums.size();
    int temp = 0;
    bool sorted = false;
    
    if (!sorted) {
        cout << "\nThe array is unsorted." << "\nSorting..." << endl;
    }

    while (!sorted) {
        sorted = true;
        for (int i = 0; i < size-1; i++) {
            if (nums[i] > nums[i+1]) {
                temp = nums[i];
                nums[i] = nums[i+1];
                nums[i+1] = temp;
                sorted = false;
            }
        }
    }
    
    // for visualisation of the array
    cout << "\n";
    for (int i=0; i < size; i++) cout << nums[i] << " ";
    cout << "\n";

    // here is the start of main logic of bs..
    int left = 0;
    int right = size - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (nums[mid] == toSearch) {
            cout << "Found " << toSearch << " at index " << mid << "\n" << endl;
            return mid;
        }
        else if (toSearch > nums[mid]) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    
    cout << toSearch << " not found\n";
    return -1;
}

int main() {
    vector<int> nums = {42, 3, 96, 12, 74, 108, 25, 59, 18, 36, 63, 31, 85, 7, 48, 79, 68, 91, 53};
    cout << "Sample Run:" << endl;
    cout << "Given an array, [42, 3, 96, 12, 74, 108, 25, 59, 18, 36, 63, 31, 85, 7, 48, 79, 68, 91, 53]" << endl;
    cout << "Search for 7" << endl;
    binarySearch(7,nums); 

    cout << "--------------------------------------------\n" << "Try it." << endl;
    cout << "Give me some numbers: (-1 to stop)" << endl;
    nums.clear();
    while (true) {
        int num_input;
        cin >> num_input;
        if (num_input < -1) {
            cout << "Invalid input, please try again\n";
            continue;
        }
        else if (num_input == -1) {

            break;
        }
        nums.push_back(num_input);
    }
    int search;
    cout << "I want to search for "; 
    cin >> search;
    binarySearch(search,nums);
    return 0;
}