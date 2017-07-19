#include <iostream>
#include <cmath>

using namespace std;

template <class T>
class bstnode{
public:
	T item;
	bstnode<T> *parent;
	bstnode<T> *left;
	bstnode<T> *right;
	bstnode();
	bstnode(T);
};

template <class T>
bstnode<T>::bstnode(){
	parent = NULL;
    left = NULL;
    right = NULL;
};

template <class T>
bstnode<T>::bstnode(T x){
	parent = NULL;
    left = NULL;
    right = NULL;
	item = x;
}

template <class T>
class bst{
private:
	bstnode<T> *root;
	bstnode<T>* min(bstnode<T>*);
public:
	bst();
	~bst();
	int search(T);
	void insert(T);
	int remove(T);
};

template <class T>
bst<T>::bst(){
	root = NULL;
}

template <class T>
bst<T>::~bst(){
	while(root!=NULL)
		remove(root->item);
}
template <class T>
int bst<T>::search(T x){
	bstnode<T> *r = root;
	int count = 0;
	while(r!=NULL){
		count++;
		if(x == r->item) return count+1;
		else if(x < r->item)r = r->left;
		else if(x >= r->item)r = r->right;
	}
	return count*(-1);
}

template <class T>
void bst<T>::insert(T x){
    bstnode<T> *n = new bstnode<T>(x);
    if(root == NULL)
        root = n;
    else{
        bstnode<T> *r = root,*r2;
        while(r!=NULL){
            r2 = r;
            if(x < r->item) r = r->left;
            else if (x >= r->item) r = r->right;
        }
        n->parent = r2;
        if(x < r2->item)
            r2->left = n;
        else
            r2->right = n;
    }
}

template <class T>
bstnode<T>* bst<T>::min(bstnode<T>* r){
    bstnode<T> *r2;
	while(r!=NULL){
        r2 = r;
        r = r->left;
    }
    return r2;
}

template <class T>
int bst<T>::remove(T x){
	bstnode<T> *r = root;
	int count = 0;
    while(r!=NULL){
		if(x == r->item){
			if(r->left == NULL && r->right == NULL){  //  leaf case.
				if(r == root)
					root = NULL;
				else if(r->parent->right == r)  // if right child.
					r->parent->right = NULL;
				else
					r->parent->left = NULL;
				r->parent = NULL;
				delete r;
			}
			else if(r->left==NULL || r->right==NULL){  // one child case
				if(r == root){
					if(r->right!=NULL)
						root = r->right;
					else
						root = r->left;
				}
				else if(r->parent->right == r){ // if right child
					r->parent->right = r->right;
					r->right->parent = r->parent;
				}
				else{
					r->parent->left = r->left;
					r->left->parent = r->parent;
				}
				r->left = r->right = r->parent = NULL;
				delete r;
			} 
			else if(r->left!=NULL && r->right!=NULL){  // two children case.
                bstnode<T> *rm;  //  rm is the successor.
                if(r->right->left!=NULL) rm = min(r->right);
                else rm = r->right;  // if walay left ang right child ni r after all.
				T minVal = rm->item;
				remove(rm->item);
				r->item = minVal;
			}
			return count+1;
		}
		else if(x < r->item)
		   r = r->left;
		else if(x > r->item)
	       r = r->right;
        count++;
    }
	return (-1)*count;
}

int main(){
	int n,m,x,r,y;
	cin >> n;
	for(int i = 0; i < n; i++){
		bst<int> t;
		cin >> m;
		for(int j = 0; j < m; j++) {
			cin >> x;
			t.insert(x);
		}
		cin >> r;
		if((y = t.remove(r))>=0)
            cout << y << " DELETED" <<endl;
        else
            cout << abs(y) << " !FOUND" << endl;
	}
}