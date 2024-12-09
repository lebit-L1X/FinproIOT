import requests

# Replace these with your Face++ API key and secret
API_KEY = "DOD9XcYeBPDRd5zgqciRX4AYBJfay250"
API_SECRET = "GOjT2ZkH9gA3XOIxnddGK6hWghT86ms0"

# Face++ Compare API URL
COMPARE_URL = "https://api-us.faceplusplus.com/facepp/v3/compare"

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

# Paths to the image files to compare
image_path1 = "C:\\Users\\Wendy\\Documents\\Code\\Python\\matigw\\c.jpg"
image_path2 = "C:\\Users\\Wendy\\Documents\\Code\\Python\\matigw\\b.png"

# Call the function
result = compare_faces(image_path1, image_path2)

# Process and print the result
if "confidence" in result:
    print(f"Confidence Score: {result['confidence']}")
    if result['confidence'] > 70:
        print("The faces are likely of the same person.")
    else:
        print("The faces are likely of different people.")
else:
    print("Error occurred or insufficient data to compare.")
    if "error_message" in result:
        print(f"Error: {result['error_message']}")
