#ifndef _PROGRESSBAR_H__
#define _PROGRESSBAR_H__

#include <ostream>
#include <string>

class progressbar {
public:
    progressbar(const std::size_t width, std::ostream &os);

    void draw(const float percent);
    void text(const std::string text);
    void clear();

private:
    const std::size_t width_;
    const float steps_;
    std::ostream &os_;
    std::string text_{"Progress"};
};

#endif /* _PROGRESSBAR_H__ */
