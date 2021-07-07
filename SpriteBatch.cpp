#include "SpriteBatch.h"

SpriteBatch::SpriteBatch() {}

SpriteBatch::~SpriteBatch() {}

void SpriteBatch::init()
{
    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);

    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);

    glEnableVertexAttribArray(0); // position
    glEnableVertexAttribArray(1); // uv

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

    glBindVertexArray(0);
}

void SpriteBatch::clean()
{
    _renderBatches.clear();

    for (unsigned long i = 0; i < _glyphs.size(); i++) {
        delete _glyphs[i];
    }

    _glyphs.clear();
}

void SpriteBatch::add(glm::vec3 destRect, GLuint texture, float size)
{
    Glyph* glyph = new Glyph;
    glyph->texture = texture;

    glyph->topLeft.position = glm::vec3(destRect.x - size/2, destRect.y, destRect.z + size/2);
    glyph->topLeft.uv = glm::vec2(0.0f, 1.0f);

    glyph->bottomLeft.position = glm::vec3(destRect.x - size/2, destRect.y, destRect.z - size/2);
    glyph->bottomLeft.uv = glm::vec2(0.0f, 0.0f);

    glyph->bottomRight.position = glm::vec3(destRect.x + size/2, destRect.y, destRect.z - size/2);
    glyph->bottomRight.uv = glm::vec2(1.0f, 0.0f);

    glyph->topRight.position = glm::vec3(destRect.x + size/2, destRect.y, destRect.z + size/2);
    glyph->topRight.uv = glm::vec2(1.0f, 1.0f);

    _glyphs.push_back(glyph);
}

void SpriteBatch::addGlyph(Glyph* glyph)
{
    _glyphs.push_back(glyph);
}

void SpriteBatch::createBatch()
{
    std::vector<Vertex> vertices;
    vertices.resize(_glyphs.size() * 6);

    if (_glyphs.empty()) {
        return;
    }

    int offset = 0;
    int cv = 0;
    for (unsigned long cg = 0; cg < _glyphs.size(); cg++) {
        if (cg == 0) {
            _renderBatches.push_back(new RenderBatch(offset, 6, _glyphs[cg]->texture));
        } else if (_glyphs[cg]->texture != _glyphs[cg - 1]->texture) {
            _renderBatches.push_back(new RenderBatch(offset, 6, _glyphs[cg]->texture));
        } else {
            _renderBatches.back()->numVertices += 6;
        }

        vertices[cv++] = _glyphs[cg]->topLeft;
        vertices[cv++] = _glyphs[cg]->bottomLeft;
        vertices[cv++] = _glyphs[cg]->bottomRight;
        vertices[cv++] = _glyphs[cg]->bottomRight;
        vertices[cv++] = _glyphs[cg]->topRight;
        vertices[cv++] = _glyphs[cg]->topLeft;
        offset += 6;
    }

    glBindBuffer(GL_ARRAY_BUFFER, _vbo);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void SpriteBatch::renderBatch()
{
    glBindVertexArray(_vao);

    for (unsigned long i = 0; i < _renderBatches.size(); i++) {
        glBindTexture(GL_TEXTURE_2D, _renderBatches[i]->texture);
        glDrawArrays(GL_TRIANGLES, _renderBatches[i]->offset, _renderBatches[i]->numVertices);
    }
    
    glBindVertexArray(0);
}
