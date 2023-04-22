#pragma once

#include "camera.h"


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

        // handle keyboard input
        void on_key(int key, int action);
};

class Mouse {
    private:
        float x, y;
        bool left_down;
        
    public:
        Mouse();

        // handle mouse move input
        void move(float x, float y, unsigned long frametime);

        // handle mouse scroll input
        void scroll(float y, Camera &camera, unsigned long frametime);

        // handle mouse click input
        void click(int button, int action);
};