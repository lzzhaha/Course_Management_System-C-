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
   const AVL<T,K>* right_sub = dynamic_cast<const AVL<T,K>*>(this->right_subtree());
   int rheight = 0;
   if(right_sub != NULL && right_sub->root  != NULL){
	   rheight = right_sub->height();
   }

   const AVL<T,K>* left_sub = dynamic_cast<const AVL<T,K>*>(this->left_subtree());
   int lheight =0;
   if(left_sub != NULL && left_sub->root  != NULL){
  	   lheight = left_sub->height();
     }

   return rheight-lheight;
}


/* TODO
 * Goal: To rectify the height values of each node of of an AVL tree 
 */
template <typename T, typename K>
void AVL<T,K>::fix_height() const
{
	//if the node is null then do nothing
	if(this->root == NULL){
		return;
	}

	int rheight = 0;
	int lheight = 0;

	//Find the height of right subtree
	const AVL<T,K>* right_sub = dynamic_cast<const AVL<T,K>*>(this->right_subtree());

	if(right_sub == NULL){
		cout<<this->root->key<<" has an empty right_subtree"<<endl;
		rheight = -1;
	}else{
		right_sub->fix_height();
		rheight = right_sub->height();
		cout<<this->root->key<<" has rheight "<<rheight<<endl;
	}

	//Find the height of left subtree
	const AVL<T,K>* left_sub = dynamic_cast<const AVL<T,K>*>(this->left_subtree());

	if(left_sub == NULL){
		cout<<this->root->key<<" has an empty leftt_subtree"<<endl;
		lheight = -1;
	}else {
		left_sub->fix_height();
		lheight = left_sub->height();
		cout<<this->root->key<<" has lheight "<<lheight<<endl;
	}

	this->root->bt_height = (lheight>rheight)? lheight+1:rheight+1;
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

    dynamic_cast<AVL<T,K>*>(origin->right)->root = left_sub->root;

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

     dynamic_cast<AVL<T,K>*>(origin->left)->root = right_sub->root;

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
	cout<<this->root->key<<"'s bfactor = "<<bfactor()<<endl;
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
			this->root->right = new AVL<T,K>;
		}

		AVL<T,K>* right_sub = dynamic_cast<AVL<T,K>*>(this->root->right);

		//cout<<"insert "<<k<<" to the right subtree"<<endl;
		right_sub->insert(x,k);

	}else{


		//cout<< "The inserted key : "<< k<<" is smaller than "<<this->root->key<<endl;

		if(this->root->left == NULL){
					//create a new subtree if the right subtree is empty
					this->root->left = new AVL<T,K>;
		}

		AVL<T,K>* left_sub = dynamic_cast<AVL<T,K>*>(this->root->left);

		//cout<<"insert "<<k<<" into left subtree"<<endl;
		left_sub->insert(x,k);
	}

    fix_height();
    balance();

}



/* TODO
 * Goal: To remove an item with key k in AVL tree 
 */
template <typename T, typename K>
void AVL<T,K>::remove(const K& k)
{
    BST<T,K>::remove(k);
    balance();
}



#endif /* AVL_CPP */
