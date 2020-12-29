
#pragma once
using namespace std;
template <typename K, typename T,typename Alloc= allocator<pair<K,T>>>
class Node {
private:
	
	pair<K, T>* KV;
	Node* next;
	Alloc Allocator;


public:
	Node(const K& key_, const T& t_) 
	{
		KV = Allocator.allocate(1);
		KV->first = key_;
		KV->second = t_;
		next = nullptr;
	}
	~Node() 
	{
		KV = nullptr;
		Allocator.deallocate(KV, 1);
	}
	K& get_key() 
	{
		return KV->first;
	}

	T& get_value() 
	{
		return KV->second;//;
	}
	const K& get_key() const
	{
		return KV->first;
	}

	const T& get_value() const
	{
		return KV->second;//;
	}
	void set_value(T t_) {
		KV->second = t_;
	}

	Node* get_next() const {
		return next;
	}

	void set_next(Node* next_) {
		next = next_;
	}
	void print() 
	{
		cout << "Key =" << KV->first << endl;
		cout << "Value = " << KV->second << endl;
	}
};

