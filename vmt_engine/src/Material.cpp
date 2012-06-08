#include "Material.h"
#include "ofMain.h"

Material::Material(){
    ambient = ofVec4f(0.7f, 0.8f, 0.9f, 1.0f);
    texture_shader.load("shaders/texture_ambient");
    this->texID = "";
}

Material::~Material(){
}

void Material::SetTextureParams(string id, textureType type) {
    this->texID = id;
    this->texType = type;
}

void Material::Enable(){
    if(texID.empty()) {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(ambient.x, ambient.y, ambient.z, ambient.w);
    }
    else {
        try {
            ofTexture &tex = TextureManager::GetTextureReference(texID, texType);
            ofTextureData texData = tex.texData;

            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(texData.textureTarget, (GLuint)texData.textureID);

            texture_shader.begin();

            texture_shader.setUniform2f("texCorrection", texData.width / texData.tex_w, texData.height / texData.tex_h);
            texture_shader.setUniform4f("color", ambient[0], ambient[1], ambient[2], ambient[3]);
            texture_shader.setUniform1i("tex", 0);
        } catch (exception& e) {
            ofLog(OF_LOG_ERROR, "Error al obtener textura: %s", e.what());
        }
    }
}

void Material::Disable() {
	texture_shader.end();
	glDisable(GL_TEXTURE_2D);
}

float Material::get(int aParam) {
    switch(aParam) {
        case AMBIENT_R:
            return ambient.x;
        case AMBIENT_G:
            return ambient.y;
        case AMBIENT_B:
            return ambient.z;
        case AMBIENT_A:
            return ambient.w;
    }
	return 0;
}

void Material::set(int aParam, float value) {
    switch(aParam)
    {
        case AMBIENT_R:
            ambient.x = value;
            break;
        case AMBIENT_G:
            ambient.y = value;
            break;
        case AMBIENT_B:
            ambient.z = value;
            break;
        case AMBIENT_A:
            ambient.w = value;
            break;
    }
}

