#pragma once

#include <QString>
#include <QStringList>


namespace FileTool
{
    static const QString file_filter("All: (*);;"
        "Video: (*mp4 *mov *avi *flv *mkv *wmv);;"
        "Audio: (*mp3 *m4a *aac *flac *wma *wav *ape *ogg);;"
        "Picture: (*png *jpg *bmp *tif *svg *raw);;"
        "PDF: (*pdf);;Doc: (*doc *docx);;PPT: (*ppt *pptx);;Excel: (*xls *xlsx);;"
        "Txt: (*txt)");

    enum UpperOrLower {Keep, Upper, Lower};
    enum OrderPlace {Back, Front};

    struct RenameRule
    {
        QString name;
        UpperOrLower upper = UpperOrLower::Keep;
        QString remove;
        QString prefix;
        QString suffix;
        QString remove_from;
        QString remove_to;
        QString replace_src;
        QString replace_dst;
        bool no_space = false;
        bool add_order = false;
        bool fix_order_length = true;
        OrderPlace order_place = OrderPlace::Back;
        int order = 0;
        int order_step = 1;
        QString order_prefix;
        QString order_suffix;
    };
    
    void rename_file(QStringList &files, const RenameRule &rule);

    void rename_file(QStringList &files, const QStringList &names);
};