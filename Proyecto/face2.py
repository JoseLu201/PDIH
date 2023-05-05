import cv2
import numpy as np
import tensorflow as tf


# Load the pre-trained face detection model
face_detector = cv2.CascadeClassifier('haarcascade_frontalface_alt.xml')

# Load the pre-trained face recognition model
face_recognizer = tf.keras.models.load_model('my_face_recognition_model.h5')

# Create a list of known faces and their names
known_faces = {
    'Jose': 'images/jose/jose_1.jpg'
}

# Load the known faces and their corresponding embeddings
known_embeddings = {}
for name, image_file in known_faces.items():
    image = cv2.imread(image_file)
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    faces = face_detector.detectMultiScale(gray, scaleFactor=1.1, minNeighbors=5)
    for (x, y, w, h) in faces:
        face = gray[y:y+h, x:x+w]
        embedding = face_recognizer.predict(np.expand_dims(face, axis=0))[0]
        known_embeddings[name] = embedding

# Initialize the video capture object
cap = cv2.VideoCapture(0)

while True:
    # Read a frame from the video stream
    ret, frame = cap.read()
    if not ret:
        break

    # Convert the frame to grayscale
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    # Detect faces in the grayscale frame
    faces = face_detector.detectMultiScale(gray, scaleFactor=1.1, minNeighbors=5)

    # Loop over each detected face
    for (x, y, w, h) in faces:
        face = gray[y:y+h, x:x+w]
        embedding = face_recognizer.predict(np.expand_dims(face, axis=0))[0]

        # Find the closest match among the known faces
        best_match_name = 'Unknown'
        best_match_distance = 1.0
        for name, known_embedding in known_embeddings.items():
            distance = np.linalg.norm(embedding - known_embedding)
            if distance < best_match_distance:
                best_match_name = name
                best_match_distance = distance

        # Draw a rectangle around the face and label it with the name of the best match
        cv2.rectangle(frame, (x, y), (x+w, y+h), (0, 255, 0), 2)
        cv2.putText(frame, best_match_name, (x, y-10), cv2.FONT_HERSHEY_SIMPLEX, 0.9, (0, 255, 0), 2)

    # Display the resulting frame
    cv2.imshow('Face Recognition', frame)
    if cv2.waitKey(1) == ord('q'):
        break

# Release the video capture object and close the window
cap.release()
cv2.destroyAllWindows()
