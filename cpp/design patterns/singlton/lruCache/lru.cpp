// #include <unordered_map>
// #include <list>
// #include <iostream>
// template < typename Key,typename Value>
// class NodeCache{
//     public:
//         NodeCache( Value data, Key* older, Key* newer) : data(data), older(older), newer(newer) {}
//         Value data;
//         Key& self;
//        Key& newer;
//        Key& older;
//     };


// class LRUCashe
// {

// public: 
//     LRUCashe(size_t capacity) : m_capacity(capacity) {
//         m_map = std::unordered_map<std::string, NodeCache<std::string ,int>>();;
//         m_map.insert_or_assign("0", NodeCache<std::string,int>(0, &std::string("0"), &std::string("0"))); //next* is the newest element, "0", "0"); //prev* is the oldest element m_map["0"] = NodeCache<std::string,int>(0, &std::string("0"), &std::string("0")); //next* is the newest element, "0", "0"); //prev* is the oldest element
//     }

//    int Put(std::string key, int value){
//     NodeCache<std::string ,int> temp = m_map.at("0");
//     m_map["0"].newer = key;
//     m_map[key].data = value;
//     m_map[key].newer = "0";
//     m_map[key].older = temp.older;

//      NodeCache<std::string,int>(value, &m_map.at(key).newer, &m_map.at(key).older);
//        m_map[key].data = value;

        
   
//    }
//    int Get(std::string key);

// private:
//     std::unordered_map<std::string, NodeCache<std::string ,int>> m_map;
//     size_t m_capacity;


// }