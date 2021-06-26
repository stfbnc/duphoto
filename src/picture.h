#ifndef PICTURE
#define PICTURE

#include <sys/stat.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

class Picture
{
private:
    int64_t error_hash = -1;
    cv::Mat picture;

    void load(std::string pic_name);
    void close();
    int64_t ahash();
    int64_t phash();
    int64_t dhash();
public:
    enum hashType
    {
        AHASH,
        PHASH,
        DHASH
    };

    explicit Picture(std::string pic_name);
    virtual ~Picture();
    int64_t getPictureHash(hashType hash_type=DHASH); // call a method for hashes
    // and write hash in a singleton map
    int64_t getErrorHashValue();
};

#endif
