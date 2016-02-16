#include "sourcegenerator.h"
#include <QTextStream>

SourceGenerator::SourceGenerator(QFile *source, QFile *dest):source(source),dest(dest)
{
    
}
bool SourceGenerator::generate()
{
    if( !source->open( QIODevice::ReadOnly | QIODevice::Text ) )
    {
        qDebug( "Could not open the input file" );
        return false;
    }
    if( !dest->open( QIODevice::WriteOnly | QIODevice::Text ) )
    {
        qDebug( "Could not open the output file" );
        return false;
    }
    QTextStream textStream(source);
    QTextStream outStream(dest);
    bool included = false;

    QString className = source->fileName();
    while(!textStream.atEnd())
    {
        //if()
        QString line = textStream.readLine();
        //int braceStart = line.indexOf("(");
        if(line.indexOf("class ") !=-1)
        {
            QString pat = "class +([a-zA-Z_][a-zA-Z0-9_]*)";
            QRegExp re(pat);
            int matches =  re.indexIn(line);
            if(matches!=-1 && re.cap(1).length()>0)
            {
                className = re.cap(1);
                if(!included)
                {
                  outStream<<"#include \""+className.toLower()+".h\"\n\n";
                  included = true;
                }
            }
        }
        if(line.indexOf("(") !=-1)
        {
            QString pat = "([a-zA-Z0-9_*]*) +([a-zA-Z0-9_~]*\\([^;]*)";
            QRegExp re(pat);
            //re.setPatternSyntax(QRegExp::PatternSyntax(0));
            //re.indexIn(txt);
            int matches =  re.indexIn(line);
            qDebug("Matches : "+QString::number(matches).toLatin1());
            if(re.cap(2).length()>0)
            {
                //outStream <<re.cap(1)<<" "<<className<<"::"<<re.cap(2)<<"\n";
                QString out = re.cap(1)>0 ? re.cap(1)+" "+className+"::"+re.cap(2) : className+"::"+re.cap(2);
                out += "\n{\n\t\n}\n\n";
                outStream << out;
                //qDebug(QString::number(i).toLatin1()+" : "+className.toLatin1()+"::"+re.cap(2).toLatin1());
            }

            qDebug("function");
        }
    }
    source->close();
}

