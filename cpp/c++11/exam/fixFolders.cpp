
// #include <string>
// #include <map>
// #include <vector>
// #include <iostream>

// class FixFolderNames{
//     public:
//      static  std::vector<std::string>  fixFolderNames(std::vector<std::string> names){
      
//         std::multimap<std::string, std::string*> nameMap;
//         int i = 0;

//         for (i = 0; i < names.size(); i++){
//             nameMap.insert({names[i] , &names[i]});
//         }

//         for(auto it = nameMap.begin(); it != nameMap.end(); it = nameMap.upper_bound(it->first)){
//             std::cout << "original name: " << it->first << std::endl;
//             auto range = nameMap.equal_range(it->first);
//             for(auto valIt = range.first; valIt != range.second; valIt++){
//                 *valIt->second = 
//             }
//         }

                  

//         return ;
//      }




// };