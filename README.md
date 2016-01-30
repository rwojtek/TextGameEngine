## Synopsis 

This is a simple text game engine creating HTML file from XML file as a source story. 

## Example

The link below shows a sample text game created by the engine. 

Try out the app: [http://world-end.herokuapp.com/](http://world-end.herokuapp.com/) (_Heroku app may have gone to sleep, reload the page if you see a black background_)

## TheSourceStory.xml (your text game story)

All you need to play your own text game is to create XML file with your game story. 
XML file has to be in particular syntax:

**Syntax of a source story file**

```
<?xml version="1.0" encoding="UTF-8"?>
<game>
	<step>
		<stepID>Your step name</stepID>
		<stepHeading size="1" bold="no" italic="no">Your step heading name</stepHeading>
		<stepText bold="yes" italic="yes">Your step text</stepText>
		<link>
			<linkStepID>Your stepID name (where the story goes after choosing undermentioned choice)</linkStepID>
			<linkText bold="no" italic="yes">Text of choice</linkText>
		</link>
	</step>
	
	<step>...
</game>
```

It is possible to create unlimited numer of steps as well as numerous stepHeading, stepText and linkStepID with linkText in each step. 

All attributes are changeable:

* size = 1-6
* bold = yes/no
* italic = yes/no

## Installation

1. Download the project
2. Unzip it on you computer
3. Create your xml file with your story
4. Call the file TheSourceStory.xml
5. Replace it with my TheSourceStory.xml file
6. Run the engine
7. Run PlayTheGame.html file to enjoy your game

## Directory Structure
```
+---html_template
|   +---css
|   +---images
|       \---backgrounds
|   \---js
+---rapidxml-1.13

+---main.cpp
+---TextGameEngine.cpp		<- Main logic program file
+---TextGameEngine.h

+---TheSourceStory.xml		<- Input file (changeable)

+---PlayTheGame.html		<- The main template file
```
## Reused sources & licenses
##### _XML parser_
- RapidXml Version 1.13 - The MIT License

##### _HTML template (has been modified)_
- [http://wegraphics.net/downloads/avenir-a-free-coming-soon-html-template/](http://wegraphics.net/downloads/avenir-a-free-coming-soon-html-template/)

##### _QUIZ questions_
- [http://www.playbuzz.com/](http://www.playbuzz.com/)
- [http://www.quiznatic.com/](http://www.quiznatic.com/)
