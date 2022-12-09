#include "UDim.h"

UDim::UDim() : scale(0.0), offset(0.0) { }
UDim::UDim(double scale, double offset) : scale(scale), offset(offset) { }

double UDim::absolute(double max) const {
	return max * this->scale + this->offset;
}