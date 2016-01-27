#include<iostream>
#include "rapidxml-1.13/rapidxml.hpp"
#include "rapidxml-1.13/rapidxml_print.hpp"
#include<fstream>
#include<cstdlib>
#include<vector>
#include<cstring>
#include "TextGameEngine.h"

using std::cout;
using std::endl;
using namespace rapidxml;

///==================== XML to String ==========================

XMLtoString::XMLtoString()
{
    XMLfile.open("TheSourceStory.xml");                  /// opening XML file

    if (XMLfile.good() == false)
    {
        cout << "File not found. Make sure if your file's name is \"TheSourceStory.xml\"";
        exit(0);
    }

    while ( getline(XMLfile, line) )                /// reading XML file to string
        stringFromXML+=line + "\n";

    XMLfile.close();                                /// closing XML file
}
///==================== String To Containers ==========================

StringToContainers::StringToContainers()
{
    xml_node <> *pStep = NULL;                 /// (I branch) parser node <step>
    xml_node <> *pDiff = NULL;                 /// (II branch) Different parser nodes <stepID> <stepHeading> <stepText> <link>
    xml_node <> *pLink = NULL;                 /// (III branch)  parser node <linkStepID> <linkText>
    stepsAmount = 0;                           /// numebers of <steps>
}
void StringToContainers::fillContainers(string stringForParser)
{
    doc.parse<1>(&stringForParser[0]);                                                                    /// parse XML file
    xml_node<> *rootNode = doc.first_node();                                                              /// link *rootNode to doc document

    for (xml_node <> *pStep = rootNode->first_node(); pStep; pStep = pStep->next_sibling())               /// set *pStep to first_node of rootNode which is <step> (I branch)
    {
        step.push_back( Step() );                                                                         /// add new element to vector <Step> step;
        step.back().headingAmount = 0;                                                                    /// amount of <stepHeading> in every <step> starts with 0
        step.back().linkAmount = 0;                                                                       /// amount of <linkStepID> in every <step> starts with 0
        stepsAmount++;                                                                                    /// incrementing number of <steps>

        for (xml_node <> *pDiff = pStep->first_node(); pDiff; pDiff = pDiff->next_sibling())              /// set *pDiff to first_node of pStep which is <stepID> (II branch)
        {
            if ( !strcmp(pDiff->name(),"stepID")){
                step.back().stepID = pDiff->value();                                                      /// assign value to step[i].StepID (only one StepID for every <step>)
            }
            else if (!strcmp(pDiff->name(),"stepHeading")){
                step.back().heading.push_back( Heading() );                                               /// add new <stepHeading> to vector <Heading> heading (there can be many <stepHeadings> in one <step>)
                step.back().heading.back().headingText = pDiff->value();                                  /// assign value to step[i].heading.headingText
                step.back().heading.back().headingSize = pDiff->first_attribute("size")->value();         /// assign value to step[i].heading.headingSize "<h1> </h1>"
                step.back().heading.back().headingBold = pDiff->first_attribute("bold")->value();         /// assign value to step[i].heading.headingBold "<b> </b>"
                step.back().heading.back().headingItalic = pDiff->first_attribute("italic")->value();     /// assign value to step[i].heading.headingItalic "<i> </i>"
                step.back().headingAmount++;                                                              /// increment number of <stepHeadings> in "<step> </step>"
            }
            else if (!strcmp(pDiff->name(),"stepText")){
                step.back().stepText.push_back( StepText() );                                             /// add new <stepText> to vector <StepText> stepText; (there can be many <stepText> in one <step>)
                step.back().stepText.back().text = pDiff->value();                                        /// assign value to step[i].stepText.text
                step.back().stepText.back().stepTextBold = pDiff->first_attribute("bold")->value();       /// assign value to step[i].stepText.textBold "<b> </b>"
                step.back().stepText.back().stepTextItalic = pDiff->first_attribute("italic")->value();   /// assign value to step[i].stepText.textItalic "<i> </i>"
                step.back().stepTextAmount++;                                                             /// increment number of <stepText> in "<step> </step>"
            }
            else if (!strcmp(pDiff->name(),"link"))
            {
                for (xml_node <> *pLink = pDiff->first_node(); pLink; pLink = pLink->next_sibling())      /// set *pLink to first_node of pDiff which is <linkStepID> (III branch)
                {
                    if (!strcmp(pLink->name(), "linkStepID")){
                        step.back().link.push_back( Link() );                                             /// add new <linkStepID> and <linkText> to vector <Link> link (there can be many <linkStepID> and <linkText> in one <step>)
                        step.back().link.back().linkStepID = pLink->value();                              /// assign value to step[i].link.linkStepID
                        step.back().linkAmount++;                                                         /// increment number of <linkStepID> or <linkText> in one "<step> </step>"
                    }
                    if (!strcmp(pLink->name(), "linkText")){
                        step.back().link.back().linkText = pLink->value();                                  /// assign value to step[i].link.linkText
                        step.back().link.back().linkTextBold = pLink->first_attribute("bold")->value();     /// assign value to step[i].link.linkTextBold "<b> </b>"
                        step.back().link.back().linkTextItalic = pLink->first_attribute("italic")->value(); /// assign value to step[i].link.linkTextItalic "<i> </i>"
                    }
                }
            }
        }
    }
}

