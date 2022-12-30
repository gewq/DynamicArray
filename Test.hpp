namespace {
	const int SIZE_INI = 5;

	//Тестовые наборы разных типов для помещения в контейнеры
	const int TEST_DATA_INT [SIZE_INI] = {-11, 98, 0, 4654646, -44696};
	const long TEST_DATA_LONG [SIZE_INI] = {56216516L, 24594561L, -48463123L, 656464L, -14614L};
	const char TEST_DATA_CHAR [SIZE_INI] = {'a', '4', '+', '%', '~'};

	//Элемент отсутствующий в тестовом массиве
	const int ABSENT_INT = 45;
	const int ABSENT_LONG = 166L;
	const int ABSENT_CHAR = 'q';
}


//Тест конструктора по-умолчанию
template <typename T>
static void testDefaultConstructor()
{
	//Конструктор по-умолчанию:
	Array<T>* container = new Array<T>;

	//устанавливает емкость = 1
	//контейнер пуст (size = 0)
	assert(container->getCapacity() == 1);
	assert(container->getSize() == 0);

	delete container;
}



//Тест параметризованного конструктора
template <typename T>
static void testParameterizedConstructor()
{
	//Параметризованный конструктор - принимает значение емкости контейнера
	const int CAPACITY_INI = 156;
	Array<T>* container = new Array<T>(CAPACITY_INI);
	
	assert(container->getCapacity() == CAPACITY_INI);	//устанавливает заданную емкость
	assert(container->getSize() == 0);					//контейнер пуст (size = 0)

	delete container;

	//Тест выброса исключения
//	Array<int> arrayException(-1);
//	Array<int> arrayException(0);
}



//Тест копирующего конструктора
template <typename T>
static void testCopyConstructor(const T* testData)
{
	//Конструктор копирования - принимает объект такого же класса
	//Создаёт копию объекта - все параметры одинаковы

	//Создать объект с которого копировать и заполнить тестовыми значениями
	Array<T>* containerSrc = new Array<T>;
	for (int i=0; i<SIZE_INI; ++i) {
		containerSrc->pushBack(testData[i]);
	}

	//1 вариант создания через копирующий конструктор
	Array<T> containerCopy_1(*containerSrc);
	//Все параметры должны совпадать
	assert(containerCopy_1.getCapacity() == containerSrc->getCapacity());
	assert(containerCopy_1.getSize() == containerSrc->getSize());
	for (int i=0; i<containerCopy_1.getSize(); ++i) {
		assert(containerCopy_1.getValue(i) == containerSrc->getValue(i));
	}

	//2 вариант создания через копирующий конструктор
	Array<T> containerCopy_2 = *containerSrc;
	//Все параметры должны совпадать
	assert(containerCopy_2.getCapacity() == containerSrc->getCapacity());
	assert(containerCopy_2.getSize() == containerSrc->getSize());
	for (int i=0; i<containerCopy_2.getSize(); ++i) {
		assert(containerCopy_2.getValue(i) == containerSrc->getValue(i));
	}

	delete containerSrc;
}



template <typename T>
void testConstructors(const T* testData)
{
	testDefaultConstructor<T>();		//Тест конструктора по-умолчанию
	testParameterizedConstructor<T>();	//Тест параметризованного конструктора
	testCopyConstructor<T>(testData);	//Тест копирующего конструктора
}



template <typename T>
void testResize(const T* testData)
{
	/*
	При увеличении емкости:
	- емкость увеличится
	- размер не изменится
	- доступны все значения изначально помещенные в контейнер

	При уменьшении емкости:
	- емкость уменьшится
	- размер уменьшится до величины емкости
	- элементы находящиеся за пределами новой емкости будут отброшены и недоступны
	*/

	//Подготовить контейнер (создать и заполнить значениями)
	Array<T>* container = new Array<T>;
	for (int i=0; i<SIZE_INI; ++i) {
		container->pushBack(testData[i]);
	}

	//Тест увеличение емкости
	const int CAPACITY_INCREASED = SIZE_INI+253;
	container->resize(CAPACITY_INCREASED);
	
	assert(container->getCapacity() == CAPACITY_INCREASED);	//Емкость увеличится
	assert(container->getSize() == SIZE_INI);				//Размер не изменится
	//Доступны все значения изначально помещенные в контейнер
	for (int i=0; i<container->getSize(); ++i) {
		assert(container->getValue(i) == testData[i]);
	}

	//Тест уменьшение емкости
	const int CAPACITY_DECREASED = SIZE_INI-2;
	container->resize(CAPACITY_DECREASED);
	
	assert(container->getCapacity() == CAPACITY_DECREASED);	//Емкость уменьшится
	assert(container->getSize() == CAPACITY_DECREASED);		//Размер уменьшится до величины емкости
	//Элементы пределах новой емкости доступны
	for (int i=0; i<container->getSize(); ++i) {
		assert(container->getValue(i) == testData[i]);
	}
	//Тест выброс исключения
//	container->resize(-1);
//	container->resize(0);
	//Значения обрезанные resize() недоступны
//	assert(container->getValue(CAPACITY_DECREASED) == testData[CAPACITY_DECREASED]);

	delete container;
}


