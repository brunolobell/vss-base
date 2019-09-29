// ® Copyright FURGBot 2019


#ifndef BALL_H
#define BALL_H


#include "geometry/point_2d.h"

#include <vector>


namespace vss_furgbol {
namespace system {

class Ball {
    private:
        geometry::Point2D position_;
        std::vector<float> movimentation_;

    public:
        Ball();
        Ball(geometry::Point2D position, std::vector<float> movimentation);
        ~Ball();

        //Getters
        geometry::Point2D getPosition();
        std::vector<float> getMovimentation();

        //Setters
        void setPosition(geometry::Point2D position);
        void setMovimentation(std::vector<float> movimentation);

        //Operators
        Ball operator=(Ball ball);
};

}
}


#endif // BALL_H