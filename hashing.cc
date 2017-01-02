#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

class growArray{
private:
    int size;
    //int used;
    int* data;
    int hash(int val){
        return val % size;
    }
    
public:
    growArray():size(0), data(nullptr){
    }
    growArray(int s): size(s), data(new int[s]){
    }
    ~growArray(){
        delete [] data;
    }
    vector<int> v;
    void add(int val){
        v.push_back(val);
        size++;
    }
    bool find(int val){
        if(data[hash(val)] != 0) return true;
        return false;
    }
    void hashing(){
        data = new int[size];
        for(int i =0; i<size;i++){
            data[i] = 0;
        }
        for(int i =0;i<size;i++){
            int index = hash(v[i]);
            if(data[index] == 0){
                data[index] = v[i];
            }
            else{
                data = new int[++size];
                for(int i =0; i<size;i++)
                    data[i] = 0;
                i = 0;
            }
        }
    }
};

class perfectHashing{
private:
    growArray* table;
    int size;
    int used;
    int hash(int val){
        return val % size;
    }

    void grow(){
        growArray* temp = table;
        table = new growArray[size*2];
        size = size*2;
        for(int i =0; i<size/2; i++){
            if(temp[i].v.size() == 0)
                continue;
            vector<int> p;
            for(int j = 0; j<p.size(); j++){
                int  val = temp[i].v[j];
                table[hash(val)].add(val);
            }
        }
        delete [] temp;
    }
public: 
    perfectHashing(): used(0),size(8),table(new growArray[8]){
    }
    void add(int val){
        if(used >= size){
            grow();
        }
        table[hash(val)].add(val);
        used++;
    }
    bool find(int val){
        int index1 = hash(val);
        if(table[index1].find(val))
            return true;
        return false;
    }
    void built(){
        for(int i =0; i<size;i++){
            if(table[i].v.size() == 0)
                continue;
            table[i].hashing();
        }
    }
};


int main(){
    int a[6] = {11,37,5,21,22,27};
    perfectHashing lib;
    for(int i =0; i<6;i++)
        lib.add(a[i]);
    lib.built();
    // for(int i =0; i<6; i++){
    //     cout<<a[i]<<' '<<lib.find(a[i])<<'\n';
    // }
    cout<<lib.find(8)<<'\n';
}