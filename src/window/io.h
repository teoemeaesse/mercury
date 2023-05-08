#pragma once


class Keyboard {
    public:
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

        Keyboard();

        // handle keyboard input
        void on_key(int key, int action);
};

class Mouse {
    private:
        float x, y,
              x_acc, y_acc,
              scroll_acc,
              sensitivity;
        
    public:
        bool left_down;

        Mouse();

        // handle mouse move input
        void on_move(float x, float y);

        // handle mouse scroll input
        void on_scroll(float y);

        // handle mouse click input
        void on_click(int button, int action);

        // get and clear the accumulated mouse movement
        float consume_x_acc();
        float consume_y_acc();
        float consume_scroll_acc();
};