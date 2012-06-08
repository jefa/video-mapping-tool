#include "ProcessMesh.h"
#include "processdialog.h"

#include <iostream>
#include <stdio.h>
#include <string>

//#include <QtGui\QApplication>
#include <QApplication>

using namespace std;

void pruebaJavier(){
    string fileName = "data/greek_helmet.obj";

    CMeshO cm;
    cm.Tr.SetIdentity();
    cm.sfn=0;
    cm.svn=0;
    cm.currentDataMask = MM_NONE;
    cm.currentDataMask |= MM_VERTCOORD | MM_VERTNORMAL | MM_VERTFLAG ;
    cm.currentDataMask |= MM_FACEVERT  | MM_FACENORMAL | MM_FACEFLAG ;

    //int mask = 0;
    bool modelOpened = ProcessMesh::open(fileName, (&cm));
    printf("MODEL OPENED==== %d\n", modelOpened);
    cout << "number of vertices " <<  cm.vert.size() << endl;
    cout << "number of faces " << cm.face.size()<< endl<< endl;

    printf("=== ProcessMesh::PoissonDiskSampling\n");
    bool subsampleFlag = true;
    int sampleNum = 5000;
    float radius = 0.f;
    CMeshO *newCmesh = ProcessMesh::PoissonDiskSampling((&cm), sampleNum, subsampleFlag, radius, 20, false);
    if (newCmesh != NULL){
        cout << "SALIDA POISSON::: " << endl;
        cout << "number of vertices " <<  newCmesh->vert.size() << endl;
        cout << "number of faces " << newCmesh->face.size()<< endl<< endl;

        bool modelSaved = ProcessMesh::save(string("CMESH"), newCmesh);
        printf("MODEL SAVED?? ==== %d\n\n", modelSaved);
    } else
        printf("=== NEW MESH NULL\n\n");

    printf("=== ProcessMesh::ComputeNormalsForPointSet\n");
    newCmesh = ProcessMesh::ComputeNormalsForPointSet(newCmesh, 10, false);
    if (newCmesh != NULL){
        cout << "SALIDA NORMALS::: " <<  endl;
        cout << "number of vertices " <<  newCmesh->vert.size() << endl;
        cout << "number of faces " << newCmesh->face.size()<< endl<< endl;

        bool modelSaved = ProcessMesh::save(string("CMESH"), newCmesh);
        printf("MODEL NORMALIZED SAVED?? ==== %d\n", modelSaved);
    } else
        printf("=== NEW MESH NULL\n");

    printf("=== ProcessMesh::SurfaceReconstructionPoisson\n");
	int OctDepth=6;
	float SamplesPerNode = 1.0f;
	int SolverDivide = 6;
	float Offset = 1.0;
    CMeshO *finalCmesh = ProcessMesh::SurfaceReconstructionPoisson(newCmesh, OctDepth, SolverDivide, SamplesPerNode, Offset);
    if (finalCmesh != NULL){
        cout << "SALIDA SURFACE::: " <<  endl;
        cout << "number of vertices " <<  finalCmesh->vert.size() << endl;
        cout << "number of faces " << finalCmesh->face.size()<< endl<< endl;

        bool modelSaved = ProcessMesh::save(string("FINALMESH"), finalCmesh);
        printf("FINAL MODEL SAVED?? ==== %d\n", modelSaved);
    } else
        printf("=== finalCmesh MESH NULL\n");
}

int main(int argc, char *argv[])
{

    QApplication app(argc, argv); //Qt app

    ProcessDialog dialog;
    dialog.show();

    //pruebaJavier();

    return app.exec(); //Qt app
}
