// ® Copyright FURGBot 2019


#ifndef FIELD_SECTION_H
#define FIELD_SECTION_H


namespace vss_furgbol {
namespace geometry {

class FieldSection {
    private:
        float min_x_;
        float min_y_;
        float max_x_;
        float max_y_;

    public:
        FieldSection();
        FieldSection(float min_x, float min_y, float max_x, float max_y);
        ~FieldSection();

        //Getters
        float getMinX();
        float getMinY();
        float getMaxX();
        float getMaxY();

        //Setters
        void setMinX(float min_x);
        void setMinY(float min_y);
        void setMaxX(float max_x);
        void setMaxY(float max_y);

        //Operators
        FieldSection operator=(FieldSection field);
};

} // namespace geometry
} // namespace vss_furgbol


#endif // FIELD_SECTION_H