#ifndef HASHES_MAP
#define HASHES_MAP

#include <vector>
#include <mutex>

class HashesMap
{
private:
    static HashesMap *instance;
    std::mutex *map_mutex;
    std::vector<std::string> pictures_names;
    std::vector<int64_t> pictures_hashes;

    explicit HashesMap();
    virtual ~HashesMap();
public:
    static HashesMap* getInstance();
    std::vector<std::string> getPicturesNames();
    std::vector<int64_t> getPicturesHashes();
    void addToMap(std::string file, int64_t hash);
};

#endif
