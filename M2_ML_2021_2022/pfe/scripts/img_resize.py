import cv2

# Read
img_dir = "data/images/last/"
img_name = "IMG_20220225_144237.jpg"
img_path = img_dir + img_name
image = cv2.imread(img_path, 1)

# Resize
image_resized = cv2.resize(image, (1280, 720))

# Save
img_output_dir = "data/images/last/"
img_output_name = img_name[:-4] + "_rescaled.jpg"
output_path = img_output_dir + img_output_name
cv2.imwrite(output_path, image_resized)

# Log
print("Saved at", output_path)
