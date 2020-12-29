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
template<class K, class T, class TA = allocator<pair<K, T>>>
class Hashmap
{
	using node_type = Node<K, T, TA>;

private:
	node_type** table;
	size_t table_size = 100;
	size_t t_size = 0;
	mutex mutex_;

	constexpr auto const static hasher = std::hash<K>();
public:
	auto hashFunc(K key) noexcept {
		return hasher(key) % table_size;
	}
	class iterator
	{
	private:

		const Hashmap<K, T, TA>* map;
		size_t index;
		node_type* node_;
	public:
		iterator() noexcept {
		}

		iterator(const Hashmap<K, T, TA>* map, bool end, size_t ind = 0) noexcept {

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

		iterator(const iterator& it) noexcept {
			map = it.map;
			index = it.index;
			node_ = it.node_;
		}

		iterator& operator++() noexcept {
			node_ = node_->get_next();
			while (node_ == nullptr && ++index < map->table_size) {
				node_ = map->table[index];
			}
			return *this;
		}


		iterator operator++(int) noexcept {
			iterator copy(*this);
			operator++();
			return copy;
		}

		bool operator==(iterator& rhs) noexcept {
			return map == rhs.map && index == rhs.index && node_ == rhs.node_;
		}



		bool operator!=(iterator& rhs) noexcept {
			return !(*this == rhs);
		}

		K operator*() noexcept {
			return node_->get_key();
		}

		K* operator->() noexcept {
			return &node_->get_key();
		}
	};

	class  const_iterator
	{
	private:

		const Hashmap<K, T, TA>* map;
		size_t index;
		node_type* node_;
	public:
		const_iterator() noexcept {
		}

		const_iterator(const Hashmap<K, T, TA>* map, bool end, size_t ind = 0) noexcept {

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

		const_iterator(const const_iterator& it) noexcept {
			map = it.map;
			index = it.index;
			node_ = it.node_;
		}

		const_iterator& operator++() noexcept {
			node_ = node_->get_next();
			while (node_ == nullptr && ++index < map->table_size) {
				node_ = map->table[index];
			}
			return *this;
		}


		const_iterator operator++(int) noexcept {
			const_iterator copy(*this);
			operator++();
			return copy;
		}

		bool operator==(const_iterator& rhs) noexcept {
			return map == rhs.map && index == rhs.index && node_ == rhs.node_;
		}

		bool operator!=(const_iterator& rhs) noexcept {
			return !(*this == rhs);
		}
		bool operator!=(iterator& rhs) noexcept {
			return !(*this == rhs);
		}

		K operator*() noexcept {
			return node_->get_key();
		}

		K* operator->() noexcept {
			return &node_->get_key();
		}
	};
	iterator begin() const noexcept {
		return iterator(this, false);
	}

	iterator end() const noexcept {
		return iterator(this, true);
	}

	const_iterator cbegin() const noexcept {
		return const_iterator(this, false);
	}

