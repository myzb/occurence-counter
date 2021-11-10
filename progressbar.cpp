#include <iomanip>
#include <string>
#include <ostream>

#include "progressbar.hpp"


progressbar::progressbar(const size_t width, std::ostream &os) :
    width_(width), steps_(width / 100.0f), os_(os) {}


void progressbar::draw(const float percent)
{
    constexpr char fill = '#';
    constexpr char rest = ' ';

    std::size_t progress = static_cast<std::size_t>(percent * steps_);

    os_ << "\r" << std::flush;
    os_ << text_;

    os_ << " [";
    for (std::size_t i = 0; i < width_; ++i)
        os_ << (i <= progress ? fill : rest);
    os_ << "] ";

    os_ << static_cast<std::size_t>(percent) << "%  ";
}


void progressbar::text(const std::string text)
{
    text_ = text;
}


void progressbar::clear()
{
    os_ << "\r" << std::flush;
    os_ <<  std::setw(text_.length() + width_ + 10) << " \n";
}
