// ® Copyright FURGBot 2019


#ifndef ROBOT_H
#define ROBOT_H


#include "geometry/field_line.h"
#include "geometry/point_2d.h"

#include <vector>


namespace vss_furgbol {
namespace system {

enum RoleLabel {
    GK, CB, ST //GoalKeeper, CenterBack, STriker
};

class Robot {
    private:
        int id_;
        int role_;
        int max_velocity_;
        float max_ball_distance_;
        float angle_;
        float target_angle_;
        geometry::FieldLine field_line_;
        geometry::Point2D position_;
        geometry::Point2D target_position_;

        int out_of_place_;

    public:
        Robot();
        ~Robot();

        //Getters
        int getId();
        int getRole();
        int getMaxVelocity();
        float getMaxBallDistance();
        float getAngle();
        float getTargetAngle();
        geometry::FieldLine getFieldLine();
        geometry::Point2D getPosition();
        geometry::Point2D getTargetPosition();

        int isOutOfPlace();

        //Setters
        void setId(int id);
        void setRole(int role);
        void setMaxVelocity(int max_velocity);
        void setMaxBallDistance(float max_ball_distance);
        void setAngle(float angle);
        void setTargetAngle(float target_angle);
        void setFieldLine(geometry::FieldLine field_line);
        void setPosition(geometry::Point2D position);
        void setTargetPosition(geometry::Point2D target_position);
        void setOutOfPlace(int out_of_place);
        
        //Operators
        void operator=(Robot robot);
};

} // namespace system
} // namespace vss_furgbol


#endif // ROBOT_H