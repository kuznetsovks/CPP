#pragma once
#include <iostream>
#include <initializer_list>
#include <iterator>
#include <unordered_map>
#include <optional>
#include "node.h"
#include <mutex>
#include <thread>
using namespace std;
template<class K, class T, class TA = allocator<Node<K, T>>>
class Hashmap
{
	using node_type = Node<K, T>;

private:
	Node<K, T>** table;
	size_t table_size = 100;
	size_t t_size = 0;
	size_t capacity;
	mutex mutex_;

	constexpr auto const static hasher = std::hash<K>();
public:
	auto hashFunc(K key) {
		return hasher(key) % table_size;
	}
	class iterator
	{
	private:

		const Hashmap<K, T, TA>* map;
		size_t index;
		Node<K, T>* node_;
	public:
		iterator() {
		}

		iterator(const Hashmap<K, T, TA>* map, bool end, size_t ind = 0) {

			this->map = map;
			if (end) {
				index = map->table_size;
				node_ = nullptr;
			}
			else {
				index = ind;
				node_ = map->table[index];
				while (node_ == nullptr && ++index < map->table_size) {
					node_ = map->table[index];
				}
			}
		}

		iterator(const iterator& it) {
			map = it.map;
			index = it.index;
			node_ = it.node_;
		}

		iterator& operator++() {
			node_ = node_->get_next();
			while (node_ == nullptr && ++index < map->table_size) {
				node_ = map->table[index];
			}
			return *this;
		}


		iterator operator++(int) {
			iterator copy(*this);
			operator++();
			return copy;
		}

		bool operator==(iterator& rhs) {
			return map == rhs.map && index == rhs.index && node_ == rhs.node_;
		}



		bool operator!=(iterator& rhs) {
			return !(*this == rhs);
		}

		K operator*() {
			return node_->get_key();
		}

		K* operator->() {
			return &node_->get_key();
		}
	};

	class  const_iterator
	{
	private:

		const Hashmap<K, T, TA>* map;
		size_t index;
		Node<K, T>* node_;
	public:
		const_iterator() {
		}

		const_iterator(const Hashmap<K, T, TA>* map, bool end, size_t ind = 0) {

			this->map = map;
			if (end) {
				index = map->table_size;
				node_ = nullptr;
			}
			else {
				index = ind;
				node_ = map->table[index];
				while (node_ == nullptr && ++index < map->table_size) {
					node_ = map->table[index];
				}
			}
		}

		const_iterator(const const_iterator& it) {
			map = it.map;
			index = it.index;
			node_ = it.node_;
		}

		const_iterator& operator++() {
			node_ = node_->get_next();
			while (node_ == nullptr && ++index < map->table_size) {
				node_ = map->table[index];
			}
			return *this;
		}


		const_iterator operator++(int) {
			const_iterator copy(*this);
			operator++();
			return copy;
		}

		bool operator==(const_iterator& rhs) {
			return map == rhs.map && index == rhs.index && node_ == rhs.node_;
		}

		bool operator!=(const_iterator& rhs) {
			return !(*this == rhs);
		}
		bool operator!=(iterator& rhs) {
			return !(*this == rhs);
		}

		K operator*() {
			return node_->get_key();
		}

		K* operator->() {
			return &node_->get_key();
		}
	};
	iterator begin() const {
		return iterator(this, false);
	}

	iterator end() const {
		return iterator(this, true);
	}

	const_iterator cbegin() const {
		return const_iterator(this, false);
	}

	const_iterator cend() const {
		return const_iterator(this, true);
	}
	iterator find(const K& key) {
		lock_guard<mutex> guard(mutex_);
		unsigned long hashValue = hashFunc(key);
		Node<K, T>* entry = table[hashValue];

		while (entry != nullptr) {
			if (entry->get_key() == key) {
				iterator it(this, false, hashValue);
				return it;
				//return entry->get_value();
			}
			entry = entry->get_next();
		}
		return end();
	}
	const_iterator cfind(const K& key) {
		lock_guard<mutex> guard(mutex_);
		unsigned long hashValue = hashFunc(key);
		Node<K, T>* entry = table[hashValue];
		while (entry != nullptr) {
			if (entry->get_key() == key) {
				const_iterator it(this, false, hashValue);
				return it;

			}
			entry = entry->get_next();
		}
		return cend();
	}
	Hashmap<K, T, TA>() {

		table = new node_type * [table_size]();
	}
	Hashmap<K, T, TA>(size_t& new_size) {
		table_size = new_size;
		table = new node_type * [table_size]();
	}

	Hashmap<K, T, TA>(initializer_list<pair<K, T> > list) {//const TA& alloc
		table = new node_type * [table_size]();
		for (auto it : list) {
			this->insert(it.first, it.second);
			//cout << it.first << endl;
			//cout << it.second << endl;
		}
	}

	Hashmap<K, T, TA>(const Hashmap<K, T, TA>& other) {
		table = other.table;
		table_size = other.table_size;
	}

	Hashmap<K, T, TA>(Hashmap<K, T, TA>&& other) {
		table = other.table;
		table_size = other.table_size;
		other.table_size = 0;
		other.table = nullptr;
	}

	Hashmap<K, T, TA>& operator=(const Hashmap<K, T, TA>& right) {
		if (this != &right)
		{
			table = right.table;
			table_size = right.table_size;
		}
		return *this;
	}

