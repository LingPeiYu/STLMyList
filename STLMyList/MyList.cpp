/*
Use function template and class template to create my own list which has some of functions of the list in STL
*/
#include<stdio.h>

template<class T>
class mylist
{
private :
	struct Node
	{
		T*pdata;//Point data
		Node* prev;//Point the previous node
		Node* next;//Point the next node

		Node(T*d, Node* p, Node* n)
		{
			pdata = d;
			prev = p;
			next = n;
		}
	};
	Node* head;//Point the first node
	Node* tail;//Point the last node

public :
	//Define iterator
	class iterator
	{
	private:
		Node* pointer;
	public:
		iterator()
		{
			pointer = NULL;
		}
	    iterator(Node* p)
		{
			pointer = p;
		}

		//Operators Overloading
		T* operator->()
		{
			return pointer->pdata;
		}
		iterator operator++()
		{
			pointer = pointer->next;
			return *this;
		}
		iterator operator--()
		{
			pointer = pointer->prev;
			return *this;
		}
		bool operator!=(const iterator b)
		{
			return this->pointer != b.pointer;
		}
		bool operator==(const iterator b)
		{
			return this->pointer == b.pointer;
		}
		T& operator*()
		{
			return *pointer->pdata;
		}

		Node* NodePointer()
		{
			return pointer;
		}
	};

	//Constructors
	mylist()
	{
		head = tail = (Node*)malloc(sizeof(Node));
	}
	mylist(T* startp, int size)
	{
		if (size >= 1)
		{
			T* p = startp;

			head = tail = new Node(p, NULL, NULL);

			Node* newNode = new Node(&p[0], NULL, NULL);
			tail->prev = newNode;
			newNode->next = tail;
			head = newNode;

			for (int i = 1; i < size; i++)
			{
				newNode = new Node(&p[i], NULL, NULL);
				newNode->prev = tail->prev;
				newNode->next = tail;
				newNode->prev->next = newNode;
				newNode->next->prev = newNode;
			}
		}
	}
	
	//The destructor
	~mylist()
	{
		Node* p,*pr;
		pr = p = head;
		while (p != NULL)
		{
			p = p->next;
			delete pr;
			pr = p;
		}
	}
	
	//Functions
	iterator& begin()
	{
		iterator it(head);
		return it;
	}

	iterator& end()
	{
		iterator it(tail);
		return it;
	}

	void swap(mylist<T>& b)
	{
		Node* p;

		p = this->head;
		this->head = b.head;
		b.head = p;

		p = this->tail;
		this->tail = b.tail;
		b.tail = p;
	}

	void insert(iterator pos, T e)
	{
		Node* newElement = new Node(new T(e), NULL, NULL);//Create a new node
		//insert
		newElement->prev = pos.NodePointer()->prev;
		newElement->next = pos.NodePointer();
		if (newElement->prev != NULL)
			newElement->prev->next = newElement;
		if (newElement->next != NULL)
			newElement->next->prev = newElement;
		//If pos points the first node, let the head pointer points the new node
		if (pos == begin())
			head = newElement;
	}

	void erase(iterator begin, iterator end)
	{
		//Remove the nodes between begin and end from the list
		if (begin.NodePointer()->prev != NULL)
			begin.NodePointer()->prev->next = end.NodePointer();
		else
			head = end.NodePointer();
		end.NodePointer()->prev = begin.NodePointer()->prev;

		//Delete useless nodes
		Node* p, * pr;
    		pr = p = begin.NodePointer();
		while (p != end.NodePointer())
		{
			p = p->next;
			delete pr;
			pr = p;
		}
	}

	void clear()
	{
		//Delete all nodes
		Node* p, * pr;
		pr = p = head;
		head = tail;
		head->prev = NULL;
		while (p != tail)
		{
			p = p->next;
			delete pr;
			pr = p;
		}
	}

	bool empty()
	{
		return head == tail;
	}

	T* front()
	{
		//If the list is empty,return null. Otherwise return the pointer of the first data
		return head==tail?NULL:head->pdata;
	}

	T* back()
	{
		//If the list is empty,return null. Otherwise return the pointer of the last data
		return tail->prev == NULL ? NULL : tail->prev->pdata;
	}

	void push_back(T e)
	{
		Node* newNode;
		if (head == tail)//The way of pushing depends on whether the list is empty or not
		{
			newNode = new Node(new T(e), NULL, NULL);
			tail->prev = newNode;
			newNode->next = tail;
			head = newNode;
		}
		else
		{
			newNode = new Node(new T(e), NULL, NULL);
			newNode->prev = tail->prev;
			newNode->next = tail;
			newNode->prev->next = newNode;
			newNode->next->prev = newNode;
		}
	}

	void pop_back(T&e)
	{
		if (head == tail)
			return;//If the list is empty, return
		else
		{
			e = *(tail->prev->pdata);//Get the last data
			//Remove the last node
			Node* p;
			if (tail->prev == head)//The way of removing depends on whether the list only has one node or not
			{
				p = head;
				head = tail;
				tail->prev = NULL;
				delete p;
			}
			else
			{
				p = tail->prev;
				tail->prev = tail->prev->prev;
				tail->prev->next = tail;
				delete p;
			}
		}
	}

