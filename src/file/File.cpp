#include "file/file.hpp"
#include <QFileInfo>
#include <QRegularExpression>


namespace FileTool
{
    void rename_file(QStringList &files, const RenameRule &rule)
    {
        QString name;
        int order = rule.order;
        const int step = rule.order_step;
        const int order_len = QString::number(files.length()).length();
        for (QString &file : files)
        {
            QFileInfo info(file);

            if (rule.name.isEmpty())
            {
                switch (rule.upper)
                {
                case UpperOrLower::Keep:
                    name = info.baseName();
                    break;
                case UpperOrLower::Upper:
                    name = info.baseName().toUpper();
                    break;
                case UpperOrLower::Lower:
                    name = info.baseName().toLower();
                    break;
                default:
                    break;
                }

                if (rule.remove_index0 > -1 && rule.remove_index1 >= rule.remove_index0
                    && rule.remove_index1 < name.length())
                {
                    name.remove(rule.remove_index0, rule.remove_index1 - rule.remove_index0 + 1);
                }
            }
            else
            {
                name = rule.name;
            }

            if (!rule.remove.isEmpty())
            {
                name.remove(QRegularExpression('(' + rule.remove + ')'));
            }

            if (rule.no_space)
            {
                name.remove(QRegularExpression("\\s"));
            }

            if (!rule.prefix.isEmpty())
            {
                name.insert(0, rule.prefix);
            }
            if (!rule.suffix.isEmpty())
            {
                name.append(rule.suffix);
            }

            if (!rule.remove_from.isEmpty() && !rule.remove_to.isEmpty())
            {
                name.remove(QRegularExpression('(' + rule.remove_from + ")[^("
                    + rule.remove_to + ")]*(" + rule.remove_to + ')'));
            }

            name.replace(rule.replace_src, rule.replace_dst);

            if (rule.remove_num)
            {
                name.remove(QRegularExpression("\\d+"));
            }
            else if (rule.fix_order)
            {
                int i = name.indexOf(QRegularExpression("\\d+"));
                if (i >= 0)
                {
                    int length = name.length(), j = i;
                    while (++j < length && name[j].isNumber());
                    if (j - i < order_len)
                    {
                        name.insert(i, QString(order_len - j + i, '0'));
                    }
                }
            }

            if (rule.add_order)
            {
                if (rule.fix_order_length)
                {
                    switch (rule.order_place)
                    {
                    case OrderPlace::Back:
                        name.append(rule.order_prefix + QString("%1").arg(order, order_len, 10, QLatin1Char('0')) + rule.order_suffix);
                        break;
                    case OrderPlace::Front:
                        name.insert(0, rule.order_prefix + QString("%1").arg(order, order_len, 10, QLatin1Char('0')) + rule.order_suffix);
                        break;
                    default:
                        break;
                    }
                }
                else
                {
                    switch (rule.order_place)
                    {
                    case OrderPlace::Back:
                        name.append(rule.order_prefix + QString::number(order) + rule.order_suffix);
                        break;
                    case OrderPlace::Front:
                        name.insert(0, rule.order_prefix + QString::number(order) + rule.order_suffix);
                        break;
                    default:
                        break;
                    }
                }
                order += step;
            }

            QFile::rename(file, info.path() + '/' + name + '.' + info.suffix());
            file = info.path() + '/' + name + '.' + info.suffix();
        }
    }

    void rename_file(QStringList &files, const QStringList &names)
    {
        size_t i = 0;
        for (QString &file : files)
        {
            QFileInfo info(file);
            QFile::rename(file, info.path() + '/' + names[i] + '.' + info.suffix());
            file = info.path() + '/' + names[i++] + '.' + info.suffix();
        }
    }

}