#ifndef IWIDGETSUPDATABLE_H
#define IWIDGETSUPDATABLE_H

enum EStateToUpdate
{
    DIAGRAM_BUILT
};

class IWidgetsUpdatable
{
public:
    virtual void updateWidgets(EStateToUpdate state) = 0;
};

#endif // IWIDGETSUPDATABLE_H
