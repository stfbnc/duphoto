#ifndef PICTURE_MANAGER
#define PICTURE_MANAGER

#include <boost/filesystem.hpp>
#include <thread>
#include "picture.h"

class PictureManager
{
private:
    std::string pic_folder;

    void getHash(std::string pic_name, int n);
public:
    explicit PictureManager(std::string folder);
    virtual ~PictureManager();
    void getHashes();
};

#endif
