#pragma once

class Keyboard {
    private:
        bool 
            w_down, 
            a_down, 
            s_down, 
            d_down, 
            r_down, 
            f_down, 
            space_down, 
            lshift_down, 
            plus_down, 
            minus_down;

    public:
        Keyboard();
};

class Mouse {
    public:
        // handle mouse input
        void handle(float y);
};