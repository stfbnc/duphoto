#ifndef PICTURE_MANAGER
#define PICTURE_MANAGER

#include <boost/filesystem.hpp>
#include <future>
#include "picture.h"
#include "hashes_map.h"

class PictureManager
{
private:
    std::string pic_folder;

    void getHash(std::string pic_name);
    int hammingDistance(int64_t hash_1, int64_t hash_2);
public:
    explicit PictureManager(std::string folder);
    virtual ~PictureManager();
    void getHashes();
    void getSimilarPictures();
};

#endif
