
(cl:in-package :asdf)

(defsystem "opencv_cam-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "clu" :depends-on ("_package_clu"))
    (:file "_package_clu" :depends-on ("_package"))
  ))