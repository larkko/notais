#pragma once

#include <memory>
#include <vector>
#include <tuple>

#include <QWidget>
#include <QComboBox>
#include <QMouseEvent>

#include "../lib/audio/adjustableaudiosource.hh"
#include "../lib/audio/oscillator.hh"
#include "../lib/sequencing/sequence.hh"
#include "../lib/effects/effect.hh"
#include "taskqueue.hh"

class Edit_instrument_widget : public QWidget
{
  Q_OBJECT
  public:
    Edit_instrument_widget
    (
        std::shared_ptr<Adjustable_audio_source> instrument,
        Task_queue & task_queue,
        QWidget * parent = nullptr,
        Qt::WindowFlags flags = Qt::WindowFlags()
    );
  private:
  signals:
    void effects_updated(std::vector<std::shared_ptr<Effect>> effects);
    void instruments_updated
    (
        std::vector<std::shared_ptr<Adjustable_audio_source>> instruments
    );
    void instrument_updated();
    void tunings_updated
    (
        std::vector<std::shared_ptr<Tuning>> tunings
    );
};

class Edit_instrument_general_tab_widget : public QWidget
{
  Q_OBJECT
  public:
    Edit_instrument_general_tab_widget
    (
        std::shared_ptr<Adjustable_audio_source> instrument,
        Task_queue & task_queue,
        QWidget * parent = nullptr
    );
  private:
    std::shared_ptr<Adjustable_audio_source> m_instrument;
};

class Edit_oscillator_widget : public QWidget
{
  Q_OBJECT
  public:
    Edit_oscillator_widget
    (
        std::shared_ptr<Oscillator> oscillator,
        Task_queue & task_queue,
        QWidget * parent = nullptr
    );
  private:
    std::shared_ptr<Oscillator> m_oscillator;
  signals:
    void oscillator_updated();
};

class Edit_sequence_widget : public QWidget
{
  Q_OBJECT
  public:
    Edit_sequence_widget
    (
        std::shared_ptr<Sequence> sequence,
        Task_queue & task_queue,
        QWidget * parent = nullptr
    );
  private:
    std::shared_ptr<Sequence> m_sequence;
    Task_queue & m_task_queue;
    QComboBox * m_instrument_selector;
    QComboBox * m_tuning_selector;
  public slots:
    void update_instruments
    (
        std::vector<std::shared_ptr<Adjustable_audio_source>> instruments
    );
    void update_tunings
    (
        std::vector<std::shared_ptr<Tuning>> tunings
    );
};

class Edit_sequence_pattern_widget : public QWidget
{
  Q_OBJECT
  public:
    Edit_sequence_pattern_widget
    (
        std::shared_ptr<Sequence> sequence,
        Task_queue & task_queue,
        QWidget * parent = nullptr
    );
  private:
    void paintEvent(QPaintEvent * event) override;
    void mousePressEvent(QMouseEvent * event) override;
    void mouseReleaseEvent(QMouseEvent * event) override;
    void mouseMoveEvent(QMouseEvent * event) override;
    void wheelEvent(QWheelEvent * event) override;
    double cell_width() const;
    double cell_height() const;
    std::tuple<int, int> click_cell(int x, int y) const;
    void clamp_location();
    std::shared_ptr<Sequence> m_sequence;
    Task_queue & m_task_queue;
    double m_horizontal_zoom;
    double m_vertical_zoom;
    int m_x_offset;
    int m_y_offset;
    int m_last_mouse_x;
    int m_last_mouse_y;
    bool m_dragging;
    double m_note_length;
    static double constexpr base_cell_width = 60;
    static double constexpr base_cell_height = 20;
};







