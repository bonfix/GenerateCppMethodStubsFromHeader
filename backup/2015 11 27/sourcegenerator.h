#ifndef SOURCEGENERATOR_H
#define SOURCEGENERATOR_H
#include <QFile>
/*
 * Generates source files
 */
class SourceGenerator
{
public:
    SourceGenerator(QFile *header, QFile *dest);
    bool generate();
    QFile *source;
    QFile *dest;
};

#endif // SOURCEGENERATOR_H
