/*
 * bst.cpp
 *
 */

#ifndef BST_CPP
#define BST_CPP


/* TODO
 * Goal: To search for an item x with key k from the BST tree
 * Return: A pointer to the subtree whose root node contains the item if found,
 *         otherwise a NULL pointer.
 */
using namespace std;
template <typename T, typename K>
BT<T,K>* BST<T,K>::search(const K& k)
{
    //write your codes here
	//Use dynamic cast to convert the abstract base class pointer to BST pointer
	if(this->root->key == k||this->root==NULL){
		return this;
	}else if(this->root->key < k){

		BST<T,K> *right_sub = dynamic_cast<BST<T,K>*>(this->root->right);
		return right_sub->search(k);
	}else{

		BST<T,K> *left_sub = dynamic_cast<BST<T,K>*>(this->root->left);
		return left_sub->search(k);
	}
}


/* TODO
 * Goal: To find the minimum node stored in a BST tree.
 * Return: A pointer to the subtree whose root node contains the minimum key
 */
template <typename T, typename K>
BT<T,K>* BST<T,K>::find_min()
{
    //write your codes here
	if(this->root == NULL || this->root->left == NULL){
		return this;
	}else{
		BST<T,K>* left_sub = dynamic_cast<BST<T,K>*>(this->root->left);
		return left_sub->find_min();
	}
}


/* TODO
 * Goal: To insert an item x with key k to a BST tree 
 */
template <typename T, typename K>
void BST<T,K>::insert(const T& x, const K& k)
{

	if(  this->root == NULL){

		cout<< "The inserted key : "<< k<<" is inserted"<<endl;

		this->root = new bt_node(x,k);

	}else if(this->root->key == k){
		//cout<< "The inserted key : "<< k<<" exists and equals to"<<this->root->key<<endl;
		return;
	}else if(this->root->key < k){
		//cout<< "The inserted key : "<< k<<" is bigger than "<<this->root->key<<endl;


		if(this->root->right== NULL){
			//create a new subtree if the right subtree is empty
			this->root->right = new BST<T,K>;
		}

		BST<T,K>* right_sub = dynamic_cast<BST<T,K>*>(this->root->right);

		//cout<<"insert "<<k<<" to the right subtree"<<endl;
		right_sub->insert(x,k);

	}else{


		//cout<< "The inserted key : "<< k<<" is smaller than "<<this->root->key<<endl;

		if(this->root->left == NULL){
					//create a new subtree if the right subtree is empty
					this->root->left = new BST<T,K>;
		}

		BST<T,K>* left_sub = dynamic_cast<BST<T,K>*>(this->root->left);

		//cout<<"insert "<<k<<" into left subtree"<<endl;
		left_sub->insert(x,k);
	}
}


/* TODO
 * Goal: To remove an item with key k in a BST tree 
 */
template <typename T, typename K>
void BST<T,K>::remove(const K& k)
{    
	//if the node is null, which means no such nodes exists, then do nothing
	if(this->root == NULL){
		return;
	}

	//the k does not equals to the key of node
	if(this->root->key > k){
		this->root->bt_height--;
		this->root->left->remove(k);
	}else if(this->root->key <k){
		this->root->bt_height--;
		this->root->right->remove(k);
	}

	//the target node is found, there are three cases

	//Two children: move root to point to the node with minimum node of right sub tree and adjust the relationship
	if(this->root->left && this->root->right){
		bt_node* del_node = this->root;
		BST<T,K>* newRoot = dynamic_cast<BST<T,K>*>(this->root->right->find_min());
		this->root = newRoot->root;

		BST<T,K>* new_right_sub = dynamic_cast<BST<T,K>*>(newRoot->root->right);

		newRoot->root = new_right_sub->root;
		this->root->left = del_node->left;
		this->root->right = del_node->right;

		del_node->left = del_node->right = NULL;
		delete del_node;
	}else{
		//One child or no child
		//set the pointer points to its child (if any) then delete it directly
		bt_node* del_node = this->root;

		BST<T,K>* right_sub = dynamic_cast<BST<T,K>*>(del_node->right);
		BST<T,K>* left_sub = dynamic_cast<BST<T,K>*>(del_node->left);

		this->root = (right_sub == NULL)? left_sub->root:right_sub->root;
		del_node->left = del_node->right = NULL;
		delete del_node;
	}
}


/* TODO
 * Goal: Clear the node stack and set current pointer to the root 
 */
template<typename T, typename K>
void BST<T,K>::iterator_init()
{
	//Do nothing if the root is NULL
	if(this->root == NULL){
		return;
	}

	this->current = this->root;

	while(!this->istack.empty()){
		this->istack.pop();
	}

}


/* TODO
 * Goal: Check whether the next smallest node exists 
 */
template<typename T, typename K>
bool BST<T,K>::iterator_end()
{
    return this->istack.empty();
}


/* TODO
 * Goal: Return the value of next smallest node from the tree 
 */
template<typename T, typename K>
T& BST<T,K>::iterator_next()
{
	bt_node*& cur = this->current;
	//the first time that this function is called

	if(this->istack.empty()){
		do{
			this->istack.push(cur);

			BST<T,K>* left_sub = dynamic_cast<BST<T,K>*>(cur->left);

			cur = dynamic_cast<BST<T,K>*>(left_sub->left_subtree())->root;

		}while(cur != NULL );
		cur = this->istack.top();
	}

	//store the return value
	T& re_val = cur->value;

	//pop the return value
	this->istack.pop();

	/*Find the second smallest element : which should be located at the left_most node of the cur node's right subtree,
	 * given that the right sub_tree's node is not null; if null, then move to its parent node, which is the top of the stack
	 * */

	BST<T,K>* right_sub = dynamic_cast<BST<T,K>*>(cur->right);

	if( (right_sub !=NULL) && (right_sub->root != NULL) ){
		cur = right_sub->root;
		this->istack.push(cur);

		BST<T,K>* left_sub = dynamic_cast<BST<T,K>*>(cur->left);

		//store the left chain into the stack.
		while( (left_sub != NULL) && (left_sub->root != NULL) ){

			cur = left_sub->root;

			this->istack.push(cur);
		}

		//Now the top of the stack should be the smallest node of the right subtree of the returned node
	}

	// if the stack is empty at this point, it means that all the node has been returned
	if(!this->istack.empty()){
		//if the returned node has an empty right_subtree, then cur node should move to its parent node.
		cur = this->istack.top();
	}

	return re_val;
}


#endif /* BST_CPP */
