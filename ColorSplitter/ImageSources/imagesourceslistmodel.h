#ifndef IMAGESOURCESLISTMODEL_H
#define IMAGESOURCESLISTMODEL_H

#include <QAbstractListModel>
#include <QFileInfoList>

enum EDisplayRegime
{
    FULL_PATH,
    FILE_NAME
};

/******************************************************************************
*
*   Images list model.
*
******************************************************************************/
class ImageSourcesListModel : public QAbstractListModel
{
public:
    ImageSourcesListModel();

    void addImages(const QStringList &images);
    void setDisplayRegime(const EDisplayRegime &displayRegime);

    QVariant data(const QModelIndex& index, int nRole) const override;
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;

private:
    QFileInfoList m_files;
    EDisplayRegime m_displayRegime;
};

#endif // IMAGESOURCESLISTMODEL_H
