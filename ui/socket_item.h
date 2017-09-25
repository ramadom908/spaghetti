#ifndef SOCKETITEM_H
#define SOCKETITEM_H

#include <QGraphicsItem>
#include <QPainter>
#include <QVector>

class LinkItem;

class SocketItem final : public QGraphicsItem {
 public:
  enum class Type { eInput, eOutput };

  constexpr static int SIZE{ 16 };

  SocketItem(Type aType, QGraphicsItem *const a_parent = nullptr);

  bool isInput() const { return m_type == Type::eInput; }
  bool isOutput() const { return m_type == Type::eOutput; }

  QRectF boundingRect() const override;

  void paint(QPainter *aPainter, QStyleOptionGraphicsItem const *a_option, QWidget *a_widget) override;

  void hoverEnterEvent(QGraphicsSceneHoverEvent *a_event) override;
  void hoverLeaveEvent(QGraphicsSceneHoverEvent *a_event) override;

  void dragEnterEvent(QGraphicsSceneDragDropEvent *a_event) override;
  void dragLeaveEvent(QGraphicsSceneDragDropEvent *a_event) override;
  void dragMoveEvent(QGraphicsSceneDragDropEvent *a_event) override;
  void dropEvent(QGraphicsSceneDragDropEvent *a_event) override;

  void mousePressEvent(QGraphicsSceneMouseEvent *a_event) override;
  void mouseMoveEvent(QGraphicsSceneMouseEvent *a_event) override;
  void mouseReleaseEvent(QGraphicsSceneMouseEvent *a_event) override;

  QVariant itemChange(GraphicsItemChange a_change, const QVariant &a_value) override;

  void setHover(bool a_hover)
  {
    m_isHover = a_hover;
    update();
  }

  QString name() const { return m_name; }
  void setName(QString a_name) { m_name = a_name; }

  void showName() { m_nameHidden = false; }
  void hideName() { m_nameHidden = true; }

  void markAsUsed()
  {
    m_used = true;
    update();
  }

  int nameWidth() const;

  void setElementId(size_t const a_elementId) { m_elementId = a_elementId; }
  size_t elementId() const { return m_elementId; }
  void setSocketId(uint8_t const a_socketId) { m_socketId = a_socketId; }
  uint8_t socketId() const { return m_socketId; }

  void setColors(QColor const a_signalOff, QColor const a_signalOn);
  void setSignal(bool const a_signal);

 private:
  QString m_name{};
  QFont m_font{};

  size_t m_elementId{};
  uint8_t m_socketId{};

  QColor m_colorSignalOn{};
  QColor m_colorSignalOff{};
  bool m_isSignalOn{};

  Type m_type{};
  bool m_isHover{};
  bool m_isDrop{};
  bool m_used{};
  bool m_nameHidden{};

  QVector<LinkItem *> m_links{};
};

#endif // SOCKETITEM_H
