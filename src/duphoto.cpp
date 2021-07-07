#include <iostream>
#include "picture_manager.h"
#include "hashes_map.h"

int main(int argc, char **argv)
{
    if(argc != 4)
    {
        throw std::runtime_error("Error executing program. Usage: ./duphoto <path to images folder> <hash method : 0 -> ahash, 1 -> dhash, 2 -> phash> <path to output log>");
    }

    std::string img_folder = argv[1];
    if(!boost::filesystem::exists(img_folder))
    {
        throw std::runtime_error("Pictures folder does not exist.");
    }
    uint8_t hash_method = atoi(argv[2]);
    if(hash_method > 2)
    {
        throw std::runtime_error("Hash method must be: 0 -> ahash, 1 -> dhash, 2 -> phash.");
    }
    std::string output_log = argv[3];
    
    PictureManager pic_manager = PictureManager(img_folder, output_log);
    switch(hash_method)
    {
    case 0:
        pic_manager.getHashes(Picture::AHASH);
        break;
    case 1:
        pic_manager.getHashes(Picture::DHASH);
        break;
    case 2:
        pic_manager.getHashes(Picture::PHASH);
        break;
    default:
        break;
    }

    pic_manager.getSimilarPictures();

    return 0;
}