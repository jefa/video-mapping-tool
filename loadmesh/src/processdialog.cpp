#include "processdialog.h"
#include "ProcessMesh.h"

ProcessDialog::ProcessDialog(QWidget *parent)
    : QWidget(parent)
{
    errorMessageDialog = new QErrorMessage(this);

    // POISSON DISK SAMPLING GROUP
    QGroupBox *fileGroup = new QGroupBox(tr("Object files"));
    QLabel *filePathLabel = new QLabel(tr("Source:"));
    filePathEdit = new QLineEdit;
    QLabel *outputNameLabel = new QLabel(tr("Destination:"));
    outputNameEdit = new QLineEdit;
    searchButton = new QPushButton(tr("Browse"));

    QHBoxLayout *filePathLayout = new QHBoxLayout;
    filePathLayout->addWidget(filePathLabel);
    filePathLayout->addWidget(filePathEdit);
    filePathLayout->addWidget(searchButton);

    QHBoxLayout *outfilePathLayout = new QHBoxLayout;
    outfilePathLayout->addWidget(outputNameLabel);
    outfilePathLayout->addWidget(outputNameEdit);

    QVBoxLayout *fileLayout = new QVBoxLayout;
    fileLayout->addLayout(filePathLayout);
    fileLayout->addLayout(outfilePathLayout);
    fileGroup->setLayout(fileLayout);

    // POISSON DISK SAMPLING GROUP
    QGroupBox *poissonDiskGroup = new QGroupBox(tr("Poisson Disk-Sampling"));
    QLabel *sampleNumLabel = new QLabel(tr("Sample Num:"));
    sampleNumSpinBox = new QSpinBox;
    sampleNumSpinBox->setMaximum(50000);

    QLabel *radiusLabel = new QLabel(tr("Radius:"));
    radiusSpinBox = new QDoubleSpinBox;

    subsampleCheckBox = new QCheckBox(tr("SubSample?"));

    QHBoxLayout *samplesLayout = new QHBoxLayout;
    samplesLayout->addWidget(sampleNumLabel);
    samplesLayout->addWidget(sampleNumSpinBox);

    QHBoxLayout *radiusLayout = new QHBoxLayout;
    radiusLayout->addWidget(radiusLabel);
    radiusLayout->addWidget(radiusSpinBox);

    QVBoxLayout *poissonDiskLayout = new QVBoxLayout;
    poissonDiskLayout->addLayout(samplesLayout);
    poissonDiskLayout->addWidget(subsampleCheckBox);
    poissonDiskLayout->addLayout(radiusLayout);
    poissonDiskGroup->setLayout(poissonDiskLayout);

    // NORMAL COMPUTE GROUP
    QGroupBox *normalGroup = new QGroupBox(tr("Normal Extrapolation"));
    QLabel *neigborsLabel = new QLabel(tr("Neigbors (K):"));
    neigborsSpinBox = new QSpinBox;

    QHBoxLayout *neigborsLayout = new QHBoxLayout;
    neigborsLayout->addWidget(neigborsLabel);
    neigborsLayout->addWidget(neigborsSpinBox);

    flipFlagCheckBox = new QCheckBox(tr("Flip flag?"));

    QVBoxLayout *normalExtrapLayout = new QVBoxLayout;
    normalExtrapLayout->addLayout(neigborsLayout);
    normalExtrapLayout->addWidget(flipFlagCheckBox);
    normalGroup->setLayout(normalExtrapLayout);

    // POISSON RECONSTRUCTION GROUP
    QGroupBox *poissonReconstrGroup = new QGroupBox(tr("Poisson Reconstruction"));

    QLabel *octdepthLabel = new QLabel(tr("Oct depth:"));
    octdepthSpinBox = new QSpinBox;
    QHBoxLayout *octetLayout = new QHBoxLayout;
    octetLayout->addWidget(octdepthLabel);
    octetLayout->addWidget(octdepthSpinBox);

    QLabel *solverdivideLabel = new QLabel(tr("Solver divide:"));
    solverdivideSpinBox = new QSpinBox;
    QHBoxLayout *solverdivideLayout = new QHBoxLayout;
    solverdivideLayout->addWidget(solverdivideLabel);
    solverdivideLayout->addWidget(solverdivideSpinBox);

    QLabel *samplespernodeLabel = new QLabel(tr("Samples per node:"));
    samplespernodeSpinBox = new QDoubleSpinBox;
    QHBoxLayout *samplespernodeLayout = new QHBoxLayout;
    samplespernodeLayout->addWidget(samplespernodeLabel);
    samplespernodeLayout->addWidget(samplespernodeSpinBox);

    QLabel *offsetLabel = new QLabel(tr("Offset:"));
    offsetSpinBox = new QDoubleSpinBox;
    QHBoxLayout *offsetLayout = new QHBoxLayout;
    offsetLayout->addWidget(offsetLabel);
    offsetLayout->addWidget(offsetSpinBox);


    QVBoxLayout *poissonRecontrLayout = new QVBoxLayout;
    poissonRecontrLayout->addLayout(octetLayout);
    poissonRecontrLayout->addLayout(solverdivideLayout);
    poissonRecontrLayout->addLayout(samplespernodeLayout);
    poissonRecontrLayout->addLayout(offsetLayout);
    poissonReconstrGroup->setLayout(poissonRecontrLayout);

    buttonBox = new QDialogButtonBox(   QDialogButtonBox::Ok
                                     | QDialogButtonBox::Cancel);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(fileGroup);
    mainLayout->addWidget(poissonDiskGroup);
    mainLayout->addWidget(normalGroup);
    mainLayout->addWidget(poissonReconstrGroup);
    mainLayout->addStretch(1);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);

    setWindowTitle(tr("Process Mesh"));

    connect(searchButton, SIGNAL(clicked()), this, SLOT(setOpenFileName()));
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(acceptPressed()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(rejectPressed()));

    init();
}