	Hashmap<K, T, TA>& operator=(Hashmap<K, T, TA>&& right) {
		if (this != &right)
		{
			table = right.table;
			table_size = right.table_size;
		}

		return *this;
	}
	void swap(Hashmap<K, T, TA>& other)
	{
		std::swap(other.table, this->table);
		std::swap(other.table_size, this->table_size);

	}

	virtual ~Hashmap() {
		for (size_t i = 0; i < table_size; i++) {
			Node<K, T>* entry = table[i];
			while (entry != nullptr) {
				Node<K, T>* prev = entry;
				entry = entry->get_next();
				delete prev;
			}
			table[i] = nullptr;
		}
		delete[] table;
	}



	template <class E, class P>
	void insert(E&& key, P&& t) {
		lock_guard<mutex> guard(mutex_);
		unsigned long hashValue = hashFunc(key);
		Node<K, T>* prev = NULL;
		Node<K, T>* entry = table[hashValue];


		while (entry != NULL && entry->get_key() != key) {
			prev = entry;
			entry = entry->get_next();

		}

		if (entry == NULL) {
			entry = new Node<K, T>(key, t);

			if (prev == NULL) {
				table[hashValue] = entry;
				t_size++;

			}
			else {
				prev->set_next(entry);
				t_size++;
			}

		}
		else {

			entry->set_value(t);
			//t_size++;
		}
		//t_size++;

	}

	template <class E, class P>
	iterator insert_(E&& key, P&& t) {
		lock_guard<mutex> guard(mutex_);
		unsigned long hashValue = hashFunc(key);

		Node<K, T>* prev = NULL;
		Node<K, T>* entry = table[hashValue];

		while (entry != NULL && entry->get_key() != key) {
			prev = entry;
			entry = entry->get_next();

		}

		if (entry == NULL) {
			entry = new Node<K, T>(key, t);

			if (prev == NULL) {
				table[hashValue] = entry;
				t_size++;
			}
			else {
				prev->set_next(entry);
				t_size++;
			}

		}
		else {
			entry->set_value(t);

		}


		iterator it(this, false, hashValue);
		return it;
	
	}



	std::optional<T> get(const K& key) {
		lock_guard<mutex> guard(mutex_);
		unsigned long hashValue = hashFunc(key);
		Node<K, T>* entry = table[hashValue];

		while (entry != nullptr) {
			if (entry->get_key() == key) {
				return entry->get_value();
			}
			entry = entry->get_next();
		}
		//cout << "not found" << endl;
		return {};
	}

	template <class... Args>
	pair<iterator, bool> emplace(Args&&... args)
	{
		//lock_guard<mutex> guard(mutex_);
		size_t temp_size = t_size;
		iterator it = this->insert_(make_pair(args...).first, make_pair(args...).second);
		if (t_size == temp_size) {
			return std::make_pair(it, false);
		}
		return std::make_pair(it, true);
	}

	T operator[](const K& key)
	{
		lock_guard<mutex> guard(mutex_);
		unsigned long hashValue = hashFunc(key);
		Node<K, T>* entry = table[hashValue];

		while (entry != nullptr) {
			if (entry->get_key() == key) {
			
				return entry->get_value();
			}
			entry = entry->get_next();
		}

		throw runtime_error("No such key");

	}
	T operator[](K&& key)
	{
		lock_guard<mutex> guard(mutex_);
		unsigned long hashValue = hashFunc(key);
		Node<K, T>* entry = table[hashValue];

		while (entry != nullptr) {
			if (entry->get_key() == key) {
				return entry->get_value();
			}
			entry = entry->get_next();
		}

		throw runtime_error("No such key");
	}



	void remove(const K& key) {
		lock_guard<mutex> guard(mutex_);
		unsigned long hashValue = hasher(key);
		Node<K, T>* prev = NULL;
		Node<K, T>* entry = table[hashValue];

		while (entry != NULL && entry->get_key() != key) {
			prev = entry;
			entry = entry->get_next();
		}

		if (entry == NULL) {
			return {};
		}
		else {
			if (prev == NULL) {
				table[hashValue] = entry->get_next();
			}
			else {
				prev->set_next(entry->get_next());
			}
			delete entry;
		}
	}

	size_t size() const noexcept
	{
		return t_size;
	}


	bool empty() const noexcept {
		lock_guard<mutex> guard(mutex_);
		for (int i = 0; i < table_size; i++) {
			if (table[i] != nullptr)
				return false;
		}
		return true;
	}

	void clear() {
		lock_guard<mutex> guard(mutex_);
		for (int i = 0; i < table_size; i++) {
			Node<K, T>* entry = table[i];
			while (entry != nullptr) {
				Node<K, T>* prev = entry;
				entry = entry->get_next();
				delete prev;
			}
			table[i] = nullptr;
		}

	}
	Node<K, T> extract(const_iterator position)
	{
		if (this->cend() != position) {

			unsigned long hashValue = hashFunc(*position);
			Node<K, T>* entry = table[hashValue];
			return *entry;

		}
	}

	Node<K, T> extract(const K& key)
	{
		iterator position = this->find(key);
		if (this->end() != position) {
			unsigned long hashValue = hashFunc(*position);
			Node<K, T>* entry = table[hashValue];
			return *entry;
		}
	}




};

