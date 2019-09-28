// ® Copyright FURGBot 2019


#ifndef BALL_H
#define BALL_H


#include "CGAL/Simple_cartesian.h"

#include <vector>


namespace vss_furgbol {
namespace system {

typedef CGAL::Simple_cartesian<float>::Point_2 point_2d;

class Ball {
    private:
        point_2d position_;
        std::vector<float> movimentation_;

    public:
        Ball();
        ~Ball();

        //Getters
        point_2d getPosition();
        std::vector<float> getMovimentation();

        //Setters
        void setPosition(point_2d position);
        void setMovimentation(std::vector<float> movimentation);

        void operator=(Ball ball);
};

}
}


#endif // BALL_H