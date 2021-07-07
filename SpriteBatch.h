#pragma once
#include "Vertex.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

class SpriteBatch {
public:
     struct Glyph {
        GLuint texture;

        Vertex topLeft;
        Vertex bottomLeft;
        Vertex bottomRight;
        Vertex topRight;
    };

    struct RenderBatch {
        RenderBatch(GLuint Offset, GLuint NumVertices, GLuint Texture): 
            offset(Offset), 
            numVertices(NumVertices), 
            texture(Texture) {}

	    GLuint offset;
	    GLuint numVertices;
	    GLuint texture;
    };

    SpriteBatch();
    ~SpriteBatch();

    void init();
    void clean();
    void add(glm::vec3 destRect, GLuint texture, float size);
    void addGlyph(Glyph* glyph);
    void createBatch();
    void renderBatch();

private:
    GLuint _vao;
    GLuint _vbo;

    std::vector<Glyph*> _glyphs;
    std::vector<RenderBatch*> _renderBatches;
};
