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

    public:
        Ball();
        ~Ball();

        //Getters
        geometry::Point2D getPosition();

        //Setters
        void setPosition(geometry::Point2D position);

        //Operators
        void operator=(Ball ball);
};

}
}


#endif // BALL_H