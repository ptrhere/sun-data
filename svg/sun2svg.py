#! /usr/bin/python3

import sys
import decimal

decimal.getcontext().prec = 8

def header():
    svgHeadRow1 = "<?xml version=\"1.0\" encoding=\"iso-8859-1\"?>"
    svgHeadRow2 = "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 20001102//EN\"" 
    svgHeadRow3 = "\"http://www.w3.org/TR/2000/CR-SVG-20001102/DTD/svg-20001102.dtd\">"
    svgHeadRow4 = "<svg width=\"84cm\" height=\"350cm\">"
    svgHead = (svgHeadRow1, svgHeadRow2, svgHeadRow3, svgHeadRow4) 
    return svgHead

def footer():
    svgFootRow1 = "</svg>"
    svgFootRow2 = "\n"
    svgFoot = (svgFootRow1, svgFootRow2)
    return svgFoot 

def openFile():
    '''
    sun-data file format:
        timestamp, ir, full, lux_msb, lux_lsb
    '''
    with open(sys.argv[1],"r") as f:
        contents = f.read()
        f.close()
    return (contents.splitlines(),sys.argv[1])

def setXcoord(step,prev):
    # change x value with step when we store previous value in prev 
    value = "x=\"" + str(decimal.Decimal(step) + decimal.Decimal(prev)) + "cm\"" 
    return value 

def setYcoord(step,prev):
    # change x value with step when we store previous value in prev 
    #decimal.getcontext().prec = 3
    value = "y=\"" + str(decimal.Decimal(step) + decimal.Decimal(prev)) + "cm\"" 
    return value 

def createGroup(startRow,endRow,coordX,stepY,ff):
    # create group start from startRow and ends at endRow with stepY and X coordinate at coordX
    prev = 0
    rows = []

    svgGroupStart = "<g fill=\"#808080\" font-size=\"12pt\" style=\"font-family:Arial\">"
    svgGroupEnd = "</g>"

    rows.append(svgGroupStart)

    for i in range(startRow,endRow):
       svgRow = "<text " + setXcoord(coordX,0) + " " + setYcoord(stepY,prev) + ">" + ff[i] + "</text>"
       prev = prev + stepY
       rows.append(svgRow)

    rows.append(svgGroupEnd)
    return rows 

def writeToFile(ff, data):
    # write to SVG file
    newFile = ff[1] + ".svg"
    ffw = open(newFile, 'w')
    
    head = header()
    for i in range(0,len(head)):
        ffw.write(head[i] + "\n")
     
    for i in range(0,len(data)):
        ffw.write(data[i] + "\n")

    foot = footer()
    for i in range(0,len(foot)):
        ffw.write(foot[i] + "\n")

    ffw.close()


def main():
    ff = openFile()

    # createGroup(startRow,endRow,coordX,stepY,ff):  
    rows = createGroup(0,363,1,0.5,ff[0])

    #for i in range(0,len(rows)):
    #    print(rows[i])

    print("Writing to file: " + ff[1] + ".svg")
    writeToFile(ff,rows)
    print("Done")

        
if __name__ == "__main__":
    main()
