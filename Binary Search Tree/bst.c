#include<stdio.h>
#include<stdlib.h>
struct node{
    int data;
    struct node *lchild;
    struct node *rchild;    
};
void inorder(struct node *p){
    if(p){
       
        inorder(p->lchild);
         printf("%d\t",p->data);
        inorder(p->rchild);
    }
}
int height(struct node *p){
    int x=0,y=0;
    if(p==NULL){
        return 0;
    }
        x=height(p->lchild);
        x=height(p->rchild);
        if(x>y)
            return x+1;
        else 
            return y+1;
}
struct node *insert(struct node *root,int key){
    struct node *p;
    if(root==NULL){
        p=(struct node*)malloc(sizeof(struct node));
        p->data=key;
        p->lchild=p->rchild=NULL;
        return p;
    }
    else if(key<root->data)
        root->lchild=insert(root->lchild,key);
    else
        root->rchild=insert(root->rchild,key);
    return root;
}
struct node *inpre(struct node *p){
    while(p && p->rchild)
        p=p->rchild;
    return p;
}
struct node *insucc(struct node *p){
    while(p && p->lchild)
        p=p->lchild;
    return p;
}
struct node *delete(struct node *p,int key)
{
    struct node *q;
    if(p==NULL)
        return NULL;
    if(p->lchild==NULL && p->rchild==NULL){
        free(p);
        return NULL;
    }
    if(key<p->data)
        p->lchild=delete(p->lchild,key);
    else if(key>p->data)
        p->rchild=delete(p->rchild,key);
    else{
        if(height(p->lchild)>height(p->rchild)){
            q=inpre(p->lchild);
            p->data=q->data;
            p->lchild=delete(p->lchild,q->data);
        }
         else{
            q=insucc(p->rchild);
            p->data=q->data;
            p->rchild=delete(p->rchild,q->data);
        }
    }
    return p;
}
int main(){
    struct node *root=NULL;
    root=insert(root,30);
    root=insert(root,20);
    root=insert(root,40);
    root=insert(root,10);
    root=insert(root,25);
    root=insert(root,35);
    root=insert(root,45);
    root=insert(root,42);
    root=insert(root,43);
    inorder(root);
    root=delete(root,30);
    inorder(root);
    return 0;
}