///==================== Containers To File ==========================

void ContainersToFile::createEngineFile(int stepsAmount, vector <Step> & step)
{
    file.open("html_template/ENGINE.html");                                                   /// creating ENGINE.html file
    fillMainNavigation(stepsAmount, step);                                      /// sending Main Navigatione PART to ENGINE file
    fillSections(stepsAmount, step);                                            /// sending All <secions> PART to ENGINE file
    closeEngineFile();
    combineFiles();
}

void ContainersToFile::fillMainNavigation(int stepsAmount, vector <Step> & step)
{
    file << "\t\t<!--Main Navigation-->\n"                                                                                  /// <!-- Main Navigation -->
            "\t\t<nav class=\"main-nav\">\n"                                                                                /// <nav class="main-nav">
            "\t\t\t<ul>\n";                                                                                                 /// <ul>

    for (int i=0; i<stepsAmount; i++)                                                                                       /// <li><a href="#question"></a></li>...
    {
        file << "\t\t\t\t<li><a href=\"#" << step[i].stepID << "\"></a></li>\n";
    }

	file << "\t\t\t<ul>\n"                                                                                                  /// </ul>
            "\t\t</nav>\n\n"                                                                                                /// </nav>
            "\t\t<!-- Slider Controls -->\n"                                                                                /// <!-- Slider Controls -->
            "\t\t<!--<a href=\"\" id=\"arrow_left\"><img src=\"html_template/images/arrow-left.png\" alt=\"Slide Left\" /></a>\n"         /// <!--<a href="" id="arrow_left"><img src="images/arrow-left.png" alt="Slide Left" /></a>
            "\t\t<a href=\"\" id=\"arrow_right\"><img src=\"html_template/images/arrow-right.png\ alt=\"Slide Right\" /></a>-->\n\n";     /// <a href="" id="arrow_right"><img src="images/arrow-right.png" alt="Slide Right" /></a>-->
}

