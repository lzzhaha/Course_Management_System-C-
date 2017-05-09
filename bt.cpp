/*
 * bt.cpp
 *
 */

#ifndef BT_CPP
#define BT_CPP


/* TODO
 * Goal: Do preorder traversal on the tree
 * Remark: print both value and key fields of each node
 */
//Print the tree by pre-order traversal
template <typename T, typename K>
void BT<T,K>::preorder_traversal() const
{
    if(this->root == NULL){
    	return;
    }
	cout<<"Key: "<<root->key<<"\t"<<"Value: "<<root->value<<endl;;

	if(root->left != NULL && root->left->root!=NULL){
		root->left->preorder_traversal();
	}

	if(root->right != NULL && root->right->root!=NULL){
		root->right->preorder_traversal();
	}

}


#endif /* BT_CPP */
