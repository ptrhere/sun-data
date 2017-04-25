#! /usr/bin/python3

import sys


def header(i):
    svgHeadRow1 = "<?xml version=\"1.0\" encoding=\"iso-8859-1\"?>"
    svgHeadRow2 = "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 20001102//EN\"" 
    svgHeadRow3 = "\"http://www.w3.org/TR/2000/CR-SVG-20001102/DTD/svg-20001102.dtd\">"
    svgHeadRow4 = "<svg width=\"84cm\" height=\"350cm\">"
    svgHead = (svgHeadRow1, svgHeadRow2, svgHeadRow3, svgHeadRow4) 
    print(svgHead[i])
 

def openFile():
    '''
    sun-data file format:
        timestamp, ir, full, lux_msb, lux_lsb
    '''
    with open(sys.argv[1],"r") as f:
        contents = f.read()
        f.close()
    return contents.splitlines()

def createSvg(sun_data):
    f1 = open('example.svg','r')
    exampleSvg = f1.readlines()
    f1.close()
    print(exampleSvg)
    print(len(sun_data)) 
    print("<text x=\"0\" y=\"2cm\" fill=\"#808080\" font-size=\"18pt\" style=\"font-family:Arial\">Sample Text</text>\n")
    ss = "<text x=\""
    print(ss)
    sss = 10
    ssss = "\""
    s = ss + str(sss) + ssss
    print(s)
 

def main():
    ff = openFile()
    print(type(ff))
    print(len(ff))
    column = []
    for i in range(0,363):
        column.append(ff[i])  
        print(column[i]) 
    createSvg(tuple(column)) 
    header(0)
    print('Hello world!')

if __name__ == "__main__":
    main()
