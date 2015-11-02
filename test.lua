local Delaunay = require("delaunay")
local Point    = Delaunay.Point

-- Creating 10 random points
local points = {}

points[1]  = Point(0, 0)
points[2]  = Point(1, 3)
points[3]  = Point(2, 5)
points[4]  = Point(3, 4)
points[5]  = Point(9, 5)
points[6]  = Point(0, 2)
points[7]  = Point(1, 0)
points[8]  = Point(5, 3)
points[9]  = Point(1, 9)
points[10] = Point(7, 3)

-- Triangulating de convex polygon made by those points
local triangles = Delaunay.triangulate(unpack(points))

-- Printing the results
for i, triangle in ipairs(triangles) do
	print(triangle)
end
