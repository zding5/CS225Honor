#include "priority_queue.h"
//#include <array>
#include <iostream>


//============================functions for node struct==========================

template <class T>
PriorityQueue<T>::node::node()
{
	parent=NULL;
	right=NULL;
	left=NULL;
	children=NULL;
	numchildren=0;
	value=NULL;
}

template <class T>
PriorityQueue<T>::node::node(T thevalue)
{
	value=thevalue;
	parent=NULL;
	children=NULL;
	right=NULL;
	left=NULL;
	numchildren=0;
}

template <class T>
PriorityQueue<T>::node::node(node*theone)
{
	value=theone->value;
	parent=NULL;
	children=NULL;
	right=NULL;
	left=NULL;
}

template <class T>
bool PriorityQueue<T>::node::insertchild(node*thechild)
{
	if(this->children!=NULL)
	{
		this->children->insertsibling(thechild);
		return 0;
	}
	else
	{
		this->children=thechild;
		this->children->parent=this;
		this->numchildren=1;
		return 1;
	}
	//return 1;
}

template <class T>
bool PriorityQueue<T>::node::insertsibling(node*brosis)
{
	node*temp=getrightmost();
	if(temp==NULL)return 0;
	else
	{
		temp->right=brosis;
		brosis->left=temp;
		brosis->parent=this->parent;
		if(temp->parent!=NULL)temp->parent->numchildren++;
		return 1;
	}
}

template <class T>
void PriorityQueue<T>::node::remove()
{
	if(this->parent!=NULL)
	{
		this->parent->numchildren--;
		if(this->left!=NULL)this->parent->children=this->left;
		else if(this->right!=NULL)this->parent->children=this->right;
		else this->parent->children=NULL;
	}
	if(this->left!=NULL)this->left->right=this->right;
	if(this->right!=NULL)this->right->left=this->left;
	this->parent=NULL;
	this->left=NULL;
	this->right=NULL;
}

template<class T>
typename PriorityQueue<T>::node* PriorityQueue<T>::node::getleftmost()
{
	if(this==NULL)return NULL;
	node*temp=this;
	while(temp->left!=NULL)temp=temp->left;
	return temp;
}

template<class T>
typename PriorityQueue<T>::node* PriorityQueue<T>::node::getrightmost()
{
	if(this==NULL)return NULL;
	node*temp=this;
	while(temp->right!=NULL)temp=temp->right;
	return temp;
}

//=============================PriorityQueue Helper Functions=================

template<class T>
bool PriorityQueue<T>::join(node*sroot)
{
	if(roots[sroot->numchildren]==NULL)
	{
		roots[sroot->numchildren]=sroot;
		return 0;
	}
	else
	{
		node*theother=roots[sroot->numchildren];
		roots[sroot->numchildren]=NULL;
		if(sroot->value>theother->value||sroot==maxroot)
		{
			theother->remove();
			sroot->insertchild(theother);
			if(roots[sroot->numchildren]!=NULL)join(sroot);
			else roots[sroot->numchildren]=sroot;
		}
		else
		{
			sroot->remove();
			theother->insertchild(sroot);
			if(roots[theother->numchildren]!=NULL)join(theother);
			else roots[theother->numchildren]=theother;
		}
		return 1;
	}
}

template <class T>
typename PriorityQueue<T>::node* PriorityQueue<T>::removemax()
{
	node*temp1=maxroot->children->getleftmost();
	node*temp2=NULL;
	while(temp1!=NULL)
	{
		temp2=temp1->right;
		temp1->remove();
		maxroot->insertsibling(temp1);
		temp1=temp2;
	}
	temp1=maxroot->getleftmost();
	if(temp1==maxroot)
	{
		if(maxroot->right!=NULL)temp1=maxroot->right;
		else
		{
			node*removed=maxroot;
			maxroot->remove();
			maxroot=NULL;
			return removed;
		}
	}
	node*removed=maxroot;
	maxroot->remove();
	maxroot=temp1;
	for(int i=0;i<100/*roots.size()*/;i++)
	{
		roots[i]=NULL;
	}
	while(temp1!=NULL)
	{
		if(temp1->value>maxroot->value)maxroot=temp1;
		temp2=temp1->right;
		join(temp1);
		temp1=temp2;
	}
	return removed;
}

//=============================PriorityQueue Member Functions================

template <class T>
PriorityQueue<T>::PriorityQueue()
{
	maxroot=NULL;
}

template <class T>
PriorityQueue<T>::PriorityQueue(PriorityQueue&theone)
{
	PriorityQueue temp;
	maxroot=NULL;
	while(!theone.isEmpty())
	{
		T tempp=theone.pop();
		insert(tempp);
		temp.insert(tempp);
	}
	while(!temp.isEmpty())
	{
		T tempp=temp.pop();
		theone.insert(tempp);
	}
}

template <class T>
PriorityQueue<T>::~PriorityQueue()
{
	while(!isEmpty())pop();
}

template <class T>
void PriorityQueue<T>::insert(const T & value)
{
	node*newnode=new node(value);
	if(maxroot==NULL)maxroot=newnode;
	else
	{
		maxroot->insertsibling(newnode);
		if(maxroot->value<newnode->value)maxroot=newnode;
	}
}

template <class T>
T PriorityQueue<T>::pop()
{
	if(isEmpty()) return T();
	else
	{
		node*popnode=removemax();
		T popvalue=popnode->value;
		delete popnode;
		return popvalue;
	}
}

template <class T>
const T & PriorityQueue<T>::top() const
{
    return maxroot->value;
}

template <class T>
bool PriorityQueue<T>::isEmpty() const
{
    return maxroot==NULL;
}
