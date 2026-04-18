import cv2
import numpy as np

def resizeByRatio(image, ratio):
  height = image.shape[0]
  width = image.shape[1]

  newHeight = int(height * ratio)
  newWidth = int(width * ratio)

  newImage = np.zeros((newHeight, newWidth, 3), np.uint8)

  for i in range(newHeight):
    for j in range(newWidth):
      x = max(0, min(height - 1, int(i / ratio)))
      y = max(0, min(width - 1, int(j / ratio)))
      newImage[i][j] = image[x][y]

  return newImage

def main():
  image0 = cv2.imread('images/image.tif')
  image1 = resizeByRatio(image0, 10)
  image2 = resizeByRatio(image1, 0.1)

  cv2.imwrite('images/image-1.tif', image1)
  cv2.imwrite('images/image-2.tif', image2)

main()
