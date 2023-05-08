#pragma once


class SSBO {
    private:
        unsigned int ssbo;

    public:
        SSBO();
        ~SSBO();

        // binds the ssbo
        void bind(unsigned int binding_point);

        // unbinds the ssbo
        void unbind();
};