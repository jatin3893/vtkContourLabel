#include "vtkContourLabel.h"
#include "vtkObjectFactory.h"
#include "vtkInformation.h"
#include "vtkInformationVector.h"
#include "vtkPointData.h"
#include "vtkSmartPointer.h"
#include "vtkDoubleArray.h"
#include <vtkCellArray.h>
#include "vtkMath.h"

vtkStandardNewMacro(vtkContourLabel)

//----------------------------------------------------------------------------
vtkContourLabel::vtkContourLabel()
{
    this->SetNumberOfInputPorts(1);
    this->SetNumberOfOutputPorts(1);
}

//----------------------------------------------------------------------------
vtkContourLabel::~vtkContourLabel()
{

}

//----------------------------------------------------------------------------
int vtkContourLabel::RequestData(vtkInformation* vtkNotUsed(request),
                                 vtkInformationVector** vtkNotUsed(request),
                                 vtkInformationVector* outputVector)
{
    // Get the info object
    vtkInformation* outInfo = outputVector->GetInformationObject(0);

    // Get the ouptut
    vtkPolyData* output = vtkPolyData::SafeDownCast(outInfo->Get(vtkDataObject::DATA_OBJECT()));
    vtkPolyData *input = vtkPolyData::SafeDownCast(this->GetInput());

    int numberOfContourLines = input->GetNumberOfLines();

    vtkPoints *points = input->GetPoints();
    vtkCellArray *cells = input->GetLines();
    vtkDataArray *scalars = input->GetPointData()->GetScalars();

    vtkPoints *outputPoints = vtkPoints::New();
    vtkDoubleArray *outputScalars = vtkDoubleArray::New();
    outputScalars->SetNumberOfComponents(1);
    outputScalars->SetName("Isovalues");

    int pointThreshold = 0;

    vtkIdType *indices;
    vtkIdType numberOfPoints;
    unsigned int lineCount = 0;
    for (cells->InitTraversal(); cells->GetNextCell(numberOfPoints, indices); lineCount++)
    {
        if (numberOfPoints < pointThreshold)
        {
            continue;
        }
        vtkIdType midPointId = GetIndexForLabelPositioning(indices, numberOfPoints);

        double midPoint[3];
        points->GetPoint(midPointId, midPoint);

        outputPoints->InsertNextPoint(midPoint);
        outputScalars->InsertNextTuple1(scalars->GetTuple1(midPointId));
    }
    output->SetPoints(outputPoints);
    output->GetPointData()->SetScalars(outputScalars);

    return VTK_OK;
}

//----------------------------------------------------------------------------
vtkIdType vtkContourLabel::GetIndexForLabelPositioning(vtkIdType *indices, int numberOfPoints)
{
    // Calculate appropriate index for labelling the contour
    // Random index is chosen for now
    vtkIdType index = indices[static_cast<vtkIdType>(vtkMath::Random(0, numberOfPoints))];
    return index;
}

//----------------------------------------------------------------------------
void vtkContourLabel::PrintSelf(ostream &os, vtkIndent indent)
{
    Superclass::PrintSelf(os, indent);
    os << "vtkContourLabel" << std::endl;
}
