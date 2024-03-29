// ® Copyright FURGBot 2019


#ifndef POINT_2D_H
#define POINT_2D_H


namespace vss {
namespace geometry {

class Point2D {
    private:
        float x_;
        float y_;
    
    public:
        Point2D();
        Point2D(float x, float y);
        ~Point2D();

        //Getters
        float getX();
        float getY();

        //Setters
        void setX(float x);
        void setY(float y);

        //Operators
        bool operator!=(Point2D point);
        bool operator==(Point2D point);
        void operator=(Point2D point);
};

}
}


#endif // POINT_2D_H