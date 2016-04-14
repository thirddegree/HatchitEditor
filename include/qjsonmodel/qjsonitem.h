#ifndef JSONITEM_H
#define JSONITEM_H
#include <QtCore>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>
class QJsonTreeItem
{
public:
    QJsonTreeItem(QJsonTreeItem * parent = 0);
    ~QJsonTreeItem();
    void appendChild(QJsonTreeItem * item);
    QJsonTreeItem *child(int row);
    const QList<QJsonTreeItem*>& children();
    QJsonTreeItem *parent();
    int childCount() const;
    int row() const;
    void setKey(const QString& key);
    void setValue(const QString& value);
    void setType(const QJsonValue::Type& type);
    void setEditable(bool canEdit);
    void setModelRow(int row);
    QString key() const;
    int modelRow() const;
    QString value() const;
    bool editable() const;
    QJsonValue::Type type() const;
    bool isEditable() const;

    static QJsonTreeItem* load(const QJsonValue& value, QJsonTreeItem* parent = 0);

private:
    QString mKey;
    QString mValue;
    int     mModelRow;
    QJsonValue::Type mType;
    bool    mEditable;
    QList<QJsonTreeItem*> mChilds;
    QJsonTreeItem * mParent;


};

#endif // JSONITEM_H
