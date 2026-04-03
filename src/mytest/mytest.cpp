/*
 * Copyright � 2012-2015 Graham Sellers
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#include <sb7.h>
#include <vmath.h>

// Remove this to draw only a single cube!
// #define MANY_CUBES

class mytest_app : public sb7::application
{
    void init()
    {
        static const char title[] = "OpenGL SuperBible - My Test";

        sb7::application::init();

        memcpy(info.title, title, sizeof(title));
    }

    GLuint compile_shaders(void)
    {
        GLuint vertex_shader;
        GLuint fragment_shader;
        GLuint program;
        // Source code for vertex shader
        static const GLchar *vertex_shader_source[] =
            {
                "#version 450 core \n"
                " \n"
                "void main(void) \n"
                "{ \n"
                " gl_Position = vec4(0.0, 0.0, 0.5, 1.0); \n"
                "} \n"};
        // Source code for fragment shader
        static const GLchar *fragment_shader_source[] =
            {
                "#version 450 core \n"
                " \n"
                "out vec4 color;                                                    \n"
                "                                                                   \n"
                "void main(void)                                                    \n"
                "{                                                                  \n"
                "    color = vec4(0.0, 0.8, 1.0, 1.0);                              \n"
                "} \n"};

        // Create and compile vertex shader
        vertex_shader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex_shader, 1, vertex_shader_source, NULL);
        glCompileShader(vertex_shader);

        // Create and compile fragment shader
        fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment_shader, 1, fragment_shader_source, NULL);
        glCompileShader(fragment_shader);

        // Create and link shader program
        program = glCreateProgram();
        glAttachShader(program, vertex_shader);
        glAttachShader(program, fragment_shader);
        glLinkProgram(program);

        return program;
    }

    virtual void
    startup()
    {
        program = compile_shaders();
        glCreateVertexArrays(1, &vao);
        glBindVertexArray(vao);
    }

    virtual void render(double currentTime)
    {
        const GLfloat color[] = { static_cast<GLfloat>(sin(currentTime) * 0.5 + 0.5),
                                  static_cast<GLfloat>(cos(currentTime) * 0.5 + 0.5),
                                  0.0f, 1.0f };
        glClearBufferfv(GL_COLOR, 0, color);

        // Use the shader program
        glUseProgram(program);

        // Draw a single point
        glDrawArrays(GL_POINTS, 0, 1);
    }

    virtual void shutdown()
    {
        glDeleteVertexArrays(1, &vao);
        glDeleteProgram(program);
        glDeleteVertexArrays(1, &vao);
    }

private:
    GLuint program;
    GLuint vao;
};

DECLARE_MAIN(mytest_app)
