;; Auto-generated. Do not edit!


(when (boundp 'opencv_cam::clu)
  (if (not (find-package "OPENCV_CAM"))
    (make-package "OPENCV_CAM"))
  (shadow 'clu (find-package "OPENCV_CAM")))
(unless (find-package "OPENCV_CAM::CLU")
  (make-package "OPENCV_CAM::CLU"))
(unless (find-package "OPENCV_CAM::CLUREQUEST")
  (make-package "OPENCV_CAM::CLUREQUEST"))
(unless (find-package "OPENCV_CAM::CLURESPONSE")
  (make-package "OPENCV_CAM::CLURESPONSE"))

(in-package "ROS")





(defclass opencv_cam::cluRequest
  :super ros::object
  :slots (_k ))

(defmethod opencv_cam::cluRequest
  (:init
   (&key
    ((:k __k) 0)
    )
   (send-super :init)
   (setq _k (round __k))
   self)
  (:k
   (&optional __k)
   (if __k (setq _k __k)) _k)
  (:serialization-length
   ()
   (+
    ;; int32 _k
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int32 _k
       (write-long _k s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int32 _k
     (setq _k (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(defclass opencv_cam::cluResponse
  :super ros::object
  :slots (_result ))

(defmethod opencv_cam::cluResponse
  (:init
   (&key
    ((:result __result) 0)
    )
   (send-super :init)
   (setq _result (round __result))
   self)
  (:result
   (&optional __result)
   (if __result (setq _result __result)) _result)
  (:serialization-length
   ()
   (+
    ;; int32 _result
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int32 _result
       (write-long _result s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int32 _result
     (setq _result (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(defclass opencv_cam::clu
  :super ros::object
  :slots ())

(setf (get opencv_cam::clu :md5sum-) "6c4229b893df484eaff1a08b305984ad")
(setf (get opencv_cam::clu :datatype-) "opencv_cam/clu")
(setf (get opencv_cam::clu :request) opencv_cam::cluRequest)
(setf (get opencv_cam::clu :response) opencv_cam::cluResponse)

(defmethod opencv_cam::cluRequest
  (:response () (instance opencv_cam::cluResponse :init)))

(setf (get opencv_cam::cluRequest :md5sum-) "6c4229b893df484eaff1a08b305984ad")
(setf (get opencv_cam::cluRequest :datatype-) "opencv_cam/cluRequest")
(setf (get opencv_cam::cluRequest :definition-)
      "int32 k
---
int32 result
")

(setf (get opencv_cam::cluResponse :md5sum-) "6c4229b893df484eaff1a08b305984ad")
(setf (get opencv_cam::cluResponse :datatype-) "opencv_cam/cluResponse")
(setf (get opencv_cam::cluResponse :definition-)
      "int32 k
---
int32 result
")



(provide :opencv_cam/clu "6c4229b893df484eaff1a08b305984ad")


