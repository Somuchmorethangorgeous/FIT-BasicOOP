#pragma once

#include <iostream>

template <typename T>
class CircularBuffer {

    T* buffer;
    int m_capacity, m_size, head, tail;

public:
    using value_type = T;

    CircularBuffer(){
        m_capacity = 1;
        m_size = 0;
        buffer = new value_type;
        head = tail = -1;
    }

    ~CircularBuffer() { delete[] buffer; }

    CircularBuffer(const CircularBuffer &cb) {
        m_size = cb.size();
        m_capacity = cb.capacity();
        head = cb.head;
        tail = cb.tail;
        buffer = new value_type[m_capacity];
        for (auto i = 0; i < m_capacity; ++i)
            buffer[i] = cb.buffer[i];
    }

    //Конструирует буфер заданной ёмкости, целиком заполняет его элементом
    CircularBuffer(int capacity, const T &elem) {
        m_size = m_capacity = capacity;
        buffer = new value_type[m_capacity];
        for (auto i = 0; i < m_capacity; ++i)
            buffer[i] = elem;
        head = 0;
        tail = capacity - 1;
    }

    //Конструирует буфер заданной ёмкости.
    explicit CircularBuffer(int capacity) {
        m_capacity = capacity;
        m_size = 0;
        head = tail = -1;
        buffer = new value_type[capacity];
    }


    //Оператор присваивания.
    CircularBuffer &operator=(const CircularBuffer &cb) {
        if (this == &cb)
            return *this;
        delete [] buffer;
        m_capacity = cb.capacity();
        m_size = cb.size();
        head = cb.head;
        tail = cb.tail;
        buffer = new value_type[m_capacity];
        for (auto i = 0; i < m_capacity; ++i)
            buffer[i] = cb.buffer[i];
        return *this;
    }

    //Доступ по индексу. Не проверяют правильность индекса.
    T &operator[] (const int i) { return buffer[i]; }

    const T &operator[] (int i) const { return buffer[i]; }

    //Доступ по индексу. Методы бросают исключение в случае неверного индекса.
    T &at(const int i) {
        if ((i < 0) || (i >= capacity()))
            throw std::out_of_range("Wrong index");
        return operator[](i);
    }

    const T& at(int i) const {
	    if ((i < 0) || (i >= capacity()))
	        throw std::out_of_range("Wrong index");
	    return operator[](i);
	}

	//Ссылка на первый элемент
    T& front() {
        if (empty())
            throw std::out_of_range("Buffer is empty");
        return at(head);
    }

	const T& front() const {
        if (empty())
            throw std::out_of_range("Buffer is empty");
        return at(head);
    }

	//Ссылка на последний элемент.
    T& back() { return at(tail); }
	const T& back() const { return at(tail); };

	//Количество элементов, хранящихся в буфере.
    int size() const { return m_size; }

	//ёмкость буфера
    int capacity() const { return m_capacity; }

	//Количество свободных ячеек в буфере.
    int reserve() const { return capacity() - size(); }

	//true, если size() == capacity().
    bool full() const { return !reserve(); }

	//Проверяем, пустой ли буфер (если ёмкость = 0, то false)
    bool empty() const { return reserve() == capacity(); }

	//Добавляет элемент в конец буфера.
	//Если текущий размер буфера равен его ёмкости, то переписывается
	//первый элемент буфера (т.е., буфер закольцован).
	void push_back(const T& item = T()){
        if (full()) {
            tail = head;
            head = (head + 1) % capacity();
        } else {
            if (empty())
                head = tail = 0;
            else
                ++tail;
            ++m_size;
        }
        back() = item;
    }

	//Добавляет новый элемент перед первым элементом буфера.
	//Аналогично push_back, может переписать последний элемент буфера.
	void push_front(const T& item = T()) {
        if (full()) {
            head = tail--;
        } else {
            if (empty()) {
                head = tail = 0;
            } else
                --head;
            ++m_size;
        }
        if (head < 0)
            head += capacity();
        if (tail < 0)
            tail += capacity();
        front() = item;
    }


	//удаляет последний элемент буфера.
	void pop_back(){
        if (empty())
            throw std::runtime_error ("Buffer is empty!");
        --m_size;
        value_type* new_buffer = new T[m_capacity - 1];
        if (size() > 0) {
            for (auto i = head, k = 0; i != tail; i = (i + 1) % capacity(), ++k)
                new_buffer[k] = at(i);
            if (!is_linearized()) {
                tail -= head;
                head = 0;
            } else
                --tail;
            --m_capacity;
            if (tail < 0)
                tail += capacity();
        }
        delete [] buffer;
        buffer = new_buffer;
    }