	const_iterator cend() const noexcept{
		return const_iterator(this, true);
	}
	iterator find(const K& key) noexcept{
		lock_guard<mutex> guard(mutex_);
		unsigned long hashValue = hashFunc(key);
		node_type* entry = table[hashValue];

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
	const_iterator cfind(const K& key) noexcept{
		lock_guard<mutex> guard(mutex_);
		unsigned long hashValue = hashFunc(key);
		node_type* entry = table[hashValue];
		while (entry != nullptr) {
			if (entry->get_key() == key) {
				const_iterator it(this, false, hashValue);
				return it;

			}
			entry = entry->get_next();
		}
		return cend();
	}
	Hashmap<K, T, TA>() noexcept{

		table = new node_type * [table_size]();
	}
	Hashmap<K, T, TA>(size_t& new_size) noexcept{
		table_size = new_size;
		table = new node_type * [table_size]();
	}

	Hashmap<K, T, TA>(initializer_list<pair<K, T> > list) noexcept {//const TA& alloc
		table = new node_type * [table_size]();
		for (auto it : list) {
			this->insert(it.first, it.second);
			//cout << it.first << endl;
			//cout << it.second << endl;
		}
	}

	Hashmap<K, T, TA>(const Hashmap<K, T, TA>& other) noexcept {
		table = other.table;
		table_size = other.table_size;
	}

	Hashmap<K, T, TA>(Hashmap<K, T, TA>&& other) noexcept {
		table = other.table;
		table_size = other.table_size;
		other.table_size = 0;
		other.table = nullptr;
	}


	

	Hashmap<K, T, TA>& operator=(const Hashmap<K, T, TA>& right) noexcept {
		
		
		if (this != &right)
		{
			table_size = right.table_size;
			t_size = right.t_size;
			for (size_t i = 0; i < table_size; i++) {
				node_type* entry = right.table[i];
				if (entry == nullptr) {
					table[i] = nullptr;
				}
				else {
					node_type* nn = new node_type(entry->get_key(), entry->get_value());
					table[i] = nn;
					
					while (entry != nullptr) {
						node_type* next = new node_type(entry->get_key(), entry->get_value());
						table[i]->set_next(next);

						table[i] = table[i]->get_next();
						entry = entry->get_next();

					}

				}
			}

		}
		return *this;
	}



	Hashmap<K, T, TA>& operator=(Hashmap<K, T, TA>&& right) noexcept{
		if (this != &right)
		{

			table_size = right.table_size;
			t_size = right.t_size;
			for (size_t i = 0; i < table_size; i++) {
				node_type* entry = right.table[i];
				if (entry == nullptr) {
					table[i] = nullptr;
				}
				else {
					node_type* nn = new node_type(entry->get_key(), entry->get_value());
					table[i] = nn;

					while (entry != nullptr) {
						node_type* next = new node_type(entry->get_key(), entry->get_value());
						table[i]->set_next(next);

						table[i] = table[i]->get_next();
						entry = entry->get_next();

					}

				}
			}
			for (size_t i = 0; i < table_size; i++) {
				right.table[i] = nullptr;
			}
			right.table_size = 0;
			right.t_size = 0;
		}

		return *this;
	}


	


	void swap(Hashmap<K, T, TA>& other) noexcept
	{
		std::swap(other.table, this->table);
		std::swap(other.table_size, this->table_size);
		std::swap(other.t_size, this->t_size);

	}

	virtual ~Hashmap() noexcept{
		for (size_t i = 0; i < table_size; i++) {
			node_type* entry = table[i];
			while (entry != nullptr) {
				node_type* prev = entry;
				entry = entry->get_next();
				delete prev;
			}
			table[i] = nullptr;
		}
		delete[] table;
	}



	template <class E, class P>
	void insert(E&& key, P&& t) noexcept{
		lock_guard<mutex> guard(mutex_);

		unsigned long hashValue = hashFunc(key);
		node_type* prev = NULL;
		node_type* entry = table[hashValue];


		while (entry != NULL && entry->get_key() != key) {
			prev = entry;
			entry = entry->get_next();

		}

		if (entry == NULL) {
			entry = new node_type(key, t);

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
	iterator insert_(E&& key, P&& t) noexcept{
		lock_guard<mutex> guard(mutex_);
		unsigned long hashValue = hashFunc(key);

		node_type* prev = NULL;
		node_type* entry = table[hashValue];

		while (entry != NULL && entry->get_key() != key) {
			prev = entry;
			entry = entry->get_next();

		}

		if (entry == NULL) {
			entry = new node_type(key, t);

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



	optional<T> get(const K& key) noexcept{
		lock_guard<mutex> guard(mutex_);
		unsigned long hashValue = hashFunc(key);
		node_type* entry = table[hashValue];

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
	pair<iterator, bool> emplace(Args&&... args) noexcept
	{
		//lock_guard<mutex> guard(mutex_);
		size_t temp_size = t_size;
		iterator it = this->insert_(make_pair(args...).first, make_pair(args...).second);
		if (t_size == temp_size) {
			return make_pair(it, false);
		}
		return make_pair(it, true);
	}

	T& operator[](const K& key)
	{
		lock_guard<mutex> guard(mutex_);
		unsigned long hashValue = hashFunc(key);
		node_type* entry = table[hashValue];

		while (entry != nullptr) {
			if (entry->get_key() == key) {
			
				return entry->get_value();
			}
			entry = entry->get_next();
		}
		throw std::runtime_error("error");

	}
	const T& operator[](const K& key) const
	{
		lock_guard<mutex> guard(mutex_);
		unsigned long hashValue = hashFunc(key);
		node_type* entry = table[hashValue];

		while (entry != nullptr) {
			if (entry->get_key() == key) {

				return entry->get_value();
			}
			entry = entry->get_next();
		}
		throw std::runtime_error("error");

	}
	T& operator[](K&& key)
	{
		lock_guard<mutex> guard(mutex_);
		unsigned long hashValue = hashFunc(key);
		node_type* entry = table[hashValue];

		while (entry != nullptr) {
			if (entry->get_key() == key) {
				return entry->get_value();
			}
			entry = entry->get_next();
		}
		throw runtime_error("error");
	}
	const T& operator[](K&& key) const
	{
		lock_guard<mutex> guard(mutex_);
		unsigned long hashValue = hashFunc(key);
		node_type* entry = table[hashValue];

		while (entry != nullptr) {
			if (entry->get_key() == key) {
				return entry->get_value();
			}
			entry = entry->get_next();
		}
		throw runtime_error("error");
	}



	void remove(const K& key) noexcept{
		lock_guard<mutex> guard(mutex_);
		unsigned long hashValue = hasher(key);
		node_type* prev = NULL;
		node_type* entry = table[hashValue];

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


	bool empty() noexcept {
		lock_guard<mutex> guard(mutex_);
		for (int i = 0; i < table_size; i++) {
			if (table[i] != nullptr)
				return false;
		}
		return true;
	}

	void clear() noexcept{
		lock_guard<mutex> guard(mutex_);
		for (int i = 0; i < table_size; i++) {
			node_type* entry = table[i];
			while (entry != nullptr) {
				node_type* prev = entry;
				entry = entry->get_next();
				delete prev;
			}
			table[i] = nullptr;
		}

	}
	node_type extract(const_iterator position) noexcept
	{
		if (this->cend() != position) {

			unsigned long hashValue = hashFunc(*position);
			node_type* entry = table[hashValue];
			return *entry;

		}
	}

	node_type extract(const K& key) noexcept
	{
		iterator position = this->find(key);
		if (this->end() != position) {
			unsigned long hashValue = hashFunc(*position);
			node_type* entry = table[hashValue];
			return *entry;
		}
	}





};

template<typename H, typename K>
void work(H& map, K k)
{
	cout << map[k] << endl;
}

template<typename H, typename K, typename T>
void work_ins(H& map, K k, T t)
{
	map.insert_(k, t);
}
