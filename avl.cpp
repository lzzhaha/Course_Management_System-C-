/*
 * avl.cpp
 */

#ifndef AVL_CPP
#define AVL_CPP

/*Notice:
 * Since	the	left	and	right	subtrees	are	of	the	type	BT*,	you	need	to
cast	it	to	BST*	or	AVL*,	otherwise	you	can’t	access	them	in	your
member	functions*/

/* TODO
 * Goal: To find the balance factor of an AVL tree
 *       balance factor = height of right sub-tree - height of left sub-tree
 * Return: (int) balance factor
 */
template <typename T, typename K>
int AVL<T,K>::bfactor() const
{
   AVL<T,K>* right_sub = dynamic_cast<AVL<T,K>*>(this->right_subtree());
   int rheight = right_sub->height();
   AVL<T,K>* left_sub = dynamic_cast<AVL<T,K>*>(left_subtree());
   int lheight = left_sub->height();

   return rheight-lheight;
}


/* TODO
 * Goal: To rectify the height values of each node of of an AVL tree 
 */
template <typename T, typename K>
void AVL<T,K>::fix_height() const
{
	int rheight = 0;
	int lheight = 0;

	//Find the height of right subtree

	AVL<T,K>* right_sub = dynamic_cast<AVL<T,K>>(this->right_subtree());

	if(right_sub == NULL){
		rheight = 0;
	}else{
		right_sub->fix_height();
		rheight = right_sub->height();
	}

	//Find the height of left subtree
	AVL<T,K>* left_sub = dynamic_cast<AVL<T,K>*>(this->left_subtree());

	if(left_sub == NULL){
		lheight = 0;
	}else {
		left_sub->fix_height();
		lheight = left_sub->height();
	}

	this->height = lheight>rheight? lheight+1:rheight+1;
}


/* TODO
 * Goal: To perform a single left (anti-clocwise) rotation of the root 
 */
template <typename T, typename K>
void AVL<T,K>::rotate_left() 
{
    bt_node* origin = this->root;

    AVL<T,K>* right_sub = dynamic_cast<AVL<T,K>*>(this->right_subtree());

    this->root = right_sub->root;

    AVL<T,K>* left_sub = dynamic_cast<AVL<T,K>*>(this->left_subtree());

    origin->right->root = left_sub->root;

    left_sub->root = origin;
}


/* TODO
 * Goal: To perform right (clockwise) rotation of the root 
 */
template <typename T, typename K>
void AVL<T,K>::rotate_right()
{
     bt_node* origin = this->root;

     AVL<T,K>* left_sub = dynamic_cast<AVL<T,K>*>(this->left_subtree());

     this->root = left_sub->root;

     AVL<T,K>* right_sub = dynamic_cast<AVL<T,K>*>(this->right_subtree());

     origin->left->root = right_sub->root;

     right_sub->root = origin;
}

/* TODO
 * Goal: To balance an AVL tree 
 */
template <typename T, typename K>
void AVL<T,K>::balance()
{
	AVL<T,K>* left_sub = dynamic_cast<AVL<T,K>*>(this->left_subtree());

	if(left_sub !=NULL && left_sub->root != NULL){
		left_sub->balance();
	}

	AVL<T,K>* right_sub = dynamic_cast<AVL<T,K>*>(this->right_subtree());

	if(right_sub !=NULL && right_sub->root != NULL){
		right_sub->balance();
	}
    //Check whether the current node is balanced or not
	if(bfactor() == -2 ){
		//left subtree has one extra node
		if(left_sub->bfactor() < 0){
			//extra node on the left subtree of left subtree
			rotate_right();
		}else{
			//extra node on the right subtree of left subtree
			left_sub->rotate_left();
			rotate_right();
		}
	}else if(bfactor() == 2){
		//right subtree has one extra node
		if(right_sub->bfactor()>0){
			//extra node on the right subtree of right subtree
			rotate_left();
		}else{
			right_sub->rotate_right();
			rotate_left();
		}
	}
}


/* TODO
 * Goal: To insert an item x with key k to AVL tree
 */
template <typename T, typename K>
void AVL<T,K>::insert(const T& x, const K& k)
{
    BST<T,K>::insert(x,k);
    balance();
}



/* TODO
 * Goal: To remove an item with key k in AVL tree 
 */
template <typename T, typename K>
void AVL<T,K>::remove(const K& k)
{
    BST<T,K>::remove(x,k);
    balance();
}



#endif /* AVL_CPP */
