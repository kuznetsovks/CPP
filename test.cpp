#include "pch.h"
#include <optional>
#include "../hashmap/hash.h"
//#include "../hashmap/node.h"
TEST(Test1, TestName1) {
	Hashmap<string, int> map;
	EXPECT_EQ(map.size(), 0);
	map.insert("sentence", 5);
	EXPECT_EQ(map.size(), 1);
}
TEST(Test2, TestName2) {
	Hashmap<string, int> map;
	map.insert("sentence", 5);
	EXPECT_EQ(map["sentence"], 5);
}

TEST(Test3, TestName3) {
	Hashmap<string, int> map;
	map.insert("sentence", 5);
	EXPECT_EQ(map.size(), 1);
	map.insert("sentence", 7);
	EXPECT_EQ(map.size(), 1);
	auto emp = map.emplace("sentence", 8);
	EXPECT_EQ(emp.second,false);
	auto emp1 = map.emplace("not sentence", 8);
	EXPECT_EQ(emp1.second, true);
}


TEST(Test4, TestName4) {
}
