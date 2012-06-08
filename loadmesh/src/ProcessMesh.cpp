#include "ProcessMesh.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
//#include <vcg/complex/trimesh/allocate.h>
#include <vcg/complex/algorithms/point_sampling.h>
#include <vcg/complex/algorithms/update/bounding.h>
#include <vcg/space/normal_extrapolation.h>
#include <wrap/io_trimesh/import.h>

#include <wrap/io_trimesh/export_ply.h>
#include <wrap/io_trimesh/export_stl.h>
#include <wrap/io_trimesh/export_obj.h>
#include <wrap/io_trimesh/export_vrml.h>
#include <wrap/io_trimesh/export_dxf.h>
#include <wrap/io_trimesh/export_vmi.h>
#include <wrap/io_trimesh/export.h>

//#include <lib3ds/node.h>
//#include <wrap/io_trimesh/export_3ds.h>

//PARA POISSON RECONSTRUCTION
//#include <common/interfaces.h>
#include <vcg/complex/algorithms/create/platonic.h>
//#include "filter_poisson.h"
#include "poisson/Geometry.h"
#include "poisson/PoissonParam.h"
//---

using namespace std;
using namespace vcg;

int Execute2(PoissonParam &Par, vector<Point3D<float> > Pts, vector<Point3D<float> > Nor, 	CoredVectorMeshData &mesh, Point3D<float> &newCenter, float &newScale, vcg::CallBackPos *cb );

class JefaBaseSampler
{
	public:
	JefaBaseSampler(CMeshO* _m){m=_m; uvSpaceFlag = false; qualitySampling=false; /*tex=0;*/};
	CMeshO *m;
	//QImage* tex;
	int texSamplingWidth;
	int texSamplingHeight;
	bool uvSpaceFlag;
	bool qualitySampling;

	void AddVert(const CMeshO::VertexType &p)
	{
		tri::Allocator<CMeshO>::AddVertices(*m,1);
		m->vert.back().ImportData(p);
	}

	void AddFace(const CMeshO::FaceType &f, CMeshO::CoordType p)
	{
		tri::Allocator<CMeshO>::AddVertices(*m,1);
		m->vert.back().P() = f.P(0)*p[0] + f.P(1)*p[1] +f.P(2)*p[2];
		m->vert.back().N() = f.V(0)->N()*p[0] + f.V(1)->N()*p[1] + f.V(2)->N()*p[2];

		if (qualitySampling)
      m->vert.back().Q() = f.V(0)->Q()*p[0] + f.V(1)->Q()*p[1] + f.V(2)->Q()*p[2];
	}
        void AddTextureSample(const CMeshO::FaceType &f, const CMeshO::CoordType &p, const Point2i &tp, float edgeDist)
	{
                if (edgeDist != .0) return;

		tri::Allocator<CMeshO>::AddVertices(*m,1);

		if(uvSpaceFlag) m->vert.back().P() = Point3f(float(tp[0]),float(tp[1]),0);
							 else m->vert.back().P() = f.P(0)*p[0] + f.P(1)*p[1] +f.P(2)*p[2];

		m->vert.back().N() = f.V(0)->N()*p[0] + f.V(1)->N()*p[1] +f.V(2)->N()*p[2];
		/*if(tex)
		{
			QRgb val;
                        // Computing normalized texels position
                        int xpos = (int)(tex->width()  * (float(tp[0])/texSamplingWidth)) % tex->width();
                        int ypos = (int)(tex->height() * (1.0- float(tp[1])/texSamplingHeight)) % tex->height();

                        if (xpos < 0) xpos += tex->width();
                        if (ypos < 0) ypos += tex->height();

			val = tex->pixel(xpos,ypos);
			m->vert.back().C().SetRGB(qRed(val),qGreen(val),qBlue(val));
		}*/

	}
}; // end class JefaBaseSampler


ProcessMesh::ProcessMesh()
{
}
ProcessMesh::~ProcessMesh()
{
}

