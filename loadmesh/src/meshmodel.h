#ifndef MESHMODEL_H
#define MESHMODEL_H
//#include <GL/glew.h>

#include <stdio.h>
#include <time.h>

#include <vcg/simplex/vertex/base.h>
#include <vcg/simplex/vertex/component_ocf.h>
#include <vcg/simplex/edge/base.h>
#include <vcg/simplex/face/base.h>
#include <vcg/simplex/face/component_ocf.h>

#include <vcg/complex/used_types.h>
#include <vcg/complex/complex.h>
#include <vcg/complex/allocate.h>

#include <vcg/simplex/face/topology.h>

#include <vcg/complex/algorithms/update/bounding.h>
#include <vcg/complex/algorithms/update/color.h>
#include <vcg/complex/algorithms/update/flag.h>
#include <vcg/complex/algorithms/update/normal.h>
#include <vcg/complex/algorithms/update/position.h>
#include <vcg/complex/algorithms/update/quality.h>
#include <vcg/complex/algorithms/update/selection.h>
#include <vcg/complex/algorithms/update/topology.h>

//#include <wrap/gl/trimesh.h>
#include <wrap/callback.h>
#include <wrap/io_trimesh/io_mask.h>
#include <wrap/io_trimesh/additionalinfo.h>
/*#include <QList>
#include <QString>
#include <QStringList>
#include <QFileInfo>
#include <QObject>
#include "GLLogStream.h"*/
//#include "filterscript.h"
//#include <QSemaphore>

enum MeshElement{
        MM_NONE             = 0x00000000,
        MM_VERTCOORD	        = 0x00000001,
        MM_VERTNORMAL       = 0x00000002,
        MM_VERTFLAG	        = 0x00000004,
        MM_VERTCOLOR	        = 0x00000008,
        MM_VERTQUALITY      = 0x00000010,
        MM_VERTMARK	        = 0x00000020,
        MM_VERTFACETOPO     = 0x00000040,
        MM_VERTCURV	        = 0x00000080,
        MM_VERTCURVDIR      = 0x00000100,
        MM_VERTRADIUS	    = 0x00000200,
        MM_VERTTEXCOORD     = 0x00000400,
        MM_VERTNUMBER       = 0x00000800,

        MM_FACEVERT         = 0x00001000,
        MM_FACENORMAL       = 0x00002000,
        MM_FACEFLAG	        = 0x00004000,
        MM_FACECOLOR	        = 0x00008000,
        MM_FACEQUALITY      = 0x00010000,
        MM_FACEMARK	        = 0x00020000,
        MM_FACEFACETOPO     = 0x00040000,
        MM_FACENUMBER       = 0x00080000,

        MM_WEDGTEXCOORD     = 0x00100000,
        MM_WEDGNORMAL       = 0x00200000,
        MM_WEDGCOLOR	        = 0x00400000,

        MM_UNKNOWN          = 0x00800000,


        // 	SubParts of bits
        MM_VERTFLAGSELECT   = 0x01000000,
        MM_FACEFLAGSELECT   = 0x02000000,

        // This part should be deprecated.
        MM_VERTFLAGBORDER   = 0x04000000,
        MM_FACEFLAGBORDER   = 0x08000000,

        // Per Mesh Stuff....
        MM_CAMERA			= 0x10000000,
        MM_TRANSFMATRIX     = 0x20000000,
        MM_COLOR            = 0x40000000,
        MM_POLYGONAL        = 0x80000000,
        MM_ALL				= 0xffffffff
};


// Forward declarations needed for creating the used types
class CVertexO;
class CEdge;
class CFaceO;

// Declaration of the semantic of the used types
class CUsedTypesO: public vcg::UsedTypes < vcg::Use<CVertexO>::AsVertexType,
                                           vcg::Use<CEdge   >::AsEdgeType,
                                           vcg::Use<CFaceO  >::AsFaceType >{};


// The Main Vertex Class
// Most of the attributes are optional and must be enabled before use.
// Each vertex needs 40 byte, on 32bit arch. and 44 byte on 64bit arch.

