import cv2
import os

# File paths - adjust as needed
src_path = "images/source.png"
dst_path = "images/target.png"

# Load images with checks
src_img = cv2.imread(src_path)
if src_img is None:
    print(f"Cannot load {src_path}")
    exit()

dst_img = cv2.imread(dst_path)
if dst_img is None:
    print(f"Cannot load {dst_path}")
    exit()

# Match dimensions
size = (400, 400)  # Fixed for demo
src_img = cv2.resize(src_img, size)
dst_img = cv2.resize(dst_img, size)

# Generate 120 transition frames
for frame in range(121):
    blend_factor = frame / 120.0
    blended = cv2.addWeighted(src_img, 1 - blend_factor, dst_img, blend_factor, 0)
    
    cv2.imshow("Image Morph", blended)
    key = cv2.waitKey(20)  # ms delay; smaller = faster
    if key == 27:  # ESC quits
        break

cv2.waitKey(0)
cv2.destroyAllWindows()
print("Morph complete!")