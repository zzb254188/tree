#include <iostream>
#include <vector>

struct Node{
       int number;
       Node *left, *right, *father;

       Node(int n){
       	number = n;
       	left = right = nullptr;
       }
       Node(){
       	left = right = nullptr;
			 }
       
};

class Tree {
public:

			Tree(){
				this->root = nullptr;
				this->tmp = nullptr;
			}
			~Tree(){
				destory();	
			}
			void destory(){
				destory(this->root);
			}
			void destory(Node* root){
				if(root == nullptr)
					return;
				destory(root->left);
				destory(root->right);
				std::cout << "destory "<< root->number <<std::endl;
				delete(root);
			}
			void insert(int n){
//				std::cout << n << " " << (this->root==nullptr)<<" " <<std::endl;
				if(this->root == nullptr){
					this->root = new Node(n);
					return;
				}
				tmp = new Node(n);
			  Node* ind = root;
				while(((tmp->number < ind->number) && ind->left != nullptr) || ((tmp->number >= ind->number) && ind->right != nullptr))		
				{
				  ind = tmp->number < ind->number ? ind->left : ind->right;	
				}
				if(tmp->number < ind->number) ind->left = tmp;
				else ind->right = tmp;				
			}
			void delete_(int n) {
				bool res = delete_(&(this->root), n);
				if(!res)
					std::cout << "deleted error" <<std::endl;
			}
			bool delete_(Node** root, int n) {
				Node*	node = *root;
				if(node==nullptr)
					return false;
				if(node->number == n)
				{
					if (node->left == nullptr ^ node->right == nullptr){
						auto depleted = node;
						*root = node->left == nullptr ? node->right : node->left;
						delete(depleted);
						return true;
					}
					if (node->left == nullptr && node->right == nullptr){
						auto depleted = node;
						*root = nullptr;
						delete(depleted);
						return true;
					}
					
					if (node->left != nullptr && node->right != nullptr){
						auto res = node->right;
						while(res->left != nullptr)
						{
							res = res->left;
						}
						node->number = res->number;
						return delete_(&(node->right), node->number);
					}
				}
				return delete_(&(node->left), n) || delete_(&(node->right), n);
			}

			void print() {
				print(this->root, 0);
			}
			void print(Node* root, int n) {
				if(root == nullptr)
					return;
			  for(int i = 0; i < n; i++)
							std::cout << "--"; 	
				std::cout << root->number << std::endl;
				print(root->left, n+1);
				print(root->right, n+1);
			}
			void preorder(){preorder(this->root);}
			void preorder(Node* root) {
				if(root == nullptr)
					return;
				std::cout << "preorder " << root->number << std::endl;
				preorder(root->left);
				preorder(root->right);
			}
			void inorder(){inorder(this->root);}
			void inorder(Node* root) {
				if(root == nullptr)
					return;
				inorder(root->left);
				std::cout << "inorder " << root->number << std::endl;
				inorder(root->right);
			}
			void postorder(){postorder(this->root);}
			void postorder(Node* root) {
				if(root == nullptr)
					return;
				postorder(root->left);
				postorder(root->right);
				std::cout << "postorder " << root->number << std::endl;
			}
private:
			Node* root;
			Node* tmp;
};

int main(int argc, char *argv[]){
	Tree t = Tree();
	std::vector<int> input = {3,2,5,7,6,8,1,4};
	for(auto x : input)
		t.insert(x);
	t.preorder();
	t.inorder();
	t.postorder();
	t.print();
	t.delete_(8);
	t.print();
	t.delete_(3);
	t.print();
	t.delete_(7);
	t.print();
	t.delete_(100);
	t.print();


	return 0;
}
