#ifndef ICOLORDIAGRAMOBSERVER_H
#define ICOLORDIAGRAMOBSERVER_H

enum EColorDiagramState
{
    CREATE_BUFFERS_NEEDED,
    DONE
};

class IObserver
{
public:
    virtual void update(EColorDiagramState state) = 0;
};

#endif // ICOLORDIAGRAMOBSERVER_H
