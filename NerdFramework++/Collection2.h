#pragma once

#include <vector>
#include "Rect2.h"
#include "Vector3.h"
#include "Vector2.h"
#include "Ray3.h"
#include "Box3.h"

template <typename T>
class Collection2
{
private:
    Vector2 _origin = Vector2::zero;
    std::vector<T*> _data;
public:
    Collection2() : _data(), _origin(Vector2::zero) { }
    Collection2(const std::vector<T*>& objects) : _data(objects), _origin(Vector2::zero) { }

    const Vector2& getOrigin() const { return _origin; }
    void setOrigin(const Vector2& value) {
        if (_origin == value) return;

        Vector3 amount = value - _origin;
        for (auto iterator = _data.begin(); iterator != _data.end(); ++iterator)
            *(iterator)->move(amount);
        _origin = value;
    }

    static void move(const std::vector<T>& objects, const Vector2& offset) {
        for (auto iterator = objects.begin(); iterator != objects.end(); ++iterator)
            *(iterator)->move(offset);
    }

    bool overlaps(const Vector2& point) const {
        for (auto iterator = _data.begin(); iterator != _data.end(); ++iterator)
            if (*(iterator)->overlaps(point))
                return true;
        return false;
    }
    bool overlaps(const Rect2<double>& rectangle) const {
        for (auto iterator = _data.begin(); iterator != _data.end(); ++iterator)
            if (*(iterator)->overlaps(rectangle))
                return true;
        return false;
    }
    bool overlaps(const Collection2<T>& group) const {
        for (auto iterator = _data.begin(); iterator != _data.end(); ++iterator)
            if (*(iterator)->overlaps(group))
                return true;
        return false;
    }

    /* Vector wrapper */
    struct Iterator {
    private:
        typename List<T*>::Iterator _iterator;
    public:
        Iterator(typename List<T*>::Iterator&& iterator) : _iterator(iterator) { }

        T* operator*() { return *_iterator; }
        void operator++() { ++_iterator; }
        void operator--() { --_iterator; }
        bool operator==(const Iterator& rhs) { return _iterator == rhs._iterator; }
        bool operator!=(const Iterator& rhs) { return _iterator != rhs._iterator; }
    };

    friend struct Iterator;

    Iterator begin() const {
        return Iterator(_data.begin());
    }
    Iterator end() const {
        return Iterator(_data.end());
    }

    void push_back(T* element) {
        _data.push_back(element);
    }
    void pop_back() {
        _data.pop_back();
    }
    Iterator insert(size_t position, T* element) {
        _data.insert(position, element);
    }
    Iterator erase(Iterator iterator) {
        _data.erase(iterator._iterator);
    }

    T** data() {
        return _data.data();
    }
    const T** data() const {
        return _data.data();
    }
    const size_t size() const {
        return _data.size();
    }
};

template <typename T>
std::ostream& operator<<(std::ostream& stream, const Collection2<T>& rhs) {
    const T* data = rhs.objects.data();
    const size_t size = rhs.objects.size();
    stream << "[ ";
    for (size_t i = 0; i < size - 1; i++)
        stream << *(*(data + i)) << ", ";
    return stream << *(*(data + size - 1)) << " ]";
}

