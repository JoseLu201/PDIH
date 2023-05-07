import cv2
import numpy as np

#Instancia del clasificador de cascada con caras frontales
cascade = cv2.CascadeClassifier("haarcascade_frontalface_alt.xml")

cap = cv2.VideoCapture(0)
if cap.isOpened():
    hframe = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))
    wframe = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
    print("Tamaño del frame de la cámara: ", wframe, "x", hframe)

    final = False
    while not final:
        #Leemos el frame en formato BGR
        ret, framebgr = cap.read()
        frame_gris = cv2.cvtColor(framebgr, cv2.COLOR_BGR2GRAY)
        if ret:
            res = cascade.detectMultiScale(frame_gris)
            for x,y,w,h in res:
                cv2.rectangle(framebgr, (x,y), (x+w, y+h) ,(255,0,255),3)
            cv2.imshow("done", framebgr)
            if cv2.waitKey(1) == ord(' '):
                final = True
        else:
            final = True
            
else:
    print("No se pudo acceder a la cámara.")





