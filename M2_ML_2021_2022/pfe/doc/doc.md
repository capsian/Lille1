# Articles

- [Dist-YOLO: Fast Object Detection with Distance Estimation](articles/Dist-YOLO_Fast_Object_Detection_with_Distance_Estimation.pdf)
  - source code: https://gitlab.com/EnginCZ/yolo-with-distance
  - abstract:
``` We present a scheme of how YOLO can be improved in order to predict the absolute distance of objects using only information from a monocular camera. 
It is fully integrated into the original architecture by extending the prediction vectors, sharing the backbone’s weights with the bounding box regressor, and updating the original loss function by a part responsible for distance estimation.
We designed two ways of handling the distance, class-agnostic and class-aware, proving class-agnostic creates smaller prediction vectors than class-aware and achieves better results. 
We demonstrate that the subtasks of object detection and distance measurement are in synergy, resulting in the increase of the precision of the original bounding box functionality. 
We show that using the KITTI dataset, the proposed scheme yields a mean relative error of 11% considering all eight classes and the distance range within [0, 150] m, which makes the solution highly competitive with existing
approaches. Finally, we show that the inference speed is identical to the unmodified YOLO, 45 frames per second.
```

- [Automated Drone Detection Using YOLOv4](articles/Automated_Drone_Detection_Using_YOLOv4.pdf)
  - abstract:
``` Drones are increasing in popularity and are reaching the public faster than ever before. Consequently, the chances of a drone being misused are multiplying. Automated drone detection is
necessary to prevent unauthorized and unwanted drone interventions. In this research, we designed an automated drone detection system using YOLOv4. The model was trained using drone and
bird datasets. We then evaluated the trained YOLOv4 model on the testing dataset, using mean average precision (mAP), frames per second (FPS), precision, recall, and F1-score as evaluation
parameters. We next collected our own two types of drone videos, performed drone detections, and calculated the FPS to identify the speed of detection at three altitudes. Our methodology showed
better performance than what has been found in previous similar studies, achieving a mAP of 74.36%, precision of 0.95, recall of 0.68, and F1-score of 0.79. For video detection, we achieved an FPS of 20.5
on the DJI Phantom III and an FPS of 19.0 on the DJI Mavic Pro.
```

- [Learning Object-Specific Distance From a Monocular Image](articles/Zhu_Learning_Object-Specific_Distance_From_a_Monocular_Image_ICCV_2019_paper.pdf)
  - abstract:
``` Environment perception, including object detection and distance estimation, is one of the most crucial tasks for autonomous driving. Many attentions have been paid on the object detection task, but distance estimation only arouse
few interests in the computer vision community. Observing that the traditional inverse perspective mapping algorithm performs poorly for objects far away from the camera or on the curved road, in this paper, we address the challenging
distance estimation problem by developing the first end-to-end learning-based model to directly predict distances for given objects in the images. Besides the introduction of a learning-based base model, we further design an enhanced
model with a keypoint regressor, where a projection loss is defined to enforce a better distance estimation, especially for objects close to the camera. To facilitate the research on this task, we construct the extented KITTI and nuScenes
(mini) object detection datasets with a distance for each object. Our experiments demonstrate that our proposed methods outperform alternative approaches (e.g., the traditional IPM, SVR) on object-specific distance estimation, particularly for the challenging cases that objects are on a curved
road. Moreover, the performance margin implies the effectiveness of our enhanced method
```

- [YOLODrone: Improved YOLO Architecture for Object Detection in Drone Images](articles/YOLODrone_Improved_YOLO_Architecture_for_Object_Detection_in_Drone_Images.pdf)
  - abstract:
``` Recent advances in robotics and computer vision fields yield emerging new applications for camera equipped drones. One such application is aerial-based object detection. However, despite the recent advances in the relevant literature,
object detection remains as a challenging task in computer vision. Existing object detection algorithms demonstrate even lower performance on drone (or aerial) images since the object detection problem is a more challenging problem in aerial images,
when compared to the detection task in ground-taken images. There are many reasons for that including: (i) the lack of large drone datasets with large object variance, (ii) the larger variance in both scale and orientation in drone images, and (iii) the
difference in shape and texture features between the ground and the aerial images. In this paper, we introduce an improved YOLO algorithm: YOLODrone for detecting objects in drone images. We evaluate our algorithm on VisDrone2019 dataset and report
improved results when compared to YOLOv3 algorithm.
```

# Links
## YOLO
- https://machinelearningmastery.com/how-to-perform-object-detection-with-yolov3-in-keras/
- https://github.com/chuanenlin/drone-net
  - DroneNet is Joseph Redmon's YOLO real-time object detection system retrained on 2664 images of DJI drones, labeled.
- https://pjreddie.com/darknet/
- https://github.com/dnjstjr93/Drone-Detection_YOLOv3_PyTorch

## Distance
- https://www.pyimagesearch.com/2015/01/19/find-distance-camera-objectmarker-using-python-opencv/
- https://github.com/paul-pias/Object-Detection-and-Distance-Measurement
- http://emaraic.com/blog/distance-measurement

## ArUco Markers

- https://www.pyimagesearch.com/2020/12/21/detecting-aruco-markers-with-opencv-and-python/
- https://automaticaddison.com/how-to-detect-aruco-markers-using-opencv-and-python/
- https://pysource.com/2021/05/28/measure-size-of-an-object-with-opencv-aruco-marker-and-python/
- https://docs.opencv.org/4.x/d5/dae/tutorial_aruco_detection.html