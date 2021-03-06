/* -*- Mode: C++; indent-tabs-mode: nil; tab-width: 4 -*-
 * -*- coding: utf-8 -*-
 *
 * Copyright (C) 2011 ~ 2017 Deepin, Inc.
 *               2011 ~ 2017 Wang Yong
 *
 * Author:     Wang Yong <wangyong@deepin.com>
 * Maintainer: Wang Yong <wangyong@deepin.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef UTILS_H
#define UTILS_H

#include <QFileInfoList>
#include <QLayout>
#include <QObject>
#include <QPainter>
#include <QString>
#include <proc/readproc.h>
#include "window_manager.h"

const int RECTANGLE_PADDING = 24;
const int RECTANGLE_RADIUS = 8;
const int RECTANGLE_FONT_SIZE = 11;

const QList<QString> GUI_BLACKLIST = {
    "sh", "fcitx", "ssh", "python2", "pulseaudio"
};

namespace Utils {
    typedef struct DiskStatus {
        float readKbs;
        float writeKbs;
    } DiskStatus;

    /**
     * Process IO details from /proc/pid/io. Note that the IO counters encompass all IO, not only to disk, but also pipes and sockets.
     * Root access is required to read /prod/pid/io (one may detect the size of a password of another process by examining this file),
     */
    struct ProcPidIO {
        /**
         * characters read - The number of bytes which this task has caused to be read from storage. This is simply the sum of bytes which this process passed to
         * read(2) and similar system calls. It includes things such as terminal I/O and is unaffected by whether or not actual physical disk I/O
         * was required (the read might have been satisfied from pagecache).
         */
        unsigned long rchar;
        /**
         * characters written - The number of bytes which this task has caused, or shall cause to be written to disk.  Similar caveats apply here as with rchar.
         */
        unsigned long wchar;
        /**
         * read syscalls - Attempt to count the number of read I/O operations—that is, system calls such as read(2) and pread(2).
         */
        unsigned long syscr;
        /**
         * write syscalls - Attempt to count the number of write I/O operations—that is, system calls such as write(2) and pwrite(2).
         */
        unsigned long syscw;
        /**
         * bytes read - Attempt to count the number of bytes which this process really did cause to be fetched from the  storage  layer.   This  is  accurate  for
         * block-backed filesystems.
         */
        unsigned long read_bytes;
        /**
         * bytes written - Attempt to count the number of bytes which this process caused to be sent to the storage layer.
         */
        unsigned long write_bytes;
        /**
         * The  big  inaccuracy  here is truncate.  If a process writes 1MB to a file and then deletes the file, it will in fact perform no writeout.
         * But it will have been accounted as having caused 1MB of write.  In other words: this field represents  the  number  of  bytes  which  this
         * process caused to not happen, by truncating pagecache.  A task can cause "negative" I/O too.  If this task truncates some dirty pagecache,
         * some I/O which another task has been accounted for (in its write_bytes) will not be happening.
         */
        unsigned long cancelled_write_bytes;
    };

    typedef struct NetworkStatus {
        uint32_t sentBytes;
        uint32_t recvBytes;
        float sentKbs;
        float recvKbs;
    } NetworkStatus;
    
    /**
     * Get process IO details, root access required.
     * @param pid the process id.
     * @param io the ProcPidIO struct to fill.
     * @return false if the operation failed (no permission, pid does not exist).
     * @root root access is required even for processes the caller owns (as the information in this file
     * might be used to deduce the size of an entered password).
     */
    bool getProcPidIO(int pid, ProcPidIO &io );

    QSize getRenderSize(int fontSize, QString string);
    QString formatMillisecond(int millisecond);
    QString getImagePath(QString imageName);
    QString getQrcPath(QString imageName);
    QString getQssPath(QString qssName);
    bool fileExists(QString path);
    qreal easeInOut(qreal x);
    qreal easeInQuad(qreal x);
    qreal easeInQuint(qreal x);
    qreal easeOutQuad(qreal x);
    qreal easeOutQuint(qreal x);
    void addLayoutWidget(QLayout *layout, QWidget *widget);
    void applyQss(QWidget *widget, QString qssName);
    void removeChildren(QWidget *widget);
    void removeLayoutChild(QLayout *layout, int index);
    void setFontSize(QPainter &painter, int textSize);
    QString convertSizeUnit(long bytes, QString unitSuffix="B");
    void drawRing(QPainter &painter, int centerX, int centerY, int radius, int penWidth, int loadingAngle, int rotationAngle, QString color, double opacity);
    void drawLoadingRing(QPainter &painter, int centerX, int centerY, int radius, int penWidth, int loadingAngle, int rotationAngle, QString color, double backgroundOpacity, double percent);
    QString formatByteCount(double v, const char** orders, int nb_orders);
    QString formatByteCount(double v);
    QString formatBandwidth(double v);
    
    QString getProcessName(proc_t* p);
    double calculateCPUPercentage(const proc_t* before, const proc_t* after, const unsigned long long &cpuTime);
    QString getProcessCmdline(pid_t pid);
    unsigned long long getTotalCpuTime();
    QPixmap getProcessIconFromName(QString procName, QMap<QString, QPixmap> *processIconMapCache, int iconSize = 24);
    QString getDisplayNameFromName(QString procName);
    bool isGuiApp(QString procName);
    void passInputEvent(int wid);
    void drawTooltipBackground(QPainter &painter, QRect rect, qreal opacity = 0.4);
    void drawTooltipText(QPainter &painter, QString text, QString textColor, int textSize, QRectF rect);
    void blurRect(WindowManager *windowManager, int widgetId, QRectF rect);
    void blurRects(WindowManager *windowManager, int widgetId, QList<QRectF> rects);
    void clearBlur(WindowManager *windowManager, int widgetId);
}


#endif
