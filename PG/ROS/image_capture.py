#!/usr/bin/env python3

import rospy
from sensor_msgs.msg import Image
import cv2
from cv_bridge import CvBridge

class ImageSubscriber:
    def __init__(self):
        rospy.init_node('image_subscriber', anonymous=True)
        self.bridge = CvBridge()
        self.image_sub = rospy.Subscriber('/camera/rgb/image_raw', Image, self.callback)
        self.image_count = 0
        self.capture_interval = rospy.Duration(10)  # Intervalo de captura em segundos

    def callback(self, data):
        # Converte a imagem ROS para OpenCV
        cv_image = self.bridge.imgmsg_to_cv2(data, desired_encoding="bgr8")

        # Captura e salva a imagem a cada intervalo definido
        if rospy.Time.now() - self.capture_interval > rospy.Time(self.image_count):
            cv2.imwrite("/home/jhonny-czk/catkin_ws/src/image_capture/images/image_{}.jpg".format(self.image_count), cv_image)
            rospy.loginfo("Imagem capturada e salva como image_{}.jpg".format(self.image_count))
            self.image_count += 1
            #self.last_capture_time = rospy.Time.now()  # Atualiza o tempo da última captura


if __name__ == '__main__':
    try:
        image_subscriber = ImageSubscriber()
        rospy.spin()
    except rospy.ROSInterruptException:
        pass
