#include "dataspace.h"

#include <iostream>

using namespace std;

namespace elegant {
namespace hdf5 {


Dataspace::Dataspace(hid_t dataspaceID)
    : m_id(dataspaceID)
{
}

Dataspace::Dataspace(const Dataspace &&other)
    : m_id(other.id())
{
}

Dataspace &Dataspace::operator=(const Dataspace &&other)
{
    m_id = other.id();
    return *this;
}

Dataspace::~Dataspace()
{
    close();
}

bool Dataspace::isValid() const
{
    return m_id > 0;
}

void Dataspace::close()
{
    if(m_id > 0) {
        herr_t closeError = H5Sclose(m_id);
        if(closeError < 0) {
            std::cerr << "WARNING: Could not close dataspace" << std::endl;
        }
    }
}

elegant::hdf5::Dataspace::operator hid_t() const
{
    return m_id;
}

int Dataspace::dimensionCount() const
{
    int result = H5Sget_simple_extent_ndims(m_id);

    if(result < 0) {
        throw std::runtime_error("Could not get the number of dimensions for dataspace");
    }

    return result;
}

bool Dataspace::isScalar() const
{
    if(extentType() == H5S_SCALAR) {
        return true;
    } else {
        return false;
    }
}

bool Dataspace::isSimple() const
{
    if(extentType() == H5S_SIMPLE) {
        return true;
    } else {
        return false;
    }
}

H5S_class_t Dataspace::extentType() const
{
    return H5Sget_simple_extent_type(m_id);
}

hid_t Dataspace::id() const
{
    return m_id;
}

vector<hsize_t> Dataspace::extents() const
{
    if(!isValid()) {
        return vector<hsize_t>();
    }

    std::vector<hsize_t> result(dimensionCount());
    int error = H5Sget_simple_extent_dims(m_id, &result[0], NULL);
    if(error < 0) {
        throw std::runtime_error("Could not get the extents for dataspace");
    }
    return result;
}

} // namespace
}
