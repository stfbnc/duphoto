#ifndef PICTURE_MANAGER
#define PICTURE_MANAGER

#include <boost/filesystem.hpp>
#include <future>
#include "picture.h"
#include "hashes_map.h"
#include "logger.h"

class PictureManager
{
private:
    std::string pic_folder;
    std::string output_log;

    void getHash(std::string pic_name, Picture::hashType hash_method);
    int hammingDistance(int64_t hash_1, int64_t hash_2);
public:
    explicit PictureManager(std::string folder, std::string out_log="out.log");
    virtual ~PictureManager();
    void getHashes(Picture::hashType hash_method);
    void getSimilarPictures();
};

#endif
