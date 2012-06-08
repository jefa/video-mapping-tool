#ifndef _PROCESSMESH
#define _PROCESSMESH

#include "meshmodel.h"
#include <string>

using namespace std;
using namespace vcg;
using namespace tri;
using namespace vertex;
using namespace face;

class ProcessMesh {

   public:
        ProcessMesh();
        virtual ~ProcessMesh();

        static bool open(string fname, CMeshO *);
        static bool save(string, CMeshO *);
        static CMeshO* PoissonDiskSampling(CMeshO *, int, bool, float, int, bool, CMeshO* = 0);
        static CMeshO* ComputeNormalsForPointSet(CMeshO*, int, bool, vcg::Point3f* =0);
        static CMeshO *SurfaceReconstructionPoisson(CMeshO*, int, int, float, float);

   //protected:

   private:
        static bool openInternal(string, CMeshO *, int&);
};

#endif // PROCESSMESH_H
