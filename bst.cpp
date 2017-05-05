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
template <typename T, typename K>
BT<T,K>* BST<T,K>::search(const K& k)
{
    //write your codes here
	//Use dynamic cast to convert the abstract base class pointer to BST pointer
	if(this->root->key == k||root==NULL){
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
    //write your codes here
	if(this->root->key == k){
		return;
	}else if(this->root == NULL){
		this->root = new node(x,k);
	}else if(this->root->key < k){
		this->root->bt_height++;
		this->root->right->insert(k);
	}else{
		this->root->bt_height++;
		this->root->left->insert(k);
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
	}else if(root->key <k){
		this->root->bt_height--;
		this->root->right->remove(k);
	}

	//the target node is found, there are three cases

	//Two children: move root to point to the node with minimum node of right sub tree and adjust the relationship
	if(this->root->left && root->right){
		bt_node* del_node = this->root;
		BT<T,K>* newRoot = this->root->right->fing_min();
		this->root = newRoot->root;

		newRoot->root = newRoot->root->right;
		this->root->left = del_node->left;
		this->root->right = del_node->right;

		del_node->left = del_node->right = NULL;
		delete del_node;
	}else{
		//One child or no child
		//set the pointer points to its child (if any) then delete it directly
		bt_node* del_node = root;
		this->root = (node->left == NULL)? node->right:node->left;
		del_node->left = del->right = NULL;
		delete del_node;
	}
}


/* TODO
 * Goal: Clear the node stack and set current pointer to the root 
 */
template<typename T, typename K>
void BST<T,K>::iterator_init()
{
	this->current = this->root;
	while(!istack.empty()){
		istack.pop();
	}
	//Use reverse-in-order_traversal to push the nodes into the stack, which constitutes a recursive stack as a whole
/*
	if(this->root == NULL){
		return;
	}

	if(this->root->right != NULL){
		BST<T,K> * right_sub = dynamic_cast<BST<T,K>*>(this->root->right);
		right_sub->iterator_init();
		istack.push(right_sub->root);
	}

	istack.push(this->root);
	if(left_sub != NULL){
		BST<T,K>* left_sub = dynamic_cast<BST<T,K>*>(this->root->left);
		left_sub->iterator_init();
		istack.push(left_sub->root);
	}
*/
}


/* TODO
 * Goal: Check whether the next smallest node exists 
 */
template<typename T, typename K>
bool BST<T,K>::iterator_end()
{
    return current!=NULL;
}


/* TODO
 * Goal: Return the value of next smallest node from the tree 
 */
template<typename T, typename K>
T& BST<T,K>::iterator_next()
{
	T* t = new T;
	return *t;

}


#endif /* BST_CPP */
