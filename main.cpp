#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPlaneSource.h>
#include <vtkContourFilter.h>
#include <vtkStripper.h>
#include <vtkPolyData.h>
#include <vtkDoubleArray.h>
#include <vtkMath.h>
#include <vtkPointData.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkLabeledDataMapper.h>
#include "vtkContourLabel.h"
#include "vtkActor2D.h"

int main()
{
    //-------------------Initialising the contour using rendom values-------------------------
    vtkPlaneSource *plane = vtkPlaneSource::New();
    plane->SetXResolution(10);
    plane->SetYResolution(20);
    plane->Update();

    vtkDoubleArray *randomScalars = vtkDoubleArray::New();
    randomScalars->SetNumberOfComponents(1);
    randomScalars->SetName("Isovalues");
    for (int i = 0; i < plane->GetOutput()->GetNumberOfPoints(); i++)
    {
        randomScalars->InsertNextTuple1(vtkMath::Random(-100.0, 100.0));
    }
    plane->GetOutput()->GetPointData()->SetScalars(randomScalars);

    vtkContourFilter *contours = vtkContourFilter::New();
    contours->SetInputConnection(plane->GetOutputPort());
    contours->GenerateValues(5, -100, 100);

    // Connect the segments of the conours into polylines
    vtkStripper *contourStripper = vtkStripper::New();
    contourStripper->SetInputConnection(contours->GetOutputPort());
    contourStripper->Update();

    vtkPolyData *contourPolyData = contourStripper->GetOutput();

    //---------------------Find Points to add labels using the newly created vtkContourLabel--------------------------------
    vtkContourLabel *contourLabel = vtkContourLabel::New();
    contourLabel->SetInputData(contourPolyData);
    contourLabel->Update();
    vtkPolyData *outputLabelPolydata = contourLabel->GetOutput();

    //----------------------------------------------------------------------
    // The labeled data mapper will place labels at the points
    vtkLabeledDataMapper *labelMapper = vtkLabeledDataMapper::New();
    labelMapper->SetFieldDataName("Isovalues");
    labelMapper->SetInputData(outputLabelPolydata);
    labelMapper->SetLabelModeToLabelScalars();
    labelMapper->SetLabelFormat("%6.2f");

    vtkActor2D *isolabels = vtkActor2D::New();
    isolabels->SetMapper(labelMapper);

    //----------------------------------------------------------------------
    //Polydata for isolines
    vtkPolyDataMapper *polyDataMapper = vtkPolyDataMapper::New();
    polyDataMapper->SetInputData(contourPolyData);
    polyDataMapper->ScalarVisibilityOff();

    vtkActor *polyDataActor = vtkActor::New();
    polyDataActor->SetMapper(polyDataMapper);
    //----------------------------------------------------------------------

    // Visualisation
    vtkRenderer *rend = vtkRenderer::New();
    rend->AddActor(polyDataActor);
    rend->AddActor2D(isolabels);

    vtkRenderWindow *renWind = vtkRenderWindow::New();
    vtkRenderWindowInteractor *interactor = vtkRenderWindowInteractor::New();

    renWind->AddRenderer(rend);
    interactor->SetRenderWindow(renWind);
    interactor->Start();
    return 0;
}

