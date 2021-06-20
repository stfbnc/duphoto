#ifndef PICTURE
#define PICTURE

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>

class Picture
{
private:
    cv::Mat *picture;

    void load(std::string pic_name);
    void close();
public:
    explicit Picture(std::string pic_name);
    ~Picture();
    std::string getPictureHash(std::string mode="dhash"); // call a method from another class (factory of hashes)
    // and write hash in a singleton map
};

#endif
