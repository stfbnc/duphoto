#include <iostream>
#include "picture_manager.h"

int main(int argc, char **argv)
{
    if(argc != 2)
    {
        throw std::runtime_error("Error executing program. Usage: ./duphoto <path to images folder>");
    }

    std::string img_folder = argv[1];
    PictureManager pic_manager = PictureManager(img_folder);
    pic_manager.getHashes();

    return 0;

    // logger class for failed images
    // and for report of similar images
}