#include "QuadGroup.h"
#include <limits>

QuadGroup::QuadGroup(string name) {
    this->name = name;
}

QuadGroup::~QuadGroup() {
    //dtor
}

string QuadGroup::getName() {
    return name;
}

void QuadGroup::addQuad2D(Quad2D* quad) {
    quads2D.push_back(quad);
    CalculateBounds();
}

vector<Quad2D*> QuadGroup::getQuads() {
    return quads2D;
}

void QuadGroup::CalculateBounds() {
    float minX = numeric_limits<float>::max();
    float minY = numeric_limits<float>::max();
    float maxX = numeric_limits<float>::min();
    float maxY = numeric_limits<float>::min();

    vector<Quad2D*>::iterator quadsIt;
    for(quadsIt = quads2D.begin(); quadsIt != quads2D.end(); quadsIt++) {
        for(int i = 0; i < 4; i++) {
            ofVec2f p = (*quadsIt)->getPoint(i);
            if (p.x < minX) minX = p.x;
            if (p.x > maxX) maxX = p.x;
            if (p.y < minY) minY = p.y;
            if (p.y > maxY) maxY = p.y;
        }
    }

    //bounds.set(minX, minY, maxX - minX, maxY - minY);
    genUVWCoords();
}

void QuadGroup::genUVWCoords() {
    vector<Quad2D*>::iterator quadsIt;

    //Case FaceMap
    /*for(quadsIt = quads2D.begin(); quadsIt != quads2D.end(); quadsIt++) {
        (*quadsIt)->setUVCoordinate(0, 0,0);
        (*quadsIt)->setUVCoordinate(1, 1,0);
        (*quadsIt)->setUVCoordinate(2, 1,1);
        (*quadsIt)->setUVCoordinate(3, 0,1);
    }*/

    //Case PlanarMap
    for(quadsIt = quads2D.begin(); quadsIt != quads2D.end(); quadsIt++) {
        for(int i = 0; i < 4; i++) {
            ofVec2f p = (*quadsIt)->getPoint(i);
            float uCoord = (p.x - bounds.x) / (bounds.width);
            float vCoord = (p.y - bounds.y) / (bounds.height);
            (*quadsIt)->setUVCoordinate(i, uCoord,vCoord);
        }
    }

}

float QuadGroup::get(int aParam) {
    if(!quads2D.empty())
        return (*(quads2D.begin()))->get(aParam);
    else
        return 0;
}

void QuadGroup::SetTextureParams(string key, textureType type) {
    vector<Quad2D*>::iterator quadsIt;
    for(quadsIt = quads2D.begin(); quadsIt != quads2D.end(); quadsIt++) {
        (*quadsIt)->getMaterial()->SetTextureParams(key, type);
    }
}

void QuadGroup::set(int aParam, float aValue) {
    switch(aParam) {
        case AMBIENT_R:
        case AMBIENT_G:
        case AMBIENT_B:
        case AMBIENT_A:
            vector<Quad2D*>::iterator quadsIt;
            for(quadsIt = quads2D.begin(); quadsIt != quads2D.end(); quadsIt++) {
                (*quadsIt)->set(aParam, aValue);
            }
            break;
    }
}

SerializedNode* QuadGroup::Serialize() {
    SerializedNode *node = new SerializedNode("group");
    node->addAttribute("id", this->name);

    vector<Quad2D*>::iterator quadsIt;
    for(quadsIt = quads2D.begin(); quadsIt != quads2D.end(); quadsIt++) {
        SerializedNode *quadNode = new SerializedNode("quad");
        quadNode->addAttribute("id", (*quadsIt)->getId());
        node->addChildNode(quadNode);
    }

    return node;
}
