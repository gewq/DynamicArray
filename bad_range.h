/**
\file bad_range.h
\brief Класс bad_range - для обработки исключения "некорректный индекс - выход за пределы массива"

Класс bad_range наследует у класса std::exception и перегружает метод what()
*/

#pragma once
#ifndef BAD_RANGE_H_SENTRY
#define BAD_RANGE_H_SENTRY

#include <string>
#include <exception>

class bad_range : public std::exception {
	public:
		/**
		Конструктор по-умолчанию не имеет смысла - поэтому удалён.
		*/
		bad_range() = delete;

		/**
		Параметризованный конструктор. На основе переданного значения индекса
		формирует строку об ошибке
		\param[in] index Индекс
		*/
		explicit bad_range(int index);

		/**
		Перегруженный метод базового класса std::exception
		\return Указатель на сообщение об ошибке
		*/
		virtual const char* what() const noexcept override;

	private:
		std::string errorMessage_;	///<Сообщение об ошибке
};

#endif