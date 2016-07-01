/*
    Copyright (C) 2015 by Elvis Angelaccio <elvis.angelaccio@kdemail.net>

    This file is part of Kronometer.

    Kronometer is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) any later version.

    Kronometer is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Kronometer.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SESSIONMODEL_H
#define SESSIONMODEL_H

#include "session.h"

#include <QAbstractTableModel>

/**
 * @brief A SessionModel is a Model for sessions.
 */
class SessionModel : public QAbstractTableModel
{
    Q_OBJECT

public:

    explicit SessionModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex& parent) const override;
    int columnCount(const QModelIndex& parent) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    bool setData(const QModelIndex& index, const QVariant& value, int role) override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;
    bool removeRows(int row, int count, const QModelIndex& parent) override;

    /**
     * Retrieve a specific Session object. The given index must be a valid index in the model.
     * @param sessionIndex The index of the session.
     * @return The Session at the given index.
     */
    const Session& at(int sessionIndex);

    /**
     * Insert a new Session object to the end of the model.
     * @param session The new Session object.
     */
    void append(const Session& session);

    /**
     * Update the given session in the model.
     * If the session does not belong to the model, nothing happens.
     * @param session The session to be updated.
     */
    void update(const Session& session);

    /**
     * @return Whether the model does not hold any session.
     */
    bool isEmpty() const;

    /**
     * Whether the given index refers to an editable value in the model.
     * @param index An index of the model.
     * @return True if the underlying data is editable, false otherwise.
     */
    bool isEditable(const QModelIndex& index) const;

    /**
     * Load the model from the given JSON object.
     * @param json A JSON object.
     */
    void read(const QJsonObject& json);

public slots:

    /**
     * Update the global sessions file with the data in the model.
     */
    void slotWrite();

private:

    enum class Column
    {
        SessionId = 0,    /**< Index of the session-number column. */
        Name = 1,         /**< Index of the session name column. */
        Date = 2,         /**< Index of the session date column. */
        Note = 3          /**< Index of the session annotation column. */
    };

    const QVector<Column> m_columns {Column::SessionId, Column::Name, Column::Date, Column::Note};

    QList<Session> m_sessionList;    /** Sessions in the model. */

    Q_DISABLE_COPY(SessionModel)
};


#endif