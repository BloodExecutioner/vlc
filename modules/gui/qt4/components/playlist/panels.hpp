/*****************************************************************************
 * panels.hpp : Panels for the playlist
 ****************************************************************************
 * Copyright (C) 2000-2005 the VideoLAN team
 * $Id$
 *
 * Authors: Clément Stenac <zorglub@videolan.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/

#ifndef _PLPANELS_H_
#define _PLPANELS_H_

#include <vlc/vlc.h>

#include "qt4.hpp"

#include <QModelIndex>
#include <QWidget>
#include <QString>

class QTreeView;
class PLModel;
class QPushButton;
class QKeyEvent;
class ClickLineEdit;

class PLPanel: public QWidget
{
    Q_OBJECT;
public:
    PLPanel( BasePlaylistWidget *p, intf_thread_t *_p_intf ) : QWidget( p )
    {
        p_intf = _p_intf;
        parent = p;
    }
    virtual ~PLPanel() {};
protected:
    intf_thread_t *p_intf;
    BasePlaylistWidget *parent;
public slots:
    virtual void setRoot( int ) = 0;
};

class PlaylistWidget;

class StandardPLPanel: public PLPanel
{
    Q_OBJECT;
public:
    StandardPLPanel( BasePlaylistWidget *, intf_thread_t *,
                     playlist_t *,playlist_item_t * );
    virtual ~StandardPLPanel();
protected:
    virtual void keyPressEvent( QKeyEvent *e );
protected:
    PLModel *model;
    friend class PlaylistWidget;
private:
    QTreeView *view;
    QPushButton *repeatButton , *randomButton,*addButton;
    ClickLineEdit *searchLine;
    int currentRootId;
public slots:
    void removeItem( int );
    virtual void setRoot( int );
private slots:
    void deleteSelection();
    void handleExpansion( const QModelIndex& );
    void toggleRandom();
    void toggleRepeat();
    void doPopup( QModelIndex index, QPoint point );
    void search( QString search );
    void clearFilter();
    void add();
    void setCurrentRootId( int );
};

#endif
