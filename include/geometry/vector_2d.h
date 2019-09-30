// ® Copyright FURGBot 2019


#ifndef VECTOR_2D_H
#define VECTOR_2D_H


#include "geometry/point_2d.h"


namespace vss_furgbol {
namespace geometry {

class Vector2D {
    private:
        Point2D origin_;
        Point2D destiny_;
    
    public:
        Vector2D();
        Vector2D(Point2D origin, Point2D destiny);
        ~Vector2D();

        //Getters
        Point2D getOrigin();
        Point2D getDestiny();
        float getComponentX();
        float getComponentY();
        float getModule();
        float getReferentX(float y);
        float getReferentY(float x);

        //Setters
        void setOrigin(Point2D origin);
        void setDestiny(Point2D destiny);

        //Operators
        void operator=(Vector2D vector);
};

} // namespace geometry
} // namespace vss_furgbol


#endif // VECTOR_2D_H