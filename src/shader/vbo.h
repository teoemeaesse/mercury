#pragma once


class VBO {
    private:
        unsigned int vbo;

    public:
        VBO();
        ~VBO();

        // binds the vbo
        void bind();

        // unbinds the vbo
        void unbind();

        // load vertex data
        void set_data(unsigned long size, void *data, unsigned int usage);
};