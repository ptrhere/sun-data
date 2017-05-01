#!/usr/bin/env python

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
    lines = contents.splitlines()
    return (lines,sys.argv[1],len(lines))

def setXcoord(step,prev):
    # change x value with step when we store previous value in prev 
    value = "x=\"" + str(decimal.Decimal(step) + decimal.Decimal(prev)) + "cm\"" 
    return value 

def setYcoord(step,prev):
    # change x value with step when we store previous value in prev 
    #decimal.getcontext().prec = 3
    value = "y=\"" + str(decimal.Decimal(step) + decimal.Decimal(prev)) + "cm\"" 
    return value 

def createGroup(subset,coordX,coordY,stepY,ff):
    # create group start from startRow and ends at endRow with stepY and X coordinate at coordX
    prev = coordY
    rows = []
    
    startRow = int(subset[0])
    endRow = int(subset[1])

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

def startStopGenerator(noOfRows,noOfCols):
    # generate tuple((start1,stop1),(start2,stop2),(start3,stop3,...(startN,stopN))
    ll = ['none'] * noOfCols 
    for i in range(0,noOfCols):
        if i == 0:
            ll[i] = (0,noOfRows)
        else:
            ll[i] = (((noOfRows*i)+1),((noOfRows*(i+1))+1))
    print(ll)
    return(ll)


def main():
    ff = openFile()
   
    # @Pepa set desired number of columns here 
    setNumOfColumns = 14

    #print(ff[2])
    #print(ff[2]/14)
    #print(round(ff[2]/14))
    noOfRows = round(ff[2]/setNumOfColumns) 
    subset = startStopGenerator(noOfRows,setNumOfColumns)
    #print(subset[0])
    #print(subset[0][1])

    # @Pepa change here 'coordX' of the columns, initial Y coord - 'coordY' and the step between the rows 'stepY' below
    # createGroup(subset,     coordX(cm),coordY(cm),stepY(cm),ff):  
    col1 = createGroup(subset[0],      1,   10.0,   0.5,   ff[0])
    col2 = createGroup(subset[1],      6,   10.0,   0.5,   ff[0])
    col3 = createGroup(subset[2],     12,   10.0,   0.5,   ff[0])
    col4 = createGroup(subset[3],     18,   10.0,   0.5,   ff[0])
    col5 = createGroup(subset[4],     24,   10.0,   0.5,   ff[0])
    col6 = createGroup(subset[5],     30,   10.0,   0.5,   ff[0])
    col7 = createGroup(subset[6],     36,   10.0,   0.5,   ff[0])
    col8 = createGroup(subset[7],     42,   10.0,   0.5,   ff[0])
    col9 = createGroup(subset[8],     48,   10.0,   0.5,   ff[0])
    col10 = createGroup(subset[9],    54,   10.0,   0.5,   ff[0])
    col11 = createGroup(subset[10],   60,   10.0,   0.5,   ff[0])
    col12 = createGroup(subset[11],   66,   10.0,   0.5,   ff[0])
    col13 = createGroup(subset[12],   72,   10.0,   0.5,   ff[0])
    col14 = createGroup(subset[13],   78,   10.0,   0.5,   ff[0])    

    #for i in range(0,len(rows)):
    #    print(rows[i])

    print("Writing to file: " + ff[1] + ".svg")
    writeToFile(ff,col1,col2,col3,col4,col5,col6,col7,col8,col9,col10,col11,col12,col13,col14)
    print("Done")

        
if __name__ == "__main__":
    main()
