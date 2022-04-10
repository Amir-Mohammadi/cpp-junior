#include<stdio.h>
#include<conio.h>
#include<iostream.h>

#define MAX 40
typedef struct nearlist nearptr;

struct graphnode{
	   char data;
	   int visit;
	   nearptr *adjacent;
	   struct graphnode *nextnode;
}*start;

struct nearlist{
	   struct graphnode *nodepointer;
	   nearptr *nextlist;
};

void findnode(char ch);
void GraphBuild();
void initDFS();
void DFS(struct graphnode *node);
void visit(struct graphnode *node);
void push(char new_item);
char pop();
int is_full();
int is_emtpy();
int connectedGraph();

struct graphnode *foundnode=NULL;
char stack[MAX];
int top=-1;

void main()
{
 clrscr();
 start=new (struct graphnode);
 start->data='\0';
 start->visit=0;
 start->adjacent=NULL;
 start->nextnode=NULL;
 GraphBuild();
 clrscr();
 cout<<"Enter node to start DFS : ";
 char ch;
 ch=getche();
 findnode(ch);
 if( !( connectedGraph() ) )
    cout<<"\nThis graph is not connected.";
 else
   {
    cout<<"\nThe Depth-First Search of this graph is :\n";
    initDFS();
    DFS(foundnode);
   }
 cout<<"\n\n\nPress ESC to exit";
 while(ch!=27)
 {
  ch=getch();
 }
}

void GraphBuild()
{

 char temp,ch;
 struct graphnode *lastnode,*node;
 struct nearlist *tempnear,*tempnear2;
 int flag=0;
 while(1)
 {
  if(flag)
    cout<<"\n";
  flag=1;
  cout<<"Enter node(s) (1 character): ";
  cin>>temp;
  if(start->data==0)
	{
	 start->data=temp;
	 lastnode=start;
	}
  else
	{
	 node=new(struct graphnode);
	 node->data=temp;
	 node->visit=0;
	 node->adjacent=NULL;
	 node->nextnode=NULL;
	 lastnode->nextnode=node;
	 lastnode=node;
	}
  Label:
  cout<<"Continue entering nodes? (Y/N) : ";
  ch=getche();
  if( (ch=='y') || (ch=='Y') )
	continue;
  else if( (ch=='n') || (ch=='N') )
	break;
  else
    {
     cout<<"\n";
	 goto Label;
    }
 }
 lastnode=start;
 flag=0;
 while(lastnode)
 {//while
  if(flag)
    lastnode=lastnode->nextnode;
  if(!lastnode)
    break;
  if(!flag)
    flag=1;
  clrscr();
  textcolor(15+BLINK);
  cprintf("  Pressing ENTER without typing anything means that the NODE has no adjacent.");
  textcolor(7);
  Label2:
  cout<<"\n"<<"Enter "<<lastnode->data<<"'s adjacent(s): ";
  temp=getche();
  if(temp=='\r')
    continue;
  findnode(temp);
  if(foundnode==NULL)
	{
	 cout<<"\nNot found. Enter correct data."<<"\n";
	 goto Label2;
	}
  else
	{//else
	 tempnear=new(struct nearlist);
	 tempnear->nodepointer=foundnode;
	 tempnear->nextlist=NULL;
	 if(lastnode->adjacent==NULL)
		lastnode->adjacent=tempnear;
	 else
	   {
		tempnear2=lastnode->adjacent;
		while(tempnear2->nextlist!=NULL)
            tempnear2=tempnear2->nextlist;
        tempnear2->nextlist=tempnear;
	   }
	}//else
  Label3:
  cout<<"\nIs there any other adjacent? (Y/N): ";
  temp=getche();
  if( (temp=='Y') || (temp=='y') )
     goto Label2;
  else if( (temp=='N') || (temp=='n') )
     continue;
  else
     goto Label3;
 }//while
}

void findnode(char ch)
{
 foundnode=start;
 while(foundnode)
 {
  if(foundnode->data==ch)
	return;
  foundnode=foundnode->nextnode;
 }
 foundnode=NULL;
}

void initDFS()
{
 struct graphnode *temp;
 temp=start;
 while(temp->nextnode)
 {
  temp->visit=0;
  temp=temp->nextnode;
 }
}

void DFS(struct graphnode *node)
{
 if(!node)
   return;
 struct nearlist *temp_item=NULL;
 temp_item=node->adjacent;
 if( !(node->visit) )
 {
  visit(node);
  while(temp_item)
  {
   push(temp_item->nodepointer->data);
   temp_item=temp_item->nextlist;
  }
 }
 findnode(pop());
 DFS(foundnode);
}

void visit(struct graphnode *node)
{
 cout<<node->data;
 node->visit=1;
}

void push(char new_item)
{
 if(is_full())
  {
   cout<<"STACK is full.";
   return;
  }
 stack[++top]=new_item;
}

char pop()
{
 char temp=stack[top--];
 return(temp);
}

int is_full()
{
 if(top==MAX-1)
   return(1);
 return(0);
}

int is_empty()
{
 if(top==-1)
   return(1);
 return(0);
}

int connectedGraph()
{
 struct graphnode *temp;
 temp=start;
 while(temp)
 {
  if(temp->adjacent==NULL)
    return(0);
  temp=temp->nextnode;
 }
 return(1);
}