
#pragma once
template <typename K, typename T>
class Node {
private:
	K key;
	T t;
	Node* next;



public:
	Node(const K& key_, const T& t_) 
	{
		key = key_;
		t = t_;
		next = nullptr;
	}

	K get_key() const
	{
		return key;
	}

	T get_value() const 
	{
		return t;
	}

	void set_value(T t_) {
			t=t_;
	}

	Node* get_next() const {
		return next;
	}

	void set_next(Node* next_) {
		next = next_;
	}
	void print() 
	{
		cout << "Key =" << key << endl;
		cout << "Value = " << t << endl;
	}
};

