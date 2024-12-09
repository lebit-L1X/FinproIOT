from flask import Flask, Response
import cv2
import os

# Get the directory of the current Python file
script_dir = os.path.dirname(os.path.abspath(__file__))

app = Flask(__name__)

# Open the webcam
camera = cv2.VideoCapture(0)  # 0 for default webcam


@app.route("/client", methods=["GET"])
def capture_image_client():
    success, frame = camera.read()
    if not success:
        return "Failed to capture image", 500
    else:
        # Save the image to local file as a.png in the script's directory
        image_path = os.path.join(script_dir, "a.png")
        cv2.imwrite(image_path, frame)
        return f"Image saved as {image_path}"


@app.route("/server", methods=["GET"])
def capture_image_server():
    success, frame = camera.read()
    if not success:
        return "Failed to capture image", 500
    else:
        # Save the image to local file as b.png in the script's directory
        image_path = os.path.join(script_dir, "b.png")
        cv2.imwrite(image_path, frame)
        return f"Image saved as {image_path}"


if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000)  # Access via http://<IP>:5000/capture
