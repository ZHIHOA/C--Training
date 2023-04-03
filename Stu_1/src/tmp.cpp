#include<iostream>
#include<vector>
#include<algorithm>
#include<ctime>
using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {

        if(s.size()==0 ||s ==""){
            return 0;
        }
        else if (s==" "||s.size()==1)
        {
            /* code */
            return 1;
        }
        else{
            vector<int> vec_cnt;
            vector<char> vec;
            int cnt =1;
        
            for(int i = 0;i<s.size();++i){      //bbc
                
                vec.push_back(s[i]);
                for (int j = i+1; j < s.size(); j++)
                {
                    /* code */
                    if (std::find(vec.begin(), vec.end(), s[j]) == vec.end()){
                        vec.push_back(s[j]);
                        cnt +=1;
                        // cout<<s[j]<<endl;
                        // cout<<cnt<<endl;
                        vec_cnt.push_back(cnt);
                        cout<<"记录一次"<<endl;
                    }
                    else{
                        vec.clear();
                        // vec_cnt.push_back(cnt);
                        cnt = 1;
                        cout<<"完成一次"<<endl;
                        break;
                    }

                }
            
        }
        vector<int>::iterator it1;
        for(it1 = vec_cnt.begin();it1 !=vec_cnt.end();++it1){
            cout<<*it1<<endl;
        }
        cout<<"-------------------"<<endl;
        vector<int>::iterator it =std::max_element(vec_cnt.begin(),vec_cnt.end());
        return *it;

    }

        }
        
};
int main(){

    
    Solution su;
    int ret = su.lengthOfLongestSubstring("dddccc");
    cout<<ret<<endl;
    return 0;
}