// ® Copyright FURGBot 2019


#ifndef ROBOT_H
#define ROBOT_H


#include "CGAL/Simple_cartesian.h"

#include <vector>


namespace vss_furgbol {
namespace system {

typedef CGAL::Simple_cartesian<float>::Point_2 point_2d;

enum RoleLabel {
    GK, CB, ST //GoalKeeper, CenterBack, STriker
};

class Robot {
    private:
        int id_;
        int role_;
        point_2d position_;
        point_2d target_;
        std::vector<float> movimentation_;

    public:
        Robot();
        ~Robot();

        //Getters
        int getId();
        int getRole();
        point_2d getPosition();
        point_2d getTarget();
        std::vector<float> getMovimentation();

        //Setters
        void setId(int id);
        void setRole(int role);
        void setPosition(point_2d position);
        void setTarget(point_2d target);
        void setMovimentation(std::vector<float> movimentation);

        void operator=(Robot robot);
};

} // namespace system
} // namespace vss_furgbol


#endif // ROBOT_H