class CVertexO  : public vcg::Vertex< CUsedTypesO,
  vcg::vertex::InfoOcf,           /*  4b */
  vcg::vertex::Coord3f,           /* 12b */
  vcg::vertex::BitFlags,          /*  4b */
  vcg::vertex::Normal3f,          /* 12b */
  vcg::vertex::Qualityf,          /*  4b */
  vcg::vertex::Color4b,           /*  4b */
  vcg::vertex::VFAdjOcf,          /*  0b */
  vcg::vertex::MarkOcf,           /*  0b */
  vcg::vertex::TexCoordfOcf,      /*  0b */
  vcg::vertex::CurvaturefOcf,     /*  0b */
  vcg::vertex::CurvatureDirfOcf,  /*  0b */
  vcg::vertex::RadiusfOcf         /*  0b */
  >{
};


// The Main Edge Class
// Currently it does not contains anything.
class CEdge : public vcg::Edge<CUsedTypesO, vcg::edge::EVAdj> {
public:
	inline CEdge(){};
  inline CEdge( CVertexO * v0, CVertexO * v1){ V(0)= v0 ; V(1)= v1;};
  static inline CEdge OrderedEdge(CVertexO* v0,CVertexO* v1){
   if(v0<v1) return CEdge(v0,v1);
   else return CEdge(v1,v0);
	}
};

// Each face needs 32 byte, on 32bit arch. and 48 byte on 64bit arch.
class CFaceO    : public vcg::Face<  CUsedTypesO,
      vcg::face::InfoOcf,              /* 4b */
      vcg::face::VertexRef,            /*12b */
      vcg::face::BitFlags,             /* 4b */
      vcg::face::Normal3f,             /*12b */
      vcg::face::QualityfOcf,          /* 0b */
      vcg::face::MarkOcf,              /* 0b */
      vcg::face::Color4bOcf,           /* 0b */
      vcg::face::FFAdjOcf,             /* 0b */
      vcg::face::VFAdjOcf,             /* 0b */
      vcg::face::WedgeTexCoordfOcf     /* 0b */
    > {};

class CMeshO    : public vcg::tri::TriMesh< vcg::vertex::vector_ocf<CVertexO>, vcg::face::vector_ocf<CFaceO> > {
public :
  int sfn; //The number of selected faces.
  int svn; //The number of selected faces.
  vcg::Matrix44f Tr; // Usually it is the identity. It is applied in rendering and filters can or cannot use it. (most of the filter will ignore this)

  const vcg::Box3f &trBB()
  {
    static vcg::Box3f bb;
    bb.SetNull();
    bb.Add(Tr,bbox);
		return bb;
	}

  int currentDataMask;

    bool hasDataMask(const int maskToBeTested) const
    {
      return ((currentDataMask & maskToBeTested)!= 0);
    }

    void updateDataMask(int neededDataMask)
    {
      if( ( (neededDataMask & MM_FACEFACETOPO)!=0) && !hasDataMask(MM_FACEFACETOPO) )
      {
        face.EnableFFAdjacency();
        vcg::tri::UpdateTopology<CMeshO>::FaceFace((*this));
      }
      if( ( (neededDataMask & MM_VERTFACETOPO)!=0) && !hasDataMask(MM_VERTFACETOPO) )
      {
        vert.EnableVFAdjacency();
        face.EnableVFAdjacency();
        vcg::tri::UpdateTopology<CMeshO>::VertexFace((*this));
      }
      if( ( (neededDataMask & MM_WEDGTEXCOORD)!=0)	&& !hasDataMask(MM_WEDGTEXCOORD)) 	face.EnableWedgeTex();
      if( ( (neededDataMask & MM_FACECOLOR)!=0)			&& !hasDataMask(MM_FACECOLOR))			face.EnableColor();
      if( ( (neededDataMask & MM_FACEQUALITY)!=0)		&& !hasDataMask(MM_FACEQUALITY))		face.EnableQuality();
      if( ( (neededDataMask & MM_FACEMARK)!=0)			&& !hasDataMask(MM_FACEMARK))				face.EnableMark();
      if( ( (neededDataMask & MM_VERTMARK)!=0)			&& !hasDataMask(MM_VERTMARK))				vert.EnableMark();
      if( ( (neededDataMask & MM_VERTCURV)!=0)			&& !hasDataMask(MM_VERTCURV))				vert.EnableCurvature();
      if( ( (neededDataMask & MM_VERTCURVDIR)!=0)		&& !hasDataMask(MM_VERTCURVDIR))		vert.EnableCurvatureDir();
      if( ( (neededDataMask & MM_VERTRADIUS)!=0)		&& !hasDataMask(MM_VERTRADIUS))			vert.EnableRadius();
      if( ( (neededDataMask & MM_VERTTEXCOORD)!=0)  && !hasDataMask(MM_VERTTEXCOORD))		vert.EnableTexCoord();

      if(  ( (neededDataMask & MM_FACEFLAGBORDER) && !hasDataMask(MM_FACEFLAGBORDER) ) ||
           ( (neededDataMask & MM_VERTFLAGBORDER) && !hasDataMask(MM_VERTFLAGBORDER) )    )
      {
        if( (currentDataMask & MM_FACEFACETOPO) || (neededDataMask & MM_FACEFACETOPO))
             vcg::tri::UpdateFlags<CMeshO>::FaceBorderFromFF((*this));
        else vcg::tri::UpdateFlags<CMeshO>::FaceBorderFromNone((*this));
        vcg::tri::UpdateFlags<CMeshO>::VertexBorderFromFace((*this));
      }

      currentDataMask |= neededDataMask;
     }

