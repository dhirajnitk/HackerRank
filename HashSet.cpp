#include <iostream>
#include <algorithm>
#include <list>
#include <string>
using namespace std;
template <typename K> class HashSet{
   list<K> *bucketArray;
   int numBuckets;
   int size;
   int initialCapacity;
   float loadRatio;
public:
    HashSet(int initialCapacity=16, float loadFactor = 0.75f){
        numBuckets =initialCapacity ;
        size = 0;
        loadRatio = loadFactor;
        bucketArray = new list<K>[numBuckets]();
    }
    //Function name and variable name cant be same;
    int Size() { return size;}
    bool isEmpty() { return size == 0;}
    int getBucketIndex( K key){
        unsigned long long  hashCode =  std::hash<K>{}(key);
        int index = hashCode % numBuckets;
        return index;
    }
    void remove(K key){
        int bucketIndex = getBucketIndex(key);
        typename  list<K> :: iterator removeKey = find (bucketArray[bucketIndex].begin(), bucketArray[bucketIndex].end(), key);
        if (removeKey != bucketArray[bucketIndex].end())
        {
            bucketArray[bucketIndex].erase(removeKey);
            size--;
        }
    }

    void add(K key){
        int bucketIndex = getBucketIndex(key);
        //typename  list<K> :: iterator insertKey = find (bucketArray[bucketIndex].begin(), bucketArray[bucketIndex].end(), key);
        auto insertKey = find (bucketArray[bucketIndex].begin(), bucketArray[bucketIndex].end(), key);
        if (insertKey != bucketArray[bucketIndex].end())
        {
            return ;
        }
        bucketArray[bucketIndex].emplace_back(key); 
            size++;
        ensureCapacity();
    }
    void ensureCapacity(){
        if((1.0*size)/numBuckets >= loadRatio){
            list<K> *temp = bucketArray;
            int oldBuckets = numBuckets;
            numBuckets = 2 * numBuckets;
            bucketArray = new list<K>[numBuckets]();
            size = 0;
            for(int id = 0;id <oldBuckets; id++){
                for ( auto listKey: temp[id])
                        add(listKey);
                temp[id].clear();
            }
        }
    }
};

int main(){
    HashSet<string> map;
    map.add(string("this"));
    cout << map.Size()  <<endl;
    map.add(string("coder"));
    cout << map.Size()  <<endl;
    map.add(string("this"));
    cout << map.Size()  <<endl;
    map.add(string("hi"));
    cout <<"Size:"<< map.Size()  <<endl;
    map.remove("this");
    cout <<"Size:" << map.Size()  <<endl;
    cout <<"Empty :" << map.isEmpty()  <<endl;
    return 0;
}   