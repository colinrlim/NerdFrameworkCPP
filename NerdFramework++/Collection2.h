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
public:
    std::vector<T> objects;

    Collection2() : objects(), _origin(Vector2::zero) { }
    Collection2(const std::vector<T>& objects) : objects(objects), _origin(Vector2::zero) { }

    const Vector2& getOrigin() const { return _origin; }
    void setOrigin(const Vector2& value) {
        if (_origin == value) return;

        Vector3 amount = value - _origin;
        for (size_t i = 0; i < objects.size(); i++)
            objects[i].move(amount);
        _origin = value;
    }

    static void move(const std::vector<T>& objects, const Vector2& offset) {
        for (size_t i = 0; i < objects.size(); i++)
            objects[i].move(offset);
    }

    bool overlaps(const Vector2& point) const {
        for (size_t i = 0; i < objects.size(); i++) {
            if (objects[i].overlaps(point))
                return true;
        }
        return false;
    }
    bool overlaps(const Rect2<double>& rectangle) const {
        for (size_t i = 0; i < objects.size(); i++) {
            if (objects[i].overlaps(rectangle))
                return true;
        }
        return false;
    }
    bool overlaps(const Collection2<T>& group) const {
        for (size_t i = 0; i < objects.size(); i++) {
            if (objects[i].overlaps(group))
                return true;
        }
        return false;
    }
};

