#include "qte.h"
#include "implicits.h"
#include "ui_interface.h"
#include "Bezier.h"
#include <QGraphicsView>

MainWindow::MainWindow() : QMainWindow(), uiw(new Ui::Assets)
{
	// Chargement de l'interface
    uiw->setupUi(this);

	// Chargement du GLWidget
	meshWidget = new MeshWidget;
	QGridLayout* GLlayout = new QGridLayout;
	GLlayout->addWidget(meshWidget, 0, 0);
	GLlayout->setContentsMargins(0, 0, 0, 0);
    uiw->widget_GL->setLayout(GLlayout);

    view = new QGraphicsView(uiw->graphicsView);
    QGridLayout* GLlayout2 = new QGridLayout;
    GLlayout2->addWidget(view, 0, 0);
    GLlayout2->setContentsMargins(10, 10, 10, 10);
    uiw->graphicsView->setLayout(GLlayout2);



	// Creation des connect
	CreateActions();

	meshWidget->SetCamera(Camera(Vector(10, 0, 0), Vector(0.0, 0.0, 0.0)));
}

MainWindow::~MainWindow()
{
	delete meshWidget;
}

void MainWindow::CreateActions()
{
	// Buttons
    connect(uiw->boxMesh, SIGNAL(clicked()), this, SLOT(BoxMeshExample()));
    connect(uiw->sphereImplicit, SIGNAL(clicked()), this, SLOT(SphereImplicitExample()));
    connect(uiw->resetcameraButton, SIGNAL(clicked()), this, SLOT(ResetCamera()));
    connect(uiw->wireframe, SIGNAL(clicked()), this, SLOT(UpdateMaterial()));
    connect(uiw->radioShadingButton_1, SIGNAL(clicked()), this, SLOT(UpdateMaterial()));
    connect(uiw->radioShadingButton_2, SIGNAL(clicked()), this, SLOT(UpdateMaterial()));
    connect(uiw->buttonBezier, SIGNAL(clicked()), this, SLOT(BezierExample()));


	// Widget edition
	connect(meshWidget, SIGNAL(_signalEditSceneLeft(const Ray&)), this, SLOT(editingSceneLeft(const Ray&)));
	connect(meshWidget, SIGNAL(_signalEditSceneRight(const Ray&)), this, SLOT(editingSceneRight(const Ray&)));
}

void MainWindow::editingSceneLeft(const Ray&)
{
}

void MainWindow::editingSceneRight(const Ray&)
{
}

void MainWindow::BoxMeshExample()
{
    Mesh boxMesh = Mesh(Box(4.0));

	std::vector<Color> cols;
	cols.resize(boxMesh.Vertexes());
    for (size_t i = 0; i < cols.size(); i++)
		cols[i] = Color(double(i) / 6.0, fmod(double(i) * 39.478378, 1.0), 0.0);

	meshColor = MeshColor(boxMesh, cols, boxMesh.VertexIndexes());
	UpdateGeometry();
}

void MainWindow::BezierExample()
{
    QGraphicsScene* scene = new QGraphicsScene;
    std::vector<Vector> tabPts {Vector(0,0,0), Vector(50,50,1), Vector(-50,100,0)};
    Bezier b (tabPts);

    QPen* p = new QPen(Qt::red); // Crée un pinceau avec la couleur noire
    p->setWidth(4);

    b.draw(*scene, *p);
    delete view->scene();
    view->setScene(scene);

    std::vector<std::vector<Vector>> vecPts = {
        {Vector(0.0, 0.0, 0.0), Vector(1.0, 0.0, 2.0), Vector(2.0, 0.0, 2.0), Vector(3.0, 0.0, 0.0)},
        {Vector(0.0, 1.0, 1.0), Vector(1.0, 1.0, 3.0), Vector(2.0, 1.0, 3.0), Vector(3.0, 1.0, 1.0)},
        {Vector(0.0, 2.0, 1.0), Vector(1.0, 2.0, 3.0), Vector(2.0, 2.0, 3.0), Vector(3.0, 2.0, 1.0)},
        {Vector(0.0, 3.0, 0.0), Vector(1.0, 3.0, 2.0), Vector(2.0, 3.0, 2.0), Vector(3.0, 3.0, 0.0)}
    };

    Bezier3D b3d(vecPts);
    Mesh meshBezier;
    b3d.Polygonize(100, 100, meshBezier);

    std::vector<Color> cols;
    cols.resize(meshBezier.Vertexes());
    for (size_t i = 0; i < cols.size(); i++)
      cols[i] = Color(0.8, 0.8, 0.8);
    meshColor = MeshColor(meshBezier, cols, meshBezier.VertexIndexes());
    UpdateGeometry();
}

void MainWindow::SphereImplicitExample()
{
  AnalyticScalarField implicit;

  Mesh implicitMesh;
  implicit.Polygonize(70, implicitMesh, Box(2.0));

  std::vector<Color> cols;
  cols.resize(implicitMesh.Vertexes());
  for (size_t i = 0; i < cols.size(); i++)
    cols[i] = Color(0.8, 0.8, 0.8);

  meshColor = MeshColor(implicitMesh, cols, implicitMesh.VertexIndexes());
  UpdateGeometry();
}

void MainWindow::UpdateGeometry()
{
	meshWidget->ClearAll();
	meshWidget->AddMesh("BoxMesh", meshColor);

    uiw->lineEdit->setText(QString::number(meshColor.Vertexes()));
    uiw->lineEdit_2->setText(QString::number(meshColor.Triangles()));

	UpdateMaterial();
}

void MainWindow::UpdateMaterial()
{
    meshWidget->UseWireframeGlobal(uiw->wireframe->isChecked());

    if (uiw->radioShadingButton_1->isChecked())
		meshWidget->SetMaterialGlobal(MeshMaterial::Normal);
	else
		meshWidget->SetMaterialGlobal(MeshMaterial::Color);
}

void MainWindow::ResetCamera()
{
	meshWidget->SetCamera(Camera(Vector(-10.0), Vector(0.0)));
}
