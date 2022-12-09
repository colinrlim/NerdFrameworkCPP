#pragma once

#include <vector>
#include <map>
#include "Tween.h"

// Only use this class with Color structs!!

template <typename T>
class ColorSequence
{
public:
    std::map<double, T> steps;

    ColorSequence() {
        steps.emplace(0.0, T::white);
    }
    ColorSequence(const std::map<double, T>& steps) : steps(steps) { };
    ColorSequence(const T& color) {
        steps.emplace(0.0, color);
        steps.emplace(1.0, T::black);
    }
    ColorSequence(const std::vector<T>& colors) {
        double stepInterval = 1.0 / (colors.size() - 1);
        for (size_t i = 0; i < colors.size(); i++)
        {
            steps.emplace(stepInterval * i, colors[i]);
        }
    }

    ColorSequence quantized(int quantization = 5) {
        std::map<double, T> quantizedSteps = std::map<double, T>();
        T first = steps.begin()->second;
        T last = steps.rbegin()->second;

        for (int i = 1; i < quantization; i++)
        {
            double stepInterval0 = Tween::quartIn(0, 1, (i - 1) / quantization);
            double stepInterval1 = Tween::quartIn(0, 1, i / quantization);
            quantizedSteps.emplace(stepInterval1, T::lerp(first, last, stepInterval0));
            quantizedSteps.emplace(stepInterval1 + 0.01, T::lerp(first, last, stepInterval1));
        }

        return TSequence(quantizedSteps);
    }
    T colorAt(double interpolant) {
        auto step0 = steps.rend();
        auto step1 = steps.end();
        for (auto it = steps.begin(); it != steps.end(); it++) {
            if (it->first >= interpolant)
            {
                step1 = it;
                break;
            }
        }
        if (step1 == steps.end())
            return steps.rbegin()->second;

        for (auto it = steps.rbegin(); it != steps.rend(); it++) {
            if (it->first < step1->first)
            {
                step0 = it;
                break;
            }
        }
        if (step0 == steps.rend())
            return steps.begin()->second;

        return T::lerp(step0->second, step1->second, (interpolant - step0->first) / (step1->first - step0->first));
    }
};

