#pragma once

#include "TestSuite.hpp"
#include "OOCore.hpp"

const std::string validValue = "val";

TEST(String, toInt, "To Int")
{
	String s;
	int val;

	s = "0";
	val = s.toInt();
	EXPECT(val, == , 0);

	s = "10";
	val = s.toInt();
	EXPECT(val, == , 10);
}
TEST(String, toFloat, "To Float")
{
	String s;
	s = "45.00";
	float val = s.toFloat();
	EXPECT(val, == , 45);
	s = "45.56";
	val = s.toFloat();
	EXPECT(val, == , 45.56f);
}
TEST(String, toDouble, "To Double")
{
	String s;
	s = "45.123456789";
	double val = s.toDouble();
	EXPECT(val, == , 45.123456789);
}
TEST(String, fromInt, "From Int")
{
	String s;
	s.from(0);
	EXPECT(s, == , "0");
	s.from(10);
	EXPECT(s, == , "10");
	s.from(1678);
	EXPECT(s, == , "1678");
	unsigned short b = 1678;
	String l(b);
	EXPECT(l, == , "1678");
}
TEST(String, fromFloat, "From Float")
{
	String s;
	s.from(2.00f);
	EXPECT(s, == , "2");
	s.from(2.56f);
	EXPECT(s, == , "2.56");
	String l(2.56f);
	EXPECT(l, == , "2.56");
}
TEST(String, fromDouble, "From Double")
{
	String s;
	s.from(2.4784);
	EXPECT(s, == , "2.4784");
	String l(2.4784);
	EXPECT(l, == , "2.4784");
}
TEST(String, fromStdStringAssign, "From std::string Assignment")
{
	std::string orig = validValue;
	String s = orig;
	EXPECT(s, == , validValue);
}
TEST(String, fromStdStringConstruct, "From std::string Construct")
{
	std::string orig = validValue;
	String s(orig);
	EXPECT(s, == , validValue);
}
TEST(String, toStdStringAssign, "To std::string Assign")
{
	String orig = validValue;
	std::string s = orig;
	EXPECT(s, == , validValue);
}
TEST(String, toStdStringConstruct, "To std::string Construct")
{
	String orig = validValue;
	std::string s(orig);
	EXPECT(s, == , validValue);
}
