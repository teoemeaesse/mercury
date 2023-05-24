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

        // writes data to the ssbo
        void set_data(unsigned long size, void *data, unsigned int usage);

        // reads all the data from the ssbo
        void get_data(unsigned long size, void *data);
};