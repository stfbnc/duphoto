#ifndef HASHES_MAP
#define HASHES_MAP

#include <map>
#include <mutex>

class HashesMap
{
private:
    static HashesMap *instance;
    std::mutex *map_mutex;
    std::map<std::string, std::string> hashes_map;

    explicit HashesMap();
    virtual ~HashesMap();
public:
    static HashesMap* getInstance();
    std::map<std::string, std::string> getDataMap();
    void addToMap(std::string file, std::string hash);
};

#endif
