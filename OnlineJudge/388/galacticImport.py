from sys import stdin

numPlanets = 0
planets = {}

def BFS():
  return 0

def findMax(planets):
  return 0  

for line in stdin:
  if numPlanets != 0:
    newPlanetData = line.strip().split(" ")
    starIndex = newPlanetData[2].find("*")
    if starIndex != -1:
      planets[newPlanetData[0]] = (float(newPlanetData[1]), True, newPlanetData[2][:starIndex] + newPlanetData[2][starIndex + 1:])
    else:
      planets[newPlanetData[0]] = (float(newPlanetData[1]), False, newPlanetData[2])
      
    numPlanets = numPlanets - 1
    if numPlanets == 0:
      planets.sort()
      for planet in planets:
        print(planets[planet])
  else:
    print("------------new galaxy-------------")
    planets = {}
    numPlanets = int(line)
      
