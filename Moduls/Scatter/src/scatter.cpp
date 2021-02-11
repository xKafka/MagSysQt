#include <Moduls/Scatter/include/scatter.h>

#include <QBoxLayout>
#include <QDebug>

using namespace QtDataVisualization;

Scatter::Scatter(QWidget *parent)
    : QWidget { parent },
      m_scatter{ std::make_unique<Q3DScatter>() },
      m_series { std::make_unique<QScatter3DSeries>() }
{
    m_scatter->addSeries(m_series.get());

    m_series->setMesh(QScatter3DSeries::Mesh::MeshPoint);

    const auto container = QWidget::createWindowContainer(m_scatter.get());

    QHBoxLayout *h_layout = new QHBoxLayout(this);
    QVBoxLayout *v_layout = new QVBoxLayout();
    h_layout->addWidget(container, 1);
    h_layout->addLayout(v_layout);

    m_scatter->axisX()->setMin(-50.0);
    m_scatter->axisX()->setMax(220.0);

    m_scatter->axisY()->setMin(-70.0); // Z
    m_scatter->axisY()->setMax(100.0);

    m_scatter->axisZ()->setMin(0.0);
    m_scatter->axisZ()->setMax(220.0);

    qDebug() << QThread::currentThreadId();

    m_scatter->scene()->activeCamera()->setCameraPreset(Q3DCamera::CameraPresetFront);
}

void Scatter::visualize(const Position &Position)
{
    QScatterDataArray data;

    m_series->dataProxy()->removeItems(0, 1);

    data << QVector3D(Position.getX(), Position.getZ(), Position.getY());

    m_series->dataProxy()->addItems(data);
}



