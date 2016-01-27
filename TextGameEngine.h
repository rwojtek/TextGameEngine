#ifndef TextGameEngine_H_
#include "rapidxml-1.13/rapidxml.hpp"
#include "rapidxml-1.13/rapidxml_print.hpp"
#include<fstream>
#include<vector>

using std::string;
using std::vector;
using std::ifstream;
using std::ofstream;
using namespace rapidxml;

///==================== LINK Struct ==========================
struct Link
{
    string linkStepID;
    string linkText;
    string linkTextBold;
    string linkTextItalic;
};
///==================== HEADING Struct =======================
struct Heading
{
    string headingText;
    string headingSize;
    string headingBold;
    string headingItalic;
};
struct StepText
{
    string text;
    string stepTextBold;
    string stepTextItalic;
};
///==================== STEP Struct ==========================
struct Step
{
    int stepTextAmount;
    int headingAmount;
    int linkAmount;
    string stepID;
    vector <Heading> heading;
    vector <StepText> stepText;
    vector <Link> link;
};
///==================== XML to String ==========================
class XMLtoString
{
    ifstream XMLfile;
    string stringFromXML;
    string line;
public:
    XMLtoString();
    string getStringFromXML()
    {
        return stringFromXML;
    }
};
///==================== String To Containers ==========================
class StringToContainers
{
    xml_document<>doc;
    xml_node <> *rootNode;
    xml_node <> *pStep;
    xml_node <> *pDiff;
    xml_node <> *pLink;
    int stepsAmount;
    vector <Step> step;
public:
    StringToContainers();
    void fillContainers(string stringForParser);
    int getStepsAmount()
    {
        return stepsAmount;
    }
    vector <Step> & getStepsTable()
    {
        return step;
    }
};
///==================== Containers To File ==========================
class ContainersToFile
{
    ofstream file;
public:
    void createEngineFile(int stepsAmount, vector <Step> & step);
    void fillMainNavigation(int stepsAmount, vector <Step> & step);
    void fillSections(int stepsAmount, vector <Step> & step);
    void closeEngineFile()
    {
        file.close();
    }
    void combineFiles();
};

#endif // TextGameEngine_H_

