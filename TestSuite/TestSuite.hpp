#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <string>

#include <Windows.h>

#ifdef TESTSUITE_EXPORTS
#define TESTSUITE_API __declspec(dllexport)
#else
#define TESTSUITE_API __declspec(dllimport)
#endif



class TestSuite;
TESTSUITE_API TestSuite& getSuite();


class TESTSUITE_API TestClassBase
{
public:
	TestClassBase(std::string Class, std::string Function);

	std::string getClass();
	std::string getFunction();
	virtual void testBody() = 0;
private:
	std::string ClassName;
	std::string FunctionName;
	TestSuite* pTestRunner;
};


class TESTSUITE_API TestSuite
{
	friend class TestClassBase;
public:
	TestSuite();
	void runAllTests();
	void results();

	void pause();

	bool m_passed;

	void test();
	void line();
	void run();
	void ok();
	void fail();
	void failSilent();

	void setBlue();
	void setGreen();
	void setRed();
	void setWhite();

	int conditionsFailed;
	int testsFailed;

private:
	void give(TestClassBase* instance);
	std::map<std::string, std::vector<TestClassBase*> > m_tests;
	HANDLE hConsole;

	int totalTests;
};

#define EXPECT(value, compare, expected) \
    if(value compare expected) \
				{} \
								else \
	{ \
		if(getSuite().m_passed) \
		{ \
            getSuite().m_passed = false; \
			getSuite().testsFailed++; \
		} \
	    getSuite().fail(); \
		std::cout << " Expected " << #value << " " << #compare << " " << expected << " but " << #value << " was " << value << "\n\n"; \
		getSuite().conditionsFailed++; \
    } \

#define TEST_INST(Class, Function) \
	test_##Class##_##Function

#define CLASS_NAME(Class, Function) \
	Class##_##Function



#define TEST(Class, Function) \
	class CLASS_NAME(Class, Function) : public TestClassBase \
	{ \
	public: \
		CLASS_NAME(Class, Function)() : TestClassBase(#Class, #Function) \
		{ \
		} \
		virtual void testBody(); \
	} TEST_INST(Class, Function); \
	void CLASS_NAME(Class, Function)::testBody()





