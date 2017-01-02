//Author:Pandong Zhang
//ID: 10403801

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <string>
#include <vector>
using namespace std;

class growArray{
private:
    int* data;
    int used;
    int capacity;
    void grow(){
    	int* temp = data;
    	capacity = capacity*2;
    	data = new int[capacity];
    	for(int i=0; i<used; i++){
    		data[i] = temp[i];
    	}
    	delete [] temp;
    }

public:
    growArray(): data(new int[1]), used(0), capacity(1){}
    growArray(int initialCapacity){
        data = new int[initialCapacity];
        used = 0;
        capacity = initialCapacity;
    }
    ~growArray(){
        delete [] data;
    }
    int length(){
        return used;
    }
    void addEnd(int v){
        if(used+1 > capacity)
        	grow();
        data[used] = v;
        used++;
    }
    //using grow() will be two times slower.
    void addStart(int v){
        int *temp = data;
        if(used+1 > capacity){
        	capacity = capacity*2;
            data = new int[capacity];
        }
        for(int i=used-1; i>=0;i--)
            data[i+1]=temp[i];
        data[0] = v;
        used++;
    }

    void removeEnd(){
        used--;
    }
    void removeStart(){
        for(int i=0;i<used-1; i++)
            data[i]=data[i+1];
        used--;
    }

    void show(){
        for(int i=0; i<used; i++)
            cout<<data[i]<<' ';
            cout<<'\n';
    }

    void add(string command, vector<string> s){
        int start = stoi(s[0]);
        int step = stoi(s[1]);
        int end = stoi(s[2]);
        if(command == "ADD_FRONT"){
            for(int i=start;i<=end;i+=step)
                addStart(i);
        }
        if(command == "ADD_BACK"){
            for(int i=start; i<=end;i+=step)
                addEnd(i);
        }
    }

    void remove(string command, int bits){
        if(command == "REMOVE_FRONT"){
            for(int i=0;i<bits;i++)
                removeStart();
        }
        if(command == "REMOVE_BACK"){
            for(int i=0;i<bits;i++)
                removeEnd();
        }
    }

    int operator[](int i){
        return data[i];
    }

};

vector<string> str_split(string str){
    char* cstr=const_cast<char*>(str.c_str());
    char* current;
    vector<string> arr;
    current=strtok(cstr,":");
    while(current!=NULL){
        arr.push_back(current);
        current=strtok(NULL,":");
    }
    return arr;
}


int main(){
    growArray a;

    ifstream infile("HW4a.txt");
    string line;
    cout<< "OUTPUT:"<<"\n";
    while(getline(infile, line)){
        if(!line.empty()){
            istringstream l(line);
            string command;
            string para;
            int bits;
            l>>command;
            if(command =="ADD_FRONT" || command == "ADD_BACK"){
                while(l>>para){
                    vector<string> s;
                    l>>para;
                    s=str_split(para);
                    a.add(command, s);
                }
            }

            if(command =="REMOVE_FRONT" || command == "REMOVE_BACK"){

                while(l>>bits){
                    a.remove(command, bits);
                }
            }
            if(command =="OUTPUT"){
                a.show();
            }
        }
    }

}

