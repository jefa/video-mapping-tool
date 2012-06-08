#ifndef __Material_h__
#define __Material_h__

#include "TextureManager.h"

#include "ofShader.h"
#include "ofImage.h"
#include "ofVectorMath.h"

#include <string>
using namespace std;

enum A_PARAM_MATERIAL
{
    AMBIENT_R, AMBIENT_G, AMBIENT_B, AMBIENT_A
};

class Material
{
	public:
        Material();
        virtual ~Material();
        void set(int aParam, float value);
        float get(int aParam);
        void Enable();
        void Disable();
        void SetTextureParams(string id, textureType type);

	private:
        ofVec4f ambient;
        ofShader texture_shader;

        string texID;
        textureType texType;

};

#endif
