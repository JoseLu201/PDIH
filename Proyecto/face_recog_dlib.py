# pip install dlib
# pip install face_recognition
import cv2
import face_recognition as face


frame = cv2.imread("cara.png")

framergb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
locs = face.face_locations(framergb)

if locs is not None:
    for i in range(len(locs)):
        t,r,b,l = locs[i] # top, right, bottom ,left
        lands = face.face_landmarks(framergb[t:b, l:r]) # diccionario de facciones de la cara
        cv2.rectangle(frame, (l,t), (r,b), (255,0,0), 2)
        cv2.imshow("landma", frame)
        cv2.waitKey() == ord(' ')



# caras particulaes

micara = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
locs = face.face_locations(micara)
cod_micara = face.face_encodings(micara,locs,model='small')[0]

#ahora la que tengo la codificacion de mi cara, en la camara uso lo siguiente
#frame = camara
#framergb
print("abrimos cam\n")
cap = cv2.VideoCapture(0)
final = False
while not final:
    #Leemos el frame en formato BGR
    ret, framebgr = cap.read()
    if ret:
        #mini = cv2.resize(framergb, dsize=(300,300),fx=0.25, fy=0.25)
        mini = framebgr
        locs = face.face_locations(mini, model='hog') # esto o hog tmb es por defecto, cnn el mejor
        cods = face.face_encodings(mini, locs, model='small') #podemos cambiar a small para obtener mejor rendimeinto pero peor calidad
        if locs is not None:
            for i in range(len(locs)):
                if face.compare_faces(cod_micara, [cods[i]])[0]:
                    color = (0,255,0)
                else:
                    color = (0,0,255)
                t,r,b,l = locs[i] # top, right, bottom ,left
                dist = face.face_distance(cod_micara,[cods[i]])[0]
                #cv2.rectangle(framebgr, (l*4,t*4), (r*4,b*4), color, 2)
                cv2.rectangle(framebgr, (l,t), (r,b), color, 2)
        cv2.imshow("Video", framebgr)
        if cv2.waitKey(1) == ord(' '):
            final = True
    else:
        final = True


##########
# tambien podemos cargar modulos de dnn
#"face_detector_20180220"
#red = cv2.dnn.readNetFromTensorFlow("opencv_face_detector_uint8.pb")
#blob = cv2.dnn.blobFromImage(imagen, 1.0, (300,300), [104., 117., 123.,], False, )
#red.setInput(blob)
#detection = red.ford