void ProcessDialog::init(){
    sampleNumSpinBox->setValue(1000);
    radiusSpinBox->setValue(0);
    subsampleCheckBox->setChecked(true);

    neigborsSpinBox->setValue(10);
    flipFlagCheckBox->setChecked(false);

    octdepthSpinBox->setValue(6);
    solverdivideSpinBox->setValue(6);
    samplespernodeSpinBox->setValue(1);
    offsetSpinBox->setValue(1);
}

void ProcessDialog::setOpenFileName()
{
    QFileDialog::Options options;
    //if (!native->isChecked())
    //    options |= QFileDialog::DontUseNativeDialog;
    QString selectedFilter;
    QString fileName = QFileDialog::getOpenFileName(this,
                                tr("Open Object file"),
                                filePathEdit->text(),
                                tr("OBJ Files (*.obj)"),
                                &selectedFilter,
                                options);
    if (!fileName.isEmpty())
        filePathEdit->setText(fileName);
}

void ProcessDialog::acceptPressed(){

    string fileName = filePathEdit->text().toStdString();
    string ouitFileName = outputNameEdit->text().toStdString();

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
    if (!modelOpened){
        errorMessageDialog->showMessage(
                tr("Error opening file."));
        return;
    }
    cout << "number of vertices " <<  cm.vert.size() << endl;
    cout << "number of faces " << cm.face.size()<< endl<< endl;

    printf("=== ProcessMesh::PoissonDiskSampling\n");
    bool subsampleFlag = subsampleCheckBox->isChecked();
    int sampleNum = sampleNumSpinBox->value();
    float radius = radiusSpinBox->value();
    CMeshO *newCmesh = ProcessMesh::PoissonDiskSampling((&cm), sampleNum, subsampleFlag, radius, 20, false);
    if (newCmesh != NULL){
        cout << "SALIDA POISSON::: " << endl;
        cout << "number of vertices " <<  newCmesh->vert.size() << endl;
        cout << "number of faces " << newCmesh->face.size()<< endl<< endl;

        bool modelSaved = ProcessMesh::save(string("CMESH"), newCmesh);
        printf("MODEL SAVED?? ==== %d\n\n", modelSaved);
    } else {
        printf("=== NEW MESH NULL\n\n");
        errorMessageDialog->showMessage(
                tr("Error performing Poisson Disk Sampling."));
        return;
    }

    printf("=== ProcessMesh::ComputeNormalsForPointSet\n");
    newCmesh = ProcessMesh::ComputeNormalsForPointSet(newCmesh, 10, false);
    if (newCmesh != NULL){
        cout << "SALIDA NORMALS::: " <<  endl;
        cout << "number of vertices " <<  newCmesh->vert.size() << endl;
        cout << "number of faces " << newCmesh->face.size()<< endl<< endl;

        bool modelSaved = ProcessMesh::save(string("CMESH"), newCmesh);
        printf("MODEL NORMALIZED SAVED?? ==== %d\n", modelSaved);
    } else {
        printf("=== NEW MESH NULL\n\n");
        errorMessageDialog->showMessage(
                tr("Error performing normal calculation."));
        return;
    }

    printf("=== ProcessMesh::SurfaceReconstructionPoisson\n");
	int OctDepth=octdepthSpinBox->value();
	float SamplesPerNode = samplespernodeSpinBox->value();
	int SolverDivide = solverdivideSpinBox->value();
	float Offset = offsetSpinBox->value();
    CMeshO *finalCmesh = ProcessMesh::SurfaceReconstructionPoisson(newCmesh, OctDepth, SolverDivide, SamplesPerNode, Offset);
    if (finalCmesh != NULL){
        cout << "SALIDA SURFACE::: " <<  endl;
        cout << "number of vertices " <<  finalCmesh->vert.size() << endl;
        cout << "number of faces " << finalCmesh->face.size()<< endl<< endl;

        bool modelSaved = ProcessMesh::save(ouitFileName, finalCmesh);
        printf("FINAL MODEL SAVED?? ==== %d\n", modelSaved);
    } else {
        printf("=== finalCmesh MESH NULL\n");
        errorMessageDialog->showMessage(
                tr("Error performing Poisson Surface Reoncstruction ."));
        return;
    }
    informationMessage("ProcessMesh", "New mesh created and saved successfully!");
}

void ProcessDialog::rejectPressed(){
    exit(0);
}

void ProcessDialog::informationMessage(string title, string msg)
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::information(this, tr(title.c_str()), msg.c_str());
    if (reply == QMessageBox::Ok)
        exit(0);
}

void ProcessDialog::criticalMessage(string title, string msg)
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::critical(this, tr(title.c_str()),
                                    msg.c_str(),
                                    QMessageBox::Ok/* | QMessageBox::Retry | QMessageBox::Ignore*/);
    //if (reply == QMessageBox::Ok)
    //    criticalLabel->setText(tr("Abort"));
}
