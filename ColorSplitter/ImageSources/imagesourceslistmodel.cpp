#include "imagesourceslistmodel.h"

ImageSourcesListModel::ImageSourcesListModel()
    : m_files()
    , m_displayRegime(EDisplayRegime::FULL_PATH)
{

}


/******************************************************************************
*   Adds images to the model
******************************************************************************/
void ImageSourcesListModel::addImages(const QStringList &images)
{
    m_files.clear();
    beginInsertRows(QModelIndex(), 0, images.size()-1);

    for(QString str : images)
    {
        QFileInfo img(str);
        m_files.append(img);
    }

    endInsertRows();
}


/******************************************************************************
*   Returns model data
******************************************************************************/
QVariant ImageSourcesListModel::data(const QModelIndex &index, int nRole) const
{
    if (!index.isValid())
        return QVariant();

    if (nRole == Qt::UserRole)
        return m_files.at(index.row()).filePath();

    if (nRole != Qt::DisplayRole)
        return QVariant();

    return m_displayRegime == EDisplayRegime::FULL_PATH ? m_files.at(index.row()).filePath() : m_files.at(index.row()).fileName();
}


/******************************************************************************
*   Returns images count
******************************************************************************/
int ImageSourcesListModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_files.size();
}


/******************************************************************************
*   Changes display regimes
******************************************************************************/
void ImageSourcesListModel::setDisplayRegime(const EDisplayRegime &displayRegime)
{
    m_displayRegime = displayRegime;
    dataChanged(index(0),index(m_files.size()-1));
}
