
template <typename T>
struct  Node
{
	T data;
	Node* next;
	Node* prev;
};

template <typename T>
class list_iterator
{
public:

	list_iterator(Node<T>* ptr):m_ptr(ptr){}


	list_iterator& operator++() {
		m_ptr = m_ptr->next;
		return *this;
	}

	 list_iterator& operator--() {
		m_ptr = m_ptr->prev;
		return *this;
	 }

	 bool operator!=(const list_iterator& it){
		 return m_ptr != it.m_ptr;
	 }

	 bool operator==(const list_iterator& it) {
		 return m_ptr == it.m_ptr;
	 }

	 T* operator->() {
		 return &m_ptr->data;
	 }
		
	 T& operator*() {
		 return m_ptr->data;
	 }


private:
	Node<T>* m_ptr;
};

template <typename T>
class list
{
public:

	~list() {
		del_list();

	}

	void push_back(const T& x) {
		Node<T>* newnode=new Node<T>;
		newnode->data = x;


		if (end_root == nullptr) {
			newnode->prev=nullptr;
			newnode->next = nullptr;
			root = newnode;
			end_root = newnode;
		}
		else
		{
			end_root->next = newnode;
			newnode->next = nullptr;
			newnode->prev = end_root;
			end_root = newnode;
		}
	}

	list_iterator<T> begin(){
		return list_iterator<T>(root);
	}

	list_iterator<T> end() {
		return list_iterator<T>(nullptr);
	}

private:
	Node<T>* root;
	Node<T>* end_root;
	void del_list(){
		for (auto i = root; i != nullptr; )
		{
			Node<T>* extra = i->next;
			delete i;
			i = extra;
		}


	}
};
  






