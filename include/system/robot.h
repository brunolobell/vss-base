// ® Copyright FURGBot 2019


#ifndef ROBOT_H
#define ROBOT_H


#include "geometry/field_section.h"
#include "geometry/point_2d.h"

#include <vector>


namespace vss_furgbol {
namespace system {

enum RoleLabel {
    GK, CB, ST, UNDEFINED //GoalKeeper, CenterBack, STriker, Undefined (for enemy robots)
};

class Robot {
    private:
        int id_;
        int role_;
        int max_velocity_;
        geometry::FieldSection field_section_;
        geometry::Point2D position_;
        geometry::Point2D target_;
        std::vector<float> movimentation_;

    public:
        Robot();
        Robot(int id, int role, int max_velocity, geometry::FieldSection field_section, geometry::Point2D position, geometry::Point2D target, std::vector<float> movimentation);
        ~Robot();

        //Getters
        int getId();
        int getRole();
        int getMaxVelocity();
        geometry::FieldSection getFieldSecton();
        geometry::Point2D getPosition();
        geometry::Point2D getTarget();
        std::vector<float> getMovimentation();

        //Setters
        void setId(int id);
        void setRole(int role);
        void setMaxVelocity(int max_velocity);
        void setFieldSection(geometry::FieldSection field_section);
        void setPosition(geometry::Point2D position);
        void setTarget(geometry::Point2D target);
        void setMovimentation(std::vector<float> movimentation);

        //Operators
        Robot operator=(Robot robot);
};

} // namespace system
} // namespace vss_furgbol


#endif // ROBOT_H