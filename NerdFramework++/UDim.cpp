#include "UDim.h"

UDim::UDim() : scale(0.0), offset(0.0) { }
UDim::UDim(double scale, double offset) : scale(scale), offset(offset) { }

double UDim::absolute(double max) const {
	return max * this->scale + this->offset;
}

std::ostream& operator<<(std::ostream& stream, const UDim& rhs) {
	return stream << "{ scale: " << rhs.scale << ", offset: " << rhs.offset << " }";
}