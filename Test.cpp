#include "Test.h"

//Тестируемый контейнер - шаблонный класс, может работать с разными
//типами данных. Поэтому тестируются разные типы данных. Для этого
//функции тестирования шаблонные.

#include "Test.hpp"	//Шаблоны функций тестирования


void testConstructors()
{
	testConstructors<int>(TEST_DATA_INT);
	testConstructors<long>(TEST_DATA_LONG);
	testConstructors<char>(TEST_DATA_CHAR);
}



void testResize()
{
	testResize<int>(TEST_DATA_INT);
	testResize<long>(TEST_DATA_LONG);
	testResize<char>(TEST_DATA_CHAR);
}



void testPushFront()
{
	testPushFront<int>(TEST_DATA_INT);
	testPushFront<long>(TEST_DATA_LONG);
	testPushFront<char>(TEST_DATA_CHAR);
}



void testPushBack()
{
	testPushBack<int>(TEST_DATA_INT);
	testPushBack<long>(TEST_DATA_LONG);
	testPushBack<char>(TEST_DATA_CHAR);
}



void testPushIndex()
{
	testPushIndex<int>(TEST_DATA_INT);
	testPushIndex<long>(TEST_DATA_LONG);
	testPushIndex<char>(TEST_DATA_CHAR);
}



void testEquality()
{
	testEquality<int>(TEST_DATA_INT);
	testEquality<long>(TEST_DATA_LONG);
	testEquality<char>(TEST_DATA_CHAR);
}



void testRemove()
{
	testRemove<int>(TEST_DATA_INT);
	testRemove<long>(TEST_DATA_LONG);
	testRemove<char>(TEST_DATA_CHAR);
}



void testFind()
{
	testFind<int>(TEST_DATA_INT);
	testFind<long>(TEST_DATA_LONG);
	testFind<char>(TEST_DATA_CHAR);
}



void testIsEmpty()
{
	testIsEmpty<int>(TEST_DATA_INT);
	testIsEmpty<long>(TEST_DATA_LONG);
	testIsEmpty<char>(TEST_DATA_CHAR);
}



void testClear()
{
	testClear<int>(TEST_DATA_INT);
	testClear<long>(TEST_DATA_LONG);
	testClear<char>(TEST_DATA_CHAR);
}