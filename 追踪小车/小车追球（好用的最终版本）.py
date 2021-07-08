import sensor, image, time, math , json

from pid import PID

from pyb import Servo

from pyb import UART




pan_servo=Servo(1)

tilt_servo=Servo(2)

green_threshold  = (0, 58, -49, -19, 39, -17)

pan_pid = PID(p=0.13, i=0, imax=90) #脱机运行或者禁用图像传输，使用这个PID

tilt_pid = PID(p=0.08, i=0, imax=90) #脱机运行或者禁用图像传输，使用这个PID





sensor.reset() # Initialize the camera sensor.

sensor.set_pixformat(sensor.RGB565) # use RGB565.

sensor.set_framesize(sensor.QQVGA) # use QQVGA for speed.

sensor.skip_frames(10) # Let new settings take affect.

sensor.set_auto_whitebal(False) # turn this off.

clock = time.clock() # Tracks FPS.


uart = UART(3,115200)

def find_max(blobs):                           #定义函数选取元素面积最大
    max_size=0                                 #初值为0
    for blob in blobs:                         #for循环迭代
        if blob[2]*blob[3] > max_size:         #被测物体面积=blob[2]*blob[3]
            max_blob=blob
            max_size = blob[2]*blob[3]
    return max_blob                            #将最大元素值返回


while(True):
    data = []
    img = sensor.snapshot()
    blobs = img.find_blobs([green_threshold])
    if blobs:

            max_blob = find_max(blobs)

            pan_error = max_blob.cx()-img.width()/2

            tilt_error = max_blob.cy()-img.height()/2


            L = (max_blob[2]+max_blob[3])/2
            l=int(1000/L)



            img.draw_cross(int(max_blob[5]),int(max_blob[6]),color=(0,255,0))                                                 #色块中心坐标CX,CY

            print('cx0:'+str(max_blob[5]),'cy0:'+str(max_blob[6]))                                                 #将色块中心坐标输出

            img.draw_rectangle(max_blob.rect())

            img.draw_cross(max_blob.cx(), max_blob.cy())




            pan_output=pan_pid.get_pid(pan_error,1)/2

            tilt_output=tilt_pid.get_pid(tilt_error,1)


            pan_servo.angle(pan_servo.angle()-pan_output)

            tilt_servo.angle(tilt_servo.angle()-tilt_output)



            data = bytearray([0xb3,0xb3,max_blob[5],max_blob[6],l,max_blob[3],0x0d , 0x5b])
            uart.write(data)



    print(data)




