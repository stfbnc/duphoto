#include <iostream>
#include "picture_manager.h"
#include "hashes_map.h"

int main(int argc, char **argv)
{
    if(argc != 2)
    {
        throw std::runtime_error("Error executing program. Usage: ./duphoto <path to images folder>");
    }

    std::string img_folder = argv[1];
    PictureManager pic_manager = PictureManager(img_folder);
    pic_manager.getHashes();

    /*std::map<std::string, int64_t> h_map = HashesMap::getInstance()->getDataMap();
    for(auto const& [key, val] : h_map)
    {
        std::cout << "File: " << key << ", hash: " << val << std::endl;
    }*/

    pic_manager.getSimilarPictures();

    return 0;

    // logger class for failed images
    // and for report of similar images
}