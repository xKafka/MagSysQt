#ifndef SCATTER_H
#define SCATTER_H

#include <QWidget>
#include <Q3DScatter>
#include <QtDataVisualization>
#include <Utils/include/position.h>

class Scatter : public QWidget
{
    Q_OBJECT

   std::unique_ptr<QtDataVisualization::Q3DScatter> m_scatter{};
   std::unique_ptr<QtDataVisualization::QScatter3DSeries> m_series{};

public:
    explicit Scatter(QWidget *parent = nullptr);

public slots:
   void visualize(const Position &);

signals:

};

#endif // SCATTER_H
