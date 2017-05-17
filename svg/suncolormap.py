import bisect
import webcolors

# illuminance (lux) - color table
# keep list in sorted order !!!
# use web color names
# eg.   https://www.w3schools.com/cssref/css_colors.asp

colorMap = [
  (0.0, 'total darkness', 'black'),
  (0.0001, 'moonless overcast night sky', 'black'),
  (0.002, 'moonless clear night sky with airglow', 'darkblue'),
  (0.05, 'full moon clear night', 'violet'),
  (0.36, 'full moon clear night', 'violet'),
  (3.4,  'dark limit civil twilight clear sky','blue'),
  (20,  'public area dark surroundings', 'aquamarine'),
  (50,  'public area dark surroundings', 'aqua'),
  (50,  'family living room','orange'),
  (80,  'office hallway / toilet', 'yellow'),
  (100,  'very dark overcast day', 'lightgray'),
  (320,  'office lighting', 'white'),
  (400,  'sunrise or sunset on clear day','orangered'),
  (500,  'office lighting', 'white'),
  (1000,  'overcast day', 'silver'),
  (10000,  'full daylight (no direct sun)', 'snow'),
  (25000, 'full daylight (no direct sun)', 'white'),
  (32000,  'direct sunlight', 'white')
]



def lerp(a, b, t):
     return map(lambda x,y: x*(1 - t) + y * t, a, b)

def selectcolor(inputvalue):
  if inputvalue < 0:
    inputvalue = 0.0
  if inputvalue > 31000:
    inputvalue=31500
  index = bisect.bisect(colorMap, (inputvalue,None,None))
  print index
  colorFrom = webcolors.name_to_rgb( colorMap[index-1][2] )
  colorTo = webcolors.name_to_rgb( colorMap[index][2] )
  ratio = (inputvalue - colorMap[index-1][0]) / (colorMap[index][0] - colorMap[index-1][0] )
  return lerp(colorFrom,colorTo,ratio)


