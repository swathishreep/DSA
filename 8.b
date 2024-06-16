 #include <stdio.h>
 #include <stdlib.h>
 // Define the structure of a tree node
 struct Node {
 int data;
 struct Node* left;
 struct Node* right;
 };
 // Function to create a new node
 struct Node* createNode(int data) {
 struct Node* newNode = (struct Node*)maloc(sizeof(struct Node));
 newNode->data = data;
 newNode->left = NULL;
 newNode->right = NULL;
 return newNode;
 }
 // Function to insert a node in the BST
 struct Node* insertNode(struct Node* root, int data) {
 if (root == NULL) return createNode(data);
 if (data < root->data)
 root->left = insertNode(root->left, data);
 else if (data > root->data)
 root->right = insertNode(root->right, data);
 return root;
 }
 // Function to find the minimum value node in the BST
 struct Node* findMin(struct Node* root) {
 while (root->left != NULL) root = root->left;
 return root;
 }
 // Function to delete a node from the BST
 struct Node* deleteNode(struct Node* root, int data) {
 if (root == NULL) return root;
 if (data < root->data)
 root->left = deleteNode(root->left, data);
 else if (data > root->data)
 root->right = deleteNode(root->right, data);
 else {
 if (root->left == NULL) {
 struct Node* temp = root->right;
 free(root);
 return temp;
 } else if (root->right == NULL) {
 struct Node* temp = root->left;
 free(root);
 return temp;
 }
 struct Node* temp = findMin(root->right);
 root->data = temp->data;
 root->right = deleteNode(root->right, temp->data);
 }
 return root;
 }
 // Function to search for a node in the BST
 struct Node* searchNode(struct Node* root, int data) {
 if (root == NULL | root->data == data)
 return root;
 if (data < root->data)
 return searchNode(root->left, data);
 else
 return searchNode(root->right, data);
 }
 // Function for Inorder Traversal
 void inorderTraversal(struct Node* root) {
 if (root == NULL) return;
 inorderTraversal(root->left);
 printf("%d ", root->data);
 inorderTraversal(root->right);
 }
 // Main function to demonstrate the BST operations
 int main() {
 struct Node* root = NULL;
 int choice, data;
 while (1) {
 printf("\nBinary Search Tree Operations:\n");
 printf("1. Insert\n2. Delete\n3. Search\n4. Display (Inorder Traversal)\n5. Exit\n");
 printf("Enter your choice: ");
 scanf("%d", &choice);
 switch(choice) {
 case1:
 printf("Enterthevaluetoinsert: ");
 scanf("%d",&data);
 root=insertNode(root,data);
 break;
 case2:
 printf("Enterthevaluetodelete: ");
 scanf("%d",&data);
 root=deleteNode(root,data);
 break;
 case3:
 printf("Enterthevaluetosearch: ");
 scanf("%d",&data);
 structNode*result=searchNode(root,data);
 if(result !=NULL)
 printf("Value%dfoundinthetree.\n",data);
 else
 printf("Value%dnotfoundinthetree.\n",data);
 break;
 case4:
 printf("InorderTraversal: ");
 inorderTraversal(root);
 printf("\n");
 break;
 case5:
 exit(0);
 default:
 printf("Invalidchoice!Pleasetryagain.\n");
 }
 }
 return0;
 
