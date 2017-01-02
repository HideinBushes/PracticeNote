//author: Pandong Zhang
//ID: 10403801

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <string>
#include <vector>

using namespace std;

class linkedList {
private:
	class node {
	public:
		int val;
		node* next;
		node(int v, node* n): val(v), next(n){}
	};
	node* head;
	node* tail;

public:
	linkedList(): head(nullptr), tail(nullptr){}

	~linkedList(){
		node* q;
		for(node *p = head; p!= nullptr; p = q){
			q= p->next;
			delete p;
		}
	}
	void addEnd(int v){
		if(tail == nullptr){
			head = new node(v, nullptr);
			tail = head;
			return;
		}
		node* p=tail;
		p->next =new node(v, nullptr);
		tail = p->next;
	}

	void addStart(int v){
		if(head == nullptr){
			head = new node(v, nullptr);
			tail = head;
			return;
		}
		head = new node(v,head);
	}

	void insert(int i, int v){
		if(head == nullptr){
			head = new node(v ,nullptr);
			tail = head;
			return;
		}
		node* p=head;
		for(int j=0; j<i && p->next != nullptr; j++){
			p=p->next;
		}
		if(p->next == nullptr){
			p->next = new node(v, nullptr);
			tail = p->next;
			return;
		}
		node* temp = new node(v, p->next);
		p->next = temp;
	}

	void removeEnd(){
		if(tail == nullptr)
			throw "No elements";
		if(head == tail){
			head = nullptr;
			tail = nullptr;
			return;
		}
		node* p = head;
		for(; p->next->next != nullptr; p=p->next){
			;
		}
		tail = p;
		p->next = nullptr;
	}

	void removeStart(){
		if(head == nullptr)
			throw "No elements";
		if(head == tail){
			head = nullptr;
			tail = nullptr;
			return;
		}
		head = head->next;
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

	int get(int i) const{
		node* p = head;
		for(;i>0;i--, p=p->next){
			if(p ==nullptr)
				throw "linkedList index out of bounds";
		}
		return p->val;
	}
	int operator[](int i)const{
		node* p;
		for(p=head;p->next != nullptr;p=p->next)
			;
		return p->val;
	}

	friend ostream& operator<<(ostream& s, const linkedList& list){
			if (list.head ==nullptr){
				s<<"No elements in the list";
				return s;
			}
			s << list.head->val;
		for (node* p=list.head->next; p!= nullptr; p=p->next){
			s << ','<< p->val;
		}
		return s;
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
	linkedList list;

	ifstream infile("HW4b.txt");
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
                    list.add(command, s);
                }
            }

            if(command =="REMOVE_FRONT" || command == "REMOVE_BACK"){

                while(l>>bits){
                    list.remove(command, bits);
                }
            }
            if(command =="OUTPUT"){
                cout<<list<<'\n';
            }
        }
    }

}