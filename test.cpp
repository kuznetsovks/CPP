#include "pch.h"
#include "../../reference.h"
#include "../../reference.cpp"
#include "../../RNA.h"
#include "../../RNA.cpp"
#include "../../RNA.h"

TEST(TestCaseName1, TestName1) {
  RNA a(A,1);
  EXPECT_EQ(a.contsize, 1);

}
TEST(TestCaseName2, TestName2) {
	RNA a(A, 1);
	RNA b(A, 1);
	EXPECT_TRUE(b==a);
	EXPECT_FALSE(b != a);
}
TEST(TestCaseName3, TestName3) {
	RNA a(A, 2);
	RNA b(C, 15);
	b[14] = a[1];

	EXPECT_EQ(b.cardinality(C), 14);
}

TEST(TestCaseName4, TestName4) {
	RNA  c(G, 16);
	RNA  d(C, 16);
	c.isComplementary(d);
	EXPECT_TRUE(c.isComplementary(d));
}
TEST(TestCaseName5, TestName5) {
	RNA  a(G, 15);
	a.trim(5);
	EXPECT_EQ(a.contsize, 5);
}
TEST(TestCaseName6, TestName6) {
	RNA  a(G, 15);
	RNA  b(G, 15);
	a.split(5, 1);
	b.split(5, 0);
	EXPECT_EQ(a.contsize, 5);
	EXPECT_EQ(b.contsize, 10);
}
TEST(TestCaseName7, TestName7) {
	RNA  a(G, 15);
	RNA  b(C, 15);
	RNA e = a + b;
	EXPECT_EQ(e.contsize, 30);
	EXPECT_EQ(e.cardinality(G), 15);
	EXPECT_EQ(e.cardinality(C), 15);
}
TEST(TestCaseName8, TestName8) {
	RNA a(A, 14);
	EXPECT_EQ(a.length(), 14);

}
TEST(TestCaseName9, TestName9) {
	RNA  c(C, 16);
	RNA  d(C, 16);
	!c;
	c.isComplementary(d);
	EXPECT_TRUE(c.isComplementary(d));
}

TEST(TestCaseName10, TestName10) {
	RNA  a(C, 10);
//	unsigned int start_time = clock();
	for (size_t i = a.length(); i < 1000000; i++)
	{
		a.push_back(G);
	}

//	unsigned int end_time = clock();
	EXPECT_EQ(a.contsize, 1000000);
}