template <typename T>
void testPushFront(const T* testData)
{
	/*
	Новый элемент помещается в начало контейнера
	При вставке элемента размер контейнера увеличивается на 1
	Вставка элемента в полный контейнер (кол-во элементов = емкости) ->
	удваивает текущую емкость
	*/

	//Начальная емкость < кол-ва вставляемых элементов -> проверить удвоение емкости
	const int CAPACITY_INI = SIZE_INI-1;
	Array<T>* container = new Array<T>(CAPACITY_INI);
	for (int i=0; i<SIZE_INI; ++i) {
		container->pushFront(testData[i]);
	}

	assert(container->getCapacity() == CAPACITY_INI*2);
	assert(container->getSize() == SIZE_INI);
	for (int i=0; i<container->getSize(); ++i) {
		//Значения в контейнере в обратном порядке их добавления
		assert(container->getValue(i) == testData[SIZE_INI-1-i]);
	}

	//Тест выброс исключения (выход за пределы контейнера)
//	container->getValue(-1);
//	container->getValue(SIZE_INI);

	delete container;
}



template <typename T>
void testPushBack(const T* testData)
{
	/*
	Новый элемент помещается в конец контейнера
	При вставке элемента размер контейнера увеличивается на 1
	Вставка элемента в полный контейнер (кол-во элементов = емкости) ->
	удваивает текущую емкость
	*/

	//Начальная емкость < кол-ва вставляемых элементов -> проверить удвоение емкости
	const int CAPACITY_INI = SIZE_INI-1;
	Array<T>* container = new Array<T>(CAPACITY_INI);
	for (int i=0; i<SIZE_INI; ++i) {
		container->pushBack(testData[i]);
	}

	assert(container->getCapacity() == CAPACITY_INI*2);
	assert(container->getSize() == SIZE_INI);
	for (int i=0; i<container->getSize(); ++i) {
		assert(container->getValue(i) == testData[i]);
	}

	//Тест выброс исключения (выход за пределы контейнера)
//	container->getValue(-1);
//	container->getValue(SIZE_INI);

	delete container;
}



template <typename T>
void testPushIndex(const T* testData)
{
	/*
	Новый элемент помещается по заданному индексу
	Индекс 0 - вставить в начало контейнера
	Индекс Size - вставить в конец контейнера
	При вставке элемента размер контейнера увеличивается на 1
	Вставка элемента в полный контейнер (кол-во элементов = емкости) ->
	удваивает текущую емкость
	*/

	//Начальная емкость < кол-ва вставляемых элементов -> проверить удвоение емкости
	const int CAPACITY_INI = SIZE_INI-1;
	Array<T>* container = new Array<T>(CAPACITY_INI);

	container->push(testData[0], 0);								//Вставить в начало
	container->push(testData[SIZE_INI-1], container->getSize());	//Вставить в конец
	//Вставить в середину
	for(int i=1; i<SIZE_INI-1; ++i) {
		container->push(testData[i], i);
	}

	assert(container->getCapacity() == CAPACITY_INI*2);
	assert(container->getSize() == SIZE_INI);

	for (int i=0; i<container->getSize(); ++i) {
		assert(container->getValue(i) == testData[i]);
	}

	//Тест выброс исключения (выход за пределы контейнера)
//	container->getValue(-1);
//	container->getValue(SIZE_INI);
}



template <typename T>
void testEquality(const T* testData)
{
	/*
	При присваивании объекта самому себе его свойства не меняются
	По результатам присваивания все параметры двух контейнеров одинаковы
	*/

	//Создать два разных контейнера
	const int CAPACITY_INI = SIZE_INI;
	Array<T> containerSrc = Array<T>(CAPACITY_INI);
	Array<T> containerDst;
	//Первый контейнер заполняем значениями
	for (int i=0; i<SIZE_INI; ++i) {
		containerSrc.pushBack(testData[i]);
	}

	//Тест присваивание объекта самому себе
	containerSrc = containerSrc;
	assert(containerSrc.getCapacity() == CAPACITY_INI);
	assert(containerSrc.getSize() == SIZE_INI);
	for (int i=0; i<containerSrc.getSize(); ++i) {
		assert(containerSrc.getValue(i) == testData[i]);
	}

	containerDst = containerDst;
	assert(containerDst.getCapacity() == 1);
	assert(containerDst.getSize() == 0);
	//Тест выброс исключения (выход за пределы контейнера)
//	assert(containerDst.getValue(0) == testData[0]);

	//Тест присваивание другого объекта
	containerDst = containerSrc;
	//Проверить равенство всех параметров
	assert(containerDst.getCapacity() == containerSrc.getCapacity());
	assert(containerDst.getSize() == containerSrc.getSize());
	for (int i=0; i<containerDst.getSize(); ++i) {
		assert(containerDst.getValue(i) == containerSrc.getValue(i));
	}
}