bool ProcessMesh::open(string fname, CMeshO *cm){

    int mask = 0;

    if (!openInternal(fname, cm, mask))
    {
        printf("Opening Failure:::: \n"); // text
        return false;
    }

    if( mask & vcg::tri::io::Mask::IOM_BITPOLYGONAL)
    {
        cm->updateDataMask(MM_POLYGONAL); // just to be sure. Hopefully it should be done in the plugin...
        int degNum = tri::Clean<CMeshO>::RemoveDegenerateFace((*cm));
        if(degNum)
            printf("Warning model contains %i degenerate faces. Removed them.\n", degNum);
        cm->updateDataMask(MM_FACEFACETOPO);
        vcg::tri::UpdateNormals<CMeshO>::PerBitQuadFaceNormalized((*cm));
        vcg::tri::UpdateNormals<CMeshO>::PerVertexFromCurrentFaceNormal((*cm));
    } // standard case
    else
    {
        if( mask & vcg::tri::io::Mask::IOM_VERTNORMAL)
            vcg::tri::UpdateNormals<CMeshO>::PerFace((*cm));
        else
            vcg::tri::UpdateNormals<CMeshO>::PerVertexNormalizedPerFaceNormalized((*cm));
    }
    vcg::tri::UpdateBounding<CMeshO>::Box((*cm));					// updates bounding box

    if(cm->fn==0){
        if((mask & vcg::tri::io::Mask::IOM_VERTNORMAL))
            cm->updateDataMask(MM_VERTNORMAL);
    }
    else
        cm->updateDataMask(MM_VERTNORMAL);

    int delVertNum = vcg::tri::Clean<CMeshO>::RemoveDegenerateVertex((*cm));
    int delFaceNum = vcg::tri::Clean<CMeshO>::RemoveDegenerateFace((*cm));

    if(delVertNum>0 || delFaceNum>0 )
        printf("MeshLab Warning::: Warning mesh contains %d vertices with NAN coords and %d degenerated faces.\nCorrected.\n", delVertNum, delFaceNum);

    return true;
}

bool ProcessMesh::openInternal(string filename, CMeshO *cm, int &mask)
{
    tri::io::ImporterOBJ<CMeshO>::Info oi;
    //oi.cb = cb;
    if (!tri::io::ImporterOBJ<CMeshO>::LoadMask(filename.c_str(), oi))
    {
        printf("ERROR::: MASK NOT LOADED\n");
        return false;
    }
    cm->Enable(oi.mask);
    //m.Enable(oi.mask);

    int result = tri::io::ImporterOBJ<CMeshO>::Open(/*m.*/(*cm), filename.c_str(), oi);
    if (result != tri::io::ImporterOBJ<CMeshO>::E_NOERROR)
    {
        const char* errMsg = tri::io::ImporterOBJ<CMeshO>::ErrorMsg(result);
        if (result & tri::io::ImporterOBJ<CMeshO>::E_NON_CRITICAL_ERROR)
            //errorMessage = errorMsgFormat.arg(fileName, tri::io::ImporterOBJ<CMeshO>::ErrorMsg(result));
            printf("ERROR::: ENONCRITICAL=%s\n",errMsg);
        //static const char *ErrorMsg(int error)
        else
        {
            //errorMessage = errorMsgFormat.arg(fileName, tri::io::ImporterOBJ<CMeshO>::ErrorMsg(result));
            printf("ERROR::: ELSE ENONCRITICAL=%s\n", errMsg);
            return false;
        }
    }

    if(oi.mask & vcg::tri::io::Mask::IOM_WEDGNORMAL) {
        //normalsUpdated = true;
         printf("NORMALS UPDATEDDDDD!!!!\n");
    }
    cm->Enable(oi.mask);
    if(cm->hasDataMask(/*MeshModel::*/MM_POLYGONAL)) printf("\t========= Mesh is Polygonal!");
    mask = oi.mask;
    printf("Fin!\n");
    return true;
}

bool ProcessMesh::save(string outFilename, CMeshO *cm){
    string fullName = outFilename + ".wrl";
    int result = tri::io::ExporterWRL<CMeshO>::Save((*cm),fullName.c_str(),/*mask*/1,/*cb*/NULL);
    if(result!=0)
    {
        //printf("ERROR AL SALVAR 3DS::: %s\n", tri::io::Exporter3DS<CMeshO>::ErrorMsg(result));
        printf("ERROR AL SALVAR WRL::: %s\n", tri::io::ExporterWRL<CMeshO>::ErrorMsg(result));
        return false;
    }
    fullName = outFilename + ".obj";
    result = tri::io::ExporterOBJ<CMeshO>::Save((*cm),fullName.c_str(),/*mask*/1,/*cb*/NULL);
    if(result!=0)
    {
        //printf("ERROR AL SALVAR 3DS::: %s\n", tri::io::Exporter3DS<CMeshO>::ErrorMsg(result));
        printf("ERROR AL SALVAR OBJ::: %s\n", tri::io::ExporterWRL<CMeshO>::ErrorMsg(result));
        return false;
    }
    fullName = outFilename + ".3ds";
    /*result = tri::io::Exporter3DS<CMeshO>::Save((*cm),fullName.c_str(),1,NULL);
    if(result!=0)
    {
        printf("ERROR AL SALVAR 3DS::: %s\n", tri::io::Exporter3DS<CMeshO>::ErrorMsg(result));
        return false;
    }*/
    return true;
}