void ContainersToFile::fillSections(int stepsAmount, vector <Step> & step)
{
    string content = "show";

    for (int i=0; i<stepsAmount; i++)
    {
        file << "\t\t<!--" << step[i].stepID << "-->" << endl;                                                            /// <!-- question1 -->
        file << "\t\t<section class=\"content " << content << " \" id=\"" << step[i].stepID << "\">" << endl;             /// <section class="content hide" id="question1">
        content = "hide";

        if (step[i].headingAmount != 0)
        {
            for (int j=0; j<step[i].headingAmount; j++)                                                                   /// <h1>#1</h1>...
            {
                if (step[i].heading[j].headingBold == "yes" && step[i].heading[j].headingItalic == "yes")
                    file << "\t\t\t<h" << step[i].heading[j].headingSize << "><b><i>" << step[i].heading[j].headingText << "</i></b></h" << step[i].heading[j].headingSize << ">" << endl;
                else if (step[i].heading[j].headingBold == "no" && step[i].heading[j].headingItalic == "no")
                    file << "\t\t\t<h" << step[i].heading[j].headingSize << ">" << step[i].heading[j].headingText << "</h" << step[i].heading[j].headingSize << ">" << endl;
                else if (step[i].heading[j].headingBold == "yes" && step[i].heading[j].headingItalic == "no")
                    file << "\t\t\t<h" << step[i].heading[j].headingSize << "><b>" << step[i].heading[j].headingText << "</b></h" << step[i].heading[j].headingSize << ">" << endl;
                else if (step[i].heading[j].headingBold == "no" && step[i].heading[j].headingItalic == "yes")
                    file << "\t\t\t<h" << step[i].heading[j].headingSize << "><i>" << step[i].heading[j].headingText << "</i></h" << step[i].heading[j].headingSize << ">" << endl;
            }
        }
        for (int j=0; j<step[i].stepTextAmount; j++)                                                       /// <p>Text</p>...
        {
            if (step[i].stepText[j].stepTextBold == "yes" && step[i].stepText[j].stepTextItalic == "yes")
                file << "\t\t\t<p><b><i>" << step[i].stepText[j].text << "</i></b></p>" << endl;
            if (step[i].stepText[j].stepTextBold == "no" && step[i].stepText[j].stepTextItalic == "no")
                file << "\t\t\t<p>" << step[i].stepText[j].text << "</p>" << endl;
            if (step[i].stepText[j].stepTextBold == "yes" && step[i].stepText[j].stepTextItalic == "no")
                file << "\t\t\t<p><b>" << step[i].stepText[j].text << "</b></p>" << endl;
            if (step[i].stepText[j].stepTextBold == "no" && step[i].stepText[j].stepTextItalic == "yes")
                file << "\t\t\t<p><i>" << step[i].stepText[j].text << "</i></p>" << endl;
        }
        file << "\t\t\t<hr>" << endl;                                                                       /// <hr>
        for (int j=0; j<step[i].linkAmount; j++)                                                            /// <a href="#question1">Text</a>...
        {
            file << "\t\t\t<p>" << endl;                                                                    /// <p>

            if (step[i].link[j].linkTextBold == "yes" && step[i].link[j].linkTextItalic == "yes")
                file << "\t\t\t<a href=\"#" << step[i].link[j].linkStepID << "\"><b><i>" << step[i].link[j].linkText << "</i></b></a>" << endl;
            if (step[i].link[j].linkTextBold == "no" && step[i].link[j].linkTextItalic == "no")
                file << "\t\t\t<a href=\"#" << step[i].link[j].linkStepID << "\">" << step[i].link[j].linkText << "</a>" << endl;
            if (step[i].link[j].linkTextBold == "yes" && step[i].link[j].linkTextItalic == "no")
                file << "\t\t\t<a href=\"#" << step[i].link[j].linkStepID << "\"><b>" << step[i].link[j].linkText << "</b></a>" << endl;
            if (step[i].link[j].linkTextBold == "no" && step[i].link[j].linkTextItalic == "yes")
                file << "\t\t\t<a href=\"#" << step[i].link[j].linkStepID << "\"><i>" << step[i].link[j].linkText << "</i></a>" << endl;

            file << "\t\t\t</p>" << endl;                                                                  /// </p>
            file << "\t\t\t<hr>" << endl;                                                                  /// </hr>
        }
        file << "\t\t</section>\n\n" << endl;                                                              /// </section>
    }
}
void ContainersToFile::combineFiles()
{
    ifstream file1("html_template/fileBEGINNING.html");                                                    /// file with lines <1-39> till "Main Navigation"
	ifstream file2("html_template/ENGINE.html");                                                           /// created file with lines <40-... till the last </section>
	ifstream file3("html_template/fileEND.html");                                                          /// starts from <!-- Background Slides -->
	ofstream combined_file("PlayTheGame.html") ;                                                           /// creating index file
	combined_file << file1.rdbuf() << endl << file2.rdbuf() << endl << file3.rdbuf() ;                     /// combining 3 files
}







