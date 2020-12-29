#include "pch.h"
#include <optional>
#include "../hashmap/hash.h"
//#include "../hashmap/node.h"
TEST(Test1, TestName1) {
	Hashmap<int, double> map;
	EXPECT_EQ(map.size(), 0);
	map.insert(1, 0.5);
	EXPECT_EQ(map.size(), 1);
}
TEST(Test2, TestName2) {
	Hashmap<int, double> map;
	map.insert(1, 0.5);
	EXPECT_EQ(map[1], 0.5);
}

TEST(Test3, TestName3) {
	Hashmap<int, double> map;
	map.insert(1, 0.5);
	EXPECT_EQ(map.size(), 1);
	map.insert(1, 0.7);
	EXPECT_EQ(map.size(), 1);
	auto emp = map.emplace(1, 0.8);
	EXPECT_EQ(emp.second,false);
	auto emp1 = map.emplace(2, 0.8);
	EXPECT_EQ(emp1.second, true);
}


TEST(Test4, TestName4) {
	Hashmap<int, double> map;
	map.insert(1, 0.5);
	map[1] = 0.6;
	EXPECT_EQ(map[1], 0.6);
}
TEST(Test5, TestName5) {
	Hashmap<int, double> map1{ pair(1, 0.1) };
	Hashmap<int, double> map2{ pair(1, 0.2), pair(2, 0.3) };

	map1 = map2;

	EXPECT_EQ(map1.size(), map2.size());
}

TEST(Test6, TestName6) {
	Hashmap<int, double> map1{ pair(1, 0.1) };
	Hashmap<int, double> map2{ pair(1, 0.2), pair(2, 0.3) };

	map1.swap(map2);

	EXPECT_EQ(map1.size(), 2);
	EXPECT_EQ(map2.size(), 1);

}
TEST(Test7, TestName7) {
	using map_type = Hashmap<char, double, allocator<pair<char, double>>>;
	map_type map {pair('b',42.14),pair('a',0.1)};
	int count = 100;
	while (count > 0) {
		vector<thread*> threads(count);
		for (size_t i = 0; i < threads.size(); ++i) { 
			threads[i] = new thread(work_ins<map_type, char, double>, ref(map), 'b', 0.875);
		}
		for (size_t i = 0; i < threads.size(); ++i) { 
			threads[i]->join();
			ASSERT_EQ(map['b'], 0.875);
			delete threads[i];
			--count;
		}
	}
}