CMeshO* ProcessMesh::PoissonDiskSampling(CMeshO *cm, int sampleNum, bool subsampleFlag, float radius, int montecarloRate, bool refineFlag, CMeshO *refineMesh)
{
    /*case FP_POISSONDISK_SAMPLING :
    parlst.addParam(new RichInt("SampleNum", 1000, "Number of samples", "The desired number of samples. The ray of the disk is calculated according to the sampling density."));
    parlst.addParam(new RichAbsPerc("Radius", 0, 0, md.mm()->cm.bbox.Diag(), "Explicit Radius", "If not zero this parameter override the previous parameter to allow exact radius specification"));
    parlst.addParam(new RichInt("MontecarloRate", 20, "MonterCarlo OverSampling", "The over-sampling rate that is used to generate the intial Montecarlo samples (e.g. if this parameter is <i>K</i> means that<i>K</i> x <i>poisson sample</i> points will be used). The generated Poisson-disk samples are a subset of these initial Montecarlo samples. Larger this number slows the process but make it a bit more accurate."));
    parlst.addParam(new RichBool("Subsample", false, "Base Mesh Subsampling", "If true the original vertices of the base mesh are used as base set of points. In this case the SampleNum should be obviously much smaller than the original vertex number.<br>Note that this option is very useful in the case you want to subsample a dense point cloud."));
    parlst.addParam(new RichBool("RefineFlag", false, "Refine Existing Samples", "If true the vertices of the below mesh are used as starting vertices, and they will utterly refined by adding more and more points until possible. "));
    parlst.addParam(new RichMesh("RefineMesh", md.mm(),&md, "Samples to be refined", "Used only if the above option is checked. "));*/

    if (cm->fn==0 && subsampleFlag==false)
    {
        printf("ProcessMesh::PoissonDiskSampling: This filter requires a mesh. It does not work on PointSet.\n");
        return false; // cannot continue
    }

    CMeshO *curCM = cm;
    CMeshO *newCM = new CMeshO();
    newCM->updateDataMask(curCM->currentDataMask);

    if(radius==0) radius = tri::SurfaceSampling<CMeshO,JefaBaseSampler>::ComputePoissonDiskRadius((*curCM),sampleNum);
    else sampleNum = tri::SurfaceSampling<CMeshO,JefaBaseSampler>::ComputePoissonSampleNum((*curCM),radius);

    printf("ProcessMesh::PoissonDiskSampling: Computing %i Poisson Samples for an expected radius of %f\n",sampleNum,radius);

    CMeshO *presampledMesh=&(*curCM);

    CMeshO MontecarloMesh; // this mesh is used only if we need real poisson sampling (and therefore we need to choose points different from the starting mesh vertices)

    if(!subsampleFlag)
    {
        //QTime tt;
        //tt.start();
        JefaBaseSampler sampler(&MontecarloMesh);
        sampler.qualitySampling =true;
        tri::SurfaceSampling<CMeshO,JefaBaseSampler>::Montecarlo((*cm), sampler, sampleNum*montecarloRate);
        MontecarloMesh.bbox = (*cm).bbox; // we want the same bounding box
        presampledMesh=&MontecarloMesh;
        //printf("ProcessMesh::PoissonDiskSampling: Generated %i Montecarlo Samples (%i msec)",MontecarloMesh.vn,tt.elapsed());
    }

    JefaBaseSampler mps(newCM);

    tri::SurfaceSampling<CMeshO,JefaBaseSampler>::PoissonDiskParam pp;
    if(refineFlag)
    {
        pp.preGenFlag=true;
        pp.preGenMesh=&((*refineMesh));
    }

    tri::SurfaceSampling<CMeshO,JefaBaseSampler>::PoissonDiskPruning((*curCM), mps, *presampledMesh, radius, pp);
    vcg::tri::UpdateBounding<CMeshO>::Box((*newCM));
    printf("ProcessMesh::PoissonDiskSampling: Sampling created a new mesh of %i points\n", newCM->vn);
    return newCM;
}

