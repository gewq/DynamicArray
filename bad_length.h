/**
\file bad_length.h
\brief Класс bad_length - для обработки исключения "некорректная емкость массива"

Класс bad_length наследует у класса std::exception и перегружает метод what()
*/

#pragma once
#ifndef BAD_LENGTH_H_SENTRY
#define BAD_LENGTH_H_SENTRY

#include <string>
#include <exception>

class bad_length : public std::exception {
	public:
		/**
		Конструктор по-умолчанию не имеет смысла - поэтому удалён.
		*/
		bad_length() = delete;
					 
		/**
		Параметризованный конструктор. На основе переданного значения емкости
		формирует строку об ошибке
		\param[in] capacity Емкость массива
		*/
		explicit bad_length(int capacity);

		/**
		Перегруженный метод базового класса std::exception
		\return Указатель на сообщение об ошибке
		*/
		virtual const char* what() const noexcept override;

	private:
		std::string errorMessage_;	///<Сообщение об ошибке
};

#endif