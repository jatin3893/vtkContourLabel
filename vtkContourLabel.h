#ifndef __vtkContourLabel_h
#define __vtkContourLabel_h

#include <vtkPolyDataAlgorithm.h>

class vtkContourLabel : public vtkPolyDataAlgorithm
{
public:
    static vtkContourLabel *New();
    vtkTypeMacro(vtkContourLabel,vtkPolyDataAlgorithm)
    virtual void PrintSelf(ostream &os, vtkIndent indent);

protected:
    vtkContourLabel();
    ~vtkContourLabel();

    // Decription:
    // Core implementation of the
    int RequestData(vtkInformation* request, vtkInformationVector** inputVector,
                    vtkInformationVector* outputVector);

    // Description:
    // Calculating appropriate position for the label
    vtkIdType GetIndexForLabelPositioning(vtkIdType *indices, int numberOfPoints);

private:
    vtkContourLabel(const vtkContourLabel&); //Not implemented
    void operator=(const vtkContourLabel&); //Not implemented
};

#endif // __vtkContourLabel_h
