/**
\file main.cpp
\brief Контейнер - динамический массив данных произвольного типа, поддерживающих операцию ==

Функция main() содержит функции тестирования класса Array.

Array представляет собой контейнер - динамический массив

Функциональность контейнера Array:
	- создать контейнер
	- скопировать контейнер
	- получить доступ к любому элементу контейнера по индексу
	- изменить размер контейнера
	- вставить элемент в контейнер
	- удалить элемент из контейнера
	- вставить элемент в начало
	- вставить элемент в конец
	- поиск элемента в контейнере по значению

Поддерживаются исключения:
	- не удалось выделить память
	- некорректная ёмкость (<= 0)
	- обращение по некорректному индексу (выход за границы массива)
*/

#include <iostream>
#include <exception>

#include "Array.h"	//Динамический массив данных
#include "Test.h"	//Модуль тестирования класса



int main()
{
	try {
		testConstructors();
		testResize();
		testPushFront();
		testPushBack();
		testPushIndex();
		testEquality();
		testRemove();
		testFind();
		testIsEmpty();
		testClear();
	}
	catch (std::bad_alloc& error) {
		std::cerr << "Allocation failed: " << error.what() << std::endl;
	}
	catch (const bad_range& error) {
		std::cerr << error.what() << std::endl;
	}
	catch (const bad_length& error) {
		std::cerr << error.what() << std::endl;
	}
	catch (std::exception& error) {
		std::cerr << error.what() << std::endl;
	}
	catch (...) {
		std::cerr << "Undefined exception" << std::endl;
	}

	return EXIT_SUCCESS;
}