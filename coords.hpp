class Vec {
    double x;
    double y;
    Vec (double x, double y) {
        this->x = x;
        this->y = y;
    }
    Vec add (Vec a , Vec b);
    Vec sub (Vec a , Vec b);
    double dot (Vec a , Vec b);
    double magnitude ();
};
