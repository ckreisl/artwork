# **Artwork**
## About
The idea of this project was given by Jeff Clark's [Word Portrait](http://www.neoformix.com/2008/EinsteinWordPortrait.html) on his website [neoformix.com](http://www.neoformix.com), which shows an image of Albert Einstein only consisting of the text "Genius". Fiete Botschen and I decided to take this image as inspiration for an university Computer Vision course project in 2015. We successfully implemented an algorithm which generates Word Portraits like the one from Jeff Clark.

Till 2015 this project was put on hold. In January, 2018 I started to refactore and optimize the code by using a summed-area table, which boosted the runtime overwhelming well. Furthermore I implemented some submodules based on this algorithm, which allows you to create images consisting of Triangles, Circles and Rectangles (and maybe more soon). Some examples can be seen below.

## Word Portrait
![Word Portrait](images/einstein_words_grey.png)

## Dependencies
* [Qt](https://www.qt.io/) (version 5.10)

## Usage
If you installed Qt Creator IDE already you can easily open the project with the provided `.pro` file.
### Linux
All possible render options can be set within an XML file. Therefor you do not need to recompile the program every time you changed some parameters. The program runs via command line with:

`./artwork [OPTIONS] <rendersettings.xml>`

A help message is included by `./artwork -h` or `./artwork --help` and will print the following lines.
```
Artwork version 0.0.1, Copyright (c) 2018 Christoph Kreisl
Usage: artwork [options] <rendersettings.xml>
Options/Arguments:
   -h --help   Display this help text
   -i iname    Load the input image from a path denoted by "iname"
   -o oname    Write the output image with the name denoted by "oname"
               If there is a file type it will be removed. Set output file type in XML
               rendersettings!
For more information check https://github.com/ckreisl
```

You can use all image types which are supported by the Qt `QImage` class.

### Windows
(will come soon)

### MacOS
(will come soon)

## Some more examples
![Lena Submodules](images/lena_modules.png)

## Status and License
Licensed under LGPLv3 and GPLv3.

Copyright (c) Christoph Kreisl
