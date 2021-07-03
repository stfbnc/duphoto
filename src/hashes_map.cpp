#include "hashes_map.h"

HashesMap* HashesMap::instance = nullptr;

HashesMap* HashesMap::getInstance()
{
    if(!instance)
        instance = new HashesMap();

    return instance;
}

std::vector<std::string> HashesMap::getPicturesNames()
{
    return pictures_names;
}

std::vector<int64_t> HashesMap::getPicturesHashes()
{
    return pictures_hashes;
}

void HashesMap::addToMap(std::string file, int64_t hash)
{
    map_mutex->lock();
    pictures_names.emplace_back(file);
    pictures_hashes.emplace_back(hash);
    map_mutex->unlock();
}

HashesMap::HashesMap()
{
    pictures_names = std::vector<std::string>();
    pictures_hashes = std::vector<int64_t>();
    map_mutex = new std::mutex();
}

HashesMap::~HashesMap()
{
    delete map_mutex;
    delete instance;
}
