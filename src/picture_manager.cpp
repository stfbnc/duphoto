#include "picture_manager.h"

PictureManager::PictureManager(std::string folder)
{
    pic_folder = folder;
}

PictureManager::~PictureManager() {}

void PictureManager::getHashes()
{
    std::vector<std::thread> threads = std::vector<std::thread>();
    int n = 0;
    for(auto i = boost::filesystem::directory_iterator(pic_folder); i != boost::filesystem::directory_iterator(); ++i)
    {
        if(!boost::filesystem::is_directory(i->path()))
        {
            std::string pic_name = pic_folder + i->path().filename().string();
            threads.emplace_back([&](){
                getHash(pic_name, n);
            });
        }
    }
    
    for(std::thread &t : threads)
    {
        t.join();
    }
}

void PictureManager::getHash(std::string pic_name, int n)
{
    Picture pic = Picture(pic_name);
    int64_t hash = pic.getPictureHash(Picture::AHASH);
    std::cout << "Thread: " << n << ", pic: " << pic_name << ", hash: " << hash << std::endl;
}