	//удаляет первый элемент буфера.
	void pop_front(){
        if (empty())
            throw std::runtime_error("Buffer is empty!");
        --m_size;
        value_type* new_buffer = new T[m_capacity - 1];
        if (size() > 0) {
            for (auto i = head + 1, k = 0; i != head; i = (i + 1) % capacity(), ++k)
                new_buffer[k] = at(i);
            if (!is_linearized()) {
                tail -= head;
                head = 0;
            } else
                --tail;
            --m_capacity;
            if (tail < 0)
                tail += capacity();
        }
        delete [] buffer;
        buffer = new_buffer;
    }

	//Сдвигает буфер так, что по нулевому индексу окажется элемент
	//с индексом new_begin.
	void rotate(int new_start) {
        at(new_start);
        if (capacity() == 1)
            return;
        int k = 0;
        while (k < new_start) {
            int tmp = buffer[0];
            for (auto i = 0; i < capacity() - 1; ++i) {
                buffer[i] = buffer[i + 1];
            }
            buffer[capacity() - 1] = tmp;
            ++k;
        }
    }
	
	//Линеаризация - сдвинуть кольцевой буфер так, что его первый элемент
	//переместится в начало аллоцированной памяти. Возвращает указатель
    //на первый элемент.
	value_type* linearize(){
        rotate(head);
        tail -= head;
        if (tail < 0)
            tail += capacity();
        head = 0;
        return buffer;
    }


	//Проверяет, является ли буфер линеаризованным.
    bool is_linearized() const { return front() == *buffer; }

	void set_capacity(int new_capacity_){
        if (new_capacity_ < 1)
            throw std::invalid_argument("Bad capacity!");
        T *new_arr = new value_type[new_capacity_];
        if (capacity() < new_capacity_) {
            for (auto i = head, k = 0; k < capacity(); i = (i + 1) % capacity(), ++k)
                new_arr[k] = at(i);
            tail -= head;
        } else {
            for (auto i = head, k = 0; k < new_capacity_; i = (i + 1) % capacity(), ++k)
                new_arr[k] = at(i);
            if (size() > new_capacity_) {
                m_size -= (size() - new_capacity_);
                tail = size() - 1;
            } else
                tail -= head;
        }
        if (tail < 0)
            tail += capacity();
        head = 0;
        m_capacity = new_capacity_;
        delete [] buffer;
        buffer = new_arr;
    }

	//Изменяет размер буфера.
	//В случае расширения, новые элементы заполняются элементом item.
	void resize(int new_size, const T& item = T()){
        const int oldCap = capacity();
        set_capacity(new_size);
        if (oldCap < new_size){
            for (auto i = oldCap; i < new_size; ++i) {
                at(i) = item;
                ++m_size;
            }
            tail = m_capacity - 1;
        }
	}

	//Обменивает содержимое буфера с буфером cb.
	void swap(CircularBuffer& cb){
        CircularBuffer tmp = cb;
        cb = *this;
        *this = tmp;
	}

	//Вставляет элемент item по индексу pos. Ёмкость буфера остается неизменной.
	void insert(int pos, const T& item = T()){
        if (pos < size())
            at((head + pos) % capacity()) = item;
        else
            throw std::length_error("Wrong index!");
	}

	//Удаляет элементы из буфера в интервале [first, last).
	void erase(int first, int last){
        if (!full())
            throw "Fill the buffer first!";
        const bool cmp = first <= last;
        const bool fPos = 0 <= first < capacity();
        const bool lPos = 0 <= last <= capacity();
        if (cmp && fPos && lPos) {
            const int dif = last - first;
            value_type* new_buffer = new T[capacity() - dif];
            m_size = 0;
            for (int i = head; i != (head + first) % capacity(); i = (i + 1) % capacity())
                new_buffer[m_size++] = buffer[i];
            for (int j = (head + last) % capacity(); j != (tail + 1) % capacity(); j = (j + 1) % capacity())
                new_buffer[m_size++] = buffer[j];
            m_capacity -= dif;
            m_size = capacity();
            tail = size() - 1;
            head = 0;
            delete [] buffer;
            buffer = new_buffer;
        }
        else
            throw std::invalid_argument("Wrong index(es)");
    }


	//Очищает буфер.
	void clear(){
	    m_size = 0;
	    head = tail = -1;
	    delete [] buffer;
	    buffer = new value_type [m_capacity];
	}
};

template <class T>
bool operator==(const CircularBuffer<T> &a, const CircularBuffer<T> &b){
    if (a.size() == b.size()){
        for (auto i = 0; i < a.capacity(); ++i) {
            if (a[i] != b[i])
                return false;
        }
        return true;
    }
    else
        return false;
}

template <class T>
bool operator!=(const CircularBuffer<T> &a, const CircularBuffer<T> &b){
    return !(a==b);
}