	void push_front(T e)
	{
		//Make a new node become the new head
		Node* newNode = new Node(new T(e), NULL, NULL);
		newNode->next = head;
		newNode->next->prev = newNode;
		head = newNode;
	}

	void splice(iterator pos, mylist<T>& a)
	{
		//Insert all nodes in List 'a' one by one to the position pointed by pos
		for (iterator it = a.begin(); it != a.end(); ++it)
		{
			insert(pos, *it);
		}
		//Clear List 'a'
		a.clear();
	}

	void splice(iterator pos, mylist<T>& a,iterator abeg,iterator aend)
	{
		//Insert all nodes between abeg and aend one by one to the position pointed by pos
		for (iterator it = abeg; it != aend; ++it)
		{
			insert(pos, *it);
		}
		//Remove all nodes between abeg and aend from List 'a'
		a.erase(abeg,aend);
	}

	void splice(iterator pos, mylist<T>& a, iterator posa)
	{
		//Insert all nodes from posa to the end of List 'a' one by one to the position pointed by pos
		for (iterator it = posa; it != a.end(); ++it)
		{
			insert(pos, *it);
		}
		//Remove all nodes from posa to the end of List 'a' from List 'a'
		a.erase(posa,a.end());
	}

	void unique()
	{
		if (head == tail)return;//if the list is empty, return
		Node* p, * pr;
		pr = head;
		p = head->next;
		while (p != tail)
		{
			if (*pr->pdata == *p->pdata)
			{
				//Remove the same and neighbouring data from the list
				pr->next = p->next;
				pr->next->prev = pr;
				delete p;
				p = pr->next;
			}
			else
			{
				pr = pr->next;
				p = p->next;
			}
		}
	}

	void remove(T x)
	{
		if (head == tail)return;//If the list is empty, return
		Node* p, * pr;
		p = pr = head;
		while(p!=tail&&*p->pdata == x)//When the first data of the list is x, use this way to remove the first node. Keep doing it until the first data isn't x.
		{
			head = head->next;
			head->prev = NULL;
			delete p;
			p = pr = head;
		}
		if (p == tail)return;//If the list is empty, return
		p = p->next;
		while (p != tail)//Check the remaining data. If it is x, remove it from list
		{
			if (*p->pdata == x)
			{
				pr = p;
				p = p->next;

				pr->prev->next = pr->next;
				pr->next->prev = pr->prev;
				delete pr;
			}
			else
				p = p->next;
		}
	}

	void Sort()
	{
		if (head == tail)return;//If the list is empty, return
		//Selection sort
		Node* p, * max, * stail;
		T* c;
		stail = tail->prev;
		while (stail != head)
		{
			p = head;
			max = p;
			while (p != stail->next)
			{
				if (*p->pdata > *max->pdata)
				{
					max = p;
				}
				p = p->next;
			}
			c = stail->pdata;
			stail->pdata = max->pdata;
			max->pdata = c;

			stail = stail->prev;
		}
	}

	void reverse()
	{
		if (head == tail)return;//If the list is empty, return

		Node* p1, * p2;
		T* c;

		p1 = head;
		p2 = tail->prev;

		//Exchange the data in p1 and p2. p1 moves forward from the head and p2 moves back from the tail
		while (p1 != p2 && p2->next != p1)
		{
			c = p1->pdata;
			p1->pdata = p2->pdata;
			p2->pdata = c;

			p1 = p1->next;
			p2 = p2->prev;
		}
	}

	bool complink(mylist<T>& a)
	{
		Node* p;
		iterator it;
		for (it = a.begin(), p = head; it != a.end() && p != tail; ++it,p=p->next)//Compare the data in two lists until one or more iterators get to the tails.
		{
			if (*it != *(p->pdata))//When find unmatched data, return false
			{
				return false;
			}
		}
		if (it == a.end() && p == tail)//If both iterators get to the tails, return true. Otherwise return false.
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void copylink(mylist<T>& a)
	{
		Node* myp,*ap;
		//Copy the data in List 'a' one by one. Meanwhile, delete the original data in this list
		for (myp=head,ap=a.head;myp!=tail&&ap!=a.tail;myp=myp->next,ap=ap->next) 
		{
			T* r = myp->pdata;
			myp->pdata = new T(*ap->pdata);
			delete r;
		}
		while (myp != tail)//If all data has been copied but the pointer still don't reach the tail, delete the remaining part
		{
			iterator it(myp);
			erase(it, end());
		}
		while (ap!=a.tail)//If the pointer reach the tail but not all data has been copied, put the remaining data behind the tail
		{
			push_back(*(new T(*ap->pdata)));
			ap = ap->next;
		}
	}

	void getfilepdata(FILE* fp)//Get data from a file
	{
		if (feof(fp))return;
		char startc = fgetc(fp);
		head = tail = new Node(new char(startc), NULL, NULL);
		Node* newNode = new Node(new char(startc), NULL, NULL);
		tail->prev = newNode;
		newNode->next = tail;
		head = newNode;
		while (!feof(fp))
		{
			char c = fgetc(fp);

			newNode = new Node(new char(c), NULL, NULL);
			newNode->prev = tail->prev;
			newNode->next = tail;
			newNode->prev->next = newNode;
			newNode->next->prev = newNode;
		}
	}

	void operator=(mylist<T>& b)
	{
		this->copylink(b);
	}
};