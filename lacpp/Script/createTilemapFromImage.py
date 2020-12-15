import cv2
import hashlib
import numpy as np
import math
import sys

# Checks if tile rotated at degree exists in hashmap
# Returns true if it does false otherwise
def checkTile(hashmap, tile, degree):
	if degree is not None:
		imageHash = hashTile(cv2.rotate(tile, degree))
	else:
		imageHash = hashTile(tile)
	if imageHash in tileMap:
		return True
	else:
		return False
		
# Returns SHA1 hash of a tile
def hashTile(tile):
	tileBytes = tile.tobytes()
	imageHash = hashlib.sha1(tileBytes).hexdigest()
	return imageHash

# This Python script creates a tilemap from an image for a tile of given width and height
# It generates a C++ map and outputs the tileset

# arg0 - Image file name
# arg1 - Tile width 
# arg2 - Tile height
# arg3 - Output image file name
# arg4 - Output C++ tile map file 

imageFile = sys.argv[1]
tileWidth = int(sys.argv[2])
tileHeight = int(sys.argv[3])
tilesetOutputImageFileName = sys.argv[4]
tilesetOutputCPPFileName = sys.argv[5]


img = cv2.imread(imageFile)
if img is None:
	print("Unable to open image: " + imageFile)
	sys.exit()
	
# Check imageWidth % tileWidth is 0, same with height
imageHeight, imageWidth = img.shape[:2]
if imageHeight % tileHeight != 0:
	print("Tile height " + str(tileHeight) + " is not a multiple of " + str(imageHeight))
	sys.exit()
if imageWidth % tileWidth != 0:
	print("Tile width " +str(tileWidth) + " is not a multiple of " + str(imageWidth))
	sys.exit()	
	
print("Using image: " + imageFile + str(imageWidth) + "x" + str(imageHeight))
print("Tile width: " + str(tileWidth))
print("Tile height: " + str(tileHeight))

# Start at (0,0) and move to end
startX = 0
startY = 0

# Assumes there are no spaces between tiles
# A later feature request to add spaces
spaceX = 0
spaceY = 0

# Calculate how many tiles across/down we need to check
tilesAcross = int((imageWidth - startX) / (tileHeight + spaceX))
tilesDown = int((imageHeight - startY) / (tileWidth + spaceY))

print("Tiles across: " + str(tilesAcross))
print("Tile down: " + str(tilesDown))

tileMap = {}


for y in range(tilesDown):
	for x in range(tilesAcross):	
		#img[y1:y2, x1:x2]
		x1 = startX + x * (tileWidth + spaceX)
		y1 = startY + y * (tileHeight + spaceY)
		x2 = tileWidth + x1
		y2 = tileHeight + y1

		# Grab a tile at (x1,y1) up to (x2,y2)
		tile = img[y1:y2, x1:x2]

		tileHash = hashTile(tile)
		if tileHash not in tileMap:
			tileMap[tileHash] = (x1,y1,x2,y2)

		# TODO: Add horizontal and vertical flip

		# Grab a tile
		# Calculate 4 hashes for each orientation (0,90,180,270 degrees)
		# If none of the hashes exist in the map, add the tile at 0 degrees
		# else if any hash already exists, add the orientation and position
		
#		tile0Degrees = checkTile(tileMap, tile, None)
#		tile90Degrees = checkTile(tileMap, tile, cv2.ROTATE_90_CLOCKWISE)
#		tile180Degrees = checkTile(tileMap, tile, cv2.ROTATE_180)
#		tile270Degrees = checkTile(tileMap, tile, cv2.ROTATE_90_COUNTERCLOCKWISE)
		
#		if tile0Degrees == False and tile90Degrees == False and tile180Degrees == False and tile270Degrees == False:
#			tileHash = hashTile(tile)
#			tileMap[tileHash] = (x1,y1,x2,y2,0)
#			continue
#		else:
#			if tile0Degrees == True:
#				tileHash = hashTile(tile)
#				tileMap[tileHash] = (x1,y1,x2,y2,0)
#				continue
#			elif tile90Degrees == True:
#				tileHash = hashTile(cv2.rotate(tile, cv2.ROTATE_90_CLOCKWISE))
#				tileMap[tileHash] = (x1,y1,x2,y2,90)
#				continue			
#			elif tile180Degrees == True:
#				tileHash = hashTile(cv2.rotate(tile, cv2.ROTATE_180))
#				tileMap[tileHash] = (x1,y1,x2,y2,180)
#				continue			
#			elif tile270Degrees == True:
#				tileHash = hashTile(cv2.rotate(tile, cv2.ROTATE_90_COUNTERCLOCKWISE))
#				tileMap[tileHash] = (x1,y1,x2,y2,270)
#				continue


# Now we have the map with all the tiles and positions
# Calculate how big the output image will be 
# It's gonna be 128 x H
print("# tiles in image " + str(tilesAcross * tilesDown ))
print("# tiles in map " + str(len(tileMap)))	
outputImageWidth = 128
outputImageHeight = tileHeight * int(math.ceil((len(tileMap) * tileWidth) / outputImageWidth))
print("Ouput image width: " + str(outputImageWidth))
print("Ouput image height: " + str(outputImageHeight))

# Create blank image
tilesetOutputImageFile = np.zeros([outputImageHeight,outputImageWidth,3],dtype=np.uint8)
tilesetOutputImageFile[:] = 255

tileX = 0
tileY = 0

# Copy tiles onto tilemap
for tile in tileMap:
	tileInfo = tileMap[tile]
	if tileX + tileWidth != outputImageWidth:
		tileX+= tileWidth
	else:
		tileX = 0
		tileY += tileHeight
	print("tilesetOutputImageFile[" + str(tileY) + ":" + str(tileHeight) + "," + str(tileX) + ":" + str(tileWidth) + "] = img[" + str(tileInfo[1]) + ":" + str(tileInfo[3]) + ", " + str(tileInfo[0]) + ":" + str(tileInfo[2]) + "]")
	tilesetOutputImageFile[tileY:tileY+tileHeight, tileX:tileX+tileWidth] = img[tileInfo[1]:tileInfo[3], tileInfo[0]:tileInfo[2]]

cv2.namedWindow('image', cv2.WINDOW_KEEPRATIO)
cv2.imshow('image',tilesetOutputImageFile)
cv2.resizeWindow('image', outputImageWidth*4, outputImageHeight*4)
cv2.imwrite(tilesetOutputImageFileName,tilesetOutputImageFile)
cv2.waitKey(0)
# 0  1  2  3

# x1,y1, x2,y2 
#(1, 1, 8, 8)

		 #[y1:y2, x1:x2] #[y1:y2, x1:x2]
#blankImage[0:7, 0:7] = img[1:8, 1:8] #img[rect[1]:rect[3], rect[0]:rect[2]]

#bx1 = 0
#by1 = 0
#bx2 = tileW
#by2 = tileH
#for tile in tileMap:
#	rect = tileMap[tile]
	#blankImage[y1:y2, x1:x2]
#	print(rect)
	# Copies each unique tile onto a blank image for user [by1:by2, bx1:bx2]
	#print('blankImage[' + str(by1) + ':' + str(by2) + ', '  + str(bx1) + ':' + str(bx2) + '] = img[' + str(rect[1]) + ':' + str(rect[3]) + ', ' + str(rect[0]) + ':' + str(rect[2]) + ']')
#	blankImage[0:7, 0:7] = img[rect[1]:rect[3], rect[0]:rect[2]]
#	blankImage[0:7, 7:7] = img[rect[1]:rect[3], rect[0]:rect[2]]
#	bx1 += tileW
#	bx2 += bx1
