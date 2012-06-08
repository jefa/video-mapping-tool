#include "Layer2D.h"

Layer2D::Layer2D()
{
    this->enabled = true;
}

Layer2D::Layer2D(string name){
    this->enabled = true;
    this->name = name;
}

Layer2D::~Layer2D()
{
    //dtor
}

Quad2D* Layer2D::addQuad2D(string id) {
    Quad2D* quad2D = new Quad2D();
    quad2D->setId(id);
    quads2D_map.insert(pair<string, Quad2D*>(id, quad2D));

    return quad2D;
}

Quad2D* Layer2D::getQuad2D(string id) {
    map<string, Quad2D*>::const_iterator iter;
    for (iter=quads2D_map.begin(); iter != quads2D_map.end(); ++iter) {
        if(iter->first.compare(id) == 0)
            return iter->second;
    }
    return NULL;
}

void Layer2D::setEnabled(bool enabled) {
    this->enabled = enabled;
}

void Layer2D::setName(string name){
    this->name = name;
}

bool Layer2D::isEnabled(){
    return enabled;
}

string Layer2D::getName(){
    return this->name;
}

map<string, Quad2D*> Layer2D::getQuads2D() {
    return quads2D_map;
}

void Layer2D::draw() {
    if(!enabled)
        return;

    map<string, Quad2D*>::const_iterator iter;
    for (iter=quads2D_map.begin(); iter != quads2D_map.end(); ++iter) {
        iter->second->draw();
    }
}

SerializedNode* Layer2D::Serialize() {
    SerializedNode *node = new SerializedNode("layer");

    node->addAttribute("id", this->name);

    map<string, Quad2D*>::const_iterator iter;
    for (iter=quads2D_map.begin(); iter != quads2D_map.end(); ++iter) {
        node->addChildNode(iter->second->Serialize());
    }

    return node;
}
