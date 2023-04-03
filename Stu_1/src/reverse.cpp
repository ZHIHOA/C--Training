#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> index;
        for(int i=0;i<nums.size()-1;i++){
            for(int j=i+1;j<nums.size()-i+1;j++){
                int tmp =nums[i]+nums[j];
                if(target==tmp){
                    index.push_back(i);
                    index.push_back(j);
                    
                }
            }
        }
        return index;
    }
};
int main(){

    Solution su;
    vector<int> vec{2,7,7,15};
    vector<int> ret = su.twoSum(vec,9);
    cout<<ret.size()<<endl;
    vector<int>::iterator it;
    for(auto it=ret.begin();it!= ret.end();++it){
        cout<<*it<<endl;
    }
    
    
}