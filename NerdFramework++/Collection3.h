#pragma once

#include <vector>
#include "Vector3.h"
#include "Ray3.h"
#include "Box3.h"

template <typename T>
class Collection3
{
private:
    Vector3 _origin = Vector3::zero;
    Vector3 _scale = Vector3::one;
public:
    std::vector<T*> objects;

    Collection3() : objects(), _origin(Vector3::zero), _scale(Vector3::one) { }
    Collection3(const std::vector<T*>& objects) : objects(objects), _origin(Vector3::zero), _scale(Vector3::one) { }

    const Vector3& getOrigin() const { return _origin; }
    void setOrigin(const Vector3& value) {
        if (_origin == value) return;

        Vector3 amount = value - _origin;
        for (size_t i = 0; i < objects.size(); i++) {
            objects[i]->move(amount);
        }
        _origin = value;
    }
    const Vector3& getScale() { return _scale; }
    void setScale(const Vector3& value, const Vector3& origin) {
        if (_scale == value) return;

        Vector3 amount = value / _scale;
        for (size_t i = 0; i < objects.size(); i++)
            objects[i]->scale(amount, origin);
        _scale = value;
    }

    static void move(const std::vector<T>& objects, const Vector3& offset) {
        for (size_t i = 0; i < objects.size(); i++)
            objects[i]->move(offset);
    }
    static void scale(const std::vector<T>& objects, const Vector3& scale, const Vector3& origin) {
        for (size_t i = 0; i < objects.size(); i++)
            objects[i]->scale(scale, origin);
    }
    bool meets(const Ray3& ray) const {
        bool meets = false;
        for (size_t i = 0; i < objects.size(); i++) {
            if (objects[i]->meets(ray)) {
                meets = true;
                break;
            }
        }
        return meets;
    }

    void rotateX(double radians, const Vector3& origin) {
        for (size_t i = 0; i < objects.size(); i++)
            objects[i]->rotateX(radians, origin);
    }
    void rotateY(double radians, const Vector3& origin) {
        for (size_t i = 0; i < objects.size(); i++)
            objects[i]->rotateY(radians, origin);
    }
    void rotateZ(double radians, const Vector3& origin) {
        for (size_t i = 0; i < objects.size(); i++)
            objects[i]->rotateZ(radians, origin);
    }
    void rotate(double r1, double r2, double r3, const Vector3& origin) {
        for (size_t i = 0; i < objects.size(); i++)
            objects[i]->rotate(r1, r2, r3, origin);
    }
};

