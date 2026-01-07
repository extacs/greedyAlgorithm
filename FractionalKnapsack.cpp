#include <iostream>
#include <iomanip>
#include <cmath>
#include <unordered_map>
#include <map>
#include <vector>
#include <string>
using namespace std;

void fractionalKnapsack(map<double, unordered_map<string, map<string,double,greater<string>> >, greater<double>>& sack, int maxCap) {
    for (auto &VWratio : sack) { // VWratio is for the order of items.
        for (auto &item : VWratio.second) { 
            cout << "  " << item.first << ":\n";
            for (auto &attr : item.second) {
                cout << fixed << setprecision(0) << "    " << attr.first << ": " << attr.second <<"\n";
            }
        }
    }
    cout << "\n\nApplying Fractional Knapsack..\n";
    double capacity = maxCap;
    bool maxReached = false; 
    bool isPartial = false;
    double currentWeight;
    vector<string> toBring;
    double totalValue = 0;
    
    for (auto &VWratio : sack) { // we solve for the VWratio outside the function to make the function cleaner (but might be irreplicable)
        for (auto &item : VWratio.second) {
            if (!maxReached) {
                toBring.push_back(item.first);
                cout << "  " << item.first;
            }
            if (capacity == 0) {
                    cout << "\n    The maximum capacity has been reached.\n";
                    cout << "      -unable to bring " << item.first << ".\n";
                    maxReached = true;
                    toBring.erase(toBring.end()-1);
                    continue;
            }
            for (auto &attr : item.second) {
                if (capacity == 0) {
                    cout << "\n    The maximum capacity has been reached.\n";
                    cout << "      -unable to bring " << item.first << ".\n";
                    maxReached = true;
                    continue;
                }
                if (attr.first=="weight") {
                    currentWeight = attr.second;
                    if(capacity-attr.second < 0) {
                        isPartial = true;
                        capacity += attr.second; // to counter the -= below 
                    }
                    capacity -= attr.second; 
                }

                if (isPartial && attr.first=="value") { // exit point of the function
                    double partialValue = capacity/currentWeight * attr.second;
                    cout << fixed << setprecision(0) << "    " << attr.first << ": " << partialValue << "  (partial)";
                    totalValue += partialValue;
                    capacity = 0;
                    continue; 
                }

                else if (attr.first=="value") {
                    totalValue += attr.second;
                }
                
                if (!maxReached && isPartial && attr.first=="weight") { // we would need to print the weight occupied of the current partial item.
                    cout << "  (exceeds capacity)\n" << fixed << setprecision(0) << "    " << attr.first << ": " << capacity << "  (partial)\n"; 
                    continue;
                }
                else if (!maxReached) {
                    cout << "\n" << fixed << setprecision(0) << "    " << attr.first << ": " << attr.second;
                    continue;
                }
            }
            if (VWratio.first == floor(VWratio.first)) {
                cout << "\n" << fixed << setprecision(0) << "    " << "v-to-w ratio: " << VWratio.first <<"\n";
            }
            else if(VWratio.first != floor(VWratio.first)) {
                cout << fixed << setprecision(1) << "    " << "v-to-w ratio: " << VWratio.first <<"\n";
            }
            cout << fixed << setprecision(0) << "      " << "Remaining Capacity: " << capacity << "\n";
            cout << fixed << setprecision(0) << "      " << "Current value: " << totalValue << "\n";
        }
    }

    // concluding block
    cout << "\nTherefore we may bring the following:\n";
    for (string x : toBring) {
        cout << " - " << x << "\n"; 
    }
    cout << "Total Value = " << totalValue;
}


int main() {
    map<double, unordered_map<string, map<string,double,greater<string>> >, greater<double>> sample_knapsack;
    cout << "Sample run:" << endl;
    cout << "- Given the maximum weight of 60 on a bag. Perform a Fractional Knapsack to find which items we would bring." << endl;
    int maxCap = 60;
    sample_knapsack[(double)40/10]["Jacket"]["weight"] = 10;
    sample_knapsack[(double)40/10]["Jacket"]["value"] = 40;
    sample_knapsack[(double)150/5]["Laptop"]["weight"] = 5;
    sample_knapsack[(double)150/5]["Laptop"]["value"] = 150;
    sample_knapsack[(double)80/8]["Camera"]["weight"] = 8;
    sample_knapsack[(double)80/8]["Camera"]["value"] = 80;
    sample_knapsack[(double)60/12]["Shoes"]["weight"] = 12;
    sample_knapsack[(double)60/12]["Shoes"]["value"] = 60;
    sample_knapsack[(double)100/20]["Snacks"]["weight"] = 20;
    sample_knapsack[(double)100/20]["Snacks"]["value"] = 100;
    sample_knapsack[(double)50/4]["Power Bank"]["weight"] = 4;
    sample_knapsack[(double)50/4]["Power Bank"]["value"] = 50;
    sample_knapsack[(double)45/15]["Blanket"]["weight"] = 15;
    sample_knapsack[(double)45/15]["Blanket"]["value"] = 45;
    sample_knapsack[(double)85/60]["Tent"]["weight"] = 60;
    sample_knapsack[(double)85/60]["Tent"]["value"] = 85;
    sample_knapsack[(double)500/200]["Pridator"]["weight"] = 200;
    sample_knapsack[(double)500/200]["Pridator"]["value"] = 500;
    fractionalKnapsack(sample_knapsack, maxCap);

    map<double, unordered_map<string, map<string,double,greater<string>> >, greater<double>> knapsack;
    cout << "\n\n--------------------------------------------\n\n" << "Try it." << endl;
    cout << "\nWhat is the maximum capacity?" << endl;
    cin >> maxCap;
    cout << "\nHow many kind items do you wish to bring" << endl; // too lazy, so let the user do the work..
    int quantity;
    cin >> quantity;
    cout << "\nProvide me some items along with their corresponding weight and value: \n" << endl;
    string item;
    double weight;
    double value;
    for (int i=0; i < quantity; i++) {
        cout << "Item: ";
        cin >> item;
        cout << "Weight: ";
        cin >> weight;
        cout << "Value: ";
        cin >> value;
        cout << "\n";
        knapsack[value/weight][item]["weight"] = weight;
        knapsack[value/weight][item]["value"] = value;
    }
    fractionalKnapsack(knapsack, maxCap);

    return 0;
}