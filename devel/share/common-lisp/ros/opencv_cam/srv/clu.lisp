; Auto-generated. Do not edit!


(cl:in-package opencv_cam-srv)


;//! \htmlinclude clu-request.msg.html

(cl:defclass <clu-request> (roslisp-msg-protocol:ros-message)
  ((my_number
    :reader my_number
    :initarg :my_number
    :type cl:integer
    :initform 0))
)

(cl:defclass clu-request (<clu-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <clu-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'clu-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name opencv_cam-srv:<clu-request> is deprecated: use opencv_cam-srv:clu-request instead.")))

(cl:ensure-generic-function 'my_number-val :lambda-list '(m))
(cl:defmethod my_number-val ((m <clu-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader opencv_cam-srv:my_number-val is deprecated.  Use opencv_cam-srv:my_number instead.")
  (my_number m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <clu-request>) ostream)
  "Serializes a message object of type '<clu-request>"
  (cl:let* ((signed (cl:slot-value msg 'my_number)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <clu-request>) istream)
  "Deserializes a message object of type '<clu-request>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'my_number) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<clu-request>)))
  "Returns string type for a service object of type '<clu-request>"
  "opencv_cam/cluRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'clu-request)))
  "Returns string type for a service object of type 'clu-request"
  "opencv_cam/cluRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<clu-request>)))
  "Returns md5sum for a message object of type '<clu-request>"
  "51b41483a7964797e1bc083c1c92baf4")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'clu-request)))
  "Returns md5sum for a message object of type 'clu-request"
  "51b41483a7964797e1bc083c1c92baf4")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<clu-request>)))
  "Returns full string definition for message of type '<clu-request>"
  (cl:format cl:nil "int32 my_number~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'clu-request)))
  "Returns full string definition for message of type 'clu-request"
  (cl:format cl:nil "int32 my_number~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <clu-request>))
  (cl:+ 0
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <clu-request>))
  "Converts a ROS message object to a list"
  (cl:list 'clu-request
    (cl:cons ':my_number (my_number msg))
))
;//! \htmlinclude clu-response.msg.html

(cl:defclass <clu-response> (roslisp-msg-protocol:ros-message)
  ((result
    :reader result
    :initarg :result
    :type cl:integer
    :initform 0))
)

(cl:defclass clu-response (<clu-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <clu-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'clu-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name opencv_cam-srv:<clu-response> is deprecated: use opencv_cam-srv:clu-response instead.")))

(cl:ensure-generic-function 'result-val :lambda-list '(m))
(cl:defmethod result-val ((m <clu-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader opencv_cam-srv:result-val is deprecated.  Use opencv_cam-srv:result instead.")
  (result m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <clu-response>) ostream)
  "Serializes a message object of type '<clu-response>"
  (cl:let* ((signed (cl:slot-value msg 'result)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <clu-response>) istream)
  "Deserializes a message object of type '<clu-response>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'result) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<clu-response>)))
  "Returns string type for a service object of type '<clu-response>"
  "opencv_cam/cluResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'clu-response)))
  "Returns string type for a service object of type 'clu-response"
  "opencv_cam/cluResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<clu-response>)))
  "Returns md5sum for a message object of type '<clu-response>"
  "51b41483a7964797e1bc083c1c92baf4")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'clu-response)))
  "Returns md5sum for a message object of type 'clu-response"
  "51b41483a7964797e1bc083c1c92baf4")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<clu-response>)))
  "Returns full string definition for message of type '<clu-response>"
  (cl:format cl:nil "int32 result~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'clu-response)))
  "Returns full string definition for message of type 'clu-response"
  (cl:format cl:nil "int32 result~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <clu-response>))
  (cl:+ 0
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <clu-response>))
  "Converts a ROS message object to a list"
  (cl:list 'clu-response
    (cl:cons ':result (result msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'clu)))
  'clu-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'clu)))
  'clu-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'clu)))
  "Returns string type for a service object of type '<clu>"
  "opencv_cam/clu")