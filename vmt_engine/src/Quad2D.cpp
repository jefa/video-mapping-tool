#include "Quad2D.h"
#include "ofGraphics.h"
#include "ofMain.h"

//Radio de los circulos
static const float radius = 5.0f;

Quad2D::Quad2D(float x1, float y1, float x2, float y2,
               float x3, float y3, float x4, float y4) {
    selected = false;
    enabled = false;

    quadPoints[0] = x1;quadPoints[1] = y1;
    quadPoints[2] = x2;quadPoints[3] = y2;
    quadPoints[4] = x3;quadPoints[5] = y3;
    quadPoints[6] = x4;quadPoints[7] = y4;

    quadTextCoords[0] = 0;quadTextCoords[1] = 0;
    quadTextCoords[2] = 1;quadTextCoords[3] = 0;
    quadTextCoords[4] = 1;quadTextCoords[5] = 1;
    quadTextCoords[6] = 0;quadTextCoords[7] = 1;

    this->material = new Material();
}

Quad2D::~Quad2D() {
    //dtor
}

void Quad2D::setEnabled(bool enabled) {
    this->enabled = enabled;
}

bool Quad2D::isEnabled() {
    return this->enabled;
}

bool Quad2D::isSelected() {
    return this->selected;
}
void Quad2D::setMaterial(Material *mat) {
    this->material = mat;
}

Material* Quad2D::getMaterial() {
    return this->material;
}

void Quad2D::setPoint(int i, ofVec2f p) {
    if(i >= 0 && i <= 3) {
        quadPoints[i * 2] = p.x;
        quadPoints[1 + (i * 2)] = p.y;
    }
}

void Quad2D::setPoint(int i, float x, float y) {
    if(i >= 0 && i <= 3) {
        quadPoints[i * 2] = x;
        quadPoints[1 + (i * 2)] = y;
    }
}

ofVec2f Quad2D::getPoint(int i) {
    if(i >= 0 && i <= 3) {
        return ofVec2f(quadPoints[i * 2], quadPoints[1 + (i * 2)]);
    }
    return ofVec2f(-1, -1);
}

void Quad2D::setUVCoordinate(int i, float u, float v) {
    if(i >= 0 && i <= 3) {
        quadTextCoords[i * 2] = u;
        quadTextCoords[1 + (i * 2)] = v;
    }
}

int Quad2D::getControlPointAt(int x, int y) {
    int result = -1;
    if(!this->selected)
        return result;

    for(int i = 0; i < 4; i++) {
        float xc = quadPoints[i * 2];
        float yc = quadPoints[(i * 2) + 1];

        if(ofDistSquared(xc, yc, x, y) <= pow(radius, 2)) {
            return i;
        }
    }
    return result;
}

void Quad2D::setSelected(bool selected) {
    this->selected = selected;
}

void Quad2D::draw() {
    if(!enabled) {
        return;
    }

    if(this->material != NULL){
        this->material->Enable();
    }
    else {
        glColor4f(0.7f, 0.8f, 0.9f, 1.0f);
    }

    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glTexCoordPointer(2, GL_FLOAT, 0, &quadTextCoords);

    glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, &quadPoints[0]);

	glDrawArrays(GL_QUADS, 0, 4);

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

    if(this->material != NULL){
        this->material->Disable();
    }

    //Esto debería pasar solo en el editor
    if(selected) {
        glColor4f(1.0f, 0.3f, 0.3f, 1.0f);
        glBegin(GL_LINE_LOOP);
        for(int i = 0; i < 8; i += 2) {
            glVertex2f(quadPoints[i], quadPoints[i+1]);
        }
        glEnd();
    }
    /*else {
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    }*/

    /*if(selected) {
        ofCircle(quadPoints[0], quadPoints[1], radius);
        ofCircle(quadPoints[2], quadPoints[3], radius);
        ofCircle(quadPoints[4], quadPoints[5], radius);
        ofCircle(quadPoints[6], quadPoints[7], radius);
    }*/

}

void Quad2D::setId(string id){
    this->id = id;
}

string Quad2D::getId(){
    return this->id;
}

void Quad2D::set(int aParam, float value) {
    switch(aParam) {
        case AMBIENT_R:
        case AMBIENT_G:
        case AMBIENT_B:
        case AMBIENT_A:
            material->set(aParam, value);
            break;
    }
}

float Quad2D::get(int aParam) {
    switch(aParam) {
        case AMBIENT_R:
        case AMBIENT_G:
        case AMBIENT_B:
        case AMBIENT_A:
            return material->get(aParam);
            break;
    }
    return -1.0f;
}

SerializedNode* Quad2D::Serialize() {
    SerializedNode *node = new SerializedNode("quad");

    node->addAttribute("id", this->id);
    node->addAttribute("enabled", this->enabled);
    node->addAttribute("p0", this->getPoint(0));
    node->addAttribute("p1", this->getPoint(1));
    node->addAttribute("p2", this->getPoint(2));
    node->addAttribute("p3", this->getPoint(3));

    return node;
}
