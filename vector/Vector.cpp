#include <exception>
#include "Vector.hpp"

Vector::Vector() 
    : size(0),
      capacity(5),
      array(new int[capacity])
{

}

Vector::Vector(const Vector& rhs)
    : size(rhs.Size()),
      capacity(rhs.Capacity() + 5),      array(new int [capacity])
{
    for (int i = 0; i < rhs.Size(); i++) {
        array[i] = rhs.array[i];
    }
}

Vector::Vector(int elements, int value) 
    : size(elements),
      capacity(elements + 5),
      array(new int[capacity])
{
    for (int i = 0; i < size; i++) {
        array[i] = value;
    }
}

Vector::Vector(const std::initializer_list<int>& list)
    : size(0),
      capacity(list.size() + 5),
      array(new int[capacity])
{
    for (int i : list) {
        PushBack(i);
    }
}

Vector::~Vector() {
    delete[] array;
}

void Vector::PushBack(int value) {
    if (size < capacity) {
        array[size] = value;
        ++size;
    } else {
        capacity *= 2;
        int* newArray = new int[capacity];
        for (int i = 0; i < size; i++) {
            newArray[i] = array[i];
        }
        newArray[size] = value;
        ++size;

        delete[] array;
        array = newArray;
    }
}

void Vector::PopBack() {
    if (size == 0) {
        throw std::runtime_error("Pop back on empty vector!");
    }
    array[size] = 0;
    --size;
}

bool Vector::Empty() const {
    return size == 0;
}

int Vector::Size() const {
    return size;
}

int Vector::Capacity() const {
    return capacity;
}

bool Vector::operator==(const Vector& rhs) const {
    if (Size() != rhs.Size()) {
        return false;
    }

    for (int i = 0; i < Size(); i++) {
        if (array[i] != rhs.array[i]) {
            return false;
        }
    }

    return true;
}

bool Vector::operator!=(const Vector& rhs) const {
    return !(*this == rhs);
}

std::ostream& operator<<(std::ostream& ostr, const Vector& rhs) {
    for (int i = 0; i < rhs.size; i++) {
        ostr << rhs.array[i] << " "; 
    }
    
    ostr << " || ";

    for (int i = rhs.size; i < rhs.capacity; i++) {
        ostr << rhs.array[i] <<  " ";
    }

    ostr << std::endl;

    return ostr;
}

Vector& Vector::operator=(const Vector& rhs) {
    if (rhs.size > size) {
        delete[] array;
        capacity = rhs.size + 5;
        array = new int[capacity];
    }
    for (int i = 0; i < rhs.size; i++) {
        array[i] = rhs.array[i];
    }

    size = rhs.size;
    return *this;
}

int& Vector::operator[](int index) {
    return array[index];
}

int& Vector::At(int index) {
    if ((index < 0) || (index >= size)) {
        throw std::runtime_error("At - Index out of range!");
    }
    return array[index];
}

int& Vector::Front() {
    return array[0];
}

int& Vector::Back() {
    return array[size - 1];
}

void Vector::Insert(int index, int value) {
    if ((index < 0) || (index >= size)) {
        throw std::runtime_error("Insert - Index out of range!");
    }
    if (size != capacity) {
        for (int i = size; i > index; i--) {
            array[i] = array[i-1];
        }
        array[index] = value;
        ++size;
    } else {
        capacity *= 2;
        int* newArray = new int[capacity];
        for (int i = 0; i < size; i++) {
            newArray[i] = array[i];
        }
        delete[] array;
        array = newArray;
        Insert(index, value);
    }
}

void Vector::Erase(int index) {
    if (index < 0 || index >= size) {
        throw std::runtime_error("Erase - Index out of range!");
    }
    for (int i = index; i < size; i++) {
        array[i] = array[i + 1];
    }
    --size;
}

void Vector::Clear() {
    size = 0;
}