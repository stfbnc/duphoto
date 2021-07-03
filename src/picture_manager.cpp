#include "picture_manager.h"

PictureManager::PictureManager(std::string folder)
{
    pic_folder = folder;
}

PictureManager::~PictureManager() {}

void PictureManager::getHashes()
{
    std::vector<std::future<void>> threads;
    for(auto i = boost::filesystem::directory_iterator(pic_folder); i != boost::filesystem::directory_iterator(); ++i)
    {
        if(!boost::filesystem::is_directory(i->path()))
        {
            std::string pic_name = pic_folder + i->path().filename().string();
            threads.emplace_back(std::async(&PictureManager::getHash, this, pic_name));
        }
    }
    
    for(auto&& t : threads)
    {
        t.get();
    }
}

void PictureManager::getSimilarPictures()
{
    std::vector<std::string> pictures = HashesMap::getInstance()->getPicturesNames();
    std::vector<int64_t> hashes = HashesMap::getInstance()->getPicturesHashes();
    for(int i = 0; i < pictures.size(); ++i)
    {
        for(int j = i + 1; j < pictures.size(); ++j)
        {
            int distance = hammingDistance(hashes.at(i), hashes.at(j));
            if(distance < 10)
            {
                std::cout << "Pic 1: " << pictures.at(i) << " | Pic 2: " << pictures.at(j) << " | d: " << distance << std::endl;
            }
        }
    }
}

void PictureManager::getHash(std::string pic_name)
{
    Picture pic = Picture(pic_name);
    int64_t hash = pic.getPictureHash(Picture::AHASH);
    HashesMap::getInstance()->addToMap(pic_name, hash);
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
