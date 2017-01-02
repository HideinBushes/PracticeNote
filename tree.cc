#include <iostream>

using namespace std;

class tree{
private:
    class treeNode{
    public:
        int val;
        treeNode* left;
        treeNode* right; 
        treeNode(int v, treeNode* left, treeNode* right):
                    val(v), left(left), right(right){}
        ~treeNode(){
            delete left;
            delete right;
        }
        void inorder(){ //left, me, right
            if(left != nullptr)
                left->inorder();
            cout << val << ' ';
            if(right != nullptr)
                right->inorder();
        }
        void preorder(){ //me, left, right
            cout<< val << ' ';
            if(left != nullptr)
                left->preorder();
            if(right != nullptr)
                right->preorder();
        }
        void postorder(){ //left, right, me
            if(left != nullptr)
                left->postorder();
            if(right != nullptr)
                right->postorder();
            cout<<val<<' ';
        }
    };
    treeNode* root;
public:
    tree():root(nullptr){}
    ~tree(){
        delete root;
    }
    void add(int val){
        if(root  == nullptr){
            root = new treeNode(val,nullptr,nullptr);
            return;
        }
        treeNode* p = root;
        while(true){
            if(val > p->val){
                if(p->right ==nullptr){
                    p->right = new treeNode(val,nullptr, nullptr);
                    return;
                }else{
                    p = p->right;
                }
            }else{
                if(p->left ==nullptr){
                    p->left = new treeNode(val, nullptr, nullptr);
                    return;
                }else{
                    p = p->left;
                }
            }
        }
    }

    void printInorder(){
        if(root == nullptr) return;
        root->inorder();
        cout<<'\n';
    }
    void printPostorder(){
        if(root == nullptr ) return;
        root->postorder();
        cout<<'\n';
    }
    void printPreorder(){
        if(root == nullptr) return;
        root->preorder();
        cout<<'\n';
    }
    

};

int main(){
    tree b;
    b.add(5);
    for(int i = 0 ; i< 10; i++){
        b.add(i);
    }
    b.printInorder();
    b.printPreorder();
    b.printPostorder();
}