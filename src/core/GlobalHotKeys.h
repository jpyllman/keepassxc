/*
 *  Copyright (C) 2017 KeePassXC Team <team@keepassxc.org>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 or (at your option)
 *  version 3 of the License.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QObject>
//#include <QWidget>

#if defined(Q_OS_WIN)
#include <QSet>
#elif defined(Q_OS_LINUX)
#include <QAbstractNativeEventFilter>
#include <QHash>
#elif defined(Q_OS_MAC)
#endif

#if defined(Q_OS_LINUX)
#include <xcb/xcb.h>
//#include <xcb/xcb_keysyms.h>
#elif defined(Q_OS_MAC)
#include <Carbon/Carbon.h>
#endif

#if defined(Q_OS_LINUX)
struct UHotkeyData
{
    xcb_keycode_t keyCode;
    int mods;
    bool operator==(const UHotkeyData& data) const
    {
        return data.keyCode == this->keyCode && data.mods == this->mods;
    }
};
#endif

class GlobalHotKeys : public QObject
#if defined(Q_OS_LINUX)
    ,
                      public QAbstractNativeEventFilter
#endif
{
    Q_OBJECT
public:
    explicit GlobalHotKeys(QObject* parent = nullptr);

private:
    // [[nodiscard]] Q_DECL_CONSTEXPR bool isParentAWidget() const
    // {
    //     return qobject_cast<QWidget*>(parent()) != nullptr;
    // }

#if defined(Q_OS_WIN)
#elif defined(Q_OS_LINUX)
    QHash<size_t, UHotkeyData> Registered;
    xcb_connection_t* X11Conn;
    xcb_window_t X11Wnd;
    // xcb_key_symbols_t* X11KeySymbs;
#elif defined(Q_OS_MAC)
#endif
};
