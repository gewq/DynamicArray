//Public методы========================================================
template <typename T>
Array<T>::Array():capacity_(1), size_(0)
{
	data_ = new T [capacity_];
}



template <typename T>
Array<T>::Array(int capacity):capacity_(capacity), size_(0)
{
	//Некорректная емкость
	if (capacity <= 0) {
		throw bad_length(capacity);
	}
	data_ = new T [capacity_];
}



template <typename T>
Array<T>::Array(const Array& other)
{
	capacity_ = other.capacity_;
	size_ = other.size_;
	data_ = new T [capacity_];
	//Скопировать массив
	for (int i = 0; i < size_; ++i) {
		data_[i] = other.data_[i];
	}
}


template <typename T>
Array<T>::~Array()
{
	delete[] data_;
}


template <typename T>
Array<T>& Array<T>::operator=(const Array& other)
{
	//Присваивание объекта самому себе
	if (this == &other) {
		return *this;
	}
	size_ = other.size_;
	capacity_ = other.capacity_;
	delete[] data_;

	data_ = new T [capacity_];
	//Скопировать массив
	for (int i = 0; i < size_; ++i) {
		data_[i] = other.data_[i];
	}
	return *this;
}


template <typename T>
bool Array<T>::isEmpty() const
{
	if (size_ == 0) {
		return true;
	}
	return false;
}


template <typename T>
int Array<T>::getCapacity() const
{
	return capacity_;
}



template <typename T>
int Array<T>::getSize() const
{
	return size_;
}



template <typename T>
T Array<T>::getValue(int index) const
{
	//Индекс за пределами массива
	if ((index < 0) || (index > size_ - 1)) {
		throw bad_range(index);
	}
	return data_[index];
}


template <typename T>
void Array<T>::resize(int capacity)
{
	//Некорректная емкость
	if (capacity <= 0) {
		throw bad_length(capacity);
	}
	capacity_ = capacity;
	if (capacity < size_) {
		size_ = capacity;
	}

	//Выделить новую память
	T* newData = new T[capacity_];
	//Скопировать массив
	for (int i = 0; i < size_; ++i) {
		newData[i] = data_[i];
	}
	//Освободить память текущего массива
	delete[] data_;
	//Указать на новый массив
	data_ = newData;
}



template <typename T>
void Array<T>::pushFront(T value)
{
	//Массив уже полон
	if (size_ == capacity_) {
		resize(size_*2);
	}
	//Сместить все элементы на 1 вперед, начиная с 1-го (индекс-0)
	moveForward(0);

	data_[0] = value;
	++size_;
}



template <typename T>
void Array<T>::pushBack(T value)
{
	//Массив уже полон
	if (size_ == capacity_) {
		resize(size_*2);
	}

	data_[size_] = value;
	++size_;
}



template <typename T>
void Array<T>::push(T value, int index)
{
	//Индекс за пределами массива
	if ((index < 0) || (index > size_)) {
		throw bad_range(index);
	}
	//Вставить в начало
	if (index == 0) {
		pushFront(value);
	}
	//Вставить в конец
	else if (index == size_) {
		pushBack(value);
	}
	else {
		//Массив уже полон
		if (size_ == capacity_) {
			resize(size_*2);
		}
		//Сместить все элементы на 1 вперед, начиная с index
		moveForward(index);
		data_[index] = value;
		++size_;
	}
}



template <typename T>
void Array<T>::remove(int index)
{
	//Индекс за пределами массива
	if ((index < 0) || (index > size_)) {
		throw bad_range(index);
	}
	//Массив НЕ пуст
	if (size_ > 0) {
		moveBack(index);
		--size_;
	}
}



template <typename T>
void Array<T>::clear()
{
	size_ = 0;
}



template <typename T>
int Array<T>::findValue(T value)
{
	for (int i = 0; i < size_; ++i) {
		if (data_[i] == value) {
			return i;	//Выход потому что нужен первый элемент
		}
	}
	return size_+1;
}



//Pivate методы========================================================
template <typename T>
void Array<T>::moveForward(int index)
{
	//Индекс за пределами массива
	if ((index < 0) || (index > size_)) {
		throw bad_range(index);
	}
	//Сместить все элементы на 1 вперед
	for (int i = size_; i > index; --i) {
		data_[i] = data_[i - 1];
	}
}



template <typename T>
void Array<T>::moveBack(int index)
{
	//Индекс за пределами массива
	if ((index < 0) || (index > size_)) {
		throw bad_range(index);
	}
	//Сместить все элементы на 1 назад
	for (int i = index; i < size_; ++i) {
		data_[i] = data_[i + 1];
	}
}