#ifndef _KMINT_IMAGE_H
#define _KMINT_IMAGE_H

#include <string>

namespace linalg {
    class image {
        std::string _filename;
        float _scale;
    public:
        image(const std::string &file, float scale = 1.0f) : _filename { file }, _scale { scale } {}
        const std::string &filename() const noexcept { return _filename; }
        float scale() const noexcept { return _scale; }
    };
}

#endif
