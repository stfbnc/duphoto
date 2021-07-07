#include "picture_manager.h"

PictureManager::PictureManager(std::string folder, std::string out_log)
{
    pic_folder = folder;
    output_log = out_log;
}

PictureManager::~PictureManager() {}

void PictureManager::getHashes(Picture::hashType hash_method)
{
    std::vector<std::future<void>> threads;
    for(auto i = boost::filesystem::directory_iterator(pic_folder); i != boost::filesystem::directory_iterator(); ++i)
    {
        if(!boost::filesystem::is_directory(i->path()))
        {
            std::string pic_name = pic_folder + i->path().filename().string();
            threads.emplace_back(std::async(&PictureManager::getHash, this, pic_name, hash_method));
        }
    }
    
    for(auto&& t : threads)
    {
        t.get();
    }
}

void PictureManager::getSimilarPictures()
{
    Logger logger(pic_folder);
    std::vector<std::string> pictures = HashesMap::getInstance()->getPicturesNames();
    std::vector<int64_t> hashes = HashesMap::getInstance()->getPicturesHashes();
    for(int i = 0; i < pictures.size(); ++i)
    {
        for(int j = i + 1; j < pictures.size(); ++j)
        {
            int distance = hammingDistance(hashes.at(i), hashes.at(j));
            if(distance < 10)
            {
                logger.writeToLog(pictures.at(i), pictures.at(j), distance);
            }
        }
    }
    logger.saveLog(output_log);
}

void PictureManager::getHash(std::string pic_name, Picture::hashType hash_method)
{
    Picture pic = Picture(pic_name);
    int64_t hash = pic.getPictureHash(hash_method);
    if(hash != pic.getErrorHashValue())
    {
        HashesMap::getInstance()->addToMap(pic_name, hash);
    }
}

int PictureManager::hammingDistance(int64_t hash_1, int64_t hash_2)
{
    int64_t x = hash_1 ^ hash_2;
    int64_t one = 1;
    int d = 0;
 
    while(x > 0)
    {
        d += x & one;
        x >>= one;
    }
 
    return d;
}
