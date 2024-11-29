#include<iostream>
#include<list>
#include<unordered_map>
using namespace std;

//Node to store the data (Linked List)
class Node{
public:
      string key;
      int value;
      Node(string key, int value){
        this->key = key;
        this->value = value;
      }
};


//LRU Cache Data Structure
class LRUCache{
public:
      int maxSize;
      list<Node> dll;   //dll->doubly linked list
      unordered_map<string, list<Node>::iterator> map;

      LRUCache(int maxSize){
        this->maxSize = maxSize > 1 ? maxSize : 1;
      }


      void insertKeyValue(string key, int value){
        //2 cases
        if(map.count(key) != 0){
          //replace the old value and update
          auto it = map[key];
          it->value = value;
        }
        else{
          //check if cache is full or not
          //if full, remove the least recently used item from cache
          if(dll.size() == maxSize){
            Node last = dll.back();
            map.erase(last.key); //remove from hashmap
            dll.pop_back();     //remove from linked list
          }

          Node newNode(key, value);
          dll.push_front(newNode);
          map[key] = dll.begin();
        }
      }


      int* getValue(string key){
        //if present
        if(map.count(key) != 0){
          auto it = map[key];

          int value = it->value;
          dll.push_front(*it);
          dll.erase(it);
          map[key] = dll.begin();
          return &dll.begin()->value;
        }
        return NULL;
      }


      string mostRecentKey(){
        return dll.front().key;
      }

};

int main(){
      LRUCache lru(3);
      lru.insertKeyValue("mango", 10);
      lru.insertKeyValue("apple", 20);
      lru.insertKeyValue("guava", 30);
      cout<<lru.mostRecentKey() <<endl;

      lru.insertKeyValue("mango", 40);
      cout<<lru.mostRecentKey() <<endl;

      int *orders = lru.getValue("mango");
      if(orders != NULL){
        cout<<"Order of Mango "<<*orders <<endl;
      }

      lru.insertKeyValue("banana", 20);

      if(lru.getValue("apple") == NULL){
        cout<<"apple doesn't exist";
      }
      if(lru.getValue("guava") == NULL){
        cout<<"guava doesn't exist";
      }
      if(lru.getValue("banana") == NULL){
        cout<<"banana doesn't exist";
      }
      if(lru.getValue("mango") == NULL){
        cout<<"mango doesn't exist";
      }

      return 0;
}