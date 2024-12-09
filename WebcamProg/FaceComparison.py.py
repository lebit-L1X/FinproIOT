from flask import Flask, request, jsonify
import requests
import os

# Replace these with your Face++ API key and secret
API_KEY = "DOD9XcYeBPDRd5zgqciRX4AYBJfay250"
API_SECRET = "GOjT2ZkH9gA3XOIxnddGK6hWghT86ms0"

# Face++ Compare API URL
COMPARE_URL = "https://api-us.faceplusplus.com/facepp/v3/compare"

app = Flask(__name__)

def compare_faces(image_path1, image_path2):
    """
    Compare two faces using Face++ API.
    """
    # Open the image files
    with open(image_path1, "rb") as image_file1, open(image_path2, "rb") as image_file2:
        files = {
            "image_file1": image_file1,
            "image_file2": image_file2,
        }
        data = {
            "api_key": API_KEY,
            "api_secret": API_SECRET,
        }
        # Make the POST request
        response = requests.post(COMPARE_URL, data=data, files=files)
        return response.json()

@app.route('/compare', methods=['GET'])
def compare():
    """
    Flask route to compare two images stored locally.
    The image paths are provided as URL parameters.
    """
    image_path1 = "C:\\Users\\Wendy\\Documents\\College\\Project\\IOT\\WebcamProg\\a.png"
    image_path2 = "C:\\Users\\Wendy\\Documents\\College\\Project\\IOT\\WebcamProg\\b.png"

    # Check if both image paths are provided
    if not image_path1 or not image_path2:
        return jsonify({"error": "Please provide both 'image1' and 'image2' parameters."}), 400

    # Check if the files exist in the specified paths
    if not os.path.exists(image_path1) or not os.path.exists(image_path2):
        return jsonify({"error": "One or both image files not found."}), 404

    # Call the compare_faces function
    result = compare_faces(image_path1, image_path2)

    # Process and return the result
    if "confidence" in result:
        confidence = result["confidence"]
        if confidence > 70:
            return jsonify({
                "valid": True,
                "confidence": confidence,
                "message": "The faces are likely of the same person."
            })
        else:
            return jsonify({
                "valid": False,
                "confidence": confidence,
                "message": "The faces are likely of different people."
            })
    else:
        error_message = result.get("error_message", "Unknown error")
        return jsonify({
            "error": "Error occurred during comparison.",
            "message": error_message
        }), 500

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
