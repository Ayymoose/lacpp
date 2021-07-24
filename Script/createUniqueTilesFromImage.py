import cv2
import hashlib
import numpy as np

# Can't remember what my script does


img = cv2.imread(r'D:\Users\Ayman\Desktop\lacpp\lacpp\Resources\Background\Misc\map.png')

# Function paramters
startX = 1
startY = 1

spaceX = 1
spaceY = 1

tileW = 7
tileH = 7

imgHeight, imgWidth = img.shape[:2]
tilesAcross = int((imgHeight - startX) / (tileW + spaceX))
tilesDown = int((imgWidth - startY) / (tileH + spaceY))
tileIndex = 0

imageMap = {}




for y in range(tilesDown):
	for x in range(tilesAcross):
		#img[y1:y2, x1:x2]
		x1 = startX + x * (tileW + spaceX)
		y1 = startY + y * (tileH + spaceY)
		x2 = tileW + x1
		y2 = tileH + y1
		tile = img[y1:y2, x1:x2]
		
		b_tile = tile.tobytes()
		sha1Hash = hashlib.sha1(b_tile).hexdigest()
		imageMap[sha1Hash] = (x1,y1,x2,y2)
		#print('SHA1 for ' + str(tileIndex) + ' is ' + )
		#cv2.imwrite('D:\\Users\\Ayman\\Desktop\\lacpp\\lacpp\\Python\\' + str(tileIndex) + '.png',tile)
		tileIndex+=1

print('startX = ' + str(startX) + ' startY = ' + str(startY))
print('spaceX = ' + str(spaceX) + ' spaceY = ' + str(spaceY))
print('tileW = ' + str(tileW) + ' tileH = ' + str(tileH))
print('Total tiles of ' + str(tileIndex))		

uniqueTileCount = len(imageMap)
print('Unique tiles of requested size is ' + str(uniqueTileCount))
for x in imageMap:
	rect = imageMap[x]
	cv2.rectangle(img,(rect[0],rect[1]),(rect[2],rect[3]),(0,255,0),1)
	#print(rect)


tilesPerRow = 16
newWidth = tilesPerRow * tileW
newHeight = tileH
blankImage = np.zeros([129,129,3],dtype=np.uint8)
blankImage[:] = 255

# 0  1  2  3

# x1,y1, x2,y2 
#(1, 1, 8, 8)

		 #[y1:y2, x1:x2] #[y1:y2, x1:x2]
#blankImage[0:7, 0:7] = img[1:8, 1:8] #img[rect[1]:rect[3], rect[0]:rect[2]]

bx1 = 0
by1 = 0
bx2 = tileW
by2 = tileH
for tile in imageMap:
	rect = imageMap[tile]
	#blankImage[y1:y2, x1:x2]
	print(rect)
	# Copies each unique tile onto a blank image for user [by1:by2, bx1:bx2]
	#print('blankImage[' + str(by1) + ':' + str(by2) + ', '  + str(bx1) + ':' + str(bx2) + '] = img[' + str(rect[1]) + ':' + str(rect[3]) + ', ' + str(rect[0]) + ':' + str(rect[2]) + ']')
	blankImage[0:7, 0:7] = img[rect[1]:rect[3], rect[0]:rect[2]]
	blankImage[0:7, 7:7] = img[rect[1]:rect[3], rect[0]:rect[2]]
	bx1 += tileW
	bx2 += bx1

cv2.namedWindow('image', cv2.WINDOW_KEEPRATIO)
cv2.imshow('image',blankImage)
cv2.resizeWindow('image', imgWidth*4, imgHeight*4)
cv2.waitKey(0)

#cv2.namedWindow('image', cv2.WINDOW_KEEPRATIO)
#cv2.imshow('image',img)
#cv2.resizeWindow('image', imgWidth*4, imgHeight*4)
#cv2.waitKey(0)