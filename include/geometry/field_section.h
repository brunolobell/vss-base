// ® Copyright FURGBot 2019


#ifndef FIELD_SECTION_H
#define FIELD_SECTION_H


namespace vss_furgbol {
namespace geometry {

class FieldSection {
    private:
        int min_x_;
        int min_y_;
        int max_x_;
        int max_y_;

    public:
        FieldSection();
        ~FieldSection();

        //Getters
        int getMinX();
        int getMinY();
        int getMaxX();
        int getMaxY();

        //Setters
        void setMinX(int min_x);
        void setMinY(int min_y);
        void setMaxX(int max_x);
        void setMaxY(int max_y);

        void operator=(FieldSection field);
};

} // namespace geometry
} // namespace vss_furgbol


#endif // FIELD_SECTION_H