CMeshO* ProcessMesh::ComputeNormalsForPointSet(CMeshO *cm, int kNeigbors, bool flipFlag, vcg::Point3f *viewp)
{
    //case FP_NORMAL_EXTRAPOLATION:
    //parlst.addParam(new RichInt ("K",(int)10,"Number of neigbors","The number of neighbors used to estimate and propagate normals."));
    //parlst.addParam(new RichBool("flipFlag",false,"Flip normals w.r.t. viewpoint","If the 'viewpoint' (i.e. scanner position) is known, it can be used to disambiguate normals orientation, so that all the normals will be oriented in the same direction."));
    //parlst.addParam(new RichPoint3f("viewPos",m.cm.shot.Extrinsics.Tra(),"Viewpoint Pos.","The viewpoint position can be set by hand (i.e. getting the current viewpoint) or it can be retrieved from mesh camera, if the viewpoint position is stored there."));

    tri::Allocator<CMeshO>::CompactVertexVector((*cm));
    NormalExtrapolation<vector<CVertexO> >::ExtrapolateNormals((*cm).vert.begin(), (*cm).vert.end(), kNeigbors,-1,NormalExtrapolation<vector<CVertexO> >::IsCorrect);
    if (flipFlag==true)
    {
        //vcg::Point3f viewp=par.getPoint3f("viewPos");
        CMeshO::VertexIterator vi;
        for(vi=(*cm).vert.begin();vi!=(*cm).vert.end();++vi)
        {
            if ((*vi).N().dot((*viewp)-(*vi).P())<0.0f)
            {
                (*vi).N()=-(*vi).N();
            }
        }
    }
    cout << "number of normal after ComputeNormalsForPointSet : " <<  (*cm).vn  << '\n';
    return cm;

}
CMeshO* ProcessMesh::SurfaceReconstructionPoisson(CMeshO *cm, int OctDepth, int SolverDivide, float SamplesPerNode, float Offset)
{
    /*case FP_POISSON_RECON :  return QString("Use the points and normal to build a surface using the Poisson Surface reconstruction approach.");
    parlst.addParam(new RichInt ("OctDepth",
                                    6,
                                    "Octree Depth",
                                    "Set the depth of the Octree used for extracting the final surface. Suggested range 5..10. Higher numbers mean higher precision in the reconstruction but also higher processing times. Be patient.\n"));
    parlst.addParam(new RichInt ("SolverDivide",
                                    6,
                                    "Solver Divide",
                                    "This integer argument specifies the depth at which a block Gauss-Seidel solver is used to solve the Laplacian equation.\n"
                                    "Using this parameter helps reduce the memory overhead at the cost of a small increase in reconstruction time. \n"
                                    "In practice, the authors have found that for reconstructions of depth 9 or higher a subdivide depth of 7 or 8 can reduce the memory usage.\n"
                                    "The default value is 8.\n"));
    parlst.addParam(new RichFloat ("SamplesPerNode",
                                    1.0,
                                    "Samples per Node",
                                    "This floating point value specifies the minimum number of sample points that should fall within an octree node as the octree\n"
                                    "construction is adapted to sampling density. For noise-free samples, small values in the range [1.0 - 5.0] can be used.\n"
                                    "For more noisy samples, larger values in the range [15.0 - 20.0] may be needed to provide a smoother, noise-reduced, reconstruction.\n"
                                    "The default value is 1.0."));
    parlst.addParam(new RichFloat ("Offset",
                                     1.0,
                                     "Surface offsetting",
                                     "This floating point value specifies a correction value for the isosurface threshold that is chosen.\n"
                                     "Values < 1 means internal offsetting, >1 external offsetting."
                                     "Good values are in the range 0.5 .. 2.\n"
                                     "The default value is 1.0 (no offsetting)."));
    */

    CMeshO *pm = new CMeshO();
    vector<Point3D<float> > Pts((*cm).vn);
	vector<Point3D<float> > Nor((*cm).vn);
	CoredVectorMeshData mesh;

	if (cm->hasDataMask(MM_WEDGTEXCOORD)){
		cm->clearDataMask(MM_WEDGTEXCOORD);
	}
	if (cm->hasDataMask(MM_VERTTEXCOORD)){
		cm->clearDataMask(MM_VERTTEXCOORD);
	}

	int cnt=0;
	CMeshO::VertexIterator vi;
	for(vi=(*cm).vert.begin(); vi!=(*cm).vert.end(); ++vi)
	if(!(*vi).IsD()){
        (*vi).N().Normalize();
        for(int ii=0;ii<3;++ii){
                Pts[cnt].coords[ii]=(*vi).P()[ii];
                Nor[cnt].coords[ii]=(*vi).N()[ii];
        }
        ++cnt;
    }
	assert(cnt==(*cm).vn);
	// Log function dump textual info in the lower part of the MeshLab screen.
	PoissonParam pp;
	pp.Depth = OctDepth;
	pp.SamplesPerNode = SamplesPerNode;
	pp.SolverDivide = SolverDivide;
	pp.Offset = Offset;
	Point3D<float> center;
	float scale;

	int ret = Execute2(pp, Pts, Nor, mesh,center,scale,/*cb*/NULL);
	mesh.resetIterator();
	int vm = mesh.outOfCorePointCount()+mesh.inCorePoints.size();
	int fm = mesh.triangleCount();

	printf("Successfully created a mesh of %d vert and %d faces\n",vm,fm);

	//(*cm).Clear();

	tri::Allocator<CMeshO>::AddVertices((*pm),vm);
	tri::Allocator<CMeshO>::AddFaces((*pm),fm);

    Point3D<float> p;
	int i;
	for (i=0; i < int(mesh.inCorePoints.size()); i++){
		p=mesh.inCorePoints[i];
		(*pm).vert[i].P()[0] = p.coords[0]*scale+center.coords[0];
		(*pm).vert[i].P()[1] = p.coords[1]*scale+center.coords[1];
		(*pm).vert[i].P()[2] = p.coords[2]*scale+center.coords[2];
    }
	for (int ii=0; ii < mesh.outOfCorePointCount(); ii++){
		mesh.nextOutOfCorePoint(p);
		(*pm).vert[ii+i].P()[0] = p.coords[0]*scale+center.coords[0];
		(*pm).vert[ii+i].P()[1] = p.coords[1]*scale+center.coords[1];
		(*pm).vert[ii+i].P()[2] = p.coords[2]*scale+center.coords[2];
	}

    TriangleIndex tIndex;
    int inCoreFlag;
    int nr_faces=mesh.triangleCount();
    for (i=0; i < nr_faces; i++){
		//
		// create and fill a struct that the ply code can handle
		//
		mesh.nextTriangle(tIndex,inCoreFlag);
		if(!(inCoreFlag & CoredMeshData::IN_CORE_FLAG[0])){tIndex.idx[0]+=int(mesh.inCorePoints.size());}
		if(!(inCoreFlag & CoredMeshData::IN_CORE_FLAG[1])){tIndex.idx[1]+=int(mesh.inCorePoints.size());}
		if(!(inCoreFlag & CoredMeshData::IN_CORE_FLAG[2])){tIndex.idx[2]+=int(mesh.inCorePoints.size());}
		for(int j=0; j < 3; j++)
		{
			(*pm).face[i].V(j) = &(*pm).vert[tIndex.idx[j]];
		}
		//ply_put_element(ply, (void *) &ply_face);
		//delete[] ply_face.vertices;
    }  // for, write faces


//	for(int i=0;i<mesh.inCorePoints.size();++i){
//		mesh.triangles[i].idx[0]+=mesh.inCorePoints.size();
//		mesh.triangles[i].idx[1]+=mesh.inCorePoints.size();
//		mesh.triangles[i].idx[2]+=mesh.inCorePoints.size();
//		}
//	Build((*cm),mesh.inCorePoints,mesh.triangles);
//	printf("Successfully created a mesh of %i faces",(*pm).vn);

    vcg::tri::UpdateBounding<CMeshO>::Box((*pm));
    vcg::tri::UpdateNormals<CMeshO>::PerVertexNormalizedPerFace((*pm));

    return pm;
}
