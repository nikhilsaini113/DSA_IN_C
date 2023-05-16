#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct student{
	int rollno;
	char name[50];
};
struct treenode
{
	struct student st;
	struct treenode *left;
    	struct treenode *right;
	int ht;
};
// Create new treenode to insert in AVL Tree
struct treenode *create_treenode(struct student st)
{
    struct treenode *temp;
        temp=(struct treenode*)malloc(sizeof(struct treenode));
		temp->st.rollno  = st.rollno;
		strcpy(temp->st.name, st.name);
		temp->left = NULL;
		temp->right= NULL;
        temp->ht = 0;
    return temp;
}  
int height(struct treenode *root)
{
	int lh,rh;
	if(root == NULL)
		return 0;
	
	if(root->left  == NULL)
		lh = 0;
	else
		lh = 1+root->left->ht;
		
	if(root->right == NULL)
		rh = 0;
	else
		rh = 1+root->right->ht;
	
	if(lh > rh)
		return lh;
	else
	    return rh;
}
 
 int balance_factor(struct treenode *root)
{
	int lh,rh;
	if(root == NULL)
		return 0;
 
	if(root->left == NULL)
		lh = 0;
	else
		lh = 1+root->left->ht;
 
	if(root->right == NULL)
		rh = 0;
	else
		rh = 1+root->right->ht;
 
	return lh - rh;
}
struct treenode * rotateright(struct treenode *x)
{
	struct treenode *temp;
	temp = x->left;
	x->left = temp->right;
	temp->right = x;
	x->ht = height(x);
	temp->ht = height(temp);
	return temp;
}
 
struct treenode * rotateleft(struct treenode *x)
{
	struct treenode *temp;
	temp = x->right;
	x->right = temp->left;
	temp->left = x;
	x->ht = height(x);
	temp->ht = height(temp);
	
	return temp;
}
 
 // Single rotation due to left-to-left case
struct treenode * LL(struct treenode *root)
{
	root = rotateright(root);
	
    return root;
}

// Double  rotation due to left-to-right case 
struct treenode * LR(struct treenode *root)
{
	root->left = rotateleft(root->left);
	root = rotateright(root);
	
	return root;
}

// Single rotation due to right-to-right case
struct treenode * RR(struct treenode *root)
{
	root = rotateleft(root);
	return root;
} 

// double rotation due to right-to-left case
struct treenode * RL(struct treenode *root)
{
	root->right = rotateright(root->right);
	root = rotateleft(root);
	return root;
}
 
// To find the inorder successor of node X
struct treenode * inorder_successor(struct treenode * x)
{
	struct treenode *y;
	if(x == NULL)
	   return NULL;
	
	if(x->right==NULL)
	    return x;
	y= x->right;   // inorder successor is leftmost son of right subtree of x
	while(y->left != NULL)
	   y = y->left;
	 
	return y;   
	   
}
 // Insertion in an AVL Tree
struct treenode * insert(struct treenode *root,struct student st)
{
	if(root == NULL)
	{
		root = create_treenode(st);
	}
	else
		if(st.rollno < root->st.rollno)     // insert in left subtree
			{
				root->left = insert(root->left,st);  //newnode will be inserted in left
				
                // possibility is that tree get heavier in left side
                if(balance_factor(root) == 2)
					if(st.rollno < root->left->st.rollno) // if case is left to left
						root = LL(root);
					else
						root = LR(root);
			}
        else        
         if(st.rollno > root->st.rollno)		// insert in right subtree
		  {
			root->right = insert(root->right,st); // newnode will be inserted in right
			
			if(balance_factor(root)== -2)
				if(st.rollno  > root->right->st.rollno)
					root = RR(root);
				else
					root = RL(root);
		  }
	
     root->ht = height(root); // after insertion calculate the height of root
		
		return root;
}
// Deletion in AVL Tree
struct treenode * Delete(struct treenode *root,int x)
{
  struct treenode *insucc;
	
	if(root == NULL)
	{
		return NULL;
	}
	else
		if(x < root->st.rollno)
		{
			root->left = Delete(root->left,x);  // node to be deleted is in left
				
				if(balance_factor(root) == -2)	//  Need to Rebalance in right side 
					if(balance_factor(root->right) <= 0)
						root = RR(root);
					else
						root = RL(root);
			}
        else
         if(x > root->st.rollno)		// Node to be deleted is in right 
		  {
			root->right = Delete(root->right,x);
			
			if(balance_factor(root)  == 2)   // Need to rebalance in left side
				if(balance_factor(root->left) >= 0)
					root = LL(root);
				else
					root = LR(root);
		  } 
	     else
          {		//key to be deleted is found
		    
            if(root->right != NULL)  // that means the node to be deleted has two children 
				{	
                    // find its inorder succesor
					insucc = inorder_successor(root);
				
                	root->st.rollno = insucc->st.rollno;     // exchange key of inorder successor
					root->right = Delete(root->right,insucc->st.rollno);
					
					if(balance_factor(root) == 2)// Need to rebalance in left side
						if(balance_factor(root->left) >= 0)  // to check for left to left case
							root = LL(root);
						else
							root = LR(root);
				}
				else  // when the root has only left child 
					return root->left;   // root->Left  become new root
			}
	root->ht = height(root);
	return root;  // return the modified root after deletion
}
struct treenode *search(struct treenode *root,int x)
{
	if(root==NULL)
		return NULL;
	if(x==root->st.rollno)
		return root;
	else if(x<root->st.rollno){
		return search(root->left,x);
	}
	else{
		return search(root->right,x);
	}
}
// Inorder traversal of AVL Tree 
void inorder(struct treenode *root)
{
	if(root != NULL)
	{
		inorder(root->left);
		printf("%d %s (BF=%d)",root->st.rollno,root->st.name,balance_factor(root));
		inorder(root->right);
	}
}

// Preorder traversal of AVL Tree 
void preorder(struct treenode *root)
{
	if(root != NULL)
	{
		printf("%d %s (BF=%d)",root->st.rollno,root->st.name,balance_factor(root));
		preorder(root->left);
		preorder(root->right);
	}
}
void main(){
	FILE *fs;
	struct treenode *root=NULL;
	struct student st;
	fs=fopen("stud.txt","r");
	if(fs==NULL){
		printf("FILE DOES NOT EXIST!\n");
		exit(0);
	}
	while(!feof(fs)){
		fscanf(fs,"%d%s",&st.rollno,st.name);
		root = insert(root,st);
		//printf("%d",st.rollno);
		//head=create_node(st,head);
		
	}
	while(1){
	int choice;
		printf("\n AVL TREE MENU");
		printf("\n1. Delete:");
		printf("\n2. Print:");
		printf("\n3. Quit:");
		printf("\n4. Search:");
		printf("\n\nEnter Your Choice[1-5]:");
		scanf("%d",&choice);
		if(choice==3){
			break;
		}
		if(choice==2){
			printf("The inorder print of AVL Tree is:\n");
			inorder(root);
			printf("\n");
			printf("The preorder print of AVL Tree is:\n");
			preorder(root);
			printf("\n");
		}
		if(choice ==1){
			while(1){
				int x;
				printf("Enter Any +ve Element to delete & -ve to exit:\n");
				scanf("%d",&x);
				if(x>0){
				root = Delete(root,x);
			}
			else 
				break;
	}
		
		}
		if(choice ==4){
			struct treenode *q;
			int s;
			printf("Enter The Element You Want To Search\n");
			scanf("%d",&s);
			q=search(root,s);
			if(q){
				printf("Element Found\n");
			}
			else 
				printf("No such element exist\n");
		}
		}
}
