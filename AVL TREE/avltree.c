

#include<stdio.h>
#include<stdlib.h>
struct student{
	int rollno;
	char name[50];
}
struct treenode
{
	int key;
	struct treenode *left;
    	struct treenode*right;
	int ht;
};

// Create new treenode to insert in AVL Tree
struct treenode *create_treenode(int key)
{
    struct treenode *temp;
        temp=(struct treenode*)malloc(sizeof(struct treenode));
		temp->key  = key;
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
struct treenode * insert(struct treenode *root,int x)
{
	if(root == NULL)
	{
		root = create_treenode(x);
	}
	else
		if(x < root->key)     // insert in left subtree
			{
				root->left = insert(root->left,x);  //newnode will be inserted in left
				
                // possibility is that tree get heavier in left side
                if(balance_factor(root) == 2)
					if(x < root->left->key) // if case is left to left
						root = LL(root);
					else
						root = LR(root);
			}
        else        
         if(x > root->key)		// insert in right subtree
		  {
			root->right = insert(root->right,x); // newnode will be inserted in right
			
			if(balance_factor(root)== -2)
				if(x  > root->right->key)
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
		if(x < root->key)
		{
			root->left = Delete(root->left,x);  // node to be deleted is in left
				
				if(balance_factor(root) == -2)	//  Need to Rebalance in right side 
					if(balance_factor(root->right) <= 0)
						root = RR(root);
					else
						root = RL(root);
			}
        else
         if(x > root->key)		// Node to be deleted is in right 
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
				
                	root->key = insucc->key;     // exchange key of inorder successor
					root->right = Delete(root->right,insucc->key);
					
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
 
// Inorder traversal of AVL Tree 
void inorder(struct treenode *root)
{
	if(root != NULL)
	{
		inorder(root->left);
		printf("%d(BF=%d)",root->key,balance_factor(root));
		inorder(root->right);
	}
}

// Preorder traversal of AVL Tree 
void preorder(struct treenode *root)
{
	if(root != NULL)
	{
		printf("%d(BF=%d)",root->key,balance_factor(root));
		preorder(root->left);
		preorder(root->right);
	}
}
int get_choice()
 {
		int choice;
		printf("\n AVL TREE MENU");
        printf("\n1. Create:");
		printf("\n2. Insert:");
		printf("\n3. Delete:");
		printf("\n4. Print:");
		printf("\n5. Quit:");
		printf("\n\nEnter Your Choice[1-5]:");
		scanf("%d",&choice);
		
		return choice;
 }
	
void main()
{
  struct treenode *root = NULL;
	int x,n,i;
	int choice;
	
	while(1)
	{  
        choice = get_choice();	
		switch(choice)
		{
			case 1: printf("\nEnter no. of elements:");
					scanf("%d",&n);
					printf("\nEnter tree key:");
					root = NULL;
					for(i=0;i<n;i++)
					{
						scanf("%d",&x);
						root = insert(root,x);
					}
					break;
				
			case 2: printf("\nEnter a key:");
					scanf("%d",&x);
					root=insert(root,x);
					break;
					
			case 3: printf("\nEnter a key:");
					scanf("%d",&x);
					root = Delete(root,x);
					break;
			
			case 4: printf("1. Inorder sequence of keys:\n");
			        printf("2. Preorder sequence of keys:\n");
			        printf("\n Enter your choice[1-2]");
			        scanf("%d", &choice);
			        if(choice ==1)
					   inorder(root);
					else
					   if(choice ==2)
					     preorder(root);
					   else
					     printf("Wrong order...\n");
					break;			
			case 5: printf("\n Exit from Program...");
			        exit(0);
            default: printf("\n Invalid Choice TRY AGAIN[1-5]:");
		}
	 }
	
}


