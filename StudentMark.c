#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
typedef struct node
{
	int data;
	int rollno;
	char name[20];
	char subject[20];
	int height;
	struct node *left,*right;
}nw;
typedef struct type
{
	int mark;
	int rollno;
	char name[20];
	char subject[20];
}std;
int Max(int a,int b);
nw* bulidNode(std *d);
nw* insertNode(nw *root,nw *temp);
void pop(nw *stack[],int *top);
void push(nw *stack[],int *top,nw *curr);
void postorder(nw *root,int cnt);
int getbalance(nw *root);
nw* leftrotate(nw *x);
nw* rightrotate(nw *y);
void main()
{
	nw *root,*child,*parent;
	int i,cnt;
	std arr[]={{80,1,"dharani","maths"},{89,2,"supriya","maths"},{85,3,"sadhana","maths"},{78,4,"kirubha","maths"},{92,5,"mithulram","maths"},{74,6,"poorni","maths"},{93,7,"anusree","maths"},{70,8,"gayathri","maths"},{87,9,"snekithasri","maths"},{71,10,"deepika","maths"},{84,11,"mehala","maths"},{75,12,"latha","maths"},{73,13,"kala","maths"},{95,14,"hemvarshan","maths"},{79,15,"madhu","maths"},{65,16,"diya","maths"},{76,17,"kavya","maths"},{90,18,"rithanya","maths"},{82,19,"savitha","maths"},{69,20,"raj","maths"}};
	clrscr();
	root=(nw*)malloc(sizeof(struct node));
	root->data=arr[0].mark;
	root->rollno=arr[0].rollno;
	strcpy(root->name,arr[0].name);
	strcpy(root->subject,arr[0].subject);
	root->left=NULL;
	root->right=NULL;
	for(i=1;i<20;i++)
	{
		child=bulidNode(&arr[i]);
		root=insertNode(root,child);
	}
	printf("\n enter the rollno to know the status of work:");
	scanf("%d",&cnt);
	postorder(root,cnt);
	getch();

}
nw* bulidNode(std *d)
{
	nw *temp;
	temp=(nw*)malloc(sizeof(struct node));
	temp->data=d->mark;
	temp->rollno=d->rollno;
	strcpy(temp->name,d->name);
	strcpy(temp->subject,d->subject);
	temp->height=1;
	temp->left=NULL;
	temp->right=NULL;
	return temp;

}
nw* insertNode(nw *root,nw *temp)
{
	nw* parent,*curr;
	int balance;
	curr=root;
	if(root==NULL)
		 return temp;
	else
	{
		while(curr!=NULL)
		{
			parent=curr;
			if(curr->data<temp->data)
				curr=curr->right;
			else
				curr=curr->left;

		}
	}

	if(parent->data<temp->data)
		parent->right=temp;
	else
		parent->left=temp;

	parent->height=1+Max(parent->left->height,parent->right->height);
	balance=getbalance(root);
	if(balance>1&&temp->data<root->left->data)
	return rightrotate(root);
	if(balance<-1&&temp->data>root->right->data)
	return leftrotate(root);
	if(balance>1&&temp->data>root->left->data)
	{
	root->left=leftrotate(root->left);
	return rightrotate(root);
	}
	if(balance<-1&&temp->data<root->right->data)
	{
	root->right=rightrotate(root->right);
	return leftrotate(root);
	}

	return root;

}
void pop(nw *stack[],int *top)
{


//printf("pop=%d",stack[*top]->data);
 *top=*top-1;

}

void push(nw *stack[],int *top,nw *curr)
{
 *top=*top+1;
 stack[*top]=curr;
// printf("push=%d",curr->data);

}

void postorder(nw *root,int cnt)
{
	nw *stack[10];
	int i=-1,j=1;
	int *top=&i;
	nw *curr=root;
	while(curr!=NULL||*top!=-1)
	{
		while(curr!=NULL)
		{
			push(stack,top,curr);
			curr=curr->left;


		}
		curr=stack[*top];
		pop(stack,top);
		j++;
		if(cnt==curr->rollno)
		{
		printf(" studentname-%s rollno-%d secured-%d mark in subject %s is %d position in class",curr->name,curr->rollno,curr->data,curr->subject,21-j);
		 }
		curr=curr->right;

	}
}
int Max(int a,int b)
{
if(a>b)
return a;
return b;
}
nw* rightrotate(nw *y)
{
 nw *x=y->left;
 nw *t2=x->right;
 x->right=y;
 y->left=t2;
 y->height=Max(y->left->height,y->right->height)+1;
 x->height=Max(x->left->height,x->right->height)+1;
 return x;
 }
nw* leftrotate(nw *x)
{
 nw *y=x->right;
 nw *t2=y->left;
 y->left=x;
 x->right=t2;
 y->height=Max(y->left->height,y->right->height)+1;
 x->height=Max(x->left->height,x->right->height)+1;

 return y;
}
int getbalance(nw *root)
{
if(root==NULL)
return 0;
return root->left->height- root->right->height;
}