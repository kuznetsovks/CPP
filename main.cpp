
#include <iostream>
using namespace std;
#include "hash.h"

int main()
{
	
	//Hashmap<char, double> map = Hashmap<char, double>();
	//Hashmap<char, double> map {pair('b',42.14),pair('a',0.1)};
	//Hashmap<char, double, allocator<pair<char, double>>> map = Hashmap<char, double, allocator<pair<char, double>>>();
	//map.insert('a', 5.0);
	Hashmap<int, double> map1{ pair(1, 0.1) };
	Hashmap<int, double> map2{ pair(1, 0.2), pair(3, 0.3) };
	cout << "size1=" << map1.size() << endl;
	cout << "size2=" << map2.size() << endl;

	map1.swap( map2);
	cout << map2[1] << endl;

	
	/*thread t1(work<Hashmap<char, double, allocator<pair<char, double>>>, char>, ref(map), 'a');
	thread t2(work<Hashmap<char, double, allocator<pair<char, double>>>, char>, ref(map), 'a');
	thread t3(work<Hashmap<char, double, allocator<pair<char, double>>>, char>, ref(map), 'a');
	thread t4(work<Hashmap<char, double, allocator<pair<char, double>>>, char>, ref(map), 'a');
	thread t5(work_ins<Hashmap<char, double, allocator<pair<char, double>>>, char, double>, ref(map), 'b', 0.875);
	thread t6(work_ins<Hashmap<char, double, allocator<pair<char, double>>>, char, double>, ref(map), 'b', 0.875);
	thread t7(work_ins<Hashmap<char, double, allocator<pair<char, double>>>, char, double>, ref(map), 'b', 0.875);
	thread t8(work<Hashmap<char, double, allocator<pair<char, double>>>, char>, ref(map), 'b');
	thread t9(work<Hashmap<char, double, allocator<pair<char, double>>>, char>, ref(map), 'b');
	thread t10(work<Hashmap<char, double, allocator<pair<char, double>>>, char>, ref(map), 'b');
	thread t11(work<Hashmap<char, double, allocator<pair<char, double>>>, char>, ref(map), 'b');
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	t6.join();
	t7.join();
	t8.join();
	t9.join();
	t10.join();
	t11.join();*/
	/*int count = 100;
	while (count > 0) {
		std::vector<thread*> threads(10);
		for (size_t i = 0; i < threads.size(); ++i) { // Start appropriate number of threads
			threads[i] = new thread(work_ins<Hashmap<char, double, allocator<pair<char, double>>>, char, double>, ref(map), 'b', 0.875);
		}
		for (size_t i = 0; i < threads.size(); ++i) { // Wait for all threads to finish
			threads[i]->join();
			delete threads[i];
			--count;
		}
	}	
	count = 100;
	while (count > 0) {
		std::vector<thread*> threads(10);
		for (size_t i = 0; i < threads.size(); ++i) { // Start appropriate number of threads
			threads[i] = new thread(work<Hashmap<char, double, allocator<pair<char, double>>>, char>, ref(map), 'b');
		}
		for (size_t i = 0; i < threads.size(); ++i) { // Wait for all threads to finish
			threads[i]->join();
			delete threads[i];
			--count;
		}
	}*/
	//Hashmap<char, double> map2 = Hashmap<char, double>();
	//std::cout << map.empty() << std::endl;
	//map.insert<char, double>('a', 37123.123);
	//double a = 0.5;
	//map['a'] = a;
	//cout << map['a'] << endl;
	//map2.insert<char, double>('b', 7.3241);
	///cout << map['b'] << endl;

	//cout << map['a'] << endl;
	//char j = 'f';
	//Hashmap<char, double> map1{ std::make_pair('f', 9.8)};
	//Hashmap<char, double>::const_iterator it(map1.cfind('f'));
	//auto pair = map1.extract(j);
	//pair.print();

	/*Hashmap<char, double>::iterator begin = map.begin();
	Hashmap<char, double>::iterator end = map.end();
	Hashmap<char, double>::iterator it = begin;
	while (it != end) {
		if (it != begin)
			cout << ", " ;
		cout << *it ;
		cout << map[*it] ;
		//cout << endl;
		++it;
	}
	*/
	//auto qwe = map.emplace('c', 4.6);
	///cout << *qwe.first << map[*qwe.first] << endl;
	//cout << qwe.second << endl;
	//cout << map.size() << endl;
	//Hashmap<char, double>::iterator it2 = map.insert_('a',5.9);
	//cout << map[*it2] << endl;
	//cout << *it1.first<< endl;
	//auto it1 = map.find('a');
	//cout << map[*it1];
	//cout << it1.first << " " << it1.second << endl;
	//cout << map2['b'] << endl;
	//map.swap(map2);
	//cout << map['b'] << endl;
	//cout << map2['a'] << endl;
	/*std::cout << map['a'] << std::endl;
	std::cout << map['e'] << std::endl;
	double p = 12312321323;
	std::cout << *map.get('a', p) << std::endl;
	std::cout << map.empty() << std::endl;
	map.clear();
	std::cout << map.empty() << std::endl;
	map.insert<char, int>('a', 5);
	std::cout << map.empty() << std::endl;*/
	//std::cout << map.empty() << std::endl;
}
