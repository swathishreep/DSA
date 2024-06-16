 #include<stdio.h>
 #include<stdlib.h>
 //Nodestructure
 typedefstructNode{
 intkey;
 structNode*left;
 structNode*right;
 intheight;
 }Node;
 //Functiontogettheheightofthetree
 intheight(Node*N) {
 if(N==NULL)
 return0;
 returnN->height;
 }
 //Functiontogetmaximumoftwointegers
 intmax(inta, intb) {
 return(a>b)?a:b;
 }
 //Functiontocreateanewnode
 Node*newNode(intkey) {
 Node*node=(Node*)malloc(sizeof(Node));
 node->key=key;
 node->left=NULL;
 node->right=NULL;
 node->height=1; //newnodeisinitiallyaddedat leaf
 return(node);
 }
 //Rightrotatesubtreerootedwithy
 Node*rightRotate(Node*y) {
 Node*x=y->left;
 Node*T2=x->right;
 //Performrotation
 x->right=y;
 y->left=T2;
 //Updateheights
 y->height=max(height(y->left),height(y->right))+1;
 x->height=max(height(x->left),height(x->right))+1;
 //Returnnewroot
 returnx;
 }
 //Leftrotatesubtreerootedwithx
 Node*leftRotate(Node*x) {
 Node*y=x->right;
 Node*T2=y->left;
 //Performrotation
 y->left=x;
 x->right=T2;
 //Updateheights
 x->height=max(height(x->left),height(x->right))+1;
 y->height=max(height(y->left),height(y->right))+1;
 //Returnnewroot
 returny;
 }
 //GetbalancefactorofnodeN
 intgetBalance(Node*N) {
 if(N==NULL)
 return0;
 returnheight(N->left)-height(N->right);
 }
 //Insertanode
 Node*insert(Node*node, intkey) {
 if(node==NULL)
 return(newNode(key));
 if(key<node->key)
 node->left=insert(node->left,key);
 elseif(key>node->key)
 node->right=insert(node->right,key);
 else//EqualkeysarenotallowedinBST
 returnnode;
 //Updateheightofthisancestornode
 node->height=1+max(height(node->left),height(node->right));
 //Getthebalancefactorofthisancestornode
 intbalance=getBalance(node);
 //Ifthisnodebecomesunbalanced, then
 //thereare4cases
 //LeftLeftCase
 if(balance>1&&key<node->left->key)
 returnrightRotate(node);

 // Right Right Case
 if (balance <-1 && key > node->right->key)
 return leftRotate(node);
 // Left Right Case
 if (balance > 1 && key > node->left->key) {
 node->left = leftRotate(node->left);
 return rightRotate(node);
 }
 // Right Left Case
 if (balance <-1 && key < node->right->key) {
 node->right = rightRotate(node->right);
 return leftRotate(node);
 }
 // return the (unchanged) node pointer
 return node;
 }
 // Function to find the node with the minimum key value
 Node *minValueNode(Node* node) {
 Node* current = node;
 // loop down to find the leftmost leaf
 while (current->left != NULL)
 current = current->left;
 return current;
 }
 // Delete a node
 Node* deleteNode(Node* root, int key) {
 // STEP 1: PERFORM STANDARD BST DELETE
 if (root == NULL)
 return root;
 // If the key to be deleted is smaler than the root's key,
 // then it lies in left subtree
 if (key < root->key)
 root->left = deleteNode(root->left, key);
 // If the key to be deleted is greater than the root's key,
 // then it lies in right subtree
 else if (key > root->key)
 root->right = deleteNode(root->right, key);
 // if key is same as root's key, then This is the node
 // to be deleted
 else {
 //nodewithonlyonechildornochild
 if((root->left==NULL) || (root->right==NULL)) {
 Node*temp=root->left?root->left :root->right;
 //Nochildcase
 if(temp==NULL) {
 temp=root;
 root=NULL;
 }else//Onechildcase
 *root=*temp; //Copythecontentsof
 //thenon-emptychild
 free(temp);
 }else{
 //nodewithtwochildren:Gettheinorder
 //successor(smallestintherightsubtree)
 Node*temp=minValueNode(root->right);
 //Copytheinordersuccessor'sdatatothisnode
 root->key=temp->key;
 //Deletetheinordersuccessor
 root->right=deleteNode(root->right, temp->key);
 }
 }
 //Ifthetreehadonlyonenodethenreturn
 if(root==NULL)
 returnroot;
 //STEP2:UPDATEHEIGHTOFTHECURRENTNODE
 root->height=1+max(height(root->left),height(root->right));
 //STEP3:GETTHEBALANCEFACTOROFTHISNODE(tocheckwhether
 //thisnodebecameunbalanced)
 intbalance=getBalance(root);
 //Ifthisnodebecomesunbalanced, thenthereare4cases
 //LeftLeftCase
 if(balance>1&&getBalance(root->left)>=0)
 returnrightRotate(root);
 //LeftRightCase
 if(balance>1&&getBalance(root->left)<0) {
 root->left=leftRotate(root->left);
 returnrightRotate(root);
 }
 //RightRightCase
 if(balance<-1&&getBalance(root->right)<=0)
 returnleftRotate(root);
 // Right Left Case
 if (balance <-1 && getBalance(root->right) > 0) {
 root->right = rightRotate(root->right);
 return leftRotate(root);
 }
 return root;
 }
 // Utility function to print the tree in order
 void inOrder(Node *root) {
 if (root != NULL) {
 inOrder(root->left);
 printf("%d ", root->key);
 inOrder(root->right);
 }
 }
 int main() {
 Node *root = NULL;
 // Insert nodes
 root = insert(root, 10);
 root = insert(root, 20);
 root = insert(root, 30);
 root = insert(root, 40);
 root = insert(root, 50);
 root = insert(root, 25);
 // Print the tree
 printf("Inorder traversal of the constructed AVL tree is \n");
 inOrder(root);
 // Delete node
 root = deleteNode(root, 40);
 // Print the tree
 printf("\nInorder traversal after deletion of 40 \n");
 inOrder(root);
 return 0;
 }