template <typename T>
void testRemove(const T* testData)
{
	/*
	Удалить элемент по заданному индексу
	При удалении элемента размер контейнера уменьшается на 1
	При удалении из пустого контейнера ничего не происходит
	*/

	//Создать контейнер и заполнить значениями
	const int CAPACITY_INI = SIZE_INI;
	Array<T>* container = new Array<T>(CAPACITY_INI);
	for (int i=0; i<SIZE_INI; ++i) {
		container->pushBack(testData[i]);
	}

	//Удалить элемента из начала контейнера
	container->remove(0);
	assert(container->getCapacity() == CAPACITY_INI);	//Емкость не изменилась
	assert(container->getSize() == SIZE_INI-1);			//Размер уменьшился

	//Удалить элемента из конца контейнера
	container->remove(container->getSize()-1);
	assert(container->getCapacity() == CAPACITY_INI);	//Емкость не изменилась
	assert(container->getSize() == SIZE_INI-2);			//Размер уменьшился

	//Удалить элемент из середины контейнера
	int indexDelete = container->getSize()/2;
	container->remove(indexDelete);
	assert(container->getCapacity() == CAPACITY_INI);	//Емкость не изменилась
	assert(container->getSize() == SIZE_INI-3);			//Размер меньше на 3 (третье удаление)
	for (int i=0; i<container->getSize(); ++i) {
		//До удаляемого элемента индексы как и были с прошлого удаления
		if (i < indexDelete) {
			assert(container->getValue(i) == testData[i+1]);
		}
		//После смещаются ещё на один
		else {
			assert(container->getValue(i) == testData[i+2]);
		}
	}

	//Удалить из пустого контейнера
	Array<T>* containerEmpty= new Array<T>;
	containerEmpty->remove(0);
	assert(containerEmpty->getCapacity() == 1);
	assert(containerEmpty->getSize() == 0);

	//Тест выброс исключения (выход за пределы контейнера)
//	container->remove(-1);
//	container->remove(CAPACITY_INI+100);

	delete container;
	delete containerEmpty;
}



template <typename T>
void testFind(const T* testData)
{
	/*
	Поиск элемента по заданному значению
	Возвращает индекс первого элемента с заданным значением
	Если ни один элемент не найден - возвращает size+1
	*/

	//Создать контейнер и заполнить значениями
	const int CAPACITY_INI = SIZE_INI;
	Array<T>* container = new Array<T>(CAPACITY_INI);
	for (int i=0; i<SIZE_INI; ++i) {
		container->pushBack(testData[i]);
	}

	for (int i=0; i<container->getSize(); ++i) {
		assert(container->findValue(testData[i]) == i);
	}
	//Элемент отсутствует в контейнере
	assert(container->findValue(ABSENT_INT) == container->getSize()+1);

	delete container;
}



template <typename T>
void testIsEmpty(const T* testData)
{
	/*
	Если контейнер пуст - возвращает true
	Если контейнер не пуст - возвращает false
	*/

	//Тест пустой контейнер
	Array<T>* container = new Array<T>;
	assert(container->isEmpty() == true);

	//Тест не пустой контейнер
	for (int i=0; i<SIZE_INI; ++i) {
		container->pushBack(testData[i]);
	}
	assert(container->isEmpty() == false);

	delete container;
}



template <typename T>
void testClear(const T* testData)
{
	/*
	Очищает контейнер от элементов
	- емкость не изменяется
	- кол-во элементов = 0
	При очистке пустого контейнера ничего не происходит
	*/

	//Создать контейнер и заполнить значениями
	const int CAPACITY_INI = SIZE_INI;
	Array<T>* container = new Array<T>(CAPACITY_INI);
	for (int i=0; i<SIZE_INI; ++i) {
		container->pushBack(testData[i]);
	}

	//Тест очистка непустого контейнера
	container->clear();
	assert(container->getCapacity() == CAPACITY_INI);
	assert(container->getSize() == 0);
	assert(container->isEmpty() == true);

	//Тест очистка пустого контейнера
	container->clear();
	assert(container->getCapacity() == CAPACITY_INI);
	assert(container->getSize() == 0);
	assert(container->isEmpty() == true);
}