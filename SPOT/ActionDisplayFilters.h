#pragma once
#include "Actions/Action.h"
#include "GUI/CMUgraphicsLib\CMUgraphics.h"
#include <string>
#include "Text_field.h"
#include "ListImagesFields.h"
#include "ButtonField.h"
#include "GUI/GUI.h"
#include "StudyPlan/StudyPlan.h"
using namespace std;
class ActionDisplayFilters :
    public Action
{
private:
    GUI* pGUI;
    StudyPlan* pS;
    window* pWind;
    const int WINDOW_HEIGHT = 340;
    const int WINDOW_WIDTH = 650;
    //top left point
    const int X_S = 307;
    const int Y_S = 170;
    const int MARGIN_VALUE = 15;
    const int TEXT_FIELD_WIDTH = 250;
    const int TEXT_FIELD_HEIGHT = 60;
    const int TEXT__FONT_SIZE = 17;
    color BkGrndColor = LIGHTGRAY;
    ListImagesFields* filters = nullptr;
    ButtonField* DoneButton = nullptr;
    FILTERS lastFilter;
public:
    ActionDisplayFilters(Registrar*);
    bool virtual Execute();
    void ClearDrawingArea() const;
    void UpdateInterface()const;
    void DrawButton()const;
    void DrawFilters()const;
    bool  DoneClicked()const;
    virtual ~ActionDisplayFilters();
};