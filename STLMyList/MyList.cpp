#include<stdio.h>

template<class T>
class mylist
{
private :
	struct Node
	{
		T*pdata;
		Node* prev;
		Node* next;

		Node(T*d, Node* p, Node* n)
		{
			pdata = d;
			prev = p;
			next = n;
		}
	};
	Node* head;//point the first node
	Node* fail;//point the last node

public :
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
		iterator operator+(int n)//not test
		{
			for (int i = 0; i < n; i++)
				pointer = pointer->next;
			return *this;
		}
		iterator operator-(int n)//not test
		{
			for (int i = 0; i < n; i++)
				pointer = pointer->prev;
			return *this;
		}
		Node* NodePointer()
		{
			return pointer;
		}
	};

	mylist()
	{
		head = fail = (Node*)malloc(sizeof(Node));
	}

	mylist(T* startp, int size)
	{
		if (size >= 1)
		{
			T* p = startp;

			head = fail = new Node(p, NULL, NULL);

			Node* newNode = new Node(&p[0], NULL, NULL);
			fail->prev = newNode;
			newNode->next = fail;
			head = newNode;

			for (int i = 1; i < size; i++)
			{
				newNode = new Node(&p[i], NULL, NULL);
				newNode->prev = fail->prev;
				newNode->next = fail;
				newNode->prev->next = newNode;
				newNode->next->prev = newNode;
			}
		}
	}
	
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
	
	iterator& begin()
	{
		iterator it(head);
		return it;
	}

	iterator& end()
	{
		iterator it(fail);
		return it;
	}

	void swap(mylist<T>& b)
	{
		Node* p;

		p = this->head;
		this->head = b.head;
		b.head = p;

		p = this->fail;
		this->fail = b.fail;
		b.fail = p;
	}

	void insert(iterator pos, T e)//not test
	{
		Node* newElement = new Node(new T(e), NULL, NULL);
		newElement->prev = pos.NodePointer()->prev;
		newElement->next = pos.NodePointer();
		if (newElement->prev != NULL)
			newElement->prev->next = newElement;
		if (newElement->next != NULL)
			newElement->next->prev = newElement;
		if (pos == begin())
			head = newElement;
	}

	void erase(iterator begin, iterator end)
	{
		if (begin.NodePointer()->prev != NULL)
			begin.NodePointer()->prev->next = end.NodePointer();
		else
			head = end.NodePointer();
		end.NodePointer()->prev = begin.NodePointer()->prev;

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
		Node* p, * pr;
		pr = p = head;
		head = fail;
		head->prev = NULL;
		while (p != fail)
		{
			p = p->next;
			delete pr;
			pr = p;
		}
	}

	bool empty()
	{
		return head == fail;
	}

	T* front()
	{
		return head==fail?NULL:head->pdata;
	}

	T* back()
	{
		return fail->prev == NULL ? NULL : fail->prev->pdata;
	}

	void push_back(T e)
	{
		Node* newNode;
		if (head == fail)
		{
			newNode = new Node(new T(e), NULL, NULL);
			fail->prev = newNode;
			newNode->next = fail;
			head = newNode;
		}
		else
		{
			newNode = new Node(new T(e), NULL, NULL);
			newNode->prev = fail->prev;
			newNode->next = fail;
			newNode->prev->next = newNode;
			newNode->next->prev = newNode;
		}
	}

	void pop_back(T&e)
	{
		if (head == fail)
			return;
		else
		{
			e = *(fail->prev->pdata);
			Node* p;
			if (fail->prev == head)
			{
				p = head;
				head = fail;
				fail->prev = NULL;
				delete p;
			}
			else
			{
				p = fail->prev;
				fail->prev = fail->prev->prev;
				fail->prev->next = fail;
				delete p;
			}
		}
	}

	void push_front(T e)
	{
		Node* newNode = new Node(new T(e), NULL, NULL);
		newNode->next = head;
		newNode->next->prev = newNode;
		head = newNode;
	}

	void splice(iterator pos, mylist<T>& a)
	{
		for (iterator it = a.begin(); it != a.end(); ++it)
		{
			insert(pos, *it);
		}
		a.clear();
	}

	void splice(iterator pos, mylist<T>& a,iterator abeg,iterator aend)
	{
		for (iterator it = abeg; it != aend; ++it)
		{
			insert(pos, *it);
		}
		a.erase(abeg,aend);
	}

	void splice(iterator pos, mylist<T>& a, iterator posa)
	{
		for (iterator it = posa; it != a.end(); ++it)
		{
			insert(pos, *it);
		}
		a.erase(posa,a.end());
	}

	void unique()
	{
		if (head == fail)return;
		Node* p, * pr;
		pr = head;
		p = head->next;
		while (p != fail)
		{
			if (*pr->pdata == *p->pdata)
			{
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
		if (head == fail)return;
		Node* p, * pr;
		p = pr = head;
		while(p!=fail&&*p->pdata == x)
		{
			head = head->next;
			head->prev = NULL;
			delete p;
			p = pr = head;
		}
		if (p == fail)return;
		p = p->next;
		while (p != fail)
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
		if (head == fail)return;
		Node* p, * max, * sfail;
		T* c;
		sfail = fail->prev;
		while (sfail != head)
		{
			p = head;
			max = p;
			while (p != sfail->next)
			{
				if (*p->pdata > *max->pdata)
				{
					max = p;
				}
				p = p->next;
			}
			c = sfail->pdata;
			sfail->pdata = max->pdata;
			max->pdata = c;

			sfail = sfail->prev;
		}
	}

	void reverse()
	{
		if (head == fail)return;

		Node* p1, * p2;
		T* c;

		p1 = head;
		p2 = fail->prev;

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
		for (it = a.begin(), p = head; it != a.end() && p != fail; ++it,p=p->next)
		{
			if (*it != *(p->pdata))
			{
				return false;
			}
		}
		if (it == a.end() && p == fail)
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
		for (myp=head,ap=a.head;myp!=fail&&ap!=a.fail;myp=myp->next,ap=ap->next)
		{
			T* r = myp->pdata;
			myp->pdata = new T(*ap->pdata);
			delete r;
		}
		while (myp != fail)//如果数据全部复制完成，而本方没到尾部，删除剩下部分
		{
			iterator it(myp);
			erase(it, end());
		}
		while (ap!=a.fail)//如果本方已到尾部，而数据没有复制完，则把剩下数据加到尾部
		{
			push_back(*(new T(*ap->pdata)));
			ap = ap->next;
		}
	}

	void getfilepdata(FILE* fp)
	{
		if (feof(fp))return;
		char startc = fgetc(fp);
		head = fail = new Node(new char(startc), NULL, NULL);
		Node* newNode = new Node(new char(startc), NULL, NULL);
		fail->prev = newNode;
		newNode->next = fail;
		head = newNode;
		while (!feof(fp))
		{
			char c = fgetc(fp);

			newNode = new Node(new char(c), NULL, NULL);
			newNode->prev = fail->prev;
			newNode->next = fail;
			newNode->prev->next = newNode;
			newNode->next->prev = newNode;
		}
	}

	void operator=(mylist<T>& b)
	{
		this->copylink(b);
	}
};