import cv2

face_detector = cv2.CascadeClassifier("haarcascade_frontalface_default.xml")
capture = cv2.VideoCapture(0)
while True:
    ret, img = capture.read()
    height, width, channels =img.shape
    #print("width:" , width, "height", height)

    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    faces = face_detector.detectMultiScale(gray)
    for(x,y,w,h) in faces:
        cv2.rectangle(img, (x,y), (x+w, y+h), (0,25,0), 1)
    
    cv2.imshow("My Image", img)
    if(cv2.waitKey(10)==27):
        break
    capture.release
    cv2.destroyAllWindows