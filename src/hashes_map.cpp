#include "hashes_map.h"

HashesMap* HashesMap::instance = nullptr;

HashesMap* HashesMap::getInstance()
{
    if(!instance)
        instance = new HashesMap();

    return instance;
}

std::map<std::string, std::string> HashesMap::getDataMap()
{
    return hashes_map;
}

void HashesMap::addToMap(std::string file, std::string hash)
{
    map_mutex->lock();
    hashes_map.emplace(file, hash);
    map_mutex->unlock();
}

HashesMap::HashesMap()
{
    hashes_map = std::map<std::string, std::string>();
    map_mutex = new std::mutex();
}

HashesMap::~HashesMap()
{
    delete map_mutex;
    delete instance;
}
