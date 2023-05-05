import cv2
import numpy as np
import os

#Instancia del clasificador de cascada con caras frontales
cascade = cv2.CascadeClassifier("haarcascade_frontalface_alt.xml")
cap = cv2.VideoCapture(0)

num_images = 0
nameID=str(input("Nombre de la cara de la persona: ")).lower()

path = 'images/jose'+ nameID

if os.path.exists(path):
    print("Ya existe ese nombre")
    nameID=str(input("Nombre de la cara de la persona: ")).lower()
    
if cap.isOpened():
    hframe = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))
    wframe = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
    print("Tamaño del frame de la cámara: ", wframe, "x", hframe)

    final = False
    #while not final :
    #    #Leemos el frame en formato BGR
    #    ret, framebgr = cap.read()
    #    frame_gris = cv2.cvtColor(framebgr, cv2.COLOR_BGR2GRAY)
    #    if ret:
    #        res = cascade.detectMultiScale(frame_gris)
    #        for x,y,w,h in res:
    #            num_images += 1
    #            name='./images/' + nameID + str(num_images) + '.jpg'
    #            cv2.imwrite(name, framebgr[y:y+h, x:x+w])
    #            print("guardando " + name)
    #            cv2.rectangle(framebgr, (x,y), (x+w, y+h) ,(255,0,255),3)
    #            
    #        cv2.imshow("done", framebgr)
    #        if cv2.waitKey(1) == ord(' ') or num_images == 50:
    #            final = True
    #    else:
    #        final = True
else:
    print("No se pudo acceder a la cámara.")


for filename in os.listdir('./images'):
    #print(filename)
    img = cv2.imread(os.path.join('./images', filename))
    img = cv2.resize(img, (300, 300))
    cv2.imwrite(os.path.join('training_images', filename), img)





