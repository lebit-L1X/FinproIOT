from flask import Flask, request, jsonify, render_template, redirect, url_for, send_from_directory
import requests
import os
import cv2

# Replace these with your Face++ API key and secret
API_KEY = "DOD9XcYeBPDRd5zgqciRX4AYBJfay250"
API_SECRET = "GOjT2ZkH9gA3XOIxnddGK6hWghT86ms0"

# Face++ Compare API URL
COMPARE_URL = "https://api-us.faceplusplus.com/facepp/v3/compare"

# Get the directory of the current Python file
script_dir = os.path.dirname(os.path.abspath(__file__))
server_images_dir = os.path.join(script_dir, "server_images")
os.makedirs(server_images_dir, exist_ok=True)

app = Flask(__name__)

def compare_faces(image_path1, image_path2):
    """
    Compare two faces using Face++ API.
    """
    with open(image_path1, "rb") as image_file1, open(image_path2, "rb") as image_file2:
        files = {
            "image_file1": image_file1,
            "image_file2": image_file2,
        }
        data = {
            "api_key": API_KEY,
            "api_secret": API_SECRET,
        }
        response = requests.post(COMPARE_URL, data=data, files=files)
        return response.json()

@app.route("/")
def index():
    """
    Display the main page for adding/deleting server images.
    """
    images = os.listdir(server_images_dir)
    return render_template("index.html", images=images)

@app.route("/add_server_image", methods=["POST"])
def add_server_image():
    """
    Add a server image.
    """
    camera = cv2.VideoCapture(0)
    success, frame = camera.read()
    camera.release()
    if success:
        image_path = os.path.join(server_images_dir, f"server_{len(os.listdir(server_images_dir)) + 1}.png")
        cv2.imwrite(image_path, frame)
    return redirect(url_for("index"))

@app.route("/delete_server_image/<image_name>", methods=["POST"])
def delete_server_image(image_name):
    """
    Delete a server image.
    """
    image_path = os.path.join(server_images_dir, image_name)
    if os.path.exists(image_path):
        os.remove(image_path)
    return redirect(url_for("index"))

@app.route("/images/<image_name>")
def get_image(image_name):
    """
    Serve an image from the server_images directory.
    """
    return send_from_directory(server_images_dir, image_name)

@app.route("/compare", methods=["GET"])
def compare():
    """
    Capture a client image and compare it with all server images.
    Return the result with the highest confidence value.
    """
    # Step 1: Capture the client image
    camera = cv2.VideoCapture(0)
    success, frame = camera.read()
    camera.release()
    if not success:
        return jsonify({"error": "Failed to capture client image."}), 500

    client_image_path = os.path.join(script_dir, "client.png")
    cv2.imwrite(client_image_path, frame)

    # Step 2: Compare the client image with server images
    if not os.path.exists(client_image_path):
        return jsonify({"error": "Client image not found."}), 404

    highest_confidence = 0
    best_match = None

    for server_image_name in os.listdir(server_images_dir):
        server_image_path = os.path.join(server_images_dir, server_image_name)
        result = compare_faces(client_image_path, server_image_path)
        confidence = result.get("confidence", 0)

        if confidence > highest_confidence:
            highest_confidence = confidence
            best_match = {
                "server_image": server_image_name,
                "confidence": confidence,
                "valid": True,
                "message": "The faces are likely of the same person."
            }

    # Step 3: Return the best match
    if best_match:
        if best_match["confidence"] > 70:
            return jsonify(best_match)
        else:
            return jsonify({
                "server_image": server_image_name,
                "confidence": confidence,
                "valid": False,
                "message": "The faces are likely of different people."
            }), 404
            
    else:
        return jsonify({
                "server_image": server_image_name,
                "confidence": confidence,
                "valid": False,
                "message": "The faces are likely of different people."
            }), 404

@app.route("/rename_server_image/<old_name>", methods=["POST"])
def rename_server_image(old_name):
    """
    Rename a server image.
    """
    new_name = request.form.get("new_name")
    if not new_name:
        return jsonify({"error": "New name not provided."}), 400

    old_path = os.path.join(server_images_dir, old_name)
    new_path = os.path.join(server_images_dir, new_name)

    if not os.path.exists(old_path):
        return jsonify({"error": "Original file not found."}), 404

    if os.path.exists(new_path):
        return jsonify({"error": "A file with the new name already exists."}), 409

    os.rename(old_path, new_path)
    return redirect(url_for("index"))


if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
