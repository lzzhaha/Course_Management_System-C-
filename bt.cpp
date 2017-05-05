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
    //write your codes here
	cout<<"Key: "<<root->key<<"\t"<<"Value: "<<root->value<<endl;;

	if(root->left != NULL){
		root->left->preorder_traversal();
	}
	if(root->right != NULL){
		root->right->pre_oreder_traversal();
	}

}


#endif /* BT_CPP */
