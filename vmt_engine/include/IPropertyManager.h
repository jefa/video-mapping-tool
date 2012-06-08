#ifndef __PropertyManager_h__
#define __PropertyManager_h__

class IPropertyManager
{
	public:

	virtual void set(int aParam, float value) = 0;
    virtual float get(int aParam) = 0;

};

#endif
