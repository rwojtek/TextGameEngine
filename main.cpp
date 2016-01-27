#include <iostream>
#include "TextGameEngine.h"

int main()
{
    XMLtoString dataForParser;
    StringToContainers dataForContainers;
    ContainersToFile dataForFile;

    dataForContainers.fillContainers(dataForParser.getStringFromXML());
    dataForFile.createEngineFile(dataForContainers.getStepsAmount(), dataForContainers.getStepsTable());
}



