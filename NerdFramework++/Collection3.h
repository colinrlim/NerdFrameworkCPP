#pragma once

#include <vector>
#include "Vector3.h"
#include "List.h"
#include "Ray3.h"
#include "Box3.h"

template <typename T>
class Collection3
{
private:
    Vector3 _origin = Vector3::zero;
    Vector3 _scale = Vector3::one;

    List<T*> _data;
public:

    Collection3() : _data(), _origin(Vector3::zero), _scale(Vector3::one) { }
    Collection3(const List<T*>& objects) : _data(objects), _origin(Vector3::zero), _scale(Vector3::one) { }
    Collection3(const std::vector<T*>& objects) : _data(objects), _origin(Vector3::zero), _scale(Vector3::one) { }

    const Vector3& getOrigin() const { return _origin; }
    void setOrigin(const Vector3& value) {
        if (_origin == value) return;

        Vector3 amount = value - _origin;
        for (auto iterator = _data.begin(); iterator != _data.end(); ++iterator)
            (**iterator).move(amount);
        _origin = value;
    }
    const Vector3& getScale() { return _scale; }
    void setScale(const Vector3& value, const Vector3& origin) {
        if (_scale == value) return;

        Vector3 amount = value / _scale;
        for (auto iterator = _data.begin(); iterator != _data.end(); ++iterator)
            (**iterator).scale(amount, origin);
        _scale = value;
    }

    static void move(const std::vector<T>& objects, const Vector3& offset) {
        for (auto iterator = objects.begin(); iterator != objects.end(); ++iterator)
            (**iterator).move(offset);
    }
    static void scale(const std::vector<T>& objects, const Vector3& scale, const Vector3& origin) {
        for (auto iterator = objects.begin(); iterator != objects.end(); ++iterator)
            (**iterator).scale(scale, origin);
    }
    bool meets(const Ray3& ray) const {
        bool meets = false;
        for (auto iterator = _data.begin(); iterator != _data.end(); ++iterator)
            if ((**iterator).meets(ray)) {
                meets = true;
                break;
            }
        return meets;
    }

    void rotateX(double radians, const Vector3& origin) {
        for (auto iterator = _data.begin(); iterator != _data.end(); ++iterator)
            (**iterator).rotateX(radians, origin);
    }
    void rotateY(double radians, const Vector3& origin) {
        for (auto iterator = _data.begin(); iterator != _data.end(); ++iterator)
            (**iterator).rotateY(radians, origin);
    }
    void rotateZ(double radians, const Vector3& origin) {
        for (auto iterator = _data.begin(); iterator != _data.end(); ++iterator)
            (**iterator).rotateZ(radians, origin);
    }
    void rotate(double r1, double r2, double r3, const Vector3& origin) {
        for (auto iterator = _data.begin(); iterator != _data.end(); ++iterator)
            (**iterator).rotate(r1, r2, r3, origin);
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
        bool operator!=(const Iterator & rhs) { return _iterator != rhs._iterator; }
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
std::ostream& operator<<(std::ostream& stream, const Collection3<T>& rhs) {
    const T* data = rhs.objects.data();
    const size_t size = rhs.objects.size();
    stream << "[ ";
    for (size_t i = 0; i < size - 1; i++)
        stream << *(*(data + i)) << ", ";
    return stream << *(*(data + size - 1)) << " ]";
}

