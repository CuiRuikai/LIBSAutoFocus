import tensorflow as tf
hello = tf.constant('Hello, TensorFlow!')  #初始化一个TensorFlow的常量
sess = tf.Session()  #启动一个会话
print(sess.run(hello)) 