"""
    This program reads from a node file and an edge file, calculates 
    the actual distance between two points given their longitude and 
    latitude, and writes to a new edge file so that the weight of each
    edge is now the actual distance in KM between the two points.
"""

# modify filename here
node_filename = "calnode.txt"
edge_filename = "caledge.txt"
write_filename = "caledge_modified.txt"


from math import radians, cos, sin, asin, sqrt

def distance(lat1, lat2, lon1, lon2):
     
    # The math module contains a function named
    # radians which converts from degrees to radians.
    lon1 = radians(lon1)
    lon2 = radians(lon2)
    lat1 = radians(lat1)
    lat2 = radians(lat2)
      
    # Haversine formula
    dlon = lon2 - lon1
    dlat = lat2 - lat1
    a = sin(dlat / 2)**2 + cos(lat1) * cos(lat2) * sin(dlon / 2)**2
 
    c = 2 * asin(sqrt(a))
    
    # Radius of earth in kilometers. Use 3956 for miles
    r = 6371
      
    # calculate the result
    return(c * r)

def make_map(node_filename):
    MAP = dict()
    with open(node_filename) as cnode:
        lines = cnode.readlines()
        for line in lines:
            nums = line.rstrip().split(" ")
            MAP[int(nums[0])] = (float(nums[1]), float(nums[2]))
    return MAP

node_map = make_map(node_filename)
write_file = open(write_filename, 'w')
with open(edge_filename) as edge_file:
    lines = edge_file.readlines()
    for line in lines:
        ID, start, end, weight = line.rstrip().split(" ")
        start, end = int(start), int(end)
        lon1, lat1 = node_map[start]
        lon2, lat2 = node_map[end]
        new_weight = round(distance(lat1, lat2, lon1, lon2), 5)
        new_line = ID + " " + str(start) + " " + str(end) + " " + str(new_weight) + "\n"
        write_file.write(new_line)
write_file.close()
