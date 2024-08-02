//approach

/*Sum the total weight of entered apples: - This would be required to store a persistent value.

Determine Target Allocations:

Compute the target weight per person given theirates of share:

Ram: 50% of total weight

Sham: 30% of total weight

Rahim: 20% of total weight

Sort Weights: Apple weights are sorted in descending order for proper distribution.

Allocate Apples:

Iterate through the sorted weights for every person and allocate apples without missing target weight

Output: Print the assigned weights of Ram, Sham and Rahim.*/


#include <bits/stdc++.h>
using namespace std;

void allocateApples(vector<int> &availableApples, vector<int> &allocatedApples, double targetWeight) {
    int currentWeight = 0;
    for (int i = 0; i < availableApples.size(); i++) {
       
        if ((availableApples[i] != -1) && (currentWeight + availableApples[i] <= targetWeight)) {
            allocatedApples.push_back(availableApples[i]);
            currentWeight += availableApples[i];
            availableApples[i] = -1;
        }
    }
    
  
    for (int weight : allocatedApples) {
        cout << weight << " ";
    }

}

int main() {
    vector<int> appleWeights;
    
    
    while (true) {
        int weight;
        cout << "Enter apple weight in grams (-1 to stop): ";
        cin >> weight;
        
        if (weight == -1) {
            break; 
            appleWeights.push_back(weight); 
        }
    }
    
 
    int totalWeight = accumulate(appleWeights.begin(), appleWeights.end(), 0);
    
    
    sort(appleWeights.rbegin(), appleWeights.rend());
    
  
    vector<int> ramApples, shamApples, rahimApples;
  
    double ramTarget = totalWeight * 0.5;
    double shamTarget = totalWeight * 0.3;
    double rahimTarget = totalWeight * 0.2;
    
   
    cout << "Allocation Result:" << endl;
    cout << "Ram: ";
    allocateApples(appleWeights, ramApples, ramTarget);
    cout << endl;
    
    cout << "Sham: ";
    allocateApples(appleWeights, shamApples, shamTarget);
    cout << endl;
    
    cout << "Rahim: ";
    allocateApples(appleWeights, rahimApples, rahimTarget);
    cout << endl;
    
    return 0;
}