train_from_base:
	python3 tools/yolov5/train.py --img 640 --batch 16 --epochs 5 --data my-drone.yaml --weights data/base_weights/best.pt

detect_base_weights:
	python3 tools/yolov5/detect.py --weights data/base_weights/best.pt --source data/videos/VID_20220208_150059.mp4

detect_base_weights_test:
	python3 tools/yolov5/detect.py --weights data/base_weights/best.pt --source data/videos/2022-02-15-154943.mp4

detect_colab_weights_v1:
	python3 tools/yolov5/detect.py --weights data/colab_weights/v1/best.pt --source data/videos/VID_20220208_150059.mp4

detect_colab_weights_v2:
	python3 tools/yolov5/detect.py --weights data/colab_weights/v2/best.pt --source data/videos/2022-02-15-154638.mp4

live_cam0:
	python3 tools/yolov5/detect.py --weights data/colab_weights/v2/best.pt --source 0

live_cam2:
	python3 tools/yolov5/detect.py --weights data/colab_weights/v2/best.pt --source 2

annotation:
	cd tools/Yolo-Annotation-Tool-New- && python3 main.py

demo1:
	python3 tools/yolov5/detect.py --weights data/base_weights/best.pt --source data/videos/VID_20220208_160639.mp4

demo2:
	python3 tools/yolov5/detect.py --weights data/colab_weights/v2/best.pt --source data/videos/VID_20220208_160639.mp4
