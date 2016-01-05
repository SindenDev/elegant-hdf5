#ifndef ERRORHELPER_H
#define ERRORHELPER_H

#include <string>
#include <hdf5.h>

class ErrorHelper
{
public:
    ErrorHelper();
    ~ErrorHelper();

    std::string walk();
    static herr_t streamBuilder(unsigned n, const H5E_error2_t *error, void *clientData);

    void close();

private:
    H5E_auto2_t m_oldFunction;
    void *m_oldClientData;
};

#endif // ERRORHELPER_H
