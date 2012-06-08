#ifndef ISERIALIZABLE_H
#define ISERIALIZABLE_H

#include "SerializedNode.h"

class ISerializable
{
    public:
        ISerializable() {}
        virtual ~ISerializable() {}

        virtual SerializedNode* Serialize() = 0;
    protected:
    private:
};

#endif // ISERIALIZABLE_H