    void Enable(int openingFileMask)
    {
      if( openingFileMask & vcg::tri::io::Mask::IOM_VERTTEXCOORD ) updateDataMask(MM_VERTTEXCOORD);
      if( openingFileMask & vcg::tri::io::Mask::IOM_WEDGTEXCOORD ) updateDataMask(MM_WEDGTEXCOORD);
      if( openingFileMask & vcg::tri::io::Mask::IOM_VERTCOLOR    ) updateDataMask(MM_VERTCOLOR);
      if( openingFileMask & vcg::tri::io::Mask::IOM_FACECOLOR    ) updateDataMask(MM_FACECOLOR);
      if( openingFileMask & vcg::tri::io::Mask::IOM_VERTRADIUS   ) updateDataMask(MM_VERTRADIUS);
      if( openingFileMask & vcg::tri::io::Mask::IOM_CAMERA       ) updateDataMask(MM_CAMERA);
      if( openingFileMask & vcg::tri::io::Mask::IOM_VERTQUALITY  ) updateDataMask(MM_VERTQUALITY);
      if( openingFileMask & vcg::tri::io::Mask::IOM_FACEQUALITY  ) updateDataMask(MM_FACEQUALITY);
      if( openingFileMask & vcg::tri::io::Mask::IOM_BITPOLYGONAL ) updateDataMask(MM_POLYGONAL);
    }

    void clearDataMask(int unneededDataMask)
    {
      if( ( (unneededDataMask & MM_VERTFACETOPO)!=0)	&& hasDataMask(MM_VERTFACETOPO)) {face.DisableVFAdjacency();
                                                                                        vert.DisableVFAdjacency(); }
      if( ( (unneededDataMask & MM_FACEFACETOPO)!=0)	&& hasDataMask(MM_FACEFACETOPO))	face.DisableFFAdjacency();

      if( ( (unneededDataMask & MM_WEDGTEXCOORD)!=0)	&& hasDataMask(MM_WEDGTEXCOORD)) 	face.DisableWedgeTex();
      if( ( (unneededDataMask & MM_FACECOLOR)!=0)			&& hasDataMask(MM_FACECOLOR))	face.DisableColor();
      if( ( (unneededDataMask & MM_FACEQUALITY)!=0)		&& hasDataMask(MM_FACEQUALITY))		face.DisableQuality();
      if( ( (unneededDataMask & MM_FACEMARK)!=0)			&& hasDataMask(MM_FACEMARK))	face.DisableMark();
      if( ( (unneededDataMask & MM_VERTMARK)!=0)			&& hasDataMask(MM_VERTMARK))	vert.DisableMark();
      if( ( (unneededDataMask & MM_VERTCURV)!=0)			&& hasDataMask(MM_VERTCURV))	vert.DisableCurvature();
      if( ( (unneededDataMask & MM_VERTCURVDIR)!=0)		&& hasDataMask(MM_VERTCURVDIR))		vert.DisableCurvatureDir();
      if( ( (unneededDataMask & MM_VERTRADIUS)!=0)		&& hasDataMask(MM_VERTRADIUS))		vert.DisableRadius();
      if( ( (unneededDataMask & MM_VERTTEXCOORD)!=0)	&& hasDataMask(MM_VERTTEXCOORD))	vert.DisableTexCoord();

      currentDataMask = currentDataMask & (~unneededDataMask);
    }
};


#endif
