#include <vector>
#include <list>




template <typename K, typename V>
class MyHashMap{
private:
    std::vector<std::list<std::pair<K,V>>> buckets;
    static constexpr size_t INIT_BUCKETS_SIZE = 10;
    static constexpr double LOAD_FACTOR_THRESHOLD = 0.75;

    size_t getBucketInx(K key){
        return std::hash<K>{}(key) % buckets.size();
    }

public:
    MyHashMap(){
        buckets.reserve(INIT_BUCKETS_SIZE);

    }
    
    void insert(const K& key, const V& value){
        size_t i = getBucketInx(key);
        for(auto& [k, v] :   buckets[i]){
            if(k == key){
                return; //key is used
            }
        }
        buckets[i].emplace_Back(key, value);     

    }

    void update()
    std::pair<K,V> remove(const K& key){
        size_t i = getBucketInx(key);
        for(auto& [k, v] :   buckets[i]){
            if(k == key){
                return [k, v]; //key is used
            }
        }

        return nullptr;
    }



};