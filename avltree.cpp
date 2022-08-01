#include <iostream>
#include <vector>

struct Node{
       int number;
       Node *left, *right, *father;

       Node(int n){
       	number = n;
       	left = right = father = nullptr;
       }
       Node(){
       	left = right = father = nullptr;
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
			int height() {
				return height(this->root);
			}
			int height(Node* node) {
				if(node==nullptr)
								return 0;
				return std::max(height(node->left), height(node->right)) + 1;
			}
			bool check(){
			  return std::abs(height(this->root->left) - height(this->root->right)) > 1;
			}
			void insert(int n){
//				std::cout << n << " " << (this->root==nullptr)<<" " <<std::endl;
				if(this->root == nullptr){
					this->root = new Node(n);
					return;
				}
				tmp = new Node(n);
			  	Node* ind = root;
				int ind_lr = 0;
				while(((tmp->number < ind->number) && ind->left != nullptr) || ((tmp->number >= ind->number) && ind->right != nullptr))		
				{
				  ind_lr = tmp->number < ind->number ? 0 : 1; 
				  ind = tmp->number < ind->number ? ind->left : ind->right;	
				}
				if(tmp->number < ind->number) ind->left = tmp;
				else ind->right = tmp;				
				tmp->father = ind;
				int insert_lr = tmp->number < ind->number ? 0 : 1;
				if(check()){
					if(ind_lr == 0 && insert_lr == 0)
						ll(ind->father->father);
					if(ind_lr == 1 && insert_lr == 1)
						rr(ind->father->father);
				}
			}
			void ll(Node* node){
				std::cout <<"ll"<<std::endl;
				Node* father = nullptr;
				if(node->father != nullptr)
					father = node->father;
				
				Node* up_node = node->left;
				Node* swap_node = up_node->right;
				std::cout <<"up "<<up_node->number<<std::endl;
				if(father == nullptr)
					this->root = up_node;
				else
					father->left = up_node;
				up_node->right = node;
				node->father = up_node;
				node->left = swap_node;
				if(swap_node != nullptr)
					swap_node->father = node;
			}

			void rr(Node* node){
				std::cout <<"rr"<<std::endl;
				Node* father = nullptr;
				if(node->father != nullptr)
					father = node->father;
				
				Node* up_node = node->right;
				Node* swap_node = up_node->left;
				std::cout <<"up "<<up_node->number<<std::endl;
				if(father == nullptr)
					this->root = up_node;
				else
					father->right = up_node;
				up_node->left = node;
				node->father = up_node;
				node->right = swap_node;
				if(swap_node != nullptr)
					swap_node->father = node;
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
	std::vector<int> input = {3,2,5,7,4,8,6,9,10};
	for(auto x : input)
	{
		t.insert(x);
		t.print();
	}
	t.preorder();
	t.inorder();
	t.postorder();
	t.print();
	std::cout<<"height : "<<t.height()<<std::endl;
	t.delete_(8);
	t.print();
	std::cout<<"height : "<<t.height()<<std::endl;
	t.delete_(3);
	t.print();
	std::cout<<"height : "<<t.height()<<std::endl;
	t.delete_(7);
	t.print();
	std::cout<<"height : "<<t.height()<<std::endl;
	t.delete_(100);
	t.print();

	std::cout<<"height : "<<t.height()<<std::endl;

	return 0;
}
