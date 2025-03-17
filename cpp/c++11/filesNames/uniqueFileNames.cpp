#include <iostream>
#include<vector>
#include <unordered_map>

using namespace std;

 std::vector<std::string> fixUniqueNames(std::vector<std::string>& names){
    std::unordered_map<std::string,int> mCount;
    std::vector<std::string> fixedNames;
    fixedNames.reserve(names.size());

    cout << "first size" << fixedNames.size() << endl;

    for(const auto& name : names){//insert all unique names to map with -1
        if(mCount.find(name) == mCount.end())
        {
            mCount[name] = -1;
        }
    }

    for(const auto& name : names){    
        if(mCount[name] == -1){//it is an unique first original name
            fixedNames.push_back(name);
            mCount[name] = 1;
        }
        else{
            int k = mCount[name];
            mCount[name]++;
            string newName;
            do{
                newName = name + '(' + to_string(k++) + ')';            
            } while(mCount.find(newName) != mCount.end());

            fixedNames.push_back(newName);
            mCount[newName] = 1;

        }
       
      
    }

     cout << "end  size" << fixedNames.size() << endl;
    return fixedNames;
 }

int main(){
    std::vector<std::string> names = {"a", "b", "c", "a", "a(1)", "a"};
    std::vector<std::string> namesFixed = fixUniqueNames(names);
   
   for(const auto& name : namesFixed)
   {
    cout << name <<',' ;
   }
   return 0;
}