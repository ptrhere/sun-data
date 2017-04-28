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

def writeToFile(ff,data1,data2,data3,data4,data5,data6,data7,data8,data9,data10,data11,data12,data13,data14):
    # write to SVG file
    newFile = ff[1] + ".svg"
    ffw = open(newFile, 'w')
    
    head = header()
    for i in range(0,len(head)):
        ffw.write(head[i] + "\n")
     
    for i in range(0,len(data1)):
        ffw.write(data1[i] + "\n")

    for i in range(0,len(data2)):
        ffw.write(data2[i] + "\n")

    for i in range(0,len(data3)):
        ffw.write(data3[i] + "\n")

    for i in range(0,len(data4)):
        ffw.write(data4[i] + "\n")

    for i in range(0,len(data5)):
        ffw.write(data5[i] + "\n")

    for i in range(0,len(data6)):
        ffw.write(data6[i] + "\n")

    for i in range(0,len(data7)):
        ffw.write(data7[i] + "\n")

    for i in range(0,len(data8)):
        ffw.write(data8[i] + "\n")

    for i in range(0,len(data9)):
        ffw.write(data9[i] + "\n")

    for i in range(0,len(data10)):
        ffw.write(data10[i] + "\n")

    for i in range(0,len(data11)):
        ffw.write(data11[i] + "\n")

    for i in range(0,len(data12)):
        ffw.write(data12[i] + "\n")

    for i in range(0,len(data13)):
        ffw.write(data13[i] + "\n")

    for i in range(0,len(data14)):
        ffw.write(data14[i] + "\n")

    foot = footer()
    for i in range(0,len(foot)):
        ffw.write(foot[i] + "\n")

    ffw.close()


def main():
    ff = openFile()

    # createGroup(startRow,endRow,coordX,stepY,ff):  
    rows1 = createGroup(0,551,1,0.5,ff[0])
    rows2 = createGroup(552,1102,10,0.5,ff[0])
    rows3 = createGroup(1103,1653,20,0.5,ff[0])
    rows4 = createGroup(1653,2204,30,0.5,ff[0])
    rows5 = createGroup(2204,2755,40,0.5,ff[0])
    rows6 = createGroup(2755,3306,50,0.5,ff[0])
    rows7 = createGroup(3306,3857,60,0.5,ff[0])
    rows8 = createGroup(3857,4408,70,0.5,ff[0])
    rows9 = createGroup(4408,4959,80,0.5,ff[0])
    rows10 = createGroup(4959,5510,90,0.5,ff[0])
    rows11 = createGroup(5510,6061,100,0.5,ff[0])
    rows12 = createGroup(6061,6612,110,0.5,ff[0])
    rows13 = createGroup(6612,7163,120,0.5,ff[0])
    rows14 = createGroup(7163,7714,130,0.5,ff[0])    

    #for i in range(0,len(rows)):
    #    print(rows[i])

    print("Writing to file: " + ff[1] + ".svg")
    writeToFile(ff,rows1,rows2,rows3,rows4,rows5,rows6,rows7,rows8,rows9,rows10,rows11,rows12,rows13,rows14)
    print("Done")

        
if __name__ == "__main__":
    main()
