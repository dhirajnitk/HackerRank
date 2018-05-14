#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

template <typename K, typename V> class HashNode{
public:
    K key;
    V value;
    HashNode<K,V>* next;
    HashNode(K key, V value) {
        this->key = key;
        this->value = value;
    }
} ;

template <typename K, typename V> class HashMap{
   vector<HashNode<K,V>*> *bucketArray;
   int numBuckets;
   int size;
public:
    HashMap(){
        bucketArray = new vector<HashNode<K,V>*>();
        numBuckets = 10;
        size = 0;
        for( int i = 0;  i<numBuckets; i ++) 
            bucketArray->emplace_back(nullptr);
    }
    //Function name and variable name cant be same;
    int Size() { return size;}
    bool isEmpty() { return size == 0;}
    int getBucketIndex( K key){
        unsigned long long  hashCode =  std::hash<K>{}(key);
        int index = hashCode % numBuckets;
        return index;
    }
    V remove(K key){
        int bucketIndex = getBucketIndex(key);
        HashNode<K,V>* head = bucketArray->at(bucketIndex);
        HashNode<K,V>* prev = nullptr;
        while(head != nullptr){
            if(head->key== key)
                break;
            prev = head;
            head = head->next;
        }
        // key not found
        if(head == nullptr)
            return NULL;

        size--;
        if(prev != nullptr)
            prev->next = head->next;
        else
            bucketArray->at(bucketIndex) =  head->next;
        return head->value;
    }
    V get(K key){
        int bucketIndex = getBucketIndex(key);
        HashNode<K,V>* head = bucketArray->at(bucketIndex);
        while(head!= nullptr){
            if(head->key == key)
                return head->value;
            head = head->next;
        }
        return NULL;
    }

    void add(K key, V value){
        int bucketIndex = getBucketIndex(key);
        HashNode<K,V>* head = bucketArray->at(bucketIndex);
        while(head!= nullptr){
            if(head->key == key){
                head->value= value;
                return;
            }
            head = head->next;
        }

        size++;
        head = bucketArray->at(bucketIndex);
        HashNode<K,V>* newNode = new HashNode<K,V>(key, value);
        newNode->next = head;
        bucketArray->at(bucketIndex) =  newNode;
        if((1.0*size)/numBuckets >= 0.7){
            vector<HashNode<K,V>*>*temp = bucketArray;
            bucketArray = new vector<HashNode<K,V>*>;
            numBuckets = 2 * numBuckets;
            size = 0;
            for (int i = 0; i < numBuckets; i ++)
                bucketArray->emplace_back(nullptr);
            HashNode<K,V>* delNode;
            for(HashNode<K,V>* headNode : *temp){
                while(headNode != nullptr){
                    add(headNode->key, headNode->value);
                    delNode = headNode;
                    headNode = headNode->next;
                    delete(delNode);
                }
            }
            temp->clear();
        }
    }
};

int main(){
    HashMap<string, int> map;
    map.add(string("this"),1);
    cout << map.Size()  <<endl;
    map.add(string("coder"),2);
    cout << map.Size()  <<endl;
    map.add(string("this"),4);
    cout << map.Size()  <<endl;
    map.add(string("hi"),5);
    cout <<"Size:"<< map.Size()  <<endl;
    cout <<"Remove returns "<< map.remove("this")  <<endl;
    cout <<"Size:" << map.Size()  <<endl;
    cout <<"Empty :" << map.isEmpty()  <<endl;
    return 